#include <Elementary.h>
#include "common.h"
#include "gui.h"
#include "log.h"
#include "theme.h"
#include "widget.h"

Widget widgets[WIDGET_COUNT] = {
   { "none", ETV_ID_NONE, NULL },
   { "access", ETV_ID_ACCESS, NULL },
   { "actionslider", ETV_ID_ACTIONSLIDER, "An actionslider is a switcher for 2 or 3 labels with customizable magnet properties. The user drags and releases the indicator, to choose a label." },
   { "bg", ETV_ID_BG, "Background object, used for setting a solid color, image or Edje group as a background to a window or any container object." },
   { "border", ETV_ID_BORDER, NULL },
   { "bubble", ETV_ID_BUBBLE, NULL },
   { "button", ETV_ID_BUTTON, NULL },
   { "calendar", ETV_ID_CALENDAR, NULL },
   { "check", ETV_ID_CHECK, NULL },
   { "clock", ETV_ID_CLOCK, NULL },
   { "colorselector", ETV_ID_COLORSELECTOR, NULL },
   { "conformant", ETV_ID_CONFORMANT, NULL },
   { "ctxpopup", ETV_ID_CTXPOPUP, NULL },
   { "datetime", ETV_ID_DATETIME, NULL },
   { "dayselector", ETV_ID_DAYSELECTOR, NULL },
   { "diskselector", ETV_ID_DISKSELECTOR, NULL },
   { "entry", ETV_ID_ENTRY, NULL },
   { "ews", ETV_ID_EWS, NULL },
   { "fileselector", ETV_ID_FILESELECTOR, NULL },
   { "fileselector_button", ETV_ID_FILESELECTOR_BUTTON, NULL },
   { "fileselector_entry", ETV_ID_FILESELECTOR_ENTRY, NULL },
   { "flipselector", ETV_ID_FLIPSELECTOR, NULL },
   { "focus_highlight", ETV_ID_FOCUS_HIGHLIGHT, NULL },
   { "frame", ETV_ID_FRAME, NULL },
   { "gengrid", ETV_ID_GENGRID, NULL },
   { "genlist", ETV_ID_GENLIST, NULL },
   { "hover", ETV_ID_HOVER, NULL },
   { "icon", ETV_ID_ICON, NULL },
   { "index", ETV_ID_INDEX, NULL },
   { "label", ETV_ID_LABEL, NULL },
   { "layout", ETV_ID_LAYOUT, NULL },
   { "list", ETV_ID_LIST, NULL },
   { "map", ETV_ID_MAP, NULL },
   { "menu", ETV_ID_MENU, NULL },
   { "multibuttonentry", ETV_ID_MULTIBUTTONENTRY, NULL },
   { "naviframe", ETV_ID_NAVIFRAME, NULL },
   { "notify", ETV_ID_NOTIFY, NULL },
   { "panel", ETV_ID_PANEL, NULL },
   { "panes", ETV_ID_PANES, NULL },
   { "photo", ETV_ID_PHOTO, NULL },
   { "photocam", ETV_ID_PHOTOCAM, NULL },
   { "player", ETV_ID_PLAYER, NULL },
   { "pointer", ETV_ID_POINTER, NULL },
   { "popup", ETV_ID_POPUP, NULL },
   { "progressbar", ETV_ID_PROGRESSBAR, NULL },
   { "radio", ETV_ID_RADIO, NULL },
   { "scroller", ETV_ID_SCROLLER, NULL },
   { "segment_control", ETV_ID_SEGMENT_CONTROL, NULL },
   { "separator", ETV_ID_SEPARATOR, NULL },
   { "slider", ETV_ID_SLIDER, NULL },
   { "slideshow", ETV_ID_SLIDESHOW, NULL },
   { "spinner", ETV_ID_SPINNER, NULL },
   { "thumb", ETV_ID_THUMB, NULL },
   { "toolbar", ETV_ID_TOOLBAR, NULL },
   { "tooltip", ETV_ID_TOOLTIP, NULL },
   { "video", ETV_ID_VIDEO, NULL },
   { "win", ETV_ID_WIN, NULL }
};

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
_widget_not_implemented_create(Widget_Type widget)
{
   Evas_Object *o;
   char buf[PATH_MAX] = {0, };

   o = elm_label_add(win);
   EXPAND(o); FILL(o);
   sprintf(buf, "Sorry, %s widget sample is not implemented yet.",
           widgets[widget].name);
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
_widget_gengrid_grid_check_content_get(void *data, Evas_Object *obj,
                                       const char *part)
{
   Evas_Object *o = NULL;
   char buf[PATH_MAX] = {0, };
   int i = ((int)(long)data % 4) + 1;

   if (!strcmp(part, "elm.swallow.icon"))
     {
        o = elm_bg_add(obj);
        snprintf(buf, sizeof(buf),
                 "%s/images/sky_0%d.jpg", elm_app_data_dir_get(), i);

        elm_bg_file_set(o, buf, NULL);
        evas_object_show(o);
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        o = elm_check_add(obj);
        elm_object_style_set(o, "grid");
        evas_object_propagate_events_set(o, EINA_FALSE);
        evas_object_show(o);
     }
   return o;
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

        elm_bg_file_set(o, buf, NULL);
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
_widget_gengrid_icon_aspect_content_get(void *data, Evas_Object *obj,
                                        const char *part)
{
   Evas_Object *o = NULL;
   char buf[PATH_MAX] = {0, };
   int i = ((int)(long)data % 4) + 1;

   if (!strcmp(part, "elm.swallow.icon"))
     {
        o = elm_bg_add(obj);
        snprintf(buf, sizeof(buf),
                 "%s/images/sky_0%d.jpg", elm_app_data_dir_get(), i);

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

typedef enum {
   GENGRID_NORMAL_STYLE,
   GENGRID_GROUP_INDEX_STYLE,
   GENGRID_DEFAULT_STYLE_STYLE,
   GENGRID_H9_GRID_CHECK_STYLE,
   GENGRID_H9_GROUP_INDEX_STYLE
} Gengrid_Style_Type;

static Evas_Object *
_widget_gengrid_create(const char *orig_style, const char *style)
{
   Evas_Object *o;
   Elm_Genlist_Item_Class *ic, *group_ic;
   int i = 0;
   char buf[PATH_MAX] = {0, };
   Gengrid_Style_Type gst = GENGRID_NORMAL_STYLE;

   /* classify styles */
   if (style && !strcmp("group_index", style))
     gst = GENGRID_GROUP_INDEX_STYLE;
   else if (style && !strcmp("default_style", style))
     gst = GENGRID_DEFAULT_STYLE_STYLE;
   else if (!strcmp("h9 grid-check-style", orig_style))
     gst = GENGRID_H9_GRID_CHECK_STYLE;
   else if (!strcmp("h9 group-index-style", orig_style))
     gst = GENGRID_H9_GROUP_INDEX_STYLE;

   o = elm_gengrid_add(win);
   elm_gengrid_align_set(o, 0, 0);
   elm_gengrid_item_size_set(o,
		   elm_config_scale_get() * 168, elm_config_scale_get() * 168);
   EXPAND(o); FILL(o);
   evas_object_show(o);

   ic = elm_gengrid_item_class_new();
   ic->func.text_get = _widget_gengrid_text_get;
   ic->func.state_get = NULL;
   ic->func.del = NULL;

   /* check for gengrid style or gengrid item style */
   strncpy(buf, orig_style, sizeof(buf));
   if ((gst == GENGRID_H9_GRID_CHECK_STYLE) ||
       (gst == GENGRID_GROUP_INDEX_STYLE) ||
       (gst == GENGRID_H9_GROUP_INDEX_STYLE))
     ic->item_style = "default";
   else if (!strncmp("item", strtok(buf, "/"), 4))
     ic->item_style = style;
   else
     elm_object_style_set(o, style);

   /* check for special custom style for h9 grid-check-style */
   if (gst == GENGRID_H9_GRID_CHECK_STYLE)
     ic->func.content_get = _widget_gengrid_grid_check_content_get;
   else if ((gst == GENGRID_GROUP_INDEX_STYLE) ||
            (gst == GENGRID_DEFAULT_STYLE_STYLE))
     ic->func.content_get = _widget_gengrid_icon_aspect_content_get;
   else
     ic->func.content_get = _widget_gengrid_content_get;

   /* check for group index */
   if (gst == GENGRID_H9_GROUP_INDEX_STYLE)
     elm_gengrid_group_item_size_set(o, 102, 102);
   else if (gst == GENGRID_GROUP_INDEX_STYLE)
     elm_gengrid_group_item_size_set(o, 31, 31);

   if ((gst == GENGRID_H9_GROUP_INDEX_STYLE) ||
       (gst == GENGRID_GROUP_INDEX_STYLE))
     {
        group_ic = elm_gengrid_item_class_new();
        group_ic->item_style = "group_index";
        group_ic->func.text_get = _widget_gengrid_text_get;
        group_ic->func.content_get = NULL;
        group_ic->func.state_get = NULL;
        group_ic->func.del = NULL;
     }

   for (i = 0; i < 50; i++)
     {
        if (((i % 10) == 0) &&
            ((gst == GENGRID_H9_GROUP_INDEX_STYLE) ||
             (gst == GENGRID_GROUP_INDEX_STYLE)))
          elm_gengrid_item_append(o, group_ic, (void *)(long)i, NULL, NULL);
        elm_gengrid_item_append(o, ic, (void *)(long)i, NULL, NULL);
     }

   if ((gst == GENGRID_H9_GROUP_INDEX_STYLE) ||
       (gst == GENGRID_GROUP_INDEX_STYLE))
     elm_gengrid_item_class_free(group_ic);

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
   const char *token;
   Elm_Genlist_Item_Type item_type = ELM_GENLIST_ITEM_NONE;

   o = elm_genlist_add(win);
   EXPAND(o); FILL(o);
   evas_object_show(o);

   ic = elm_genlist_item_class_new();
   ic->func.text_get = _widget_genlist_text_get;
   ic->func.content_get = _widget_genlist_content_get;
   ic->func.state_get = NULL;
   ic->func.del = NULL;

   strncpy(buf, orig_style, sizeof(buf));
   token = strtok(buf, "/");

   /* set item or genlist style */
   if (!strncmp("item", token, 4) || !strncmp("tree", token, 4))
     ic->item_style = style;
   else
     elm_object_style_set(o, style);

   /* check compress mode */
   if (!strncmp("item_compress", token, 13) ||
       !strncmp("tree_compress", token, 13))
     elm_genlist_mode_set(o, ELM_LIST_COMPRESS);

   /* check tree */
   if (!strncmp("tree", token, 4))
     item_type = ELM_GENLIST_ITEM_TREE;

   for (i = 0; i < 50; i++)
     {
        elm_genlist_item_append(o, ic, (void *)(long)i, NULL, item_type,
                                NULL, NULL);
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

void
widget_resize(Evas_Object *o)
{
   Evas_Coord w = 0, h = 0;

   if (option_is_force_resize())
     {
        option_preview_size_get(&w, &h);
        evas_object_size_hint_min_set(o, w, h);
        evas_object_size_hint_max_set(o, w, h);
     }
}

Evas_Object *
widget_create(Widget_Type widget, const char *orig_style)
{
   Evas_Object *o = NULL;
   const char *style = NULL;

   if (orig_style)
     style = eina_stringshare_add(_parse_style(orig_style));
   //INF("widget : %s, orig_style : %s, style : %s", widget, orig_style, style);

   if (widget == ETV_ID_ACTIONSLIDER)
     o = _widget_actionslider_create(style);
   else if (widget == ETV_ID_BG)
     o = _widget_bg_create(style);
   else if (widget == ETV_ID_BUTTON)
     o = _widget_button_create(style);
   else if (widget == ETV_ID_CHECK)
     o = _widget_check_create(style);
   else if (widget == ETV_ID_CLOCK)
     o = _widget_clock_create(style);
   else if (widget == ETV_ID_ENTRY)
     o = _widget_entry_create(style);
   else if (widget == ETV_ID_FILESELECTOR)
     o = _widget_fileselector_create(style);
   else if (widget == ETV_ID_FRAME)
     o = _widget_frame_create(style);
   else if (widget == ETV_ID_GENGRID)
     o = _widget_gengrid_create(orig_style, style);
   else if (widget == ETV_ID_GENLIST)
     o = _widget_genlist_create(orig_style, style);
   else if (widget == ETV_ID_HOVER)
     o = _widget_hover_create(style);
   else if (widget == ETV_ID_ICON)
     o = _widget_icon_create(orig_style);
   else if (widget == ETV_ID_LABEL)
     o = _widget_label_create(style);
   else if (widget == ETV_ID_LAYOUT)
     o = _widget_layout_create(style);
   else if (widget == ETV_ID_MENU)
     o = _widget_menu_create(orig_style);
   else if (widget == ETV_ID_PROGRESSBAR)
     o = _widget_progressbar_create(orig_style);
   else if (widget == ETV_ID_SEPARATOR)
     o = _widget_separator_create(style, orig_style);
   else if (widget == ETV_ID_SPINNER)
     o = _widget_spinner_create(style);
   else
     o = _widget_not_implemented_create(widget);
   elm_object_theme_set(o, th);

   widget_resize(o);

   return o;
}

const char *
widget_name_get_by_type(Widget_Type type)
{
   if (type < WIDGET_COUNT)
     return widgets[type].name;
   else
     return NULL;
}

const char *
widget_desc_get_by_type(Widget_Type type)
{
   if (type < WIDGET_COUNT)
     return widgets[type].desc;
   else
     return NULL;
}
