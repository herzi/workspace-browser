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

#include <glib/gi18n.h>

#define WA_WORKSPACE "WorkspaceApplet::Workspace"

static GtkWidget* menu = NULL;

static void
select_cb (GtkItem * item,
           gpointer  user_data)
{
  gchar* text = g_strdup_printf (_("%s (rename)"),
                                 wnck_workspace_get_name (user_data));
  gtk_menu_item_set_label (GTK_MENU_ITEM (item), text);
  g_free (text);
}

static void
unselect_cb (GtkItem * item,
             gpointer  user_data)
{
  gtk_menu_item_set_label (GTK_MENU_ITEM (item),
                           wnck_workspace_get_name (user_data));
}

static void
untoggle (GtkWidget* widget,
          gpointer   user_data)
{
  gtk_toggle_button_set_active (user_data, FALSE);

  gtk_widget_destroy (widget);
  g_object_unref (widget);
  menu = NULL;
}

static void
button_toggled_cb (GtkToggleButton* button,
                   gpointer         user_data)
{
  if (gtk_toggle_button_get_active (button))
    {
      GtkWidget* item = NULL;
      GList    * window;

      g_return_if_fail (!menu);

      menu = g_object_ref_sink (gtk_menu_new ());
      item = gtk_menu_item_new_with_label (wnck_workspace_get_name (user_data));
      gtk_widget_set_sensitive (item, FALSE);
      g_signal_connect (item, "select",
                        G_CALLBACK (select_cb), user_data);
      g_signal_connect (item, "deselect",
                        G_CALLBACK (unselect_cb), user_data);
      gtk_widget_show (item);
      gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

      item = gtk_separator_menu_item_new ();
      gtk_widget_show (item);
      gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

      for (window = wnck_screen_get_windows (wnck_workspace_get_screen (user_data)); window; window = window->next)
        {
          if (!wnck_window_is_on_workspace (window->data, user_data) ||
              (wnck_window_get_state (window->data) & WNCK_WINDOW_STATE_SKIP_PAGER))
            {
              continue;
            }

          item = gtk_image_menu_item_new ();
          gtk_menu_item_set_label (GTK_MENU_ITEM (item),
                                   wnck_window_get_name (window->data));

          gtk_widget_show (item);
          gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
        }

      gtk_menu_attach_to_widget (GTK_MENU (menu),
                                 GTK_WIDGET (button),
                                 NULL);

      gtk_menu_popup (GTK_MENU (menu),
                      NULL, NULL,
                      NULL,
                      NULL,
                      0, gtk_get_current_event_time ());

      g_object_add_weak_pointer (G_OBJECT (menu), (gpointer*)&menu);

      g_signal_connect (menu, "selection-done",
                        G_CALLBACK (untoggle), button);
    }
}

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

  g_signal_connect (button, "toggled",
                    G_CALLBACK (button_toggled_cb), workspace);
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
