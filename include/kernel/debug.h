#ifndef DEBUG_H
#define DEBUG_H

void mukernel_log_impl(const char *level,const char *file,const char *func,int line,const char *trace);

#define DEBUG_INFO(trace)  mukernel_log_impl("INFO",  __FILE__, __func__, __LINE__, trace)
#define DEBUG_ERR(trace)   mukernel_log_impl("ERROR", __FILE__, __func__, __LINE__, trace)

#endif

