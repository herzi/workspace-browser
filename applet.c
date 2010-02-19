#include <string.h>

#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "applet.h"

static gboolean
hello_applet_fill (PanelApplet *applet,
                   const gchar *iid,
                   gpointer     data)
{
        GtkWidget *label;

        if (strcmp (iid, "OAFIID:My_HelloApplet") != 0)
                return FALSE;

        label = gtk_label_new ("Hello World");
        gtk_widget_set_tooltip_text (label, REVISION);
        gtk_container_add (GTK_CONTAINER (applet), label);

        gtk_widget_show_all (GTK_WIDGET (applet));

        return TRUE;
}


PANEL_APPLET_BONOBO_FACTORY ("OAFIID:My_HelloApplet_Factory",
                             PANEL_TYPE_APPLET,
                             "TheHelloWorldApplet",
                             "0",
                             hello_applet_fill,
                             NULL);

