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

#include "window-menu-item.h"

static void
window_item_activated (GtkWidget * widget,
                       WnckWindow* window)
{
  WnckWorkspace* workspace = wnck_window_get_workspace (window);

  if (workspace && wnck_screen_get_active_workspace (wnck_window_get_screen (window)) != workspace)
    {
      wnck_workspace_activate (workspace, gtk_get_current_event_time ());
    }

  if (wnck_screen_get_active_window (wnck_window_get_screen (window)) == window)
    {
      wnck_window_minimize (window);
    }
  else
    {
      wnck_window_activate_transient (window, gtk_get_current_event_time ());
    }
}

GtkWidget*
window_menu_item_new (WnckWindow* window)
{
  WnckApplication* application;
  GdkPixbuf* pixbuf;
  GtkWidget* item;
  GtkWidget* label;
  gchar    * markup;

  g_return_val_if_fail (WNCK_IS_WINDOW (window), NULL);

  item = gtk_image_menu_item_new ();

  application = wnck_window_get_application (window);

  /* FIXME: track icon changes */
  pixbuf = wnck_application_get_icon (application);
  if (pixbuf)
    {
      GtkWidget* image = gtk_image_new_from_pixbuf (pixbuf);
      gtk_widget_show (image);
      gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
    }

  g_signal_connect (item, "activate",
                    G_CALLBACK (window_item_activated), window);

  /* FIXME: track name changes */
  label = gtk_label_new (NULL);
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  markup = g_strdup_printf ("<b>%s</b>\n<small>%s</small>",
                            wnck_application_get_name (application),
                            wnck_window_get_name (window));
  gtk_label_set_markup (GTK_LABEL (label), markup);
  g_free (markup);

  gtk_widget_show (label);
  gtk_container_add (GTK_CONTAINER (item), label);

  return item;
}


/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
