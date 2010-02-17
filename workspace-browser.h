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

#ifndef WORKSPACE_BROWSER_H
#define WORKSPACE_BROWSER_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _WorkspaceBrowser        WorkspaceBrowser;
typedef struct _WorkspaceBrowserClass   WorkspaceBrowserClass;
typedef struct _WorkspaceBrowserPrivate WorkspaceBrowserPrivate;

#define WORKSPACE_TYPE_BROWSER         (workspace_browser_get_type ())
#define WORKSPACE_BROWSER(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), WORKSPACE_TYPE_BROWSER, WorkspaceBrowser))
#define WORKSPACE_BROWSER_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), WORKSPACE_TYPE_BROWSER, WorkspaceBrowserClass))
#define WORKSPACE_IS_BROWSER(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), WORKSPACE_TYPE_BROWSER))
#define WORKSPACE_IS_BROWSER_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), WORKSPACE_TYPE_BROWSER))
#define WORKSPACE_BROWSER_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), WORKSPACE_TYPE_BROWSER, WorkspaceBrowserClass))

GType      workspace_browser_get_type (void);
GtkWidget* workspace_browser_new      (void);

struct _WorkspaceBrowser
{
  GtkHBox                  base_instance;
  WorkspaceBrowserPrivate* _private;
};

struct _WorkspaceBrowserClass
{
  GtkHBoxClass             base_class;
};

G_END_DECLS

#endif /* !WORKSPACE_BROWSER_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
