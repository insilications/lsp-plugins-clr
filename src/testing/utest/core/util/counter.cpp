/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 27 нояб. 2018 г.
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

#include <dsp/dsp.h>
#include <test/utest.h>
#include <test/helpers.h>
#include <core/util/Counter.h>

#define SRATE       22000
#define FREQ        100.0f
#define INITIAL     200

using namespace lsp;

UTEST_BEGIN("core.util", counter)

    UTEST_MAIN
    {
        Counter c;

        size_t init = SRATE / FREQ;
        float freq  = float(SRATE) / float(INITIAL);

        // Set sample rate and frequency
        c.set_sample_rate(SRATE, true);
        c.set_frequency(FREQ, false);

        // Check proper state
        UTEST_ASSERT(c.get_sample_rate() == SRATE);
        UTEST_ASSERT(c.pending() == SRATE);
        UTEST_ASSERT(c.get_frequency() == FREQ);
        UTEST_ASSERT(c.get_initial_value() == init);
        UTEST_ASSERT(!c.fired());

        // Perform submit of number of pending samples and check state
        c.submit(SRATE);
        UTEST_ASSERT(c.fired());
        UTEST_ASSERT(c.pending() == init);
        UTEST_ASSERT(c.commit());
        UTEST_ASSERT(!c.fired());

        // Perform submit more than number of pending samples and check state
        c.submit(init*2 + (init >> 1));
        UTEST_ASSERT(c.fired());
        UTEST_ASSERT(c.pending() == (init - (init >> 1)));
        UTEST_ASSERT(c.commit());
        UTEST_ASSERT(!c.fired());

        // Update initial value
        c.set_initial_value(INITIAL, true);
        UTEST_ASSERT(c.pending() == INITIAL);
        UTEST_ASSERT(float_equals_relative(freq, c.get_frequency(), 1e-4f));
        UTEST_ASSERT(c.get_initial_value() == INITIAL);
        UTEST_ASSERT(!c.fired());

        // Perform submit of number of pending samples and check state
        c.submit(INITIAL >> 1);
        UTEST_ASSERT(!c.fired());
        UTEST_ASSERT(c.pending() == (INITIAL - (INITIAL >> 1)));
        c.submit(INITIAL);
        UTEST_ASSERT(c.fired());
        UTEST_ASSERT(c.pending() == (INITIAL - (INITIAL >> 1)));
        UTEST_ASSERT(c.commit());
        UTEST_ASSERT(!c.fired());

        // Lower sample rate
        c.set_sample_rate(SRATE >> 1, true);
        UTEST_ASSERT(c.get_sample_rate() == (SRATE >> 1));
        UTEST_ASSERT(c.pending() == INITIAL);
        UTEST_ASSERT(float_equals_relative(freq*0.5f, c.get_frequency(), 1e-4f));
        UTEST_ASSERT(c.get_initial_value() == INITIAL);
        UTEST_ASSERT(!c.fired());

        // Raise sample rate
        c.preserve_frequency();
        c.set_sample_rate(SRATE, true);
        UTEST_ASSERT(c.get_sample_rate() == SRATE);
        UTEST_ASSERT(c.pending() == (INITIAL << 1));
        UTEST_ASSERT(float_equals_relative(freq*0.5f, c.get_frequency(), 1e-4f));
        UTEST_ASSERT(c.get_initial_value() == (INITIAL << 1));
        UTEST_ASSERT(!c.fired());
   }

UTEST_END;
