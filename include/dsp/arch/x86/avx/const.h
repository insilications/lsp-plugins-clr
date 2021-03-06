/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 05 окт. 2015 г.
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

#ifndef DSP_ARCH_X86_AVX_CONST_H_
#define DSP_ARCH_X86_AVX_CONST_H_

#ifndef DSP_ARCH_X86_AVX_IMPL
    #error "This header should not be included directly"
#endif /* DSP_ARCH_X86_AVX_IMPL */

// Parameters for SSE
#define AVX_MULTIPLE                8
#define AVX_ALIGN                   (AVX_MULTIPLE * sizeof(float))
#define SFENCE                      ARCH_X86_ASM ( __ASM_EMIT("sfence") )
#define VZEROUPPER                  ARCH_X86_ASM ( __ASM_EMIT("vzeroupper") )
#define VMOVNTPS                    "vmovaps"

#define AVX_SVEC8(name, value)      const float name[] __lsp_aligned64      = { value, value, value, value, value, value, value, value }
#define AVX_UVEC8(name, value)      const uint32_t name[] __lsp_aligned64   = { value, value, value, value, value, value, value, value }
#define AVX_UVEC(name, a, b, c, d, e ,f, g, h) \
                                    const uint32_t name[] __lsp_aligned64   = { uint32_t(a), uint32_t(b), uint32_t(c), uint32_t(d), uint32_t(e), uint32_t(f), uint32_t(f), uint32_t(h) }

namespace avx
{
    /* Logarithm approximation coefficients */
    AVX_SVEC8(L0, 7.0376836292E-2);
    AVX_SVEC8(L1, -1.1514610310E-1);
    AVX_SVEC8(L2, 1.1676998740E-1);
    AVX_SVEC8(L3, -1.2420140846E-1);
    AVX_SVEC8(L4, +1.4249322787E-1);
    AVX_SVEC8(L5, -1.6668057665E-1);
    AVX_SVEC8(L6, +2.0000714765E-1);
    AVX_SVEC8(L7, -2.4999993993E-1);
    AVX_SVEC8(L8, +3.3333331174E-1);
    AVX_SVEC8(L9, 0.5);
    AVX_SVEC8(LXE, -2.12194440e-4);

    /* Math constants */
    AVX_SVEC8(ZERO, 0.0f);
    AVX_SVEC8(ONE, 1.0f);
    AVX_SVEC8(PI,  M_PI);
    AVX_SVEC8(PI_2, M_PI_2);
    AVX_SVEC8(SQRT1_2, M_SQRT1_2);
    AVX_SVEC8(LN2, M_LN2);

    /* Sign Mask */
    AVX_UVEC8(X_SIGN,  0x7fffffff);
    AVX_UVEC8(R_SIGN,  0x80000000);
    AVX_SVEC8(X_HALF,  0.5f);
    AVX_UVEC8(X_MANT,  0x007fffff);
    AVX_UVEC8(X_MMASK, 0x0000007f);
    AVX_SVEC8(X_AMP_THRESH, AMPLIFICATION_THRESH);
    AVX_UVEC8(X_P_DENORM, 0x00800000);
    AVX_UVEC8(X_N_DENORM, 0x80800000);

    /* Positive and negative infinities */
    AVX_UVEC8(X_P_INF,  0x7f800000);
    AVX_UVEC8(X_N_INF,  0xff800000);
    AVX_UVEC8(X_P_INFM1,0x7f7fffff);
    AVX_UVEC8(X_N_INFM1,0xff7fffff);
    AVX_UVEC8(X_ZERO_M1,0xffffffff);

    /* Saturation replacement */
    AVX_SVEC8(SX_P_INF, FLOAT_SAT_P_INF);
    AVX_SVEC8(SX_N_INF, FLOAT_SAT_N_INF);
    AVX_SVEC8(SX_P_NAN, FLOAT_SAT_P_NAN);
    AVX_SVEC8(SX_N_NAN, FLOAT_SAT_N_NAN);

    /* Miscellaneous vectors */
    AVX_UVEC(X_MASK0001, -1, 0, 0, 0, 0, 0, 0, 0);
}

#endif /* DSP_ARCH_X86_AVX_CONST_H_ */
