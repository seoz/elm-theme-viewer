#include <Elementary.h>
#include "common.h"
#include "gui.h"
#include "log.h"

static const char *
_parse_style(const char *orig_style)
{
   char buf[PATH_MAX] = {0, };
   const char *style;

   strncpy(buf, orig_style, sizeof(buf));
   style = strtok(buf, "/");
   style = strtok(NULL, "/");
   //INF("%s", style);

   return style;
}

Evas_Object *
_widget_actionslider_create(const char *style)
{
   Evas_Object *as;

   as = elm_actionslider_add(win);
   if (style) elm_object_style_set(as, style);
   elm_actionslider_indicator_pos_set(as, ELM_ACTIONSLIDER_LEFT);
   elm_actionslider_magnet_pos_set(as, ELM_ACTIONSLIDER_CENTER|
                                   ELM_ACTIONSLIDER_RIGHT);
   elm_actionslider_enabled_pos_set(as, ELM_ACTIONSLIDER_CENTER |
                                    ELM_ACTIONSLIDER_RIGHT);
   elm_object_part_text_set(as, "left", NULL);
   elm_object_part_text_set(as, "center", "Accept");
   elm_object_part_text_set(as, "right", "Reject");
   evas_object_show(as);

   return as;
}

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
_widget_check_create(const char *style)
{
   Evas_Object *o;
   o = elm_check_add(win);
   if (style) elm_object_style_set(o, style);
   evas_object_show(o);
   return o;
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
widget_create(const char *widget, const char *orig_style)
{
   Evas_Object *o = NULL;
   const char *style;

   if (orig_style)
     style = eina_stringshare_add(_parse_style(orig_style));
   if (!widget && !style)
     o = _widget_bg_create(NULL);
   else if (!strcmp(widget, "actionslider"))
     o = _widget_actionslider_create(style);
   else if (!strcmp(widget, "bg"))
     o = _widget_bg_create(style);
   else if (!strcmp(widget, "button"))
     o = _widget_button_create(style);
   else if (!strcmp(widget, "check"))
     o = _widget_check_create(style);
   else if (!strcmp(widget, "frame"))
     o = _widget_frame_create(style);
   else
     o = _widget_bg_create(NULL);
   return o;
}
