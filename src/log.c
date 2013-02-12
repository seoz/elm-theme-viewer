#include <Eina.h>

int log_dom = -1;

void
log_init(void)
{
   log_dom = eina_log_domain_register("elm-theme-viewer", EINA_COLOR_LIGHTRED);
   //eina_log_domain_level_set("elm-theme-viewer", EINA_LOG_LEVEL_DBG);
}

void
log_shutdown(void)
{
   eina_log_domain_unregister(log_dom);
   log_dom = -1;
}
