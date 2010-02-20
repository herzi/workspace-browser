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

#include "workspace-button.h"
#include "wb-label.h"
#include "window-menu-item.h"
#include <glib/gi18n.h>

struct _WorkspaceButtonPrivate
{
  GtkWidget    * label;
  WnckWorkspace* workspace;
  WnckWindow   * active;
};

enum
{
  PROP_0,
  PROP_WORKSPACE
};

#define PRIV(i) (((WorkspaceButton*)(i))->_private)

static GtkWidget* menu = NULL;

G_DEFINE_TYPE (WorkspaceButton, workspace_button, GTK_TYPE_TOGGLE_BUTTON);

#if 0
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
#endif

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
menu_position_func (GtkMenu * menu,
                    gint    * x,
                    gint    * y,
                    gboolean* push_in,
                    gpointer  user_data)
{
  GtkRequisition  requisition;
  GtkAllocation   allocation;
  GdkRectangle    monitor_geometry;
  GdkScreen     * screen;
  int             monitor;

  screen = gtk_widget_get_screen (GTK_WIDGET (menu));

  gtk_widget_get_allocation (user_data, &allocation);
  gtk_widget_size_request (GTK_WIDGET (menu), &requisition);

  gdk_window_get_root_coords (gtk_widget_get_parent_window (user_data),
                              allocation.x, allocation.y,
                              &allocation.x, &allocation.y);

  monitor = gdk_screen_get_monitor_at_window (screen, GTK_WIDGET (user_data)->window);
  gtk_menu_set_monitor (menu, monitor);
  gdk_screen_get_monitor_geometry (screen, monitor, &monitor_geometry);

  if (allocation.y >= monitor_geometry.y &&
      allocation.y + allocation.height + requisition.height <= monitor_geometry.y + monitor_geometry.height)
    {
      *y = allocation.y + allocation.height;
    }
  else if (allocation.y - requisition.height >= monitor_geometry.y &&
           allocation.y <= monitor_geometry.y + monitor_geometry.height)
    {
      *y = allocation.y - requisition.height;
    }
  else
    {
      g_warning ("implement menu somewhere else");
      *y = allocation.y;
    }

  switch (gtk_widget_get_direction (user_data))
    {
    case GTK_TEXT_DIR_RTL:
      *x = allocation.x + allocation.width - requisition.width;
      break;
    case GTK_TEXT_DIR_LTR:
    case GTK_TEXT_DIR_NONE:
      *x = allocation.x;
      break;
    default:
      g_warn_if_reached ();
      *x = allocation.x;
      break;
    }
}

static void
button_toggled_cb (GtkToggleButton* button)
{
  if (gtk_toggle_button_get_active (button))
    {
      GtkWidget* item = NULL;
      GList    * window;

      g_return_if_fail (!menu);

      menu = g_object_ref_sink (gtk_menu_new ());
      item = gtk_menu_item_new_with_label (wnck_workspace_get_name (PRIV (button)->workspace));
      gtk_widget_set_sensitive (item, FALSE);
#if 0
      g_signal_connect (item, "select",
                        G_CALLBACK (select_cb), PRIV (button)->workspace);
      g_signal_connect (item, "deselect",
                        G_CALLBACK (unselect_cb), PRIV (button)->workspace);
#endif
      gtk_widget_show (item);
      gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

      item = gtk_separator_menu_item_new ();
      gtk_widget_show (item);
      gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

      for (window = wnck_screen_get_windows (wnck_workspace_get_screen (PRIV (button)->workspace)); window; window = window->next)
        {
          if (!wnck_window_is_on_workspace (window->data, PRIV (button)->workspace) ||
              (wnck_window_get_state (window->data) & WNCK_WINDOW_STATE_SKIP_TASKLIST))
            {
              continue;
            }

          item = window_menu_item_new (window->data);
          gtk_widget_show (item);
          gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
        }

      gtk_menu_attach_to_widget (GTK_MENU (menu),
                                 GTK_WIDGET (button),
                                 NULL);

      gtk_menu_set_screen (GTK_MENU (menu),
                           gtk_widget_get_screen (GTK_WIDGET (button)));
      gtk_menu_popup (GTK_MENU (menu),
                      NULL, NULL,
                      menu_position_func, button,
                      0, gtk_get_current_event_time ());

      g_object_add_weak_pointer (G_OBJECT (menu), (gpointer*)&menu);

      g_signal_connect (menu, "selection-done",
                        G_CALLBACK (untoggle), button);
    }
}

