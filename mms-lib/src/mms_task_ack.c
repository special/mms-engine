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

#include "mms_task.h"
#include "mms_task_http.h"
#include "mms_file_util.h"
#include "mms_codec.h"

static
const char*
mms_task_ack_encode(
    const MMSConfig* config,
    const char* id,
    const char* transaction_id)
{
    const char* result = NULL;
    const char* file = MMS_ACKNOWLEDGE_IND_FILE;
    char* dir = mms_message_dir(config, id);
    int fd = mms_create_file(dir, file, NULL, NULL);
    if (fd >= 0) {
        MMSPdu* pdu = g_new0(MMSPdu, 1);
        pdu->type = MMS_MESSAGE_TYPE_ACKNOWLEDGE_IND;
        pdu->version = MMS_VERSION;
        pdu->transaction_id = g_strdup(transaction_id);
        pdu->ai.report = config->send_dr;
        if (mms_message_encode(pdu, fd)) result = file;
        mms_message_free(pdu);
        close(fd);
    }
    g_free(dir);
    return result;
}

/* Create MMS delivery acknowledgement task */
MMSTask*
mms_task_ack_new(
    const MMSConfig* config,
    MMSHandler* handler,
    const char* id,
    const char* imsi,
    const char* tx_id)
{
    const char* file = mms_task_ack_encode(config, id, tx_id);
    if (file) {
        return mms_task_http_alloc(0, config, handler, "Ack",
            id, imsi, NULL, NULL, file);
    }
    return NULL;
}

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
