#include "version.h"

int version() {
#ifdef PROJECT_VERSION_PATCH
    return PROJECT_VERSION_PATCH;
#endif
    return -1;
}
