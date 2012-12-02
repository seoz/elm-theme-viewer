#include <Elementary.h>
#include "common.h"
#include "gui.h"
#include "log.h"
#include "theme.h"

/*
 * Get the second part from the orig_style
 *
 * base/default -> default (actionslider)
 * base/hoversel_horizontal/entry -> hoversel_horizontal (button)
 * item/default/default -> default (genlist item)
 * item/full/default -> full (genlist item)
 */
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

/* Remove "/default" from the end of string.
 *
 * arrow_left/default -> arrow_left (icon)
 * separator/default -> separator (menu)
 */
static void
_trim_end_default(const char *orig_style, char *style)
{
   strncpy(style, orig_style, strlen(orig_style));
   style[strlen(orig_style) - strlen("/default")] = '\0';
   //INF("%s %s", style, orig_style);
}

Evas_Object *
_widget_not_implemented_create(const char *widget)
{
   Evas_Object *o;
   char buf[PATH_MAX] = {0, };

   o = elm_label_add(win);
   EXPAND(o); FILL(o);
   sprintf(buf, "Sorry, %s widget sample is not implemented yet.", widget);
   elm_object_text_set(o, buf);
   evas_object_show(o);

   return o;
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

static char *
_widget_gengrid_text_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[256];
   snprintf(buf, sizeof(buf),
            "Item # %i - elm-theme-viewer is an awesome program!",
            (int)(long)data);
   return strdup(buf);
}

static Evas_Object *
_widget_gengrid_content_get(void *data, Evas_Object *obj, const char *part)
{
   Evas_Object *o = NULL;
   char buf[PATH_MAX] = {0, };
   int i = ((int)(long)data % 4) + 1;

   if (!strcmp(part, "elm.swallow.icon"))
     {
        o = elm_bg_add(obj);
        snprintf(buf, sizeof(buf),
                 "%s/images/sky_0%d.jpg", elm_app_data_dir_get(), i);
printf("%s\n", buf);

        elm_bg_file_set(o, buf, NULL);
        evas_object_size_hint_aspect_set(o, EVAS_ASPECT_CONTROL_VERTICAL,
                                         1, 1);
        evas_object_show(o);
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        o = elm_check_add(obj);
        evas_object_propagate_events_set(o, EINA_FALSE);
        evas_object_show(o);
     }
   return o;
}

static Evas_Object *
_widget_gengrid_create(const char *orig_style, const char *style)
{
   Evas_Object *o;
   Elm_Genlist_Item_Class *ic;
   int i = 0;
   char buf[PATH_MAX] = {0, };

   o = elm_gengrid_add(win);
   elm_gengrid_item_size_set(o, 150, 150);
   EXPAND(o); FILL(o);
   evas_object_show(o);

   ic = elm_gengrid_item_class_new();
   ic->func.text_get = _widget_gengrid_text_get;
   ic->func.content_get = _widget_gengrid_content_get;
   ic->func.state_get = NULL;
   ic->func.del = NULL;

   strncpy(buf, orig_style, sizeof(buf));
   if (!strncmp("item", strtok(buf, "/"), 4))
     ic->item_style = style;
  else
     elm_object_style_set(o, style);

   for (i = 0; i < 50; i++)
     {
        elm_gengrid_item_append(o, ic, (void *)(long)i, NULL, NULL);
     }

   elm_gengrid_item_class_free(ic);

   return o;
}

static char *
_widget_genlist_text_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[256];
   snprintf(buf, sizeof(buf),
            "Item # %i - elm-theme-viewer is an awesome program!",
            (int)(long)data);
   return strdup(buf);
}

