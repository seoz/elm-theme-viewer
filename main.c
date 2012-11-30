#include <Elementary.h>
#include "log.h"
#include "gui.h"
#include "theme.h"

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   const char *edje_file = NULL;

   if (argc > 2)
     {
        printf("Usage: elm-theme-viewer EDJE_FILE_NAME\n");
        return 0;
     }
   if ((argc == 2) && argv[1])
     edje_file = argv[1];
   else
     edje_file = "/usr/local/share/elementary/themes/default.edj";

   log_init();

   // TODO: run this in a background
   theme_init();
   theme_load(edje_file);
   theme_set(edje_file);

   gui_create(edje_file);
   gui_widget_load();

   elm_run();

   theme_unset(edje_file);
   elm_shutdown();

   return 0;
}
ELM_MAIN()
