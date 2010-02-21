#include <string.h>

#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "workspace-browser.h"

static gboolean
hello_applet_fill (PanelApplet *applet,
                   const gchar *iid,
                   gpointer     data)
{
  GtkWidget *label;

  gtk_rc_parse_string ("style \"workspace-browser-applet-button-style\"\n"
                       "    {\n"
                       "         GtkWidget::focus-line-width=0\n"
                       "         GtkWidget::focus-padding=0\n"
                       "    }\n"
                       "\n"
                       "  widget \"*.workspace-button\" style \"workspace-browser-applet-button-style\"\n");

  if (strcmp (iid, "OAFIID:Herzis_WorkspaceBrowserApplet") != 0)
    return FALSE;

  panel_applet_set_flags (applet,
                          PANEL_APPLET_EXPAND_MAJOR | PANEL_APPLET_EXPAND_MINOR | PANEL_APPLET_HAS_HANDLE);

  label = workspace_browser_new ();
  gtk_container_add (GTK_CONTAINER (applet), label);

  gtk_widget_show_all (GTK_WIDGET (applet));

  return TRUE;
}


PANEL_APPLET_BONOBO_FACTORY ("OAFIID:Herzis_WorkspaceBrowserApplet_Factory",
                             PANEL_TYPE_APPLET,
                             "WorkspaceBrowserApplet",
                             "0",
                             hello_applet_fill,
                             NULL);

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
