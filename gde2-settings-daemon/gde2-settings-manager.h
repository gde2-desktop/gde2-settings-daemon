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

#ifndef __GDE2_SETTINGS_MANAGER_H
#define __GDE2_SETTINGS_MANAGER_H

#include <glib-object.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GDE2_TYPE_SETTINGS_MANAGER         (gde2_settings_manager_get_type ())
#define GDE2_SETTINGS_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GDE2_TYPE_SETTINGS_MANAGER, Gde2SettingsManager))
#define GDE2_SETTINGS_MANAGER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GDE2_TYPE_SETTINGS_MANAGER, Gde2SettingsManagerClass))
#define GDE2_IS_SETTINGS_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GDE2_TYPE_SETTINGS_MANAGER))
#define GDE2_IS_SETTINGS_MANAGER_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GDE2_TYPE_SETTINGS_MANAGER))
#define GDE2_SETTINGS_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GDE2_TYPE_SETTINGS_MANAGER, Gde2SettingsManagerClass))

typedef struct Gde2SettingsManagerPrivate Gde2SettingsManagerPrivate;

typedef struct
{
        GObject                      parent;
        Gde2SettingsManagerPrivate  *priv;
} Gde2SettingsManager;

typedef struct
{
        GObjectClass   parent_class;

        void          (* plugin_activated)         (Gde2SettingsManager *manager,
                                                    const char           *name);
        void          (* plugin_deactivated)       (Gde2SettingsManager *manager,
                                                    const char           *name);
} Gde2SettingsManagerClass;

typedef enum
{
        GDE2_SETTINGS_MANAGER_ERROR_GENERAL
} Gde2SettingsManagerError;

#define GDE2_SETTINGS_MANAGER_ERROR gde2_settings_manager_error_quark ()

GQuark                 gde2_settings_manager_error_quark         (void);
GType                  gde2_settings_manager_get_type   (void);

Gde2SettingsManager * gde2_settings_manager_new        (void);

gboolean               gde2_settings_manager_start      (Gde2SettingsManager *manager,
                                                          GError              **error);
void                   gde2_settings_manager_stop       (Gde2SettingsManager *manager);

gboolean               gde2_settings_manager_awake      (Gde2SettingsManager *manager,
                                                          GError              **error);

#ifdef __cplusplus
}
#endif

#endif /* __GDE2_SETTINGS_MANAGER_H */
