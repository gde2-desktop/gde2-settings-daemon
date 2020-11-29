/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 William Jon McCann <mccann@jhu.edu>
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <glib-object.h>
#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <gio/gio.h>

#include "gde2-settings-plugin-info.h"
#include "gde2-settings-manager.h"
#include "gde2-settings-manager-glue.h"
#include "gde2-settings-profile.h"

#define MSD_MANAGER_DBUS_PATH "/org/gde2/SettingsDaemon"

#define DEFAULT_SETTINGS_PREFIX "org.gde2.SettingsDaemon"

#define PLUGIN_EXT ".gde2-settings-plugin"

#define GDE2_SETTINGS_MANAGER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GDE2_TYPE_SETTINGS_MANAGER, Gde2SettingsManagerPrivate))

struct Gde2SettingsManagerPrivate
{
        DBusGConnection            *connection;
        GSList                     *plugins;
};

enum {
        PLUGIN_ACTIVATED,
        PLUGIN_DEACTIVATED,
        LAST_SIGNAL
};

static guint signals [LAST_SIGNAL] = { 0, };

static void     gde2_settings_manager_class_init  (Gde2SettingsManagerClass *klass);
static void     gde2_settings_manager_init        (Gde2SettingsManager      *settings_manager);
static void     gde2_settings_manager_finalize    (GObject                   *object);

G_DEFINE_TYPE (Gde2SettingsManager, gde2_settings_manager, G_TYPE_OBJECT)

static gpointer manager_object = NULL;

GQuark
gde2_settings_manager_error_quark (void)
{
        static GQuark ret = 0;
        if (ret == 0) {
                ret = g_quark_from_static_string ("gde2_settings_manager_error");
        }

        return ret;
}

static void
maybe_activate_plugin (Gde2SettingsPluginInfo *info, gpointer user_data)
{
        if (gde2_settings_plugin_info_get_enabled (info)) {
                gboolean res;
                res = gde2_settings_plugin_info_activate (info);
                if (res) {
                        g_debug ("Plugin %s: active", gde2_settings_plugin_info_get_location (info));
                } else {
                        g_debug ("Plugin %s: activation failed", gde2_settings_plugin_info_get_location (info));
                }
        } else {
                g_debug ("Plugin %s: inactive", gde2_settings_plugin_info_get_location (info));
        }
}

static gint
compare_location (Gde2SettingsPluginInfo *a,
                  Gde2SettingsPluginInfo *b)
{
        const char *loc_a;
        const char *loc_b;

        loc_a = gde2_settings_plugin_info_get_location (a);
        loc_b = gde2_settings_plugin_info_get_location (b);

        if (loc_a == NULL || loc_b == NULL) {
                return -1;
        }

        return strcmp (loc_a, loc_b);
}

static int
compare_priority (Gde2SettingsPluginInfo *a,
                  Gde2SettingsPluginInfo *b)
{
        int prio_a;
        int prio_b;

        prio_a = gde2_settings_plugin_info_get_priority (a);
        prio_b = gde2_settings_plugin_info_get_priority (b);

        return prio_a - prio_b;
}

static void
on_plugin_activated (Gde2SettingsPluginInfo *info,
                     Gde2SettingsManager    *manager)
{
        const char *name;
        name = gde2_settings_plugin_info_get_location (info);
        g_debug ("Gde2SettingsManager: emitting plugin-activated %s", name);
        g_signal_emit (manager, signals [PLUGIN_ACTIVATED], 0, name);
}

static void
on_plugin_deactivated (Gde2SettingsPluginInfo *info,
                       Gde2SettingsManager    *manager)
{
        const char *name;
        name = gde2_settings_plugin_info_get_location (info);
        g_debug ("Gde2SettingsManager: emitting plugin-deactivated %s", name);
        g_signal_emit (manager, signals [PLUGIN_DEACTIVATED], 0, name);
}

static gboolean
is_item_in_schema (const char * const *items,
                   const char         *item)
{
	while (*items) {
	       if (g_strcmp0 (*items++, item) == 0)
		       return TRUE;
	}
	return FALSE;
}

static gboolean
is_schema (const char *schema)
{
	return is_item_in_schema (g_settings_list_schemas (), schema);
}

