#ifndef __INCLUDE_COMMON_
#define __INCLUDE_COMMON_

#ifdef HAVE_CONFIG_H
#include "elm_theme_viewer_config.h"
#endif

#include "widget.h"

#define WEIGHT evas_object_size_hint_weight_set
#define ALIGN evas_object_size_hint_align_set
#define EXPAND(X) WEIGHT((X), EVAS_HINT_EXPAND, EVAS_HINT_EXPAND)
#define FILL(X) ALIGN((X), EVAS_HINT_FILL, EVAS_HINT_FILL)

typedef struct _ETV_Data ETV_Data;
struct _ETV_Data
{
   Eina_Bool tizen; // flag to check the Tizen platform
   Widget_Type selected_widget_type; // selected widget type
};

extern ETV_Data *ed;

#endif
