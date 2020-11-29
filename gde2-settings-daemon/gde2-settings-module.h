/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2005 - Paolo Maggi
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef GDE2_SETTINGS_MODULE_H
#define GDE2_SETTINGS_MODULE_H

#include <glib-object.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GDE2_TYPE_SETTINGS_MODULE               (gde2_settings_module_get_type ())
#define GDE2_SETTINGS_MODULE(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_SETTINGS_MODULE, Gde2SettingsModule))
#define GDE2_SETTINGS_MODULE_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_TYPE_SETTINGS_MODULE, Gde2SettingsModuleClass))
#define GDE2_IS_SETTINGS_MODULE(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_SETTINGS_MODULE))
#define GDE2_IS_SETTINGS_MODULE_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE ((obj), GDE2_TYPE_SETTINGS_MODULE))
#define GDE2_SETTINGS_MODULE_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj), GDE2_TYPE_SETTINGS_MODULE, Gde2SettingsModuleClass))

typedef struct _Gde2SettingsModule Gde2SettingsModule;

GType                    gde2_settings_module_get_type          (void) G_GNUC_CONST;

Gde2SettingsModule     *gde2_settings_module_new               (const gchar *path);

const char              *gde2_settings_module_get_path          (Gde2SettingsModule *module);

GObject                 *gde2_settings_module_new_object        (Gde2SettingsModule *module);

#ifdef __cplusplus
}
#endif

#endif
