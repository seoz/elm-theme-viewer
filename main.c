#include <Elementary.h>
#include "log.h"
#include "gui.h"
#include "theme.h"

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   log_init();
   gui_create();
   theme_init();
   theme_load();

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
