/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 16 авг. 2018 г.
 *
 * lsp-plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins. If not, see <https://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <test/ptest.h>

namespace test
{
    PerformanceTest *PerformanceTest::__root = NULL;

    PerformanceTest::PerformanceTest(const char *group, const char *name, float time, size_t iterations): Test(group, name)
    {
        __test_time         = time;
        __test_iterations   = iterations;

        // Self-register
        __next              = __root;
        __root              = this;
    }

    PerformanceTest::~PerformanceTest()
    {
        free_stats();
    }

    void PerformanceTest::destroy_stats(stats_t *stats)
    {
        if (stats->key != NULL)
            free(stats->key);
        if (stats->time != NULL)
            free(stats->time);
        if (stats->n_time != NULL)
            free(stats->n_time);
        if (stats->iterations != NULL)
            free(stats->iterations);
        if (stats->n_iterations != NULL)
            free(stats->n_iterations);
        if (stats->performance != NULL)
            free(stats->performance);
        if (stats->time_cost != NULL)
            free(stats->time_cost);
        if (stats->rel != NULL)
            free(stats->rel);
    }

    void PerformanceTest::estimate(size_t *len, const char *text)
    {
        size_t slen = (text != NULL) ? strlen(text) : 0;
        if (slen > (*len))
            *len = slen;
    }

    void PerformanceTest::gather_stats(const char *key, double time, wsize_t iterations)
    {
        size_t count    = __test_stats.size();
        stats_t *stats  = __test_stats.add();
        if (stats == NULL)
            return;

        stats->time         = NULL;
        stats->n_time       = NULL;
        stats->iterations   = NULL;
        stats->n_iterations = NULL;
        stats->performance  = NULL;
        stats->time_cost    = NULL;
        stats->rel          = NULL;

        if (key == NULL)
        {
            stats->key          = NULL;
            stats->cost         = iterations + 1;
            double cost_max     = 0.0f;
            size_t first        = -1;

            // Find first non-gathered entry
            for (size_t i=0; i<count; ++i)
            {
                stats = __test_stats.at(i);
                if ((stats->rel  == NULL) && (stats->key != NULL))
                {
                    first = i;
                    break;
                }
            }

            // Find maximum
            for (size_t i=first; i<count; ++i)
            {
                stats = __test_stats.at(i);
                if (cost_max < stats->cost)
                    cost_max = stats->cost;
            }

            // Fill performance column
            for (size_t i=first; i<count; ++i)
            {
                stats = __test_stats.at(i);
                int n = asprintf(&stats->rel, "%.2f", 100.0 * (cost_max / stats->cost));
                if (n < 0)
                    return;
            }

            return;
        }

        stats->key      = strdup(key);
        stats->cost     = time / iterations;
        int n = asprintf(&stats->time, "%.2f", time);
        if (n >= 0)
            n = asprintf(&stats->n_time, "%.2f", __test_time);
        if (n >= 0)
            n = asprintf(&stats->iterations, "%lld", (long long)(iterations));
        if (n >= 0)
            n = asprintf(&stats->n_iterations, "%lld", (long long)((iterations * __test_time) / time));
        if (n >= 0)
            n = asprintf(&stats->performance, "%.2f", (iterations / time));
        if (n >= 0)
            n = asprintf(&stats->time_cost, "%.4f", (1000000.0 * time) / iterations);

        if ((n < 0) ||
            (stats->key == NULL) ||
            (stats->time == NULL) ||
            (stats->n_time == NULL) ||
            (stats->iterations == NULL) ||
            (stats->n_iterations == NULL) ||
            (stats->performance == NULL) ||
            (stats->time_cost == NULL))
        {
            destroy_stats(stats);
            __test_stats.remove(stats);
        }
    }

    /*
     Table drawing symbols:
        ┌ ─ ┬ ─ ┐

        │   │   │

        ├ ─ ┼ ─ ┤

        │   │   │

        └ ─ ┴ ─ ┘
     */

    void PerformanceTest::out_text(FILE *out, size_t length, const char *text, int align, const char *padding, const char *tail)
    {
        size_t tlen     = (text != NULL) ? strlen(text) : 0;
        length         -= tlen;
        if (align >= 0)
        {
            size_t pad = (align == 0) ? ((length + 1) >> 1) : length;
            length -= pad;
            while (pad--)
                fputs(padding, out);
        }
        if (text != NULL)
            fputs(text, out);

        while (length--)
            fputs(padding, out);
        if (tail != NULL)
            fputs(tail, out);
    }

