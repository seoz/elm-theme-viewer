#include <Elementary.h>
#include "common.h"
#include "log.h"
#include "theme.h"
#include "widget.h"
#include "gui.h"

#if (ELM_VERSION_MAJOR == 1) && (ELM_VERSION_MINOR < 8)
  #define PANES_TOP "top"
  #define PANES_BOTTOM "bottom"
#else
  #define PANES_TOP "left"
  #define PANES_BOTTOM "right"
#endif

void gui_mobile_description_set(void);
Evas_Object *bt_desc;

static void
_block_clicked(void *data EINA_UNUSED, Evas_Object *obj,
               void *event_info EINA_UNUSED)
{
   evas_object_hide(obj);
}

static void
_option_finger_size_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{
   Evas_Object *o, *box;

   elm_layout_signal_emit(gui_layout, "option,set,clicked", "option");

   // outer box
   box = o = elm_box_add(win);
   elm_layout_content_set(gui_layout, "option_set", o);
   evas_object_show(o);

   gui_option_finger_size_create(box);
}

static void
_option_scale_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                   void *event_info EINA_UNUSED)
{
   Evas_Object *o, *box;

   elm_layout_signal_emit(gui_layout, "option,set,clicked", "option");

   // outer box
   box = o = elm_box_add(win);
   elm_layout_content_set(gui_layout, "option_set", o);
   evas_object_show(o);

   gui_option_scale_create(box);
}

static void
_option_size_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{
   Evas_Object *o, *box;

   elm_layout_signal_emit(gui_layout, "option,set,clicked", "option");

   // outer box
   box = o = elm_box_add(win);
   elm_layout_content_set(gui_layout, "option_set", o);
   evas_object_show(o);

   gui_option_force_resize_create(box);
   gui_option_width_size_create(box);
   gui_option_height_size_create(box);
}

static void
_desc_btn_clicked_cb(void *data EINA_UNUSED,
                     Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   gui_mobile_description_set();
}

static void
_toolbar_item_clicked_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                         void *event_info)
{
   Evas_Object *option_obj = NULL;

   if (!event_info) return;

   if (!elm_toolbar_item_selected_get(event_info))
     {
        option_obj = elm_layout_content_get(gui_layout, "option_set");
        if (option_obj)
          evas_object_del(option_obj);
     }
}

static void
_clicked_double_cb(void *data EINA_UNUSED, Evas_Object *obj,
                   void *event_info EINA_UNUSED)
{
   static Eina_Bool contracted = EINA_FALSE;
   Evas_Coord miny = 0, panel_h = 0;
   double size = 0.0;
   static double prev_size = 0.0;

   if (!contracted)
     {
        prev_size = elm_panes_content_left_size_get(obj);
        if (preview_box)
          {
             evas_object_size_hint_min_get(preview_box, NULL, &miny);
             if (miny <= 0)
               miny = 50 * elm_config_scale_get();
             evas_object_geometry_get(obj, NULL, NULL, NULL, &panel_h);
             size = miny / (double)panel_h;
          }
        elm_panes_content_left_size_set(obj, size);
     }
   else
     {
        elm_panes_content_left_size_set(obj, prev_size);
     }
   contracted = !contracted;
   INF("size y %f %d", size, contracted);
}

static void
_mobile_option_create(ETV_Data *ed, Evas_Object *parent)
{
   Evas_Object *tb;

   tb = elm_toolbar_add(parent);
   elm_layout_content_set(gui_layout, "option", tb);
   elm_toolbar_shrink_mode_set(tb, ELM_TOOLBAR_SHRINK_SCROLL);
   evas_object_smart_callback_add(tb, "clicked", _toolbar_item_clicked_cb, NULL);
   evas_object_show(tb);

   if (ed->tizen) elm_object_style_set(tb, "tabbar");

   elm_toolbar_item_append(tb, NULL, "finger", _option_finger_size_sel_cb,
                           NULL);
   elm_toolbar_item_append(tb, NULL, "scale", _option_scale_sel_cb, NULL);
   elm_toolbar_item_append(tb, NULL, "size", _option_size_sel_cb, NULL);
}

void
gui_mobile_create(ETV_Data *ed, const char *edje_file, int width, int height,
                  Eina_Bool fullscreen)
{
   Evas_Object *o, *conform, *ic, *box;
   char buf[PATH_MAX];

   if (!edje_file) return;

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = o = elm_win_util_standard_add("elm-theme-viewer", "Elm Theme Viewer");
   elm_win_autodel_set(o, EINA_TRUE);
   if (fullscreen)
     elm_win_fullscreen_set(win, EINA_TRUE);
   else
     evas_object_resize(o, width, height);
   evas_object_show(o);

   elm_win_conformant_set(o, EINA_TRUE);
   elm_win_indicator_mode_set(o, ELM_WIN_INDICATOR_SHOW);

   conform = o = elm_conformant_add(win);
   EXPAND(o);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   gui_layout = o = elm_layout_add(win);
   snprintf(buf, sizeof(buf), "%s/themes/layout_mobile.edj",
            elm_app_data_dir_get());
   elm_layout_file_set(o, buf, "etv/main/layout");
   elm_object_content_set(conform, o);
   evas_object_show(o);

   box = o = elm_box_add(win);
   elm_box_horizontal_set(o, EINA_TRUE);
   elm_layout_content_set(gui_layout, "title", o);
   evas_object_show(o);

   ic = elm_icon_add(win);
   snprintf(buf, sizeof(buf), "%s/images/ETV_logo_s.png", elm_app_data_dir_get());
   EXPAND(ic); FILL(ic);
   elm_image_file_set(ic, buf, NULL);
   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   elm_box_pack_end(box, ic);
   evas_object_show(ic);

   o = elm_label_add(win);
   EXPAND(o); FILL(o);
   elm_object_text_set(o, "Elm-Theme-Viewer");
   elm_box_pack_end(box, o);
   evas_object_show(o);

   // button_description
   bt_desc = o = elm_button_add(win);
   elm_object_text_set(o, "Desc");
   evas_object_show(o);
   elm_layout_content_set(gui_layout, "button_description", o);
   evas_object_smart_callback_add(o, "clicked",
                                  _desc_btn_clicked_cb, NULL);

   // panes for preview and menu
   o = elm_panes_add(win);
   elm_panes_horizontal_set(o, EINA_TRUE);
   evas_object_show(o);
   evas_object_smart_callback_add(o, "clicked,double", _clicked_double_cb, o);
   elm_layout_content_set(gui_layout, "preview", o);

   // preview_frame
   elm_object_part_content_set(o, PANES_TOP, gui_preview_create(win));

   // widget_list
   elm_object_part_content_set(o, PANES_BOTTOM, gui_left_menu_create(win));

   _mobile_option_create(ed, win);
}

void
gui_mobile_description_set(void)
{
   Evas_Object *popup;

   popup = elm_popup_add(win);
   elm_object_part_text_set(popup, "title,text", "Description of Widget");
   elm_object_content_set(popup, gui_description_label_get());
   evas_object_smart_callback_add(popup, "block,clicked",
                                  _block_clicked, NULL);
   evas_object_show(popup);
}
