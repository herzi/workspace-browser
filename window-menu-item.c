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
  GtkWidget* item;

  g_return_val_if_fail (WNCK_IS_WINDOW (window), NULL);

  item = gtk_image_menu_item_new ();
  gtk_menu_item_set_label (GTK_MENU_ITEM (item),
                           wnck_window_get_name (window));
  g_signal_connect (item, "activate",
                    G_CALLBACK (window_item_activated), window);

  return item;
}


/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
