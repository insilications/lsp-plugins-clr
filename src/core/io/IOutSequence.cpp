/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 14 июн. 2018 г.
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

#include <core/io/IOutSequence.h>

namespace lsp
{
    namespace io
    {
        IOutSequence::IOutSequence()
        {
            nErrorCode      = STATUS_OK;
        }

        IOutSequence::~IOutSequence()
        {
        }

        status_t IOutSequence::write(lsp_wchar_t c)
        {
            return set_error(STATUS_NOT_IMPLEMENTED);
        }

        status_t IOutSequence::write(const lsp_wchar_t *c, size_t count)
        {
            return set_error(STATUS_NOT_IMPLEMENTED);
        }

        status_t IOutSequence::write_ascii(const char *s)
        {
            if (s == NULL)
                return set_error(STATUS_BAD_ARGUMENTS);
            return write_ascii(s, ::strlen(s));
        }

        status_t IOutSequence::write_ascii(const char *s, size_t count)
        {
            return set_error(STATUS_NOT_IMPLEMENTED);
        }

        status_t IOutSequence::write(const LSPString *s)
        {
            if (s == NULL)
                return set_error(STATUS_BAD_ARGUMENTS);
            return write(s->characters(), s->length());
        }

        status_t IOutSequence::write(const LSPString *s, ssize_t first)
        {
            if (s == NULL)
                return set_error(STATUS_BAD_ARGUMENTS);

            ssize_t len = s->length();
            if (first > len)
                return set_error(STATUS_OVERFLOW);
    
            const lsp_wchar_t *v = s->characters();
            return write(&v[first], len - first);
        }
    
        status_t IOutSequence::write(const LSPString *s, ssize_t first, ssize_t last)
        {
            if (s == NULL)
                return set_error(STATUS_BAD_ARGUMENTS);

            ssize_t len = s->length();
            if (first > len)
                return set_error(STATUS_OVERFLOW);
            else if (last > len)
                return set_error(STATUS_OVERFLOW);

            len = last - first;
            if (len < 0)
                return set_error(STATUS_OVERFLOW);
            else if (len == 0)
                return set_error(STATUS_OK);

            const lsp_wchar_t *v = s->characters();
            return write(&v[first], len);
        }

        status_t IOutSequence::writeln(lsp_wchar_t c)
        {
            lsp_wchar_t w[2];
            w[0] = c;
            w[1] = '\n';
            return write(w, 2);
        }

        status_t IOutSequence::writeln(const lsp_wchar_t *c, size_t count)
        {
            LSP_STATUS_ASSERT(write(c, count));
            return write('\n');
        }

        status_t IOutSequence::writeln_ascii(const char *s)
        {
            LSP_STATUS_ASSERT(write_ascii(s));
            return write('\n');
        }

        status_t IOutSequence::writeln(const LSPString *s)
        {
            LSP_STATUS_ASSERT(write(s));
            return write('\n');
        }

        status_t IOutSequence::writeln(const LSPString *s, ssize_t first)
        {
            LSP_STATUS_ASSERT(write(s, first));
            return write('\n');
        }

        status_t IOutSequence::writeln(const LSPString *s, ssize_t first, ssize_t last)
        {
            LSP_STATUS_ASSERT(write(s, first, last));
            return write('\n');
        }

        status_t IOutSequence::IOutSequence::flush()
        {
            return set_error(STATUS_NOT_IMPLEMENTED);
        }

        status_t IOutSequence::close()
        {
            return set_error(STATUS_OK);
        }
    }

} /* namespace lsp */
