/*
 * LSPCChunkAccessor.cpp
 *
 *  Created on: 14 янв. 2018 г.
 *      Author: sadko
 */

#include <errno.h>
#include <malloc.h>
#include <unistd.h>
#include <core/files/lspc/LSPCChunkAccessor.h>

namespace lsp
{
    status_t LSPCResource::acquire()
    {
        if (fd < 0)
            return STATUS_CLOSED;
        ++refs;
        return STATUS_OK;
    }
    
    status_t LSPCResource::release()
    {
        if (fd < 0)
            return STATUS_CLOSED;
        if ((--refs) <= 0)
        {
            close(fd);
            fd      = -1;
        }

        return STATUS_OK;
    }

    status_t LSPCResource::allocate(uint32_t *id)
    {
        uint32_t cid = chunk_id + 1;
        if (cid == 0)
            return STATUS_OVERFLOW;
        *id = chunk_id = cid;
        return STATUS_OK;
    }

    status_t LSPCResource::write(const void *buf, size_t count)
    {
        if (fd < 0)
            return STATUS_CLOSED;

        // Write data at the end of file
        const uint8_t *bptr = static_cast<const uint8_t *>(buf);
        while (count > 0)
        {
            errno       = 0;
            size_t written  = pwrite(fd, bptr, count, length);
            if ((written < count) && (errno != 0))
                return STATUS_IO_ERROR;

            bptr       += written;
            length     += written;
            count      -= written;
        }

        return STATUS_OK;
    }

    ssize_t LSPCResource::read(wsize_t pos, void *buf, size_t count)
    {
        if (fd < 0)
            return STATUS_CLOSED;

        // Write data at the end of file
        uint8_t *bptr   = static_cast<uint8_t *>(buf);
        ssize_t total   = 0;
        while (count > 0)
        {
            errno       = 0;
            size_t read = pread(fd, bptr, count, pos);
            if (read < count)
                return total;

            bptr       += read;
            count      -= read;
            total      += read;
        }

        return total;
    }

    LSPCChunkAccessor::LSPCChunkAccessor(LSPCResource *fd, uint32_t magic)
    {
        pFile           = fd;
        set_error((pFile != NULL) ? pFile->acquire() : STATUS_BAD_STATE);
        nMagic          = magic;
        nBufSize        = (pFile != NULL) ? pFile->bufsize : 0;

        if (nBufSize > 0)
        {
            // Adjust buffer size
            if (nBufSize < MIN_BUF_SIZE)
                nBufSize        = MIN_BUF_SIZE;

            // Allocate buffer
            pBuffer         = static_cast<uint8_t *>(malloc(nBufSize));
            if (pBuffer == NULL)
            {
                set_error(STATUS_NO_MEM);
                return;
            }
            nBufPos         = 0;
        }

        nUID            = 0;

        set_error(STATUS_OK);
    }
    
    LSPCChunkAccessor::~LSPCChunkAccessor()
    {
        do_close();
    }

    status_t LSPCChunkAccessor::do_close()
    {
        if (pBuffer != NULL)
        {
            free(pBuffer);
            pBuffer = NULL;
        }
        if (pFile == NULL)
            return set_error(STATUS_CLOSED);
        set_error(pFile->release());
        pFile = NULL;
        return last_error();
    }

    status_t LSPCChunkAccessor::close()
    {
        return do_close();
    }

} /* namespace lsp */
