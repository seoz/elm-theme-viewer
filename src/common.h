#ifndef __INCLUDE_COMMON_
#define __INCLUDE_COMMON_

#define WEIGHT evas_object_size_hint_weight_set
#define ALIGN evas_object_size_hint_align_set
#define EXPAND(X) WEIGHT((X), EVAS_HINT_EXPAND, EVAS_HINT_EXPAND)
#define FILL(X) ALIGN((X), EVAS_HINT_FILL, EVAS_HINT_FILL)
#define ELM_THEME_VIEWER_DATA_DIR "/usr/local/share/elm-theme-viewer"

#endif
