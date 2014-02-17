/*
 * Copyright (C) 2013-2014 Jolla Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef JOLLA_MMS_UTIL_H
#define JOLLA_MMS_UTIL_H

#include "mms_lib_types.h"
#include <libsoup/soup.h>

typedef struct mms_http_transfer {
    MMSConnection* connection;
    SoupSession* session;
    SoupMessage* message;
    int fd;
} MMSHttpTransfer;

char*
mms_strip_address_type(
    char* address);

char**
mms_split_address_list(
    const char* addres_list);

MMSPdu*
mms_decode_bytes(
    GBytes* bytes);

SoupURI*
mms_parse_http_uri(
    const char* raw_uri);

MMSHttpTransfer*
mms_http_transfer_new(
    const MMSConfig* config,
    MMSConnection* connection,
    const char* method,
    const char* uri,
    int fd);

void
mms_http_transfer_free(
    MMSHttpTransfer* tx);

/* NULL-resistant variant of g_strstrip */
G_INLINE_FUNC char* mms_strip(char* str)
    { return str ? g_strstrip(str) : NULL; }

#endif /* JOLLA_MMS_UTIL_H */

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */