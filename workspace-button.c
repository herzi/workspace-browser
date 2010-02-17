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
#include "window-menu-item.h"
#include <glib/gi18n.h>

struct _WorkspaceButtonPrivate
{
  WnckWorkspace* workspace;
};

enum
{
  PROP_0,
  PROP_WORKSPACE
};

#define PRIV(i) (((WorkspaceButton*)(i))->_private)

static GtkWidget* menu = NULL;

G_DEFINE_TYPE (WorkspaceButton, workspace_button, GTK_TYPE_TOGGLE_BUTTON);

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
      g_signal_connect (item, "select",
                        G_CALLBACK (select_cb), PRIV (button)->workspace);
      g_signal_connect (item, "deselect",
                        G_CALLBACK (unselect_cb), PRIV (button)->workspace);
      gtk_widget_show (item);
      gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

      item = gtk_separator_menu_item_new ();
      gtk_widget_show (item);
      gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

      for (window = wnck_screen_get_windows (wnck_workspace_get_screen (PRIV (button)->workspace)); window; window = window->next)
        {
          if (!wnck_window_is_on_workspace (window->data, PRIV (button)->workspace) ||
              (wnck_window_get_state (window->data) & WNCK_WINDOW_STATE_SKIP_PAGER))
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
workspace_button_init (WorkspaceButton* self)
{
  PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self, WORKSPACE_TYPE_BUTTON, WorkspaceButtonPrivate);
}

static void
get_property ()
{
  g_warning ("%s(%s): FIXME: unimplemented", G_STRFUNC, G_STRLOC);
}

static void
set_property (GObject     * object,
              guint         prop_id,
              GValue const* value,
              GParamSpec  * pspec)
{
  switch (prop_id)
    {
      GtkWidget* label;
    case PROP_WORKSPACE:
      /* FIXME: update to renames */
      g_return_if_fail (!PRIV (object)->workspace);
      PRIV (object)->workspace = g_value_get_object (value);
      /* FIXME: create label in init */
      label = gtk_label_new (wnck_workspace_get_name (PRIV (object)->workspace));
      gtk_widget_show (label);
      gtk_container_add (GTK_CONTAINER (object), label);
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
