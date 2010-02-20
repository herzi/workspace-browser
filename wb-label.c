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

#include "wb-label.h"

G_DEFINE_TYPE (WbLabel, wb_label, GTK_TYPE_LABEL);

static void
wb_label_init (WbLabel* self)
{}

static void
size_allocate (GtkWidget    * widget,
               GtkAllocation* allocation)
{
  GTK_WIDGET_CLASS (wb_label_parent_class)->size_allocate (widget, allocation);

  if (pango_layout_is_ellipsized (gtk_label_get_layout (GTK_LABEL (widget))))
    {
      gtk_widget_set_tooltip_text (widget, gtk_label_get_text (GTK_LABEL (widget)));
    }
  else
    {
      gtk_widget_set_tooltip_text (widget, NULL);
    }
}

static void
wb_label_class_init (WbLabelClass* self_class)
{
  GtkWidgetClass* widget_class = GTK_WIDGET_CLASS (self_class);

  widget_class->size_allocate = size_allocate;
}

GtkWidget*
wb_label_new (void)
{
  return g_object_new (WB_TYPE_LABEL,
                       NULL);
}

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
