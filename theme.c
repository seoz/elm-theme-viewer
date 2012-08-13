#include <Edje.h>

typedef struct _Widget_Data Widget_Data;
struct _Widget_Data
{
   Eina_List *styles;
};

char *widgets[] = {
     "actionslider", "bg", "border?", "bubble", "button", "calendar",
     "check", "clock", "colorselector", "conformant", "ctxpopup",
     "datetime", "dayselector", "diskselector", "entry", "fileselector",
     "flipselector", "frame", "gengrid", "genlist", "hover", "icon", "index",
     "label", "layout", "list", "map", "menu", "multibuttonentry", "naviframe",
     "notify", "panel", "panes", "photo", "photocam", "player", "pointer",
     "popup", "progressbar", "radio", "scroller", "segment_control",
     "separator", "slider", "slideshow", "spinner", "thumb", "toolbar",
     "tooltip", "video", "win", NULL };
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
        //fprintf(stderr, "%s\n", widgets[i++]);
     }
}

void
theme_load(void)
{
   Eina_List *l, *ll;
   const char *group;

   l = edje_file_collection_list("/usr/local/share/elementary/themes/default.edj");
   if (!l) return;

   EINA_LIST_FOREACH(l, ll, group)
     fprintf(stderr, "%s\n", group);

   edje_file_collection_list_free(l);
}
