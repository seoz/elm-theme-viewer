#include <Elementary.h>
#include "common.h"
#include "gui.h"
#include "log.h"
#include "theme.h"

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
   EXPAND(as); ALIGN(as, EVAS_HINT_FILL, 0);
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
   EXPAND(bg); FILL(bg);
   if (style) elm_object_style_set(bg, style);
   evas_object_show(bg);
   return bg;
}

Evas_Object *
_widget_button_create(const char* style)
{
   Evas_Object *btn;
   btn = elm_button_add(win);
   EXPAND(btn); ALIGN(btn, EVAS_HINT_FILL, 0);
   elm_object_style_set(btn, style);
   elm_object_text_set(btn, "THIS IS A BUTTON TEST");
   evas_object_show(btn);

   return btn;
}

Evas_Object *
_widget_clock_create(const char* style)
{
   Evas_Object *o;
   o = elm_clock_add(win);
   EXPAND(o);
   elm_object_style_set(o, style);
   evas_object_show(o);

   return o;
}

Evas_Object *
_widget_entry_create(const char* style)
{
   char buf[PATH_MAX];

   Evas_Object *o;
   o = elm_entry_add(win);
   EXPAND(o); FILL(o);
   elm_object_style_set(o, style);
   snprintf(buf, sizeof(buf),
            "This is an entry widget in this window that<br/>"
            "uses markup <b>like this</> for styling and<br/>");
   elm_object_text_set(o, buf);
   evas_object_show(o);

   return o;
}

Evas_Object *
_widget_check_create(const char *style)
{
   Evas_Object *o;
   o = elm_check_add(win);
   EXPAND(o);
   if (style) elm_object_style_set(o, style);
   evas_object_show(o);
   return o;
}

Evas_Object *
_widget_frame_create(const char *style)
{
   Evas_Object *o, *lbl;
   char buf[PATH_MAX];

   o = elm_frame_add(win);
   elm_object_style_set(o, style);
   EXPAND(o); ALIGN(o, EVAS_HINT_FILL, 0);
   elm_object_text_set(o, "Frame Styles");
   evas_object_show(o);

   lbl = elm_label_add(win);
   sprintf(buf, "This is a %s style frame.", style);
   elm_object_text_set(lbl, buf);
   elm_object_content_set(o, lbl);
   evas_object_show(lbl);

   return o;
}

Evas_Object *
_widget_fileselector_create(const char *style)
{
   Evas_Object *o;
   char buf[40];

   o = elm_fileselector_add(win);
   EXPAND(o); FILL(o);
   elm_fileselector_is_save_set(o, EINA_TRUE);
   elm_fileselector_expandable_set(o, EINA_FALSE);
   elm_fileselector_path_set(o, getenv("HOME"));
   EXPAND(o); FILL(o);
   sprintf(buf, "%s Style.", style);
   elm_object_text_set(o, buf);
   evas_object_show(o);

   return o;
}

static void
_hover_bt_cb(void *data, Evas_Object *obj, void *event_info)
{
   evas_object_show(data);
}

Evas_Object *
_widget_hover_create(const char* style)
{
   Evas_Object *hv, *bt, *bt2;

   hv = elm_hover_add(win);
   elm_object_style_set(hv, style);

   bt = elm_button_add(win);
   EXPAND(bt); ALIGN(bt, EVAS_HINT_FILL, 0);
   elm_object_text_set(bt, "click here to see hover");
   evas_object_smart_callback_add(bt, "clicked", _hover_bt_cb, hv);
   elm_hover_parent_set(hv, win);
   elm_hover_target_set(hv, bt);
   evas_object_show(bt);

   bt2 = elm_button_add(win);
   elm_object_text_set(bt2, "Popup");
   elm_object_part_content_set(hv, "middle", bt2);
   evas_object_show(bt2);

   return bt;
}

Evas_Object *
_widget_icon_create(const char *orig_style)
{
   Evas_Object *o;
   char style[PATH_MAX] = {0, };

   strncpy(style, orig_style, strlen(orig_style));
   style[strlen(orig_style) - strlen("/default")] = '\0';
   INF("%s %d %d", style, strlen(orig_style), strlen("/default"));

   o = elm_icon_add(win);
   EXPAND(o);
   elm_icon_standard_set(o, style);
   evas_object_size_hint_min_set(o, 100, 100);
   evas_object_show(o);

   return o;
}

Evas_Object *
_widget_separator_create(const char *style, const char *orig_style)
{
   Evas_Object *o;

   char buf[PATH_MAX] = {0, };
   const char *type;

   strncpy(buf, orig_style, sizeof(buf));
   type = strtok(buf, "/");
   //INF("%s", type);

   o = elm_separator_add(win);
   if (!strcmp("horizontal", type))
     {
        ALIGN(o, EVAS_HINT_FILL, 0);
        elm_separator_horizontal_set(o, EINA_TRUE);
     }
   else
     ALIGN(o, 0, EVAS_HINT_FILL);
   evas_object_show(o);

   return o;
}

Evas_Object *
widget_create(const char *widget, const char *orig_style)
{
   Evas_Object *o = NULL;
   const char *style = NULL;

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
   else if (!strcmp(widget, "clock"))
     o = _widget_clock_create(style);
   else if (!strcmp(widget, "entry"))
     o = _widget_entry_create(style);
   else if (!strcmp(widget, "fileselector"))
     o = _widget_fileselector_create(style);
   else if (!strcmp(widget, "frame"))
     o = _widget_frame_create(style);
   else if (!strcmp(widget, "hover"))
     o = _widget_hover_create(style);
   else if (!strcmp(widget, "icon"))
     o = _widget_icon_create(orig_style);
   else if (!strcmp(widget, "separator"))
     o = _widget_separator_create(style, orig_style);
   else
     o = _widget_bg_create(NULL);
   elm_object_theme_set(o, th);
   return o;
}
