#ifndef __INCLUDE_WIDGET__
#define __INCLUDE_WIDGET__

#define WIDGET_COUNT 58

typedef enum
{
   ETV_ID_NONE,
   ETV_ID_ACCESS,
   ETV_ID_ACTIONSLIDER,
   ETV_ID_BG,
   ETV_ID_BORDER,
   ETV_ID_BUBBLE,
   ETV_ID_BUTTON,
   ETV_ID_CALENDAR,
   ETV_ID_CHECK,
   ETV_ID_CLOCK,
   ETV_ID_COLORSELECTOR,
   ETV_ID_CONFORMANT,
   ETV_ID_CTXPOPUP,
   ETV_ID_DATETIME,
   ETV_ID_DAYSELECTOR,
   ETV_ID_DISKSELECTOR,
   ETV_ID_ENTRY,
   ETV_ID_EWS,
   ETV_ID_FILESELECTOR,
   ETV_ID_FILESELECTOR_BUTTON,
   ETV_ID_FILESELECTOR_ENTRY,
   ETV_ID_FLIPSELECTOR,
   ETV_ID_FOCUS_HIGHLIGHT,
   ETV_ID_FRAME,
   ETV_ID_GENGRID,
   ETV_ID_GENLIST,
   ETV_ID_HOVER,
   ETV_ID_ICON,
   ETV_ID_INDEX,
   ETV_ID_LABEL,
   ETV_ID_LAYOUT,
   ETV_ID_LIST,
   ETV_ID_MAP,
   ETV_ID_MENU,
   ETV_ID_MULTIBUTTONENTRY,
   ETV_ID_NAVIFRAME,
   ETV_ID_NOTIFY,
   ETV_ID_PANEL,
   ETV_ID_PANES,
   ETV_ID_PHOTO,
   ETV_ID_PHOTOCAM,
   ETV_ID_PLAYER,
   ETV_ID_POINTER,
   ETV_ID_POPUP,
   ETV_ID_PROGRESSBAR,
   ETV_ID_RADIO,
   ETV_ID_SCROLLER,
   ETV_ID_SEGMENT_CONTROL,
   ETV_ID_SEPARATOR,
   ETV_ID_SLIDER,
   ETV_ID_SLIDESHOW,
   ETV_ID_SPINNER,
   ETV_ID_THUMB,
   ETV_ID_TOOLBAR,
   ETV_ID_TOOLTIP,
   ETV_ID_VIDEO,
   ETV_ID_WIN,
   ETV_ID_LAST
} Widget_Type;

typedef struct _Widget Widget;
struct _Widget
{
   const char *name;
   Widget_Type type;
   const char *desc;
};

typedef struct _Widget_Data Widget_Data;
struct _Widget_Data
{
   Widget_Type type; // widget type
   Eina_List *styles; // list of styles
};

Widget widgets[WIDGET_COUNT];

Evas_Object *widget_create(Widget_Type widget, const char *style);
void widget_resize(Evas_Object *o);
const char *widget_name_get_by_type(Widget_Type type);
const char *widget_desc_get_by_type(Widget_Type type);
Eina_Bool option_is_force_resize(void);
void option_preview_size_get(Evas_Coord *w, Evas_Coord *h);

#endif
