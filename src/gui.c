#include <Elementary.h>
#include "common.h"
#include "log.h"
#include "theme.h"
#include "widget.h"

#define SIZE_WIDTH_MIN 40
#define SIZE_WIDTH_MAX 500
#define SIZE_WIDTH_DEFAULT 300
#define SIZE_HEIGHT_MIN 30
#define SIZE_HEIGHT_MAX 400
#define SIZE_HEIGHT_DEFAULT 100

Evas_Object *list, *win, *gui_layout, *preview_box, *preview_obj;
Evas_Object *description_frame, *option_frame;
Evas_Object *size_width_slider, *size_height_slider;
Evas_Object *option_force_resize;

typedef struct _Style_Data Style_Data;
struct _Style_Data
{
   Widget_Type widget_type;
   const char *style;
};

static void
_preview_create(Widget_Type widget, const char *style)
{
   Evas_Object *o;

   if (preview_obj)
     {
        evas_object_del(preview_obj);
        preview_obj = NULL;
     }

   if (widget && style)
     {
        o = widget_create(widget, style);
        elm_box_pack_end(preview_box, o);
        preview_obj = o;
     }
}

static void
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

   elm_layout_content_set(gui_layout, "left_menu", nf);
}

static void
_finger_size_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   double val = elm_slider_value_get(obj);
   double v;

   v = round(val);
   if (v != val) elm_slider_value_set(obj, v);
   elm_config_finger_size_set(v);
   INF("finger size changed : %f %f", val, v);
}

static void
_scale_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   double val = elm_slider_value_get(obj);
   double v;

   v = (double)(int)round(val * 10.0) / 10.0;
   if (v != val) elm_slider_value_set(obj, v);
   elm_config_scale_set(v);
   INF("scale changed : %f %f", val, v);
}

static void
_size_width_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   double val = elm_slider_value_get(obj);
   double v;

   v = round(val);
   if (v != val) elm_slider_value_set(obj, v);

   if (preview_obj)
     widget_resize(preview_obj);

   INF("size width changed : %f %f", val, v);
}

static void
_size_height_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   double val = elm_slider_value_get(obj);
   double v;

   v = round(val);
   if (v != val) elm_slider_value_set(obj, v);

   if (preview_obj)
     widget_resize(preview_obj);

   INF("size height changed : %f %f", val, v);
}

static void
_force_resize_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
   Eina_Bool checked = elm_check_state_get(obj);

   elm_object_disabled_set(size_width_slider, !checked);
   elm_object_disabled_set(size_height_slider, !checked);
}