static void
workspace_button_init (WorkspaceButton* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, WORKSPACE_TYPE_BUTTON, WorkspaceButtonPrivate);
  PRIV (self)->label = wb_label_new ();
  gtk_label_set_ellipsize (GTK_LABEL (PRIV (self)->label), PANGO_ELLIPSIZE_MIDDLE);
  gtk_widget_show (PRIV (self)->label);
  gtk_container_add (GTK_CONTAINER (self), PRIV (self)->label);
}

static void
get_property ()
{
  g_warning ("%s(%s): FIXME: unimplemented", G_STRFUNC, G_STRLOC);
}

static void
set_active_window (WorkspaceButton* self,
                   WnckWindow     * window)
{
  if (PRIV (self)->active == window)
    {
      return;
    }

  if (PRIV (self)->active)
    {
      PRIV (self)->active = NULL;
    }

  if (window)
    {
      PRIV (self)->active = window;

      gtk_label_set_text (GTK_LABEL (PRIV (self)->label),
                          wnck_window_get_name (PRIV (self)->active));

      if (pango_layout_is_ellipsized (gtk_label_get_layout (GTK_LABEL (PRIV (self)->label))))
        {
          gtk_widget_set_tooltip_text (PRIV (self)->label,
                                       wnck_window_get_name (PRIV (self)->active));
        }
      // FIXME: connect to window state changes
    }
  else
    {
      gtk_label_set_text (GTK_LABEL (PRIV (self)->label),
                          wnck_workspace_get_name (PRIV (self)->workspace));
    }
}

static void
active_window_changed (WnckScreen* screen,
                       WnckWindow* previous,
                       gpointer    user_data)
{
  WorkspaceButton* self = user_data;
  WnckWindow     * current = wnck_screen_get_active_window (screen);

  if (current && wnck_window_is_on_workspace (current, PRIV (self)->workspace))
    {
      set_active_window (self, current);
    }
  else if (previous && wnck_window_is_on_workspace (previous, PRIV (self)->workspace))
    {
      set_active_window (self, previous);
    }
}

static void
window_closed (WnckScreen* screen,
               WnckWindow* window,
               gpointer    user_data)
{
  if (window == PRIV (user_data)->active)
    {
      set_active_window (user_data, NULL);
    }
}

static void
set_property (GObject     * object,
              guint         prop_id,
              GValue const* value,
              GParamSpec  * pspec)
{
  switch (prop_id)
    {
    case PROP_WORKSPACE:
      /* FIXME: update to renames */
      g_return_if_fail (!PRIV (object)->workspace);
      g_return_if_fail (g_value_get_object (value));
      g_return_if_fail (G_VALUE_HOLDS (value, WNCK_TYPE_WORKSPACE));

      PRIV (object)->workspace = g_value_get_object (value);
      gtk_label_set_text (GTK_LABEL (PRIV (object)->label),
                          wnck_workspace_get_name (PRIV (object)->workspace));

      g_signal_connect (wnck_workspace_get_screen (PRIV (object)->workspace), "active-window-changed",
                        G_CALLBACK (active_window_changed), object);
      g_signal_connect (wnck_workspace_get_screen (PRIV (object)->workspace), "window-closed",
                        G_CALLBACK (window_closed), object);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
workspace_button_class_init (WorkspaceButtonClass* self_class)
{
  GObjectClass        * object_class = G_OBJECT_CLASS (self_class);
  GtkToggleButtonClass* toggle_class = GTK_TOGGLE_BUTTON_CLASS (self_class);

  object_class->get_property = get_property;
  object_class->set_property = set_property;

  g_object_class_install_property (object_class, PROP_WORKSPACE,
                                   g_param_spec_object ("workspace", NULL, NULL,
                                                        WNCK_TYPE_WORKSPACE,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

  toggle_class->toggled = button_toggled_cb;

  g_type_class_add_private (self_class, sizeof (WorkspaceButtonPrivate));
}

GtkWidget*
workspace_button_new (WnckWorkspace* workspace)
{
  return g_object_new (WORKSPACE_TYPE_BUTTON,
                       "workspace", workspace,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
