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

#include "workspace-browser.h"
#include "workspace-button.h"

#define WA_WORKSPACE "WorkspaceApplet::Workspace"

G_DEFINE_TYPE (WorkspaceBrowser, workspace_browser, GTK_TYPE_HBOX);

static void
workspace_created_cb (WnckScreen   * screen,
                      WnckWorkspace* workspace,
                      gpointer       user_data)
{
  GtkWidget* button = workspace_button_new (workspace);

  gtk_widget_show (button);
  gtk_box_pack_start (user_data, button,
                      TRUE, TRUE, 0);
  gtk_box_reorder_child (user_data, button,
                         wnck_workspace_get_number (workspace));
}

static void
workspace_destroyed_cb (WnckScreen   * screen,
                        WnckWorkspace* workspace,
                        gpointer       user_data)
{
  GList    * children;
  GtkWidget* button;

  children = gtk_container_get_children (user_data);
  button   = g_list_nth_data (children, wnck_workspace_get_number (workspace));

  gtk_container_remove (user_data, button);

  g_list_free (children);
}

static void
workspace_browser_init (WorkspaceBrowser* self)
{
  WnckScreen* screen = wnck_screen_get_default ();

  g_signal_connect (screen, "workspace-created",
                    G_CALLBACK (workspace_created_cb), self);
  g_signal_connect (screen, "workspace-destroyed",
                    G_CALLBACK (workspace_destroyed_cb), self);
}

static void
workspace_browser_class_init (WorkspaceBrowserClass* self_class)
{}

GtkWidget*
workspace_browser_new (void)
{
  return g_object_new (WORKSPACE_TYPE_BROWSER,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
