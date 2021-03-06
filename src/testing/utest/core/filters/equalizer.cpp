/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 26 дек. 2020 г.
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

#include <test/utest.h>
#include <test/helpers.h>
#include <core/filters/Equalizer.h>
#include <test/FloatBuffer.h>
#include <core/io/Path.h>
#include <dsp/dsp.h>

using namespace lsp;

#define FFT_RANK        12
#define BUF_SIZE        (1 << (FFT_RANK + 2))

UTEST_BEGIN("core.filters", equalizer)

    void test_latency(const char *label, equalizer_mode_t mode)
    {
        Equalizer eq;
        filter_params_t fp;

        printf("Testing equalizer latency report for %s mode\n", label);

        // Configure the equalizer
        eq.init(1, FFT_RANK);
        eq.set_mode(mode);
        eq.set_sample_rate(48000);

        fp.nType    = FLT_BT_LRX_HIPASS;
        fp.fFreq    = 100.0f;
        fp.fFreq2   = 100.0f;
        fp.fGain    = 1.0f;
        fp.nSlope   = 2;
        fp.fQuality = 0.0f;
        eq.set_params(0, &fp);

        // Obtain it's impulse response
        FloatBuffer src(BUF_SIZE);
        FloatBuffer dst(BUF_SIZE);

        src.fill_zero();
        src[0] = 1.0f;
        dst.fill_zero();
        eq.process(dst, src, BUF_SIZE);
        UTEST_ASSERT(!src.corrupted());
        UTEST_ASSERT(!dst.corrupted());

        // Save result
        io::Path path;
        UTEST_ASSERT(path.fmt("tmp/%s-%s.csv", full_name(), label) > 0);
        printf("  output results: %s\n", path.as_utf8());
        FILE *out = fopen(path.as_native(), "w");
        UTEST_ASSERT(out != NULL);
        fprintf(out, "samples;in;out\n");
        for (size_t i=0; i<BUF_SIZE; ++i)
            fprintf(out, "%d;%.g;%.g\n", int(i), src[i], dst[i]);
        fclose(out);

        // Check that latency matches
        size_t latency  = eq.get_latency();
        size_t index    = dsp::abs_max_index(dst, BUF_SIZE);

        printf("  latency = %d, maximum = %d\n", int(latency), int(index));

        UTEST_ASSERT(latency == index);

        // Destroy equalizer
        eq.destroy();
    }

    UTEST_MAIN
    {
        test_latency("FIR", EQM_FIR);
        test_latency("FFT", EQM_FFT);
        test_latency("SPM", EQM_SPM);
    }

UTEST_END




