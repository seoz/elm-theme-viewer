#include <Elementary.h>
#include "common.h"
#include "log.h"
#include "theme.h"
#include "widget.h"
#include "gui.h"

Evas_Object *label, *bt_hide, *bt_desc;

static void
_hide_btn_clicked_cb(void *data EINA_UNUSED,
                     Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED);

static void
_block_clicked(void *data EINA_UNUSED, Evas_Object *obj,
			   void *event_info EINA_UNUSED)
{
   evas_object_hide(obj);
}

static void
_finger_size_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{

}

static void
_width_size_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{
}

static void
_height_size_sel_cb(void *data EINA_UNUSED, Evas_Object *obj EINA_UNUSED,
                    void *event_info EINA_UNUSED)
{
}

static void
_show_btn_clicked_cb(void *data EINA_UNUSED,
                     Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   elm_object_text_set(bt_hide, "Hide");
   evas_object_smart_callback_del(bt_hide, "clicked", _show_btn_clicked_cb);
   evas_object_smart_callback_add(bt_hide, "clicked",
                                  _hide_btn_clicked_cb, NULL);

   elm_layout_signal_emit(gui_layout,
                          "show,button,clicked", "button_description");
}

static void
_hide_btn_clicked_cb(void *data EINA_UNUSED,
                     Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   elm_object_text_set(bt_hide, "Show");
   evas_object_smart_callback_del(bt_hide, "clicked", _hide_btn_clicked_cb);
   evas_object_smart_callback_add(bt_hide, "clicked",
                                  _show_btn_clicked_cb, NULL);

   elm_layout_signal_emit(gui_layout,
                          "hide,button,clicked", "button_description");
}

static void
_desc_btn_clicked_cb(void *data EINA_UNUSED,
                     Evas_Object *obj EINA_UNUSED,
                     void *event_info EINA_UNUSED)
{
   Evas_Object *popup;
   popup = elm_popup_add(win);
   elm_object_part_text_set(popup, "title,text", "Description of Widget");
   elm_object_content_set(popup, label);
   evas_object_show(popup);

   evas_object_smart_callback_add(popup, "block,clicked",
                                  _block_clicked, NULL);
}
static void
_mobile_option_create(Evas_Object *parent)
{
   Evas_Object *tb;
   tb = elm_toolbar_add(parent);
   elm_layout_content_set(gui_layout, "option", tb);
   evas_object_show(tb);

   elm_toolbar_item_append(tb, NULL, "finger", _finger_size_sel_cb, NULL);
   elm_toolbar_item_append(tb, NULL, "width", _width_size_sel_cb, NULL);
   elm_toolbar_item_append(tb, NULL, "height", _height_size_sel_cb, NULL);
}

void
gui_mobile_create(const char *edje_file, int width, int height,
                  Eina_Bool fullscreen)
{
   Evas_Object *o, *preview_frame;
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
   snprintf(path, sizeof(path), "%s/themes/layout_mobile.edj",
            elm_app_data_dir_get());
   elm_layout_file_set(o, path, "etv/main/layout");
   evas_object_size_hint_weight_set(o, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, o);
   evas_object_show(o);

   // button_hide
   bt_hide = o = elm_button_add(win);
   elm_object_text_set(o, "Hide");
   evas_object_show(o);
   elm_layout_content_set(gui_layout, "button_hide", o);
   evas_object_smart_callback_add(o, "clicked",
                                  _hide_btn_clicked_cb, NULL);

   // button_description
   bt_desc = o = elm_button_add(win);
   elm_object_text_set(o, "Description");
   evas_object_show(o);
   elm_layout_content_set(gui_layout, "button_description", o);
   evas_object_smart_callback_add(o, "clicked",
                                  _desc_btn_clicked_cb, NULL);

   // preview_frame
   preview_frame = o = elm_frame_add(win);
   elm_object_text_set(o, "Preview");
   evas_object_show(o);
   elm_layout_content_set(gui_layout, "widget_preview", o);

   preview_box = o = elm_box_add(win);
   elm_object_content_set(preview_frame, o);
   evas_object_show(o);

   // widget_list
   gui_left_menu_create(win);

   _mobile_option_create(win);
}

void
gui_mobile_description_set(const char *txt)
{
   label = elm_label_add(win);
   elm_label_line_wrap_set(label, ELM_WRAP_MIXED);
   elm_object_text_set(label, txt);
}
