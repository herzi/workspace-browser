#include <string.h>

#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "applet.h"
#include "workspace-browser.h"

static gboolean
hello_applet_fill (PanelApplet *applet,
                   const gchar *iid,
                   gpointer     data)
{
        GtkWidget *label;

        if (strcmp (iid, "OAFIID:Herzis_WorkspaceBrowserApplet") != 0)
                return FALSE;

        panel_applet_set_flags (applet, PANEL_APPLET_HAS_HANDLE);

        label = workspace_browser_new ();
        gtk_widget_set_tooltip_text (label, REVISION);
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

