#include <Elementary.h>
#include "log.h"
#include "theme.h"
#include "widget.h"

Eina_List *widget_list;
Elm_Theme *th;

void
theme_init(void)
{
   int i = 0;
   Widget_Data *wd = NULL;

   if (widget_list) return;

   // TODO : create only necessary widget data. do not create all wd for unused widgets.
   while (widgets[i].type < ETV_ID_LAST)
     {
        wd = (Widget_Data *)calloc(1, sizeof(Widget_Data));
        wd->type = widgets[i].type;
        widget_list = eina_list_append(widget_list, wd);
        i++;
     }
   INF("Theme Init Done");
}

void
theme_set(const char *edje_file)
{
   if (!edje_file) return;

   th = elm_theme_new();
   elm_theme_ref_set(th, NULL);
   elm_theme_overlay_add(th, edje_file);
}

void
theme_unset(const char *edje_file)
{
   if (!edje_file) return;

   elm_theme_overlay_del(th, edje_file);
   elm_theme_free(th);
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
             //ERR("%s is not a proper elementary style.", token);
             continue;
          }

        // get the widget name
        token = strtok(NULL, "/");
        if (!token) continue;

        // get the widget data of the widget
        wd = NULL;
        EINA_LIST_FOREACH(widget_list, l, wd)
          {
             if (!strcmp(widgets[wd->type].widget, token))
               break;
          }
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

   //edje_file_collection_list_free(l); // TODO

   INF("Theme Load Done");
}

void
theme_widgets_print(void)
{
   Eina_List *l;
   Widget_Data *wd;

   EINA_LIST_FOREACH(widget_list, l, wd)
     INF("%s %d", widgets[wd->type].widget, eina_list_count(wd->styles));
}

Eina_List *
theme_widget_styles_get(Widget_Type widget)
{
   Widget_Data *wd = NULL;
   Eina_List *l;

   if (!widget) return NULL;

   EINA_LIST_FOREACH(widget_list, l, wd)
     {
        if (widget == wd->type)
          break;
     }
   return wd->styles;
}

void
theme_widget_styles_print(Widget_Type widget)
{
   Eina_List *l = NULL;
   Widget_Data *wd = NULL;
   char *style = NULL;

   EINA_LIST_FOREACH(widget_list, l, wd)
     {
        if (widget == wd->type)
          break;
     }

   EINA_LIST_FOREACH(wd->styles, l, style)
     INF("%s", style);
}
