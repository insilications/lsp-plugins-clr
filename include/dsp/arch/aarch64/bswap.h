/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 18 мар. 2019 г.
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

#ifndef DSP_ARCH_AARCH64_BSWAP_H_
#define DSP_ARCH_AARCH64_BSWAP_H_

inline uint16_t __lsp_forced_inline    byte_swap(uint16_t v)
{
    ARCH_AARCH64_ASM (
        __ASM_EMIT("rev16   %[v], %[v]")
        : [v] "+r"(v)
        : :
    );
    return v;
}

inline uint32_t __lsp_forced_inline    byte_swap(uint32_t v)
{
    ARCH_AARCH64_ASM (
        __ASM_EMIT("rev32   %[v], %[v]")
        : [v] "+r"(v)
        : :
    );
    return v;
}

inline uint64_t __lsp_forced_inline    byte_swap(uint64_t v)
{
    ARCH_AARCH64_ASM (
        __ASM_EMIT("rev    %[v], %[v]")
        : [v] "+r"(v)
        : :
    );
    return v;
}

inline float __lsp_forced_inline    byte_swap(float v)
{
    ARCH_AARCH64_ASM (
        __ASM_EMIT("rev32   %[v], %[v]")
        : [v] "+r"(v)
        : :
    );
    return v;
}

inline double __lsp_forced_inline    byte_swap(double v)
{
    ARCH_AARCH64_ASM (
        __ASM_EMIT("rev     %[v], %[v]")
        : [v] "+r"(v)
        : :
    );
    return v;
}

inline void __lsp_forced_inline    byte_swap(uint16_t *v, size_t n)
{
    uint64_t tmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("subs        %[n], %[n], #4")
        __ASM_EMIT("b.lo        2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[tmp], [%[v]]")
        __ASM_EMIT("rev16       %[tmp], %[tmp]")
        __ASM_EMIT("str         %[tmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #4")
        __ASM_EMIT("b.ge        1b")

        __ASM_EMIT("2:")
        __ASM_EMIT("adds        %[n], %[n], #3")
        __ASM_EMIT("b.lt        4f")

        __ASM_EMIT("3:")
        __ASM_EMIT("ldrh        %w[tmp], [%[v]]")
        __ASM_EMIT("rev16       %w[tmp], %w[tmp]")
        __ASM_EMIT("strh        %w[tmp], [%[v]], #2")
        __ASM_EMIT("subs        %[n], %[n], #1")
        __ASM_EMIT("b.ge        3b")

        __ASM_EMIT("4:")
        : [v] "+r"(v), [n] "+r" (n), [tmp] "=&r"(tmp)
        : : "cc", "memory"
    );
}

inline void __lsp_forced_inline    byte_swap(int16_t *v, size_t n)
{
    uint64_t tmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("subs        %[n], %[n], #4")
        __ASM_EMIT("b.lo        2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[tmp], [%[v]]")
        __ASM_EMIT("rev16       %[tmp], %[tmp]")
        __ASM_EMIT("str         %[tmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #4")
        __ASM_EMIT("b.ge        1b")

        __ASM_EMIT("2:")
        __ASM_EMIT("adds        %[n], %[n], #3")
        __ASM_EMIT("b.lt        4f")

        __ASM_EMIT("3:")
        __ASM_EMIT("ldrh        %w[tmp], [%[v]]")
        __ASM_EMIT("rev16       %w[tmp], %w[tmp]")
        __ASM_EMIT("strh        %w[tmp], [%[v]], #2")
        __ASM_EMIT("subs        %[n], %[n], #1")
        __ASM_EMIT("b.ge        3b")

        __ASM_EMIT("4:")
        : [v] "+r"(v), [n] "+r" (n), [tmp] "=&r"(tmp)
        : : "cc", "memory"
    );
}

inline void __lsp_forced_inline    byte_swap(uint32_t *v, size_t n)
{
    uint64_t tmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("subs        %[n], %[n], #2")
        __ASM_EMIT("b.lo        2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[tmp], [%[v]]")
        __ASM_EMIT("rev32       %[tmp], %[tmp]")
        __ASM_EMIT("str         %[tmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #2")
        __ASM_EMIT("b.ge        1b")

        __ASM_EMIT("2:")
        __ASM_EMIT("adds        %[n], %[n], #1")
        __ASM_EMIT("b.lt        4f")
        __ASM_EMIT("ldr         %w[tmp], [%[v]]")
        __ASM_EMIT("rev32       %[tmp], %[tmp]")
        __ASM_EMIT("str         %w[tmp], [%[v]], #2")

        __ASM_EMIT("4:")
        : [v] "+r"(v), [n] "+r" (n), [tmp] "=&r"(tmp)
        : : "cc", "memory"
    );
}

