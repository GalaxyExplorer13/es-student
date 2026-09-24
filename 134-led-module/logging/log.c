#include "log.h"
#include "device.h"

void log_prefix(const char *level, const char *function, int line)
{
    printf("%s %s:%d ", level, function, line);
}
