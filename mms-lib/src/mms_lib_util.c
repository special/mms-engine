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

#include "mms_lib_util.h"
#include "mms_file_util.h"
#include "mms_message.h"
#include "mms_task.h"
#include "mms_log.h"

#ifdef MMS_RESIZE_IMAGEMAGICK
#  include <magick/api.h>
#endif

#define MMS_DEFAULT_ROOT_DIR        "/tmp/mms"
#define MMS_DEFAULT_USER_AGENT      "Jolla MMS"
#define MMS_DEFAULT_RETRY_SECS      (15)
#define MMS_DEFAULT_IDLE_SECS       (20)
#define MMS_DEFAULT_SIZE_LIMIT      (300*1024)
#define MMS_DEFAULT_MAX_PIXELS      (3000000)

/**
 * MMS error domain
 */
GQuark
mms_lib_error_quark()
{
    return g_quark_from_static_string("mms-lib-error-quark");
}

/**
 * One-time initialization
 */
void
mms_lib_init(
    const char* path)
{
    /* g_type_init has been deprecated since version 2.36
     * the type system is initialised automagically since then */
    G_GNUC_BEGIN_IGNORE_DEPRECATIONS;
    g_type_init();
    G_GNUC_END_IGNORE_DEPRECATIONS;

#ifdef MMS_RESIZE_IMAGEMAGICK
    MagickCoreGenesis(path, MagickFalse);
#endif
}

/**
 * Deinitialization
 */
void
mms_lib_deinit()
{
#ifdef MMS_RESIZE_IMAGEMAGICK
    MagickCoreTerminus();
#endif
}

/**
 * Reset configuration to default
 */
void
mms_lib_default_config(
    MMSConfig* config)
{
    config->root_dir = MMS_DEFAULT_ROOT_DIR;
    config->user_agent = MMS_DEFAULT_USER_AGENT;
    config->retry_secs = MMS_DEFAULT_RETRY_SECS;
    config->idle_secs = MMS_DEFAULT_IDLE_SECS;
    config->size_limit = MMS_DEFAULT_SIZE_LIMIT;
    config->max_pixels = MMS_DEFAULT_MAX_PIXELS;
    config->keep_temp_files = FALSE;
    config->attic_enabled = FALSE;
    config->send_dr = TRUE;
}

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
