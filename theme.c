#include <Edje.h>

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
