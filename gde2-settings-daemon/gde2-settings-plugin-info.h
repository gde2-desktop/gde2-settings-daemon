/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2008 Red Hat, Inc.
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

#ifndef __GDE2_SETTINGS_PLUGIN_INFO_H__
#define __GDE2_SETTINGS_PLUGIN_INFO_H__

#include <glib-object.h>
#include <gmodule.h>

#ifdef __cplusplus
extern "C" {
#endif
#define GDE2_TYPE_SETTINGS_PLUGIN_INFO              (gde2_settings_plugin_info_get_type())
#define GDE2_SETTINGS_PLUGIN_INFO(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), GDE2_TYPE_SETTINGS_PLUGIN_INFO, Gde2SettingsPluginInfo))
#define GDE2_SETTINGS_PLUGIN_INFO_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass),  GDE2_TYPE_SETTINGS_PLUGIN_INFO, Gde2SettingsPluginInfoClass))
#define GDE2_IS_SETTINGS_PLUGIN_INFO(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), GDE2_TYPE_SETTINGS_PLUGIN_INFO))
#define GDE2_IS_SETTINGS_PLUGIN_INFO_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_SETTINGS_PLUGIN_INFO))
#define GDE2_SETTINGS_PLUGIN_INFO_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj),  GDE2_TYPE_SETTINGS_PLUGIN_INFO, Gde2SettingsPluginInfoClass))

typedef struct Gde2SettingsPluginInfoPrivate Gde2SettingsPluginInfoPrivate;

typedef struct
{
        GObject                         parent;
        Gde2SettingsPluginInfoPrivate *priv;
} Gde2SettingsPluginInfo;

typedef struct
{
        GObjectClass parent_class;

        void          (* activated)         (Gde2SettingsPluginInfo *info);
        void          (* deactivated)       (Gde2SettingsPluginInfo *info);
} Gde2SettingsPluginInfoClass;

GType            gde2_settings_plugin_info_get_type           (void) G_GNUC_CONST;

Gde2SettingsPluginInfo *gde2_settings_plugin_info_new_from_file (const char *filename);

gboolean         gde2_settings_plugin_info_activate        (Gde2SettingsPluginInfo *info);
gboolean         gde2_settings_plugin_info_deactivate      (Gde2SettingsPluginInfo *info);

gboolean         gde2_settings_plugin_info_is_active       (Gde2SettingsPluginInfo *info);
gboolean         gde2_settings_plugin_info_get_enabled     (Gde2SettingsPluginInfo *info);
gboolean         gde2_settings_plugin_info_is_available    (Gde2SettingsPluginInfo *info);

const char      *gde2_settings_plugin_info_get_name        (Gde2SettingsPluginInfo *info);
const char      *gde2_settings_plugin_info_get_description (Gde2SettingsPluginInfo *info);
const char     **gde2_settings_plugin_info_get_authors     (Gde2SettingsPluginInfo *info);
const char      *gde2_settings_plugin_info_get_website     (Gde2SettingsPluginInfo *info);
const char      *gde2_settings_plugin_info_get_copyright   (Gde2SettingsPluginInfo *info);
const char      *gde2_settings_plugin_info_get_location    (Gde2SettingsPluginInfo *info);
int              gde2_settings_plugin_info_get_priority    (Gde2SettingsPluginInfo *info);

void             gde2_settings_plugin_info_set_priority    (Gde2SettingsPluginInfo *info,
                                                            int                     priority);
void             gde2_settings_plugin_info_set_schema      (Gde2SettingsPluginInfo *info,
                                                            gchar                  *schema);
#ifdef __cplusplus
}
#endif

#endif  /* __GDE2_SETTINGS_PLUGIN_INFO_H__ */
