#ifndef __NODA_H
#define __NODA_H

#include "noda_common.h"
#include "noda_bus_center.h"
#include "noda_device_center.h"
#include "noda_internal.h"

#ifndef NODA_HEARTBEAT_MILLIS
#define NODA_HEARTBEAT_MILLIS 200
#endif

#ifdef __cplusplus
extern "C" {
#endif

int noda_onstart(void);
int noda_onclean(void);
int noda_onloop(void);

#ifndef NODA_USE_CUSTOM_APP_ENTRY
int main(int argc, const char** argv) {
    NODA_UNUSED(argc);
    NODA_UNUSED(argv);
    int rt = noda_startup();
    if (NODA_OK == rt) {
        while (NODA_OK == (rt = noda_loop()));
        rt = noda_cleanup();
    }
    return rt;
}
#endif

#ifdef __cplusplus
}
#endif

#endif // __NODA_H