static Evas_Object *
_widget_genlist_content_get(void *data, Evas_Object *obj, const char *part)
{
   Evas_Object *ic = elm_icon_add(obj);
   if (!strcmp(part, "elm.swallow.end"))
     elm_icon_standard_set(ic, "folder");
   else
     elm_icon_standard_set(ic, "home");
   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

static Evas_Object *
_widget_genlist_create(const char *orig_style, const char *style)
{
   Evas_Object *o;
   Elm_Genlist_Item_Class *ic;
   int i = 0;
   char buf[PATH_MAX] = {0, };

   o = elm_genlist_add(win);
   EXPAND(o); FILL(o);
   evas_object_show(o);

   ic = elm_genlist_item_class_new();
   ic->func.text_get = _widget_genlist_text_get;
   ic->func.content_get = _widget_genlist_content_get;
   ic->func.state_get = NULL;
   ic->func.del = NULL;

   strncpy(buf, orig_style, sizeof(buf));
   if (!strncmp("item", strtok(buf, "/"), 4))
     ic->item_style = style;
  else
     elm_object_style_set(o, style);

   for (i = 0; i < 50; i++)
     {
        elm_genlist_item_append(o, ic, (void *)(long)i, NULL,
                                ELM_GENLIST_ITEM_NONE, NULL, NULL);
     }

   elm_genlist_item_class_free(ic);

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

   _trim_end_default(orig_style, style);

   o = elm_icon_add(win);
   EXPAND(o);
   elm_icon_standard_set(o, style);
   evas_object_size_hint_min_set(o, 100, 100);
   evas_object_show(o);

   return o;
}

Evas_Object *
_widget_label_create(const char *style)
{
   Evas_Object *o;
   char buf[PATH_MAX] = {0, };

   o = elm_label_add(win);
   EXPAND(o); FILL(o);
   sprintf(buf, "This is a %s style label.", style);
   elm_object_text_set(o, buf);
   elm_object_style_set(o, style);
   evas_object_show(o);

   return o;
}

static Evas_Object *
_widget_layout_content_create(Evas_Object *layout)
{
   Evas_Object *table, *bg, *lbl;

   table = elm_table_add(layout);
   EXPAND(table); FILL(table);
   evas_object_show(table);

   bg = elm_bg_add(win);
   EXPAND(bg); FILL(bg);
   elm_bg_color_set(bg, 100, 100, 100);
   elm_table_pack(table, bg, 0, 0, 1, 1);
   evas_object_show(bg);

   lbl = elm_label_add(win);
   EXPAND(lbl); FILL(lbl);
   elm_object_text_set(lbl, "This dark area is a content area.");
   elm_table_pack(table, lbl, 0, 0, 1, 1);
   evas_object_show(lbl);

   return table;
}

static void
_widget_layout_icon_create(Evas_Object *layout)
{
   Evas_Object *ic;

   ic = elm_icon_add(win);
   elm_icon_standard_set(ic, "chat");
   evas_object_size_hint_min_set(ic, 20, 20);
   elm_layout_icon_set(layout, ic);
}

static void
_widget_layout_end_create(Evas_Object *layout)
{
   Evas_Object *ic;

   ic = elm_icon_add(win);
   elm_icon_standard_set(ic, "close");
   evas_object_size_hint_min_set(ic, 20, 20);
   elm_layout_end_set(layout, ic);
}

static Evas_Object *
_widget_layout_create(const char *style)
{
   Evas_Object *o, *lbl, *content;

   o = elm_layout_add(win);
   elm_layout_theme_set(o, "layout", "application", style);
   EXPAND(o); FILL(o);
   evas_object_show(o);

   if (!strcmp("toolbar-content", style))
     {
        content = _widget_layout_content_create(o);
        elm_layout_content_set(o, "elm.swallow.content", content);
     }
   else if (!strcmp("toolbar-content-back", style))
     {
        elm_object_part_text_set(o, "elm.text.title", "Layout Title");
        _widget_layout_end_create(o);
        content = _widget_layout_content_create(o);
        elm_layout_content_set(o, "elm.swallow.content", content);
     }
   else if (!strcmp("toolbar-content-back-next", style))
     {
        elm_object_part_text_set(o, "elm.text.title", "Layout Title");
        elm_object_part_text_set(o, "elm.text.title", "Layout Title");
        content = _widget_layout_content_create(o);
        elm_layout_content_set(o, "elm.swallow.content", content);
     }
   else if (!strcmp("content-back", style))
     {
        elm_object_part_text_set(o, "elm.text.title", "Layout Title");
        _widget_layout_end_create(o);
        content = _widget_layout_content_create(o);
        elm_layout_content_set(o, "elm.swallow.content", content);
     }
   else if (!strcmp("content-back-next", style))
     {
        elm_object_part_text_set(o, "elm.text.title", "Layout Title");
        content = _widget_layout_content_create(o);
        elm_layout_content_set(o, "elm.swallow.content", content);
     }
   else if (!strcmp("titlebar", style))
     {
        elm_object_part_text_set(o, "elm.text", "Layout Title");
        _widget_layout_icon_create(o);
        _widget_layout_end_create(o);
        content = _widget_layout_content_create(o);
        elm_layout_content_set(o, "elm.swallow.content", content);
     }
   else if (!strcmp("toolbar-table", style))
     {
        content = _widget_layout_content_create(o);
        elm_layout_table_pack(o, "elm.table.content", content, 0, 0, 1, 1);

        lbl = elm_label_add(win);
        elm_object_text_set(lbl, "This area is also a content area which packed into a table.");
        EXPAND(lbl); FILL(lbl);
        evas_object_show(lbl);
        elm_layout_table_pack(o, "elm.table.content", lbl, 0, 1, 1, 1);

        lbl = elm_label_add(win);
        elm_object_text_set(lbl, "This area is also a content area which packed into a table.");
        EXPAND(lbl); FILL(lbl);
        evas_object_show(lbl);
        elm_layout_table_pack(o, "elm.table.content", lbl, 1, 0, 1, 1);

        content = _widget_layout_content_create(o);
        elm_layout_table_pack(o, "elm.table.content", content, 1, 1, 1, 1);
     }
   else if (!strcmp("toolbar-vbox", style))
     {
        content = _widget_layout_content_create(o);
        elm_layout_box_append(o, "elm.box.content", content);

        lbl = elm_label_add(win);
        elm_object_text_set(lbl, "This area is also a content area which packed into a box.");
        EXPAND(lbl); FILL(lbl);
        evas_object_show(lbl);
        elm_layout_box_append(o, "elm.box.content", lbl);
     }

   return o;
}

static void
_widget_menu_resize(void *data, Evas *evas, Evas_Object *obj, void *event)
{
   Evas_Coord w, h;
   Evas_Object *rect = data;

   evas_object_geometry_get(obj, NULL, NULL, &w, &h);
   evas_object_resize(rect, w, h);
}

static void
_widget_menu_show(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
   Evas_Event_Mouse_Down *ev = event_info;
   elm_menu_move(data, ev->canvas.x, ev->canvas.y);
   evas_object_show(data);
}

static Evas_Object *
_widget_menu_create(const char *orig_style)
{
   Evas_Object *o, *rect, *table, *lbl;
   Elm_Object_Item *menu_it;
   char style[PATH_MAX] = {0, };

   _trim_end_default(orig_style, style);

   table = elm_table_add(win);
   EXPAND(table); FILL(table);
   evas_object_show(table);

   rect = evas_object_rectangle_add(evas_object_evas_get(win));
   EXPAND(rect); FILL(rect);
   evas_object_color_set(rect, 100, 100, 100, 255);
   elm_table_pack(table, rect, 0, 0, 1, 1);
   evas_object_show(rect);

   lbl = elm_label_add(table);
   EXPAND(lbl); FILL(lbl);
   elm_object_text_set(lbl, "Click this dark area.");
   elm_table_pack(table, lbl, 0, 0, 1, 1);
   evas_object_repeat_events_set(lbl, EINA_TRUE);
   evas_object_show(lbl);

   o = elm_menu_add(win);
   if (!strcmp("item", style))
     {
        elm_menu_item_add(o, NULL, NULL, "first item", NULL, NULL);
        elm_menu_item_add(o, NULL, "mail-reply-all", "second item", NULL, NULL);
        elm_menu_item_add(o, NULL, "window-new", "third item", NULL, NULL);
     }
   else if (!strcmp("item_with_submenu", style))
     {
        elm_menu_item_add(o, NULL, NULL, "first item", NULL, NULL);
        menu_it = elm_menu_item_add(o, NULL, "mail-reply-all", "second item", NULL, NULL);
        elm_menu_item_add(o, menu_it, NULL, "first sub menu", NULL, NULL);
        elm_menu_item_add(o, menu_it, "mail-reply-all", "second sub menu", NULL, NULL);
     }
   else if (!strcmp("separator", style))
     {
        elm_menu_item_add(o, NULL, NULL, "between separator", NULL, NULL);
        elm_menu_item_separator_add(o, NULL);
        elm_menu_item_add(o, NULL, NULL, "between separator", NULL, NULL);
        elm_menu_item_separator_add(o, NULL);
        elm_menu_item_add(o, NULL, NULL, "between separator", NULL, NULL);
     }

   evas_object_event_callback_add(win, EVAS_CALLBACK_RESIZE,
                                  _widget_menu_resize, rect);
   evas_object_event_callback_add(rect, EVAS_CALLBACK_MOUSE_DOWN,
                                  _widget_menu_show, o);

   return table;
}

Evas_Object *
_widget_progressbar_create(const char *style2)
{
   char buf[PATH_MAX] = {0, };
   const char *style;
   Evas_Object *o;

   o = elm_progressbar_add(win);
   EXPAND(o); FILL(o);
   elm_progressbar_pulse(o, EINA_TRUE);
   evas_object_show(o);

   strncpy(buf, style2, sizeof(buf));
   style = strtok(buf, "/");
   if (!strcmp("vertical", style))
     elm_progressbar_horizontal_set(o, EINA_FALSE);
   style = strtok(NULL, "/");

   elm_object_style_set(o, style);
   elm_object_text_set(o, style);

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
_widget_spinner_create(const char *style)
{
   Evas_Object *o;

   o = elm_spinner_add(win);

   elm_spinner_min_max_set(o, -50.0, 250.0);
   EXPAND(o);
   ALIGN(o, EVAS_HINT_FILL, 0.5);

   elm_spinner_label_format_set(o, "%1.1f units");
   elm_spinner_step_set(o, 1.3);
   elm_spinner_wrap_set(o, EINA_TRUE);

   if (!strcmp("vertical", style))
     elm_object_style_set(o, "vertical");
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
   //INF("widget : %s, orig_style : %s, style : %s", widget, orig_style, style);

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
   else if (!strcmp(widget, "gengrid"))
     o = _widget_gengrid_create(orig_style, style);
   else if (!strcmp(widget, "genlist"))
     o = _widget_genlist_create(orig_style, style);
   else if (!strcmp(widget, "hover"))
     o = _widget_hover_create(style);
   else if (!strcmp(widget, "icon"))
     o = _widget_icon_create(orig_style);
   else if (!strcmp(widget, "label"))
     o = _widget_label_create(style);
   else if (!strcmp(widget, "layout"))
     o = _widget_layout_create(style);
   else if (!strcmp(widget, "menu"))
     o = _widget_menu_create(orig_style);
   else if (!strcmp(widget, "progressbar"))
     o = _widget_progressbar_create(orig_style);
   else if (!strcmp(widget, "separator"))
     o = _widget_separator_create(style, orig_style);
   else if (!strcmp(widget, "spinner"))
     o = _widget_spinner_create(style);
   else
     o = _widget_not_implemented_create(widget);
   elm_object_theme_set(o, th);
   return o;
}
