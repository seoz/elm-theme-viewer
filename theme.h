extern char *widgets[];

void theme_init(void);
void theme_load(const char *edje_file);
Eina_List * widget_styles_get(const char *widget);
void widget_styles_print(const char *widget);
