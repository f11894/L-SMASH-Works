/*****************************************************************************
 * lwlibav_dec.c / lwindex.cpp
 *****************************************************************************
 * Copyright (C) 2012-2013 L-SMASH Works project
 *
 * Authors: Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *****************************************************************************/

/* This file is available under an ISC license. */

#include "cpp_compat.h"

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */
#include <libavformat/avformat.h>   /* Demuxer */
#include <libavcodec/avcodec.h>     /* Decoder */
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#include "lwlibav_dec.h"

int lwlibav_get_av_frame
(
    AVFormatContext *format_ctx,
    int              stream_index,
    AVPacket        *pkt
)
{
    av_init_packet( pkt );
    while( read_av_frame( format_ctx, pkt ) >= 0 )
    {
        if( pkt->stream_index != stream_index )
        {
            av_free_packet( pkt );
            continue;
        }
        return 0;
    }
    /* Return a null packet. */
    pkt->data = NULL;
    pkt->size = 0;
    return 1;
}
