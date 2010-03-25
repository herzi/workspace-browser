#include <string.h>

#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "workspace-browser.h"

static void
popup_about_dialog (BonoboUIComponent* component,
                    gpointer           user_data,
                    gchar const      * verbname)
{
  static GtkWidget* dialog = NULL;

  if (!dialog)
    {
      dialog = gtk_about_dialog_new ();
#if 0
      gtk_about_dialog_set_artists ();
      gtk_about_dialog_set_authors ();
      gtk_about_dialog_set_comments ();
      gtk_about_dialog_set_copyright ();
      gtk_about_dialog_set_documenters ();
      gtk_about_dialog_set_license ();
      gtk_about_dialog_set_wrap_license ();
      gtk_about_dialog_set_logo (); or gtk_about_dialog_set_logo_icon_name ();
      gtk_about_dialog_set_program_name ();
      gtk_about_dialog_set_translator_credits ();
      gtk_about_dialog_set_version ();
      gtk_about_dialog_set_website ();
      gtk_about_dialog_set_website_label ();
#endif
    }

  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_hide (dialog);
}

static gboolean
hello_applet_fill (PanelApplet *applet,
                   const gchar *iid,
                   gpointer     data)
{
  BonoboUIVerb verbs[] =
    {
      BONOBO_UI_VERB ("WorkspaceBrowserAbout", popup_about_dialog),
      BONOBO_UI_VERB_END
    };
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

  panel_applet_set_flags  (applet, PANEL_APPLET_EXPAND_MAJOR | PANEL_APPLET_EXPAND_MINOR | PANEL_APPLET_HAS_HANDLE);
  panel_applet_setup_menu (applet,
                           "<Root>"
                             "<popups>"
                               "<popup name=\"button3\">"
#if 0
                                 "<menuitem name=\"Tasklist Preferences Item\" verb=\"WorkspaceBrowserPreferences\" _label=\"_Preferences\" "
                                           "pixtype=\"stock\" pixname=\"gtk-properties\"/>"
                                 "<menuitem name=\"Tasklist Help Item\" verb=\"WorkspaceBrowserHelp\" _label=\"_Help\" "
                                           "pixtype=\"stock\" pixname=\"gtk-help\"/>"
#endif
                                 "<menuitem name=\"Tasklist About Item\" verb=\"WorkspaceBrowserAbout\" _label=\"_About\""
                                           "pixtype=\"stock\" pixname=\"gnome-stock-about\"/>"
                               "</popup>"
                             "</popups>"
                           "</Root>",
                           verbs,
                           applet);

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
