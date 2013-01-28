#include <Elementary.h>
#include <Ecore_Getopt.h>
#include "common.h"
#include "log.h"
#include "gui.h"
#include "theme.h"

static const Ecore_Getopt options = {
   PACKAGE_NAME,
   "%prog [options]",
   PACKAGE_VERSION,
   "(C) 2012-2013 Daniel Juyung Seo",
   "BSD 2-Clause",
   "Elementary theme previewer witten with Enlightenment Foundation Libraries.",
   EINA_TRUE,
   {
      ECORE_GETOPT_STORE_STR('t', "theme",
                             "Set the theme to load and parse."),
      ECORE_GETOPT_VERSION  ('V', "version"),
      ECORE_GETOPT_COPYRIGHT('C', "copyright"),
      ECORE_GETOPT_LICENSE  ('L', "license"),
      ECORE_GETOPT_HELP     ('h', "help"),
      ECORE_GETOPT_SENTINEL
   }
};

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   const char *edje_file = NULL;

   int args;
   char *theme = NULL;
   Eina_Bool quit_option = EINA_FALSE;

   Ecore_Getopt_Value values[] = {
     ECORE_GETOPT_VALUE_STR(theme),
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_NONE
   };

   elm_app_compile_bin_dir_set(PACKAGE_BIN_DIR);
   elm_app_compile_data_dir_set(PACKAGE_DATA_DIR);
   elm_app_info_set(elm_main, "elm-theme-viewer", "images/logo.png");

   log_init();

   args = ecore_getopt_parse(&options, values, argc, argv);
   if (args < 0)
     {
        ERR("Could not parse command line options.");
        return 1;
     }

   if (quit_option) return 0;

   if (theme)
     {
        char path[PATH_MAX];
        if (eina_str_has_suffix(theme, ".edj"))
          eina_strlcpy(path, theme, sizeof(path));
        else
          snprintf(path, sizeof(path), "%s.edj", theme);

        edje_file = eina_stringshare_add(path);
     }
   else
     {
        edje_file = "/usr/local/share/elementary/themes/default.edj";
	 }
   INF("theme file : %s", edje_file);

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