inline void __lsp_forced_inline    byte_swap(int32_t *v, size_t n)
{
    uint64_t tmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("subs        %[n], %[n], #2")
        __ASM_EMIT("b.lo        2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[tmp], [%[v]]")
        __ASM_EMIT("rev32       %[tmp], %[tmp]")
        __ASM_EMIT("str         %[tmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #2")
        __ASM_EMIT("b.ge        1b")

        __ASM_EMIT("2:")
        __ASM_EMIT("adds        %[n], %[n], #1")
        __ASM_EMIT("b.lt        4f")
        __ASM_EMIT("ldr         %w[tmp], [%[v]]")
        __ASM_EMIT("rev32       %[tmp], %[tmp]")
        __ASM_EMIT("str         %w[tmp], [%[v]], #2")

        __ASM_EMIT("4:")
        : [v] "+r"(v), [n] "+r" (n), [tmp] "=&r"(tmp)
        : : "cc", "memory"
    );
}

inline void __lsp_forced_inline    byte_swap(float *v, size_t n)
{
    uint64_t tmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("subs        %[n], %[n], #2")
        __ASM_EMIT("b.lo        2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[tmp], [%[v]]")
        __ASM_EMIT("rev32       %[tmp], %[tmp]")
        __ASM_EMIT("str         %[tmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #2")
        __ASM_EMIT("b.ge        1b")

        __ASM_EMIT("2:")
        __ASM_EMIT("adds        %[n], %[n], #1")
        __ASM_EMIT("b.lt        4f")
        __ASM_EMIT("ldr         %w[tmp], [%[v]]")
        __ASM_EMIT("rev32       %[tmp], %[tmp]")
        __ASM_EMIT("str         %w[tmp], [%[v]], #2")

        __ASM_EMIT("4:")
        : [v] "+r"(v), [n] "+r" (n), [tmp] "=&r"(tmp)
        : : "cc", "memory"
    );
}

inline void __lsp_forced_inline    byte_swap(uint64_t *v, size_t n)
{
    uint64_t xtmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("cbz         %[n], 2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[xtmp], [%[v]]")
        __ASM_EMIT("rev         %[xtmp], %[xtmp]")
        __ASM_EMIT("str         %[xtmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #1")
        __ASM_EMIT("b.ne        1b")

        __ASM_EMIT("2:")
        : [v] "+r"(v), [n] "+r" (n), [xtmp] "=&r"(xtmp)
        : : "cc", "memory"
    );
}

inline void __lsp_forced_inline    byte_swap(int64_t *v, size_t n)
{
    uint64_t xtmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("cbz         %[n], 2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[xtmp], [%[v]]")
        __ASM_EMIT("rev         %[xtmp], %[xtmp]")
        __ASM_EMIT("str         %[xtmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #1")
        __ASM_EMIT("b.ne        1b")

        __ASM_EMIT("2:")
        : [v] "+r"(v), [n] "+r" (n), [xtmp] "=&r"(xtmp)
        : : "cc", "memory"
    );
}

inline void __lsp_forced_inline    byte_swap(double *v, size_t n)
{
    uint64_t xtmp;

    ARCH_AARCH64_ASM (
        __ASM_EMIT("cbz         %[n], 2f")

        __ASM_EMIT("1:")
        __ASM_EMIT("ldr         %[xtmp], [%[v]]")
        __ASM_EMIT("rev         %[xtmp], %[xtmp]")
        __ASM_EMIT("str         %[xtmp], [%[v]], #8")
        __ASM_EMIT("subs        %[n], %[n], #1")
        __ASM_EMIT("b.ne        1b")

        __ASM_EMIT("2:")
        : [v] "+r"(v), [n] "+r" (n), [xtmp] "=&r"(xtmp)
        : : "cc", "memory"
    );
}

#endif /* DSP_ARCH_AARCH64_BSWAP_H_ */