static void
_load_file (Gde2SettingsManager *manager,
            const char           *filename)
{
        Gde2SettingsPluginInfo  *info;
        char                    *schema;
        GSList                  *l;

        g_debug ("Loading plugin: %s", filename);
        gde2_settings_profile_start ("%s", filename);

        info = gde2_settings_plugin_info_new_from_file (filename);
        if (info == NULL) {
                goto out;
        }

        l = g_slist_find_custom (manager->priv->plugins,
                                 info,
                                 (GCompareFunc) compare_location);
        if (l != NULL) {
                goto out;
        }

        schema = g_strdup_printf ("%s.plugins.%s",
                                  DEFAULT_SETTINGS_PREFIX,
                                  gde2_settings_plugin_info_get_location (info));
        
	/* Ignore unknown schemas or else we'll assert */
	if (is_schema (schema)) {
	       manager->priv->plugins = g_slist_prepend (manager->priv->plugins,
		                                         g_object_ref (info));

	       g_signal_connect (info, "activated",
		                 G_CALLBACK (on_plugin_activated), manager);
	       g_signal_connect (info, "deactivated",
		                 G_CALLBACK (on_plugin_deactivated), manager);

	       /* Also sets priority for plugins */
	       gde2_settings_plugin_info_set_schema (info, schema);
	} else {
	       g_warning ("Ignoring unknown module '%s'", schema);
	}

        g_free (schema);

 out:
        if (info != NULL) {
                g_object_unref (info);
        }

        gde2_settings_profile_end ("%s", filename);
}

static void
_load_dir (Gde2SettingsManager *manager,
           const char           *path)
{
        GError     *error;
        GDir       *d;
        const char *name;

        g_debug ("Loading settings plugins from dir: %s", path);
        gde2_settings_profile_start (NULL);

        error = NULL;
        d = g_dir_open (path, 0, &error);
        if (d == NULL) {
                g_warning ("%s", error->message);
                g_error_free (error);
                return;
        }

        while ((name = g_dir_read_name (d))) {
                char *filename;

                if (!g_str_has_suffix (name, PLUGIN_EXT)) {
                        continue;
                }

                filename = g_build_filename (path, name, NULL);
                if (g_file_test (filename, G_FILE_TEST_IS_REGULAR)) {
                        _load_file (manager, filename);
                }
                g_free (filename);
        }

        g_dir_close (d);

        gde2_settings_profile_end (NULL);
}

static void
_load_all (Gde2SettingsManager *manager)
{
        gde2_settings_profile_start (NULL);

        /* load system plugins */
        _load_dir (manager, GDE2_SETTINGS_PLUGINDIR G_DIR_SEPARATOR_S);

        manager->priv->plugins = g_slist_sort (manager->priv->plugins, (GCompareFunc) compare_priority);
        g_slist_foreach (manager->priv->plugins, (GFunc) maybe_activate_plugin, NULL);
        gde2_settings_profile_end (NULL);
}

static void
_unload_plugin (Gde2SettingsPluginInfo *info, gpointer user_data)
{
        if (gde2_settings_plugin_info_get_enabled (info)) {
                gde2_settings_plugin_info_deactivate (info);
        }
        g_object_unref (info);
}

static void
_unload_all (Gde2SettingsManager *manager)
{
         g_slist_foreach (manager->priv->plugins, (GFunc) _unload_plugin, NULL);
         g_slist_free (manager->priv->plugins);
         manager->priv->plugins = NULL;
}

/*
  Example:
  dbus-send --session --dest=org.gde2.SettingsDaemon \
  --type=method_call --print-reply --reply-timeout=2000 \
  /org/gde2/SettingsDaemon \
  org.gde2.SettingsDaemon.Awake
*/
gboolean
gde2_settings_manager_awake (Gde2SettingsManager *manager,
                              GError              **error)
{
        g_debug ("Awake called");
        return gde2_settings_manager_start (manager, error);
}

