#define DBG(...) EINA_LOG_DOM_DBG(log_dom, __VA_ARGS__)
#define INF(...) EINA_LOG_DOM_INFO(log_dom, __VA_ARGS__)
#define WRN(...) EINA_LOG_DOM_WARN(log_dom, __VA_ARGS__)
#define ERR(...) EINA_LOG_DOM_ERR(log_dom, __VA_ARGS__)
#define CRI(...) EINA_LOG_DOM_CRIT(log_dom, __VA_ARGS__)

extern int log_dom;

void log_init(void);
void log_shutdown(void);
