#include <Elementary.h>
#include "common.h"
#include "log.h"
#include "theme.h"
#include "widget.h"
#include "gui.h"
#include "gui_mobile.h"

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
Eina_Bool m_version = EINA_FALSE;

void
gui_version_set(Eina_Bool version)
{
   m_version = version;
}

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

Evas_Object *
gui_left_menu_create(Evas_Object *parent)
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

static void
_finger_size_changed_cb(void *data EINA_UNUSED, Evas_Object *obj,
                        void *event_info EINA_UNUSED)
{
   double val = elm_slider_value_get(obj);
   double v;

   v = round(val);
   if (v != val) elm_slider_value_set(obj, v);
   elm_config_finger_size_set(v);
   INF("finger size changed : %f %f", val, v);
}

static void
_scale_changed_cb(void *data EINA_UNUSED, Evas_Object *obj,
                  void *event_info EINA_UNUSED)
{
   double val = elm_slider_value_get(obj);
   double v;

   v = (double)(int)round(val * 10.0) / 10.0;
   if (v != val) elm_slider_value_set(obj, v);

   if (preview_obj) elm_object_scale_set(preview_obj, v);

   INF("scale changed : %f %f", val, v);
}

static void
_size_width_changed_cb(void *data EINA_UNUSED, Evas_Object *obj,
                       void *event_info EINA_UNUSED)
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
_size_height_changed_cb(void *data EINA_UNUSED, Evas_Object *obj,
                        void *event_info EINA_UNUSED)
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
_force_resize_changed_cb(void *data EINA_UNUSED, Evas_Object *obj,
                         void *event_info EINA_UNUSED)
{
   Eina_Bool checked = elm_check_state_get(obj);

   elm_object_disabled_set(size_width_slider, !checked);
   elm_object_disabled_set(size_height_slider, !checked);
}

void
gui_option_force_resize_create(Evas_Object *box)
{
   Evas_Object *o;

   option_force_resize = o = elm_check_add(box);
   elm_object_text_set(o, "Force resize");
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   evas_object_smart_callback_add(o, "changed", _force_resize_changed_cb,
                                  NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);

}

void
gui_option_width_size_create(Evas_Object *box)
{
   Evas_Object *o;

   o = elm_label_add(box);
   elm_object_text_set(o, "Size Width");
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   size_width_slider = o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.0f");
   elm_slider_indicator_format_set(o, "%1.0f");
   elm_slider_min_max_set(o, SIZE_WIDTH_MIN, SIZE_WIDTH_MAX);
   elm_slider_value_set(o, SIZE_WIDTH_DEFAULT);
   elm_object_disabled_set(o, EINA_TRUE);
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   evas_object_smart_callback_add(o, "delay,changed", _size_width_changed_cb,
                                  NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);
}

void
gui_option_height_size_create(Evas_Object *box)
{
   Evas_Object *o;

   o = elm_label_add(box);
   elm_object_text_set(o, "Size Height");
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   size_height_slider = o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.0f");
   elm_slider_indicator_format_set(o, "%1.0f");
   elm_slider_min_max_set(o, SIZE_HEIGHT_MIN, SIZE_HEIGHT_MAX);
   elm_slider_value_set(o, SIZE_HEIGHT_DEFAULT);
   elm_object_disabled_set(o, EINA_TRUE);
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   evas_object_smart_callback_add(o, "delay,changed", _size_height_changed_cb,
                                  NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);
}

void
gui_option_finger_size_create(Evas_Object *box)
{
   Evas_Object *o;

   o = elm_label_add(box);
   elm_object_text_set(o, "Finger Size");
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.0f");
   elm_slider_indicator_format_set(o, "%1.0f");
   elm_slider_min_max_set(o, 5, 200);
   elm_slider_value_set(o, elm_config_finger_size_get());
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   evas_object_smart_callback_add(o, "delay,changed", _finger_size_changed_cb,
                                  NULL);
   elm_box_pack_end(box, o);
   evas_object_show(o);
}

void
gui_option_scale_create(Evas_Object *box)
{
   Evas_Object *o;

   o = elm_label_add(box);
   elm_object_text_set(o, "Scale");
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   o = elm_slider_add(box);
   elm_slider_unit_format_set(o, "%1.1f");
   elm_slider_indicator_format_set(o, "%1.1f");
   elm_slider_min_max_set(o, 0.25, 5.0);
   elm_slider_value_set(o, elm_config_scale_get());
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   evas_object_smart_callback_add(o, "delay,changed", _scale_changed_cb, NULL);
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
   gui_option_finger_size_create(box);

   o = elm_separator_add(box);
   elm_separator_horizontal_set(o, EINA_TRUE);
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   // scale
   gui_option_scale_create(box);

   o = elm_separator_add(box);
   elm_separator_horizontal_set(o, EINA_TRUE);
   WEIGHT(o, EVAS_HINT_EXPAND, 0.0);
   FILL(o);
   elm_box_pack_end(box, o);
   evas_object_show(o);

   // size
   gui_option_force_resize_create(box);
   gui_option_width_size_create(box);
   gui_option_height_size_create(box);

   // padding
   o = elm_box_add(box);
   EXPAND(o); FILL(o);
   elm_box_pack_end(box, o);
   evas_object_show(o);
}

