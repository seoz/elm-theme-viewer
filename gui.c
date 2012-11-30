#include <Elementary.h>
#include "common.h"
#include "log.h"
#include "theme.h"
#include "widget.h"

Evas_Object *list, *win, *viewer_box, *viewer_box_cur_obj;

typedef struct _Style_Data Style_Data;
struct _Style_Data
{
   const char *widget;
   const char *style;
};

static Evas_Object *
_elm_min_set(Evas_Object *obj, Evas_Object *parent, Evas_Coord w, Evas_Coord h)
{
   Evas_Object *table, *rect;

   table = elm_table_add(parent);
   evas_object_show(table);

   rect = evas_object_rectangle_add(evas_object_evas_get(table));
   evas_object_size_hint_min_set(rect, w, h);
   EXPAND(rect); FILL(rect);
   elm_table_pack(table, rect, 0, 0, 1, 1);

   EXPAND(obj); FILL(obj);
   elm_table_pack(table, obj, 0, 0, 1, 1);

   return table;
}

static Evas_Object *
_left_menu_create(Evas_Object *parent)
{
   Evas_Object *nf;

   nf = elm_naviframe_add(parent);
   evas_object_show(nf);

   list  = elm_list_add(parent);
   elm_list_select_mode_set(list, ELM_OBJECT_SELECT_MODE_ALWAYS);
   evas_object_data_set(list, "nf", nf);
   elm_naviframe_item_push(nf, "Widgets", NULL, NULL, list, NULL);
   evas_object_show(list);

   return nf;
}

void
gui_create(const char *edje_file)
{
   Evas_Object *o;
   Evas_Object *box, *btn, *table, *left;

   if (!edje_file) return;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = o = elm_win_util_standard_add("elm-theme-viewer", "Elm Theme Viewer");
   elm_win_autodel_set(o, EINA_TRUE);
   evas_object_resize(o, 600, 500);
   evas_object_show(o);

   // outer box
   box = o = elm_box_add(win);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   o = elm_label_add(win);
   elm_object_text_set(o, edje_file);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   btn = o = elm_button_add(win);
   elm_object_disabled_set(btn, EINA_TRUE);
   elm_object_text_set(o, "Select Theme");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   // inner box
   viewer_box = o = elm_box_add(win);
   elm_box_horizontal_set(o, EINA_TRUE);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   left = _left_menu_create(win);
   table = o = _elm_min_set(left, box, 250, 0); // set min size hint
   WEIGHT(o, 0.0, EVAS_HINT_EXPAND);
   FILL(o);
   elm_box_pack_end(viewer_box, table);

   o = widget_create(NULL, NULL);
   EXPAND(o); FILL(o);
   elm_box_pack_end(viewer_box, o);
   viewer_box_cur_obj = o;

   INF("GUI Creation Done");

   return;
}

static void
_style_list_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   Style_Data *sd = data;
   Evas_Object *o;

   if (!data || !sd->widget || !sd->style) return;
   INF("%s %s", sd->widget, sd->style);

   o = widget_create(sd->widget, sd->style);
   if (o)
     {
        if (viewer_box_cur_obj)
          {
             elm_box_unpack(viewer_box, viewer_box_cur_obj);
             evas_object_del(viewer_box_cur_obj);
          }
        elm_box_pack_end(viewer_box, o);
        viewer_box_cur_obj = o;
     }
}

static void
_widget_list_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *nf = evas_object_data_get(obj, "nf");
   Evas_Object *li;
   Elm_Object_Item *it;
   Eina_List *styles, *l;
   char *style;
   Style_Data *sd;

   if (!nf) return;

   li = elm_list_add(nf);
   elm_list_select_mode_set(li, ELM_OBJECT_SELECT_MODE_ALWAYS);
   styles = theme_widget_styles_get((const char *)data);
   EINA_LIST_FOREACH(styles, l, style)
     {
        // TODO: sd needs to be freed properly
        sd = (Style_Data *)calloc(1, sizeof(Style_Data));
        sd->widget = data;
        sd->style = style;
        elm_list_item_append(li, style, NULL, NULL, _style_list_sel_cb, sd);
     }

   elm_list_go(li);
   it = elm_naviframe_item_push(nf, "Styles", NULL, NULL, li, NULL);
   elm_object_item_part_text_set(it, "subtitle", (char *)data);
}

void
gui_widget_load(void)
{
   Eina_List *l;
   Widget_Data *wd;

   EINA_LIST_FOREACH(widget_list, l, wd)
     {
        if (eina_list_count(wd->styles))
          {
             elm_list_item_append(list, wd->widget, NULL, NULL,
                                  _widget_list_sel_cb, wd->widget);
          }
     }
   elm_list_go(list);
}
