#include <Elementary.h>
#include "log.h"
#include "theme.h"

#define WEIGHT evas_object_size_hint_weight_set
#define ALIGN_ evas_object_size_hint_align_set
#define EXPAND(X) WEIGHT((X), EVAS_HINT_EXPAND, EVAS_HINT_EXPAND)
#define FILL(X) ALIGN_((X), EVAS_HINT_FILL, EVAS_HINT_FILL)

Evas_Object *list;

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
_right_content_create(Evas_Object *parent)
{
   Evas_Object *o;

   o = elm_bg_add(parent);
   evas_object_show(o);

   return o;
}

static Evas_Object *
_left_menu_create(Evas_Object *parent)
{
   Evas_Object *nf;

   nf = elm_naviframe_add(parent);
   evas_object_show(nf);

   list  = elm_list_add(parent);
   evas_object_data_set(list, "nf", nf);
   elm_naviframe_item_push(nf, "Widgets", NULL, NULL, list, NULL);
   evas_object_show(list);

   return nf;
}

void
gui_create(const char *edje_file)
{
   Evas_Object *win, *o;
   Evas_Object *box, *lbl, *btn, *box2, *table, *left, *right;

   if (!edje_file) return;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = o = elm_win_util_standard_add("elm-theme-viewer", "Elm Theme Viewer");
   elm_win_autodel_set(o, EINA_TRUE);
   evas_object_resize(o, 300, 400);
   evas_object_show(o);

   // outer box
   box = o = elm_box_add(win);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   lbl = o = elm_label_add(win);
   elm_object_text_set(o, edje_file);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   btn = o = elm_button_add(win);
   elm_object_text_set(o, "Select Theme");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   // inner box
   box2 = o = elm_box_add(win);
   elm_box_horizontal_set(o, EINA_TRUE);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   left = _left_menu_create(win);
   table = o = _elm_min_set(left, box, 200, 0); // set min size hint
   WEIGHT(o, 0.0, EVAS_HINT_EXPAND);
   FILL(o);
   elm_box_pack_end(box2, table);

   right = o = _right_content_create(win);
   EXPAND(o); FILL(o);
   elm_box_pack_end(box2, o);

   INF("GUI Creation Done");

   return;
}

static void
_widget_list_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *nf = evas_object_data_get(obj, "nf");
   if (!nf) return;
}

void
gui_widget_load(void)
{
   int i = 0;

   while (widgets[i])
     {
        elm_list_item_append(list, widgets[i], NULL, NULL, _widget_list_sel_cb, widgets[i]);
        i++;
     }
}
