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
   { "bubble", ETV_ID_BUBBLE, "The Bubble is a widget to show text similar to how speech is represented in comics." },
   { "button", ETV_ID_BUTTON, "This is a push-button. Press it and run some function. It can contain a simple label and icon object and it also has an autorepeat feature." },
   { "calendar", ETV_ID_CALENDAR, "This is a calendar widget. It helps applications to flexibly display a calender with day of the week, date, year and month. Applications are able to set specific dates to be reported back, when selected, in the smart callbacks of the calendar widget." },
   { "check", ETV_ID_CHECK, "The check widget allows for toggling a value between true and false." },
   { "clock", ETV_ID_CLOCK, "This is a digital clock widget. In its default theme, it has a vintage 'flipping numbers clock' appearance, which will animate sheets of individual algarisms individually as time goes by." },
   { "colorselector", ETV_ID_COLORSELECTOR, "A ColorSelector is a color selection widget. It allows application to set a series of colors.It also allows to load/save colors from/to config with a unique identifier, by default, the colors are loaded/saved from/to config using 'default' identifier. The colors can be picked by user from the color set by clicking on individual color item on the palette or by selecting it from selector." },
   { "conformant", ETV_ID_CONFORMANT, NULL },
   { "ctxpopup", ETV_ID_CTXPOPUP, "A ctxpopup is a widget that, when shown, pops up a list of items. It automatically chooses an area inside its parent object's view (set via elm_ctxpopup_add() and elm_ctxpopup_hover_parent_set()) to optimally fit into it. In the default theme, it will also point an arrow to it's top left position at the time one shows it. Ctxpopup items have a label and/or an icon. It is intended for a small number of items (hence the use of list, not genlist)." },
   { "datetime", ETV_ID_DATETIME, "Datetime widget is used to display and input date & time values. This widget displays date and time as per the system's locale settings (Date includes Day, Month & Year along with the defined separators and Time includes Hour, Minute & AM/PM fields. Separator for AM/PM field is ignored." },
   { "dayselector", ETV_ID_DAYSELECTOR, "Dayselector is a day selection widget. It displays all seven days of the week and allows the user to select multiple days." },
   { "diskselector", ETV_ID_DISKSELECTOR, "A diskselector is a kind of list widget. It scrolls horizontally, and can contain label and icon objects. Three items are displayed with the selected one in the middle." },
   { "entry", ETV_ID_ENTRY, "An entry is a convenience widget which shows a box that the user can enter text into. Entries by default don't scroll, so they grow to accommodate the entire text, resizing the parent window as needed. This can be changed with the elm_entry_scrollable_set() function." },
   { "ews", ETV_ID_EWS, NULL },
   { "fileselector", ETV_ID_FILESELECTOR, "A file selector is a widget that allows a user to navigate through a file system, reporting file selections back via its API." },
   { "fileselector_button", ETV_ID_FILESELECTOR_BUTTON, "Fileselector button is a button that, when clicked, creates an Elementary window (or inner window) with a file selector widget within. When a file is chosen, the (inner) window is closed and the button emits a signal having the selected file as it's event_info." },
   { "fileselector_entry", ETV_ID_FILESELECTOR_ENTRY, "Fileselector entry is an entry made to be filled with or display a file system path string. Besides the entry itself, the widget has a file selector button on its side, which will raise an internal file selector widget, when clicked, for path selection aided by file system navigation." },
   { "flipselector", ETV_ID_FLIPSELECTOR, "A flip selector is a widget to show a set of text items, one at a time, with the same sheet switching style as the clock widget, when one changes the current displaying sheet (thus, the 'flip' in the name)." },
   { "focus_highlight", ETV_ID_FOCUS_HIGHLIGHT, NULL },
   { "frame", ETV_ID_FRAME, "Frame is a widget that holds some content and has a title." },
   { "gengrid", ETV_ID_GENGRID, NULL },
   { "genlist", ETV_ID_GENLIST, NULL },
   { "hover", ETV_ID_HOVER, "A Hover object will hover over its parent object at the target location. Anything in the background will be given a darker coloring to indicate that the hover object is on top (at the default theme). When the hover is clicked it is dismissed(hidden), if the contents of the hover are clicked that doesn't cause the hover to be dismissed." },
   { "icon", ETV_ID_ICON, "An icon object is used to display standard icon images (\"delete\", \"edit\", \"arrows\", etc.) or images coming from a custom file (PNG, JPG, EDJE, etc.), on icon contexts." },
   { "index", ETV_ID_INDEX, "An index widget gives you an index for fast access to whichever group of other UI items one might have. It's a list of text items (usually letters, for alphabetically ordered access)." },
   { "label", ETV_ID_LABEL, "Widget to display text, with simple html-like markup." },
   { "layout", ETV_ID_LAYOUT, NULL },
   { "list", ETV_ID_LIST, "A list widget is a container whose children are displayed vertically or horizontally, in order, and can be selected. The list can accept only one or multiple item selections. Also has many modes of items displaying." },
   { "map", ETV_ID_MAP, "This is a widget specifically for displaying a map. It uses basically OpenStreetMap provider http://www.openstreetmap.org/, but custom providers can be added." },
   { "menu", ETV_ID_MENU, "A menu is a list of items displayed above its parent. When the menu is showing its parent is darkened. Each item can have a sub-menu. The menu object can be used to display a menu on a right click event, in a toolbar, anywhere." },
   { "multibuttonentry", ETV_ID_MULTIBUTTONENTRY, NULL },
   { "naviframe", ETV_ID_NAVIFRAME, NULL },
   { "notify", ETV_ID_NOTIFY, "Display a container in a particular region of the parent(top, bottom, etc). A timeout can be set to automatically hide the notify. This is so that, after an evas_object_show() on a notify object, if a timeout was set on it, it will automatically get hidden after that time." },
   { "panel", ETV_ID_PANEL, "A panel is a type of animated container that contains subobjects. It can be expanded or contracted by clicking the button on it's edge." },
   { "panes", ETV_ID_PANES, NULL },
   { "photo", ETV_ID_PHOTO, "The Elementary photo widget is intended for displaying a photo, for ex., a person's image (contact). Simple, yet with a very specific purpose. It has a decorative frame around the inner image itself, on the default theme. If and while no photo is set on it, it displays a person icon, indicating it's a photo placeholder." },
   { "photocam", ETV_ID_PHOTOCAM, "Photocam is a widget meant specifically for displaying high-resolution digital camera photos, giving speedy feedback (fast load), zooming and panning as well as fitting logic, all with low memory footprint. It is entirely focused on jpeg images, and takes advantage of properties of the jpeg format (via Evas loader features in the jpeg loader)." },
   { "player", ETV_ID_PLAYER, NULL },
   { "pointer", ETV_ID_POINTER, NULL },
   { "popup", ETV_ID_POPUP, "This widget is an enhancement of Notify. <br>In addition to Content area, there are two optional sections namely Title area and Action area. <br>Popup Widget displays its content with a particular orientation in the parent area. This orientation can be one among top, center, bottom, left, top-left, top-right, bottom-left and bottom-right. Content part of Popup can be an Evas Object set by application or it can be Text set by application or set of items containing an icon and/or text. The content/item-list can be removed using elm_object_content_set with second parameter passed as NULL." },
   { "progressbar", ETV_ID_PROGRESSBAR, "The progress bar is a widget for visually representing the progress status of a given job/task." },
   { "radio", ETV_ID_RADIO, "Radio is a widget that allows for 1 or more options to be displayed and have the user choose only 1 of them." },
   { "scroller", ETV_ID_SCROLLER, NULL },
   { "segment_control", ETV_ID_SEGMENT_CONTROL, "Segment control widget is a horizontal control made of multiple segment items, each segment item functioning similar to discrete two state button. A segment control groups the items together and provides compact single button with multiple equal size segments." },
   { "separator", ETV_ID_SEPARATOR, "Separator is a very thin object used to separate other objects." },
   { "slider", ETV_ID_SLIDER, "The slider adds a draggable “slider” widget for selecting the value of something within a range." },
   { "slideshow", ETV_ID_SLIDESHOW, "This widget, as the name indicates, is a pre-made image slideshow panel, with API functions acting on (child) image items presentation. " },
   { "spinner", ETV_ID_SPINNER, "A spinner is a widget which allows the user to increase or decrease numeric values using arrow buttons, or edit values directly, clicking over it and typing the new value." },
   { "thumb", ETV_ID_THUMB, "A thumbnail object is used for displaying the thumbnail of an image or video. You must have compiled Elementary with Ethumb_Client support. Also, Ethumb's DBus service must be present and auto-activated in order to have thumbnails generated. You must also have a session bus, not a system one." },
   { "toolbar", ETV_ID_TOOLBAR, "A toolbar is a widget that displays a list of items inside a box. It can be scrollable, show a menu with items that don't fit to toolbar size or even crop them." },
   { "tooltip", ETV_ID_TOOLTIP, "The Tooltip is an (internal, for now) smart object used to show a content in a frame on mouse hover of objects(or widgets), with tips/information about them." },
   { "video", ETV_ID_VIDEO, "Elementary comes with two object that help design application that need to display video." },
   { "win", ETV_ID_WIN, "The window class of Elementary. Contains functions to manipulate windows. The Evas engine used to render the window contents is specified in the system or user elementary config files (whichever is found last), and can be overridden with the ELM_ENGINE environment variable for testing. Engines that may be supported (depending on Evas and Ecore-Evas compilation setup and modules actually installed at runtime) are (listed in order of best supported and most likely to be complete and work to lowest quality)." }
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