    void PerformanceTest::dump_stats(FILE *out) const
    {
        size_t key          = strlen("Case");
        size_t time         = strlen("Time[s]");
        size_t n_time       = strlen("Samp[s]");
        size_t iterations   = strlen("Iter");
        size_t n_iterations = strlen("Est");
        size_t performance  = strlen("Perf[i/s]");
        size_t time_cost    = strlen("Cost[us/i]");
        size_t rel          = strlen("Rel[%]");

        // Estimate size of all columns
        for (size_t i=0, n=__test_stats.size(); i < n; ++i)
        {
            stats_t *stats = __test_stats.at(i);

            estimate(&key, stats->key);
            estimate(&time, stats->time);
            estimate(&n_time, stats->n_time);
            estimate(&iterations, stats->iterations);
            estimate(&n_iterations, stats->n_iterations);
            estimate(&performance, stats->performance);
            estimate(&time_cost, stats->time_cost);
            estimate(&rel, stats->rel);
        }

        // Output table header
        fputs("┌", out);
        out_text(out, key, "Case", -1, "─", "┬");
        out_text(out, time, "Time[s]", 1, "─", "┬");
        out_text(out, iterations, "Iter", 1, "─", "┬");
        out_text(out, n_time, "Samp[s]", 1, "─", "┬");
        out_text(out, n_iterations, "Est", 1, "─", "┬");
        out_text(out, performance, "Perf[i/s]", 1, "─", "┬");
        out_text(out, time_cost, "Cost[us/i]", 1, "─", "┬");
        out_text(out, rel, "Rel[%]", 1, "─", "┐\n");

        int separator = 0;

        // Output table data
        for (size_t i=0, n=__test_stats.size(); i < n; ++i)
        {
            stats_t *stats = __test_stats.at(i);
            if (stats->key != NULL)
            {
                if (separator == 1)
                {
                    fputs("├", out);
                    out_text(out, key, NULL, -1, "─", "┼");
                    out_text(out, time, NULL, 1, "─", "┼");
                    out_text(out, iterations, NULL, 1, "─", "┼");
                    out_text(out, n_time, NULL, 1, "─", "┼");
                    out_text(out, n_iterations, NULL, 1, "─", "┼");
                    out_text(out, performance, NULL, 1, "─", "┼");
                    out_text(out, time_cost, NULL, 1, "─", "┼");
                    out_text(out, rel, NULL, 1, "─", "┤\n");
                }
                else if (separator == 2)
                {
                    fputs("╞", out);
                    out_text(out, key, NULL, -1, "═", "╪");
                    out_text(out, time, NULL, 1, "═", "╪");
                    out_text(out, iterations, NULL, 1, "═", "╪");
                    out_text(out, n_time, NULL, 1, "═", "╪");
                    out_text(out, n_iterations, NULL, 1, "═", "╪");
                    out_text(out, performance, NULL, 1, "═", "╪");
                    out_text(out, time_cost, NULL, 1, "═", "╪");
                    out_text(out, rel, NULL, 1, "═", "╡\n");
                }
                separator = 0;

                fputs("│", out);
                out_text(out, key, stats->key, -1, " ", "│");
                out_text(out, time, stats->time, 1, " ", "│");
                out_text(out, iterations, stats->iterations, 1, " ", "│");
                out_text(out, n_time, stats->n_time, 1, " ", "│");
                out_text(out, n_iterations, stats->n_iterations, 1, " ", "│");
                out_text(out, performance, stats->performance, 1, " ", "│");
                out_text(out, time_cost, stats->time_cost, 1, " ", "│");
                out_text(out, rel, stats->rel, 1, " ", "│\n");
            }
            else
                separator = stats->cost;
        }

        // Output table footer
        fputs("└", out);
        out_text(out, key, NULL, -1, "─", "┴");
        out_text(out, time, NULL, 1, "─", "┴");
        out_text(out, iterations, NULL, 1, "─", "┴");
        out_text(out, n_time, NULL, 1, "─", "┴");
        out_text(out, n_iterations, NULL, 1, "─", "┴");
        out_text(out, performance, NULL, 1, "─", "┴");
        out_text(out, time_cost, NULL, 1, "─", "┴");
        out_text(out, rel, NULL, 1, "─", "┘\n");
    }

    void PerformanceTest::free_stats()
    {
        for (size_t i=0, n=__test_stats.size(); i < n; ++i)
            destroy_stats(__test_stats.at(i));
        __test_stats.flush();
    }

    PerformanceTest *ptest_init()
    {
        return PerformanceTest::__root;
    }

    int PerformanceTest::printf(const char *fmt, ...)
    {
        va_list vl;
        va_start(vl, fmt);
        int res = vprintf(fmt, vl);
        va_end(vl);
        fflush(stdout);
        return res;
    }}


