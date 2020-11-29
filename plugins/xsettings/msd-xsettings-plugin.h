/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 William Jon McCann <mccann@jhu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef __GDE2_XSETTINGS_PLUGIN_H__
#define __GDE2_XSETTINGS_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <gmodule.h>

#include "gde2-settings-plugin.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GDE2_TYPE_XSETTINGS_PLUGIN                (gde2_xsettings_plugin_get_type ())
#define GDE2_XSETTINGS_PLUGIN(o)                  (G_TYPE_CHECK_INSTANCE_CAST ((o), GDE2_TYPE_XSETTINGS_PLUGIN, Gde2XSettingsPlugin))
#define GDE2_XSETTINGS_PLUGIN_CLASS(k)            (G_TYPE_CHECK_CLASS_CAST((k), GDE2_TYPE_XSETTINGS_PLUGIN, Gde2XSettingsPluginClass))
#define GDE2_IS_XSETTINGS_PLUGIN(o)               (G_TYPE_CHECK_INSTANCE_TYPE ((o), GDE2_TYPE_XSETTINGS_PLUGIN))
#define GDE2_IS_XSETTINGS_PLUGIN_CLASS(k)         (G_TYPE_CHECK_CLASS_TYPE ((k), GDE2_TYPE_XSETTINGS_PLUGIN))
#define GDE2_XSETTINGS_PLUGIN_GET_CLASS(o)        (G_TYPE_INSTANCE_GET_CLASS ((o), GDE2_TYPE_XSETTINGS_PLUGIN, Gde2XSettingsPluginClass))

typedef struct Gde2XSettingsPluginPrivate Gde2XSettingsPluginPrivate;

typedef struct
{
        Gde2SettingsPlugin          parent;
        Gde2XSettingsPluginPrivate *priv;
} Gde2XSettingsPlugin;

typedef struct
{
        Gde2SettingsPluginClass parent_class;
} Gde2XSettingsPluginClass;

GType   gde2_xsettings_plugin_get_type            (void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT GType register_gde2_settings_plugin (GTypeModule *module);

#ifdef __cplusplus
}
#endif

#endif /* __GDE2_XSETTINGS_PLUGIN_H__ */
