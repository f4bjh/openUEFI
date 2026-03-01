#ifndef DEBUG_H
#define DEBUG_H

void mukernel_log_impl(const char *level,const char *file,const char *func,int line,const char *fmt, ...);

#define DEBUG_INFO(fmt, ...)  mukernel_log_impl("INFO",  __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define DEBUG_ERR(fmt, ...)   mukernel_log_impl("ERROR", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

#endif

