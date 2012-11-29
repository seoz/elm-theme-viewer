#include <Edje.h>
#include "log.h"
#include "theme.h"

typedef struct _Widget_Data Widget_Data;
struct _Widget_Data
{
   Eina_List *styles;
};

char *widgets[] = {
     "access", "actionslider", "bg", "border", "bubble", "button", "calendar",
     "check", "clock", "colorselector", "conformant", "ctxpopup", "datetime",
     "dayselector", "diskselector", "entry", "ews", "fileselector",
	 "fileselector_entry", "flipselector", "focus_highlight", "frame",
	 "gengrid", "genlist", "hover", "icon", "index", "label", "layout", "list",
	 "map", "menu", "multibuttonentry", "naviframe", "notify", "panel", "panes",
	 "photo", "photocam", "player", "pointer", "popup", "progressbar", "radio",
	 "scroller", "segment_control", "separator", "slider", "slideshow",
	 "spinner", "thumb", "toolbar", "tooltip", "video", "win", NULL };
Eina_Hash *widget_list;

static void
_widget_entry_free_cb(void *data)
{
   free(data);
}

void
theme_init(void)
{
   int i = 0;
   Widget_Data *wd = NULL;

   widget_list = eina_hash_string_superfast_new(_widget_entry_free_cb);
   while (widgets[i])
     {
        // TODO : free the data when it's not used anymore.
        wd = (Widget_Data *)calloc(1, sizeof(Widget_Data));
        eina_hash_add(widget_list, widgets[i], wd);
        //INF("%s", widgets[i]);
        i++;
     }
   INF("Theme Init Done");
}

void
theme_load(const char *edje_file)
{
   Eina_List *l = NULL, *ll = NULL;
   char *group = NULL, *token = NULL;
   char *style = NULL;
   char buf[PATH_MAX] = {0, };
   Widget_Data *wd = NULL;
   Eina_Compare_Cb cmp_func = (Eina_Compare_Cb)strcmp;

   if (!edje_file) return;

   l = edje_file_collection_list(edje_file);
   if (!l) return;

   EINA_LIST_FOREACH(l, ll, group)
     {
        strncpy(buf, group, sizeof(buf));

        token = strtok(buf, "/");
        if (strncmp("elm", token, 5))
          {
             ERR("%s is not a proper elementary style.", token);
             continue;
          }

        // get the widget name
        token = strtok(NULL, "/");
        if (!token) continue;

        // get the widget data of the widget
        wd = eina_hash_find(widget_list, token);
        if (!wd)
          {
             //ERR("%s is not a proper elementary widget.", token);
             continue;
          }

        // get the style name
        style = strstr(group, "/");
        style = strstr(style + 1, "/");
        style++;

        //INF("%s %s %p", group, style, wd);
        wd->styles = eina_list_sorted_insert(wd->styles, cmp_func, style);
     }

   edje_file_collection_list_free(l);

   INF("Theme Load Done");
}

Eina_List *
widget_styles_get(const char *widget)
{
   Widget_Data *wd = NULL;

   wd = eina_hash_find(widget_list, widget);
   return wd->styles;
}

void
widget_styles_print(const char *widget)
{
   Eina_List *l = NULL;
   Widget_Data *wd = NULL;
   char *style = NULL;

   wd = eina_hash_find(widget_list, widget);
   EINA_LIST_FOREACH(wd->styles, l, style)
     INF("%s", style);
}