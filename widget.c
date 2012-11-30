#include <Elementary.h>
#include "common.h"
#include "gui.h"

Evas_Object *
_widget_bg_create(const char *style)
{
   Evas_Object *bg;
   bg = elm_bg_add(win);
   if (style) elm_object_style_set(bg, style);
   evas_object_show(bg);
   return bg;
}

Evas_Object *
_widget_frame_create(const char *style)
{
   Evas_Object *fr;
   char buf[40];

   fr = elm_frame_add(win);
   EXPAND(fr); FILL(fr);
   sprintf(buf, "%s Style.", style);
   elm_object_text_set(fr, buf);
   evas_object_show(fr);

   return fr;
}

Evas_Object *
_widget_button_create(const char* style)
{
   Evas_Object *btn;
   btn = elm_button_add(win);
   elm_object_style_set(btn, style);
   elm_object_text_set(btn, "THIS IS A BUTTON TEST");
   evas_object_show(btn);

   return btn;
}

Evas_Object *
widget_create(const char *widget, const char *style)
{
   Evas_Object *o = NULL;

   if (!widget && !style)
     o = _widget_bg_create(NULL);
   else if (!strcmp(widget, "bg"))
     o = _widget_bg_create(style);
   else if (!strcmp(widget, "button"))
     o = _widget_button_create(style);
   else if (!strcmp(widget, "frame"))
     o = _widget_frame_create(style);
   else
     o = _widget_bg_create(NULL);
   return o;
}
