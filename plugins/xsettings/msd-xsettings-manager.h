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

#ifndef __GDE2_XSETTINGS_MANAGER_H
#define __GDE2_XSETTINGS_MANAGER_H

#include <glib-object.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GDE2_TYPE_XSETTINGS_MANAGER         (gde2_xsettings_manager_get_type ())
#define GDE2_XSETTINGS_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GDE2_TYPE_XSETTINGS_MANAGER, Gde2XSettingsManager))
#define GDE2_XSETTINGS_MANAGER_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GDE2_TYPE_XSETTINGS_MANAGER, Gde2XSettingsManagerClass))
#define GDE2_IS_XSETTINGS_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GDE2_TYPE_XSETTINGS_MANAGER))
#define GDE2_IS_XSETTINGS_MANAGER_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GDE2_TYPE_XSETTINGS_MANAGER))
#define GDE2_XSETTINGS_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GDE2_TYPE_XSETTINGS_MANAGER, Gde2XSettingsManagerClass))

typedef struct Gde2XSettingsManagerPrivate Gde2XSettingsManagerPrivate;

typedef struct
{
        GObject                     parent;
        Gde2XSettingsManagerPrivate *priv;
} Gde2XSettingsManager;

typedef struct
{
        GObjectClass   parent_class;
} Gde2XSettingsManagerClass;

GType                   gde2_xsettings_manager_get_type            (void);

Gde2XSettingsManager * gde2_xsettings_manager_new                 (void);
gboolean                gde2_xsettings_manager_start               (Gde2XSettingsManager *manager,
                                                                     GError               **error);
void                    gde2_xsettings_manager_stop                (Gde2XSettingsManager *manager);

#ifdef __cplusplus
}
#endif

#endif /* __GDE2_XSETTINGS_MANAGER_H */