static gboolean
register_manager (Gde2SettingsManager *manager)
{
        GError *error = NULL;

        manager->priv->connection = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
        if (manager->priv->connection == NULL) {
                if (error != NULL) {
                        g_critical ("error getting system bus: %s", error->message);
                        g_error_free (error);
                }
                return FALSE;
        }

        dbus_g_connection_register_g_object (manager->priv->connection, MSD_MANAGER_DBUS_PATH, G_OBJECT (manager));

        return TRUE;
}

gboolean
gde2_settings_manager_start (Gde2SettingsManager *manager,
                              GError              **error)
{
        gboolean ret;

        g_debug ("Starting settings manager");

        ret = FALSE;

        gde2_settings_profile_start (NULL);

        if (!g_module_supported ()) {
                g_warning ("gde2-settings-daemon is not able to initialize the plugins.");
                g_set_error (error,
                             GDE2_SETTINGS_MANAGER_ERROR,
                             GDE2_SETTINGS_MANAGER_ERROR_GENERAL,
                             "Plugins not supported");

                goto out;
        }

        _load_all (manager);

        ret = TRUE;
 out:
        gde2_settings_profile_end (NULL);

        return ret;
}

void
gde2_settings_manager_stop (Gde2SettingsManager *manager)
{
        g_debug ("Stopping settings manager");

        _unload_all (manager);
}

static void
gde2_settings_manager_dispose (GObject *object)
{
        Gde2SettingsManager *manager;

        manager = GDE2_SETTINGS_MANAGER (object);

        gde2_settings_manager_stop (manager);

        G_OBJECT_CLASS (gde2_settings_manager_parent_class)->dispose (object);
}

static void
gde2_settings_manager_class_init (Gde2SettingsManagerClass *klass)
{
        GObjectClass   *object_class = G_OBJECT_CLASS (klass);

        object_class->dispose = gde2_settings_manager_dispose;
        object_class->finalize = gde2_settings_manager_finalize;

        signals [PLUGIN_ACTIVATED] =
                g_signal_new ("plugin-activated",
                              G_TYPE_FROM_CLASS (object_class),
                              G_SIGNAL_RUN_LAST,
                              G_STRUCT_OFFSET (Gde2SettingsManagerClass, plugin_activated),
                              NULL,
                              NULL,
                              g_cclosure_marshal_VOID__STRING,
                              G_TYPE_NONE,
                              1, G_TYPE_STRING);
        signals [PLUGIN_DEACTIVATED] =
                g_signal_new ("plugin-deactivated",
                              G_TYPE_FROM_CLASS (object_class),
                              G_SIGNAL_RUN_LAST,
                              G_STRUCT_OFFSET (Gde2SettingsManagerClass, plugin_deactivated),
                              NULL,
                              NULL,
                              g_cclosure_marshal_VOID__STRING,
                              G_TYPE_NONE,
                              1, G_TYPE_STRING);

        g_type_class_add_private (klass, sizeof (Gde2SettingsManagerPrivate));

        dbus_g_object_type_install_info (GDE2_TYPE_SETTINGS_MANAGER, &dbus_glib_gde2_settings_manager_object_info);
}

static void
gde2_settings_manager_init (Gde2SettingsManager *manager)
{

        manager->priv = GDE2_SETTINGS_MANAGER_GET_PRIVATE (manager);
}

static void
gde2_settings_manager_finalize (GObject *object)
{
        Gde2SettingsManager *manager;

        g_return_if_fail (object != NULL);
        g_return_if_fail (GDE2_IS_SETTINGS_MANAGER (object));

        manager = GDE2_SETTINGS_MANAGER (object);

        g_return_if_fail (manager->priv != NULL);

        G_OBJECT_CLASS (gde2_settings_manager_parent_class)->finalize (object);
}

Gde2SettingsManager *
gde2_settings_manager_new (void)
{
        if (manager_object != NULL) {
                g_object_ref (manager_object);
        } else {
                gboolean res;

                manager_object = g_object_new (GDE2_TYPE_SETTINGS_MANAGER,
                                               NULL);
                g_object_add_weak_pointer (manager_object,
                                           (gpointer *) &manager_object);
                res = register_manager (manager_object);
                if (! res) {
                        g_object_unref (manager_object);
                        return NULL;
                }
        }

        return GDE2_SETTINGS_MANAGER (manager_object);
}
