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

static void
append_menu_item (GtkMenu    * menu,
                  gchar const* category,
                  gchar const* icon_name,
                  gchar const* window_title)
{
  static GtkSizeGroup* categories = NULL;

  GtkWidget* widget = gtk_menu_item_new ();
  GtkWidget* hbox = gtk_hbox_new (FALSE, 6);

  if (!categories)
    {
      categories = gtk_size_group_new (GTK_SIZE_GROUP_HORIZONTAL);
    }

  GtkWidget* category_label = gtk_label_new (category);
  gtk_misc_set_alignment (GTK_MISC (category_label), 1.0, 0.5);

  gtk_box_pack_start (GTK_BOX (hbox), category_label,
                      FALSE, FALSE, 0);

  gtk_size_group_add_widget (categories, category_label);

  gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new (),
                      FALSE, FALSE, 0);

  if (icon_name)
    {
      GtkWidget* icon = gtk_image_new_from_icon_name (icon_name, GTK_ICON_SIZE_MENU);

      gtk_box_pack_start (GTK_BOX (hbox), icon,
                          FALSE, FALSE, 0);
    }

  category_label = gtk_label_new (window_title);
  gtk_box_pack_start (GTK_BOX (hbox), category_label,
                      FALSE, FALSE, 0);

  gtk_widget_show_all (hbox);
  gtk_container_add (GTK_CONTAINER (widget), hbox);

  gtk_menu_shell_append (GTK_MENU_SHELL (menu), widget);
}

int
main (int   argc,
      char**argv)
{
  GtkWidget* menu;

  gtk_init (&argc, &argv);

  menu = gtk_menu_new ();
  append_menu_item (GTK_MENU (menu), "Internet",   "empathy",  "Empathy - Buddy List");
  append_menu_item (GTK_MENU (menu), NULL,         "firefox",  "Blog Tutorial - Mozilla Firefox");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), gtk_separator_menu_item_new ());
  append_menu_item (GTK_MENU (menu), "System",     "nautilus", "herzi - File Browser");
  append_menu_item (GTK_MENU (menu), NULL,         "gnome-terminal", "herzi@boober:~/Hacking/Desktop/workspace-applet");
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), gtk_separator_menu_item_new ());
  append_menu_item (GTK_MENU (menu), "Multimedia", "rhythmbox", "Music Player");

  gtk_widget_show_all (menu);
  gtk_menu_popup (GTK_MENU (menu),
                  NULL, NULL,
                  NULL, NULL,
                  0, gtk_get_current_event_time ());

  g_signal_connect (menu, "selection-done",
                    G_CALLBACK (gtk_main_quit), NULL);

  gtk_main ();
  return 0;
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
