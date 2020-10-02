#pragma once

#define __FILENAME_X__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILENAME_X__)

#define LG_Log(FMT, ARGS...)do { \
            printf("[%23s]%30s@L%04d: " FMT "\n",__FILENAME__,__FUNCTION__, __LINE__, ## ARGS); \
            } while (0)