static void
_option_size_create(Evas_Object *box)
{
   Evas_Object *o;

   option_force_resize = o = elm_check_add(box);
   elm_object_text_set(o, "Force resize");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(o, "changed", _force_resize_changed_cb, NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_label_add(box);
   elm_object_text_set(o, "Size Width");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   size_width_slider = o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.0f");
   elm_slider_indicator_format_set(o, "%1.0f");
   elm_slider_min_max_set(o, SIZE_WIDTH_MIN, SIZE_WIDTH_MAX);
   elm_slider_value_set(o, SIZE_WIDTH_DEFAULT);
   elm_object_disabled_set(o, EINA_TRUE);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(o, "delay,changed", _size_width_changed_cb,
                                  NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_label_add(box);
   elm_object_text_set(o, "Size Height");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   size_height_slider = o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.0f");
   elm_slider_indicator_format_set(o, "%1.0f");
   elm_slider_min_max_set(o, SIZE_HEIGHT_MIN, SIZE_HEIGHT_MAX);
   elm_slider_value_set(o, SIZE_HEIGHT_DEFAULT);
   elm_object_disabled_set(o, EINA_TRUE);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(o, "delay,changed", _size_height_changed_cb,
                                  NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);
}

static void
_option_create(Evas_Object *parent)
{
   Evas_Object *o, *box;

   option_frame = o = elm_frame_add(parent);
   elm_object_text_set(o, "Option");
   evas_object_show(o);
   elm_layout_content_set(gui_layout, "option", o);

   // outer box
   box = o = elm_box_add(option_frame);
   elm_object_content_set(option_frame, o);
   evas_object_show(o);

   // finger size
   o = elm_label_add(box);
   elm_object_text_set(o, "Finger Size");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.0f");
   elm_slider_indicator_format_set(o, "%1.0f");
   elm_slider_min_max_set(o, 5, 200);
   elm_slider_value_set(o, elm_config_finger_size_get());
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(o, "delay,changed", _finger_size_changed_cb, NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_separator_add(box);
   elm_separator_horizontal_set(o, EINA_TRUE);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   // scale
   o = elm_label_add(box);
   elm_object_text_set(o, "Scale");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.1f");
   elm_slider_indicator_format_set(o, "%1.1f");
   elm_slider_min_max_set(o, 0.25, 5.0);
   elm_slider_value_set(o, elm_config_scale_get());
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_smart_callback_add(o, "delay,changed", _scale_changed_cb, NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_separator_add(box);
   elm_separator_horizontal_set(o, EINA_TRUE);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   _option_size_create(box);

   // padding
   o = elm_box_add(box);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, o);
   evas_object_show(o);
}

void
gui_create(const char *edje_file)
{
   Evas_Object *o, *preview_frame;

   if (!edje_file) return;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = o = elm_win_util_standard_add("elm-theme-viewer", "Elm Theme Viewer");
   elm_win_autodel_set(o, EINA_TRUE);
   evas_object_resize(o, 600, 500);
   evas_object_show(o);

   gui_layout = o = elm_layout_add(win);
   elm_layout_file_set(o, "data/layout.edj", "etv/main/layout");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   // title text
   elm_layout_text_set(gui_layout, "edje_name_txt", edje_file);

   // left menu
   _left_menu_create(win);

   // preview
   preview_frame = o = elm_frame_add(win);
   elm_object_text_set(o, "Preview");
   evas_object_show(o);
   elm_layout_content_set(gui_layout, "preview", o);

   preview_box = o = elm_box_add(win);
   elm_object_content_set(preview_frame, o);
   evas_object_show(o);

   // description
   description_frame = o = elm_frame_add(win);
   elm_object_text_set(o, "Description");
   evas_object_show(o);
   elm_layout_content_set(gui_layout, "description", o);

   // option
   _option_create(win);

   INF("GUI Creation Done");

   return;
}

void
gui_description_set(const char *txt)
{
   Evas_Object *o;

   o = elm_label_add(win);
   elm_label_line_wrap_set(o, ELM_WRAP_MIXED);
   elm_object_text_set(o, txt);
   elm_object_content_set(description_frame, o);
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(o, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(o);
}

static void
_style_list_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   Style_Data *sd = data;

   if (!data || !sd->widget_type || !sd->style) return;
   INF("%s %s", widget_name_get_by_type(sd->widget_type), sd->style);

   _preview_create(sd->widget_type, sd->style);
}

static void
_nf_prev_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
   _preview_create(ETV_ID_NONE, NULL);
   gui_description_set(NULL);
   elm_naviframe_item_pop(data);
}

static void
_style_list_gengrid_group_index_sel_cb(void *data, Evas_Object *obj,
                                      void *event_info)
{
   _preview_create(ETV_ID_GENGRID, "h9 group-index-style");
}

static void
_style_list_gengrid_grid_check_sel_cb(void *data, Evas_Object *obj,
                                      void *event_info)
{
   _preview_create(ETV_ID_GENGRID, "h9 grid-check-style");
}

static void
_custom_styles_add(Evas_Object *list, Widget_Type widget)
{
   if (ETV_ID_GENGRID == widget)
     {
        elm_list_item_append(list, "(H9) Grid Check Style", NULL, NULL,
                             _style_list_gengrid_grid_check_sel_cb, NULL);
        elm_list_item_append(list, "(H9) Group Index Style", NULL, NULL,
                             _style_list_gengrid_group_index_sel_cb, NULL);
     }
}

static void
_widget_list_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *nf = evas_object_data_get(obj, "nf");
   Evas_Object *li, *prev_btn;
   Elm_Object_Item *it;
   Eina_List *styles, *l;
   char *style;
   Style_Data *sd;
   Widget_Type type = (Widget_Type)data;

   if (!nf) return;

   li = elm_list_add(nf);
   elm_list_select_mode_set(li, ELM_OBJECT_SELECT_MODE_ALWAYS);
   styles = theme_widget_styles_get(type);
   EINA_LIST_FOREACH(styles, l, style)
     {
        // TODO: sd needs to be freed properly
        sd = (Style_Data *)calloc(1, sizeof(Style_Data));
        sd->widget_type = type;
        sd->style = style;
        elm_list_item_append(li, style, NULL, NULL, _style_list_sel_cb, sd);
     }

   // add additional hacky custom styles for special reasons
   _custom_styles_add(li, sd->widget_type);

   elm_list_go(li);

   prev_btn = elm_button_add(win);
   elm_object_text_set(prev_btn, "< Back");
   evas_object_smart_callback_add(prev_btn, "clicked",
                                  _nf_prev_btn_clicked_cb, nf);
   evas_object_show(prev_btn);

   it = elm_naviframe_item_push(nf, "Styles", prev_btn, NULL, li, NULL);
   elm_object_item_part_text_set(it, "subtitle", (char *)widget_name_get_by_type(type));

   gui_description_set(widget_desc_get_by_type(type));
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
             elm_list_item_append(list,
                                  widget_name_get_by_type(wd->type),
                                  NULL, NULL,
                                  _widget_list_sel_cb, (void *)wd->type);
          }
     }
   elm_list_go(list);
}

Eina_Bool
option_is_force_resize(void)
{
   if (!option_force_resize)
     return EINA_FALSE;
   return elm_check_state_get(option_force_resize);
}

void
option_preview_size_get(Evas_Coord *w, Evas_Coord *h)
{
   if (size_width_slider)
     *w = elm_slider_value_get(size_width_slider);
   else
     *w = -1;

   if (size_height_slider)
     *h = elm_slider_value_get(size_height_slider);
   else
     *h = -1;
}
