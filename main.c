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

#include <gtk/gtk.h>
#include <libwnck/libwnck.h>

static void
workspace_created_cb (WnckScreen   * screen,
                      WnckWorkspace* workspace,
                      gpointer       user_data)
{
  GtkWidget* button = gtk_toggle_button_new_with_label (wnck_workspace_get_name (workspace));
  /* FIXME: update to renames */

  gtk_widget_show (button);
  gtk_box_pack_start (user_data, button,
                      FALSE, FALSE, 0);
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

int
main (int   argc,
      char**argv)
{
  WnckScreen* screen;
  GtkWidget * box;
  GtkWidget * window;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  box    = gtk_hbox_new (TRUE, 0);

  g_signal_connect (window, "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);

  gtk_container_add (GTK_CONTAINER (window), box);
  gtk_widget_show_all (window);

  screen = wnck_screen_get_default ();
  g_signal_connect (screen, "workspace-created",
                    G_CALLBACK (workspace_created_cb), box);
  g_signal_connect (screen, "workspace-destroyed",
                    G_CALLBACK (workspace_destroyed_cb), box);

  gtk_main ();
  return 0;
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