Evas_Object *
gui_preview_create(Evas_Object *parent)
{
   Evas_Object *o, *preview_frame;

   preview_frame = o = elm_frame_add(parent);
   elm_object_text_set(o, "Preview");

   evas_object_show(o);

   preview_box = o = elm_box_add(win);
   elm_object_content_set(preview_frame, o);
   evas_object_show(o);

   return preview_frame;
}

void
gui_create(const char *edje_file, Evas_Coord width, Evas_Coord height,
           Eina_Bool fullscreen)
{
   Evas_Object *o;
   char path[PATH_MAX];

   if (!edje_file) return;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = o = elm_win_util_standard_add("elm-theme-viewer", "Elm Theme Viewer");
   elm_win_autodel_set(o, EINA_TRUE);
   if (fullscreen)
     elm_win_fullscreen_set(win, EINA_TRUE);
   else
     evas_object_resize(o, width, height);
   evas_object_show(o);

   gui_layout = o = elm_layout_add(win);
   snprintf(path, sizeof(path), "%s/themes/layout.edj", elm_app_data_dir_get());
   elm_layout_file_set(o, path, "etv/main/layout");
   EXPAND(o);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   // title text
   elm_layout_text_set(gui_layout, "edje_name_txt", edje_file);

   // left menu
   elm_layout_content_set(gui_layout, "menu", gui_left_menu_create(win));

   // preview
   elm_layout_content_set(gui_layout, "preview", gui_preview_create(win));

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

Evas_Object *
gui_description_label_get(void)
{
   Evas_Object *o;
   const char *txt = NULL;

   o = elm_label_add(win);
   elm_label_line_wrap_set(o, ELM_WRAP_MIXED);
   txt = widget_desc_get_by_type(ed->selected_widget_type);
   if (!ed->selected_widget_type)
     elm_object_text_set(o, "Widget is not selected.");
   else if (!txt)
     elm_object_text_set(o, "There is no description for this widget.");
   else
     elm_object_text_set(o, txt);
   evas_object_show(o);

   return o;
}

static void
_style_list_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                   void *event_info EINA_UNUSED)
{
   Style_Data *sd = data;

   if (!data || !sd->widget_type || !sd->style) return;
   INF("%s %s", widget_name_get_by_type(sd->widget_type), sd->style);

   _preview_create(sd->widget_type, sd->style);
}

static void
_nf_prev_btn_clicked_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                        void *event_info EINA_UNUSED)
{
   _preview_create(ETV_ID_NONE, NULL);
   elm_naviframe_item_pop(data);
}

static void
_style_list_gengrid_group_index_sel_cb(void *data EINA_UNUSED,
                                       Evas_Object *obj EINA_UNUSED,
                                       void *event_info EINA_UNUSED)
{
   _preview_create(ETV_ID_GENGRID, "h9 group-index-style");
}

static void
_style_list_gengrid_grid_check_sel_cb(void *data EINA_UNUSED,
                                      Evas_Object *obj EINA_UNUSED,
                                      void *event_info EINA_UNUSED)
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
_widget_list_sel_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   Evas_Object *nf = evas_object_data_get(obj, "nf");
   Evas_Object *li, *prev_btn;
   Elm_Object_Item *it;
   Eina_List *styles, *l;
   char *style;
   Style_Data *sd;
   Widget_Type type = (Widget_Type)data;

   if (!nf) return;

   ed->selected_widget_type = type;

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

   elm_list_item_selected_set(elm_list_first_item_get(li), EINA_TRUE);
   elm_list_go(li);

   it = elm_naviframe_item_push(nf, "Styles", NULL, NULL, li, NULL);
   elm_object_item_part_text_set(it, "subtitle",
                                 (char *)widget_name_get_by_type(type));
   if (ed->tizen)
     {
        prev_btn = elm_button_add(win);
        elm_object_style_set(prev_btn, "naviframe/back_btn/default");
        evas_object_smart_callback_add(prev_btn, "clicked",
                                       _nf_prev_btn_clicked_cb, nf);
        elm_object_item_part_content_set(it, "title_left_btn", prev_btn);
        evas_object_show(prev_btn);

        elm_object_item_signal_emit(it,
                                    "elm,state,toolbar,close,internal","elm");
     }

   if (!m_version)
     elm_object_content_set(description_frame, gui_description_label_get());
   else
     {
        // mobile version sets the guidescription on button click
     }
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
