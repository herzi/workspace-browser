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

#ifndef WB_LABEL_H
#define WB_LABEL_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _WbLabel        WbLabel;
typedef struct _WbLabelClass   WbLabelClass;
typedef struct _WbLabelPrivate WbLabelPrivate;

#define WB_TYPE_LABEL         (wb_label_get_type ())
#define WB_LABEL(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), WB_TYPE_LABEL, WbLabel))
#define WB_LABEL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), WB_TYPE_LABEL, WbLabelClass))
#define WB_IS_LABEL(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), WB_TYPE_LABEL))
#define WB_IS_LABEL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), WB_TYPE_LABEL))
#define WB_LABEL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), WB_TYPE_LABEL, WbLabelClass))

GType      wb_label_get_type (void);
GtkWidget* wb_label_new      (void);

struct _WbLabel
{
  GtkLabel        base_instance;
  WbLabelPrivate* _private;
};

struct _WbLabelClass
{
  GtkLabelClass   base_class;
};

G_END_DECLS

#endif /* !WB_LABEL_H */

/* vim:set et sw=2 cino=t0,f0,(0,{s,>2s,n-1s,^-1s,e2s: */
