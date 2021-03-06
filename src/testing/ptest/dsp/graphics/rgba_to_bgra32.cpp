/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 18 нояб. 2018 г.
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
#include <test/ptest.h>
#include <core/sugar.h>

#define MIN_RANK 6
#define MAX_RANK 14

namespace native
{
    void rgba_to_bgra32(void *dst, const float *src, size_t count);
}

IF_ARCH_X86(
    namespace sse2
    {
        void rgba_to_bgra32(void *dst, const float *src, size_t count);
    }
)

IF_ARCH_ARM(
    namespace neon_d32
    {
        void rgba_to_bgra32(void *dst, const float *src, size_t count);
    }
)

typedef void (* rgba_to_bgra32_t)(void *dst, const float *src, size_t count);

//-----------------------------------------------------------------------------
// Performance test for logarithmic axis calculation
PTEST_BEGIN("dsp.graphics", rgba_to_bgra32, 5, 5000)

    void call(const char *label, void *dst, const float *src, size_t count, rgba_to_bgra32_t func)
    {
        if (!PTEST_SUPPORTED(func))
            return;

        char buf[80];
        sprintf(buf, "%s x %d", label, int(count));
        printf("Testing %s pixels...\n", buf);

        PTEST_LOOP(buf,
            func(dst, src, count);
        );
    }

    PTEST_MAIN
    {
        size_t buf_size     = 1 << MAX_RANK;
        uint8_t *data       = NULL;

        uint8_t *dst        = alloc_aligned<uint8_t>(data, buf_size * sizeof(float) * 4 + buf_size * sizeof(uint32_t), 64);
        float *src          = reinterpret_cast<float *>(&dst[buf_size * sizeof(uint32_t)]);

        for (size_t i=0; i<buf_size*4; ++i)
             src[i]             = float(rand()) / (RAND_MAX - 1);

        for (size_t i=MIN_RANK; i <= MAX_RANK; ++i)
        {
            size_t count = 1 << i;

            call("native::rgba_to_bgra32", dst, src, count, native::rgba_to_bgra32);
            IF_ARCH_X86(call("sse2::rgba_to_bgra32", dst, src, count, sse2::rgba_to_bgra32));
            IF_ARCH_ARM(call("neon_d32::rgba_to_bgra32", dst, src, count, neon_d32::rgba_to_bgra32));

            PTEST_SEPARATOR;
        }

        free_aligned(data);
    }
PTEST_END


