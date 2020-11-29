/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2002-2005 Paolo Maggi
 * Copyright (C) 2007      William Jon McCann <mccann@jhu.edu>
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#ifndef __GDE2_SETTINGS_PLUGIN_H__
#define __GDE2_SETTINGS_PLUGIN_H__

#include <glib-object.h>
#include <gmodule.h>

#ifdef __cplusplus
extern "C" {
#endif
#define GDE2_TYPE_SETTINGS_PLUGIN              (gde2_settings_plugin_get_type())
#define GDE2_SETTINGS_PLUGIN(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), GDE2_TYPE_SETTINGS_PLUGIN, Gde2SettingsPlugin))
#define GDE2_SETTINGS_PLUGIN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass),  GDE2_TYPE_SETTINGS_PLUGIN, Gde2SettingsPluginClass))
#define GDE2_IS_SETTINGS_PLUGIN(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), GDE2_TYPE_SETTINGS_PLUGIN))
#define GDE2_IS_SETTINGS_PLUGIN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_SETTINGS_PLUGIN))
#define GDE2_SETTINGS_PLUGIN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj),  GDE2_TYPE_SETTINGS_PLUGIN, Gde2SettingsPluginClass))

typedef struct
{
        GObject parent;
} Gde2SettingsPlugin;

typedef struct
{
        GObjectClass parent_class;

        /* Virtual public methods */
        void            (*activate)                     (Gde2SettingsPlugin *plugin);
        void            (*deactivate)                   (Gde2SettingsPlugin *plugin);
} Gde2SettingsPluginClass;

GType            gde2_settings_plugin_get_type           (void) G_GNUC_CONST;

void             gde2_settings_plugin_activate           (Gde2SettingsPlugin *plugin);
void             gde2_settings_plugin_deactivate         (Gde2SettingsPlugin *plugin);

/*
 * Utility macro used to register plugins
 *
 * use: GDE2_SETTINGS_PLUGIN_REGISTER (PluginName, plugin_name)
 */
#define GDE2_SETTINGS_PLUGIN_REGISTER(PluginName, plugin_name)                 \
        G_DEFINE_DYNAMIC_TYPE (PluginName,                                     \
                               plugin_name,                                    \
                               GDE2_TYPE_SETTINGS_PLUGIN)                      \
                                                                               \
G_MODULE_EXPORT GType                                                          \
register_gde2_settings_plugin (GTypeModule *type_module)                       \
{                                                                              \
        plugin_name##_register_type (type_module);                             \
                                                                               \
        return plugin_name##_get_type();                                       \
}

#ifdef __cplusplus
}
#endif

#endif  /* __GDE2_SETTINGS_PLUGIN_H__ */
