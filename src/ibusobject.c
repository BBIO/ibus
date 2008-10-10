/* vim:set et sts=4: */
/* ibus - The Input Bus
 * Copyright (C) 2008-2009 Huang Peng <shawn.p.huang@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "ibusobject.h"
#include "ibusinternel.h"

enum {
    DESTROY,
    LAST_SIGNAL,
};

static guint            _signals[LAST_SIGNAL] = { 0 };

/* functions prototype */
static void     ibus_object_class_init      (IBusObjectClass  *klass);
static void     ibus_object_init            (IBusObject       *client);
static void     ibus_object_finalize        (GObject            *obj);

static GObjectClass *_parent_class = NULL;


GType
ibus_object_get_type (void)
{
    static GType type = 0;
    
    static const GTypeInfo type_info = {
        sizeof (IBusObjectClass),
        (GBaseInitFunc)     NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc)    ibus_object_class_init,
        NULL,               /* class finialize */
        NULL,               /* class data */
        sizeof (IBusObject),
        0,
        (GInstanceInitFunc) ibus_object_init,
    };

    if (type == 0) {
        type = g_type_register_static (G_TYPE_OBJECT,
                    "IBusObject",
                    &type_info,
                    (GTypeFlags)0);
    }
    
    return type;
}

IBusObject *
ibus_object_new (void)
{
    return IBUS_OBJECT (g_object_new (IBUS_TYPE_OBJECT, NULL));
}

static void
ibus_object_class_init     (IBusObjectClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

    _parent_class = (GObjectClass *) g_type_class_peek_parent (klass);

    gobject_class->finalize = ibus_object_finalize;

    _signals[DESTROY] =
        g_signal_new (I_("destroy"),
            G_TYPE_FROM_CLASS (gobject_class),
            G_SIGNAL_RUN_FIRST,
            G_STRUCT_OFFSET (IBusObjectClass, destroy),
            NULL, NULL,
            ibus_marshal_VOID__VOID,
            G_TYPE_NONE, 0);
}

static void
ibus_object_init (IBusObject *obj)
{
}


static void
ibus_object_finalize (GObject *obj)
{
    g_signal_emit (obj, _signals[DESTROY], 0);
    G_OBJECT_CLASS(_parent_class)->finalize (obj);
}


