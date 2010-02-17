/* This file is part of herzi's playground
 *
 * Copyright (C) 2010  Sven Herzberg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef WORKSPACE_BUTTON_H
#define WORKSPACE_BUTTON_H

#include <gtk/gtk.h>
#include <libwnck/libwnck.h>

G_BEGIN_DECLS

typedef struct _WorkspaceButton        WorkspaceButton;
typedef struct _WorkspaceButtonClass   WorkspaceButtonClass;
typedef struct _WorkspaceButtonPrivate WorkspaceButtonPrivate;

#define WORKSPACE_TYPE_BUTTON         (workspace_button_get_type ())
#define WORKSPACE_BUTTON(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), WORKSPACE_TYPE_BUTTON, WorkspaceButton))
#define WORKSPACE_BUTTON_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), WORKSPACE_TYPE_BUTTON, WorkspaceButtonClass))
#define WORKSPACE_IS_BUTTON(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), WORKSPACE_TYPE_BUTTON))
#define WORKSPACE_IS_BUTTON_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), WORKSPACE_TYPE_BUTTON))
#define WORKSPACE_BUTTON_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), WORKSPACE_TYPE_BUTTON, WorkspaceButtonClass))

GType      workspace_button_get_type (void);
GtkWidget* workspace_button_new      (WnckWorkspace* workspace);

struct _WorkspaceButton
{
  GtkToggleButton         base_instance;
  WorkspaceButtonPrivate* _private;
};

struct _WorkspaceButtonClass
{
  GtkToggleButtonClass    base_class;
};

G_END_DECLS

#endif /* !WORKSPACE_BUTTON_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
