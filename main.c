#include <Elementary.h>
#include "gui.h"

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   gui_create();

   elm_run();
   elm_shutdown();

   return 0;
}
ELM_MAIN()
