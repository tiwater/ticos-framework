/************************************************************************
 * @file 03_cloud.ino
 * @brief 项目程序入口
 * @author tiwater
 * @date 2022-10-24 17:36:37
 * @copyright tiwater
 ************************************************************************/

/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 250

#include "ticos_project.h"
#include <ticos/log.h>

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    return TICOS_OK;
}

static bool g_light_on;

static void set_light(bool on) {
    ticos_iot_t* iot = ticos_dev(DEV_IOT);
    // 设置属性值
    ticos_set(iot, prop_switch, on);
    ticos_set(iot, prop_led, on);

    ticos_dev_setval(DEV_IO3, level, on);

    g_light_on = on;
}

static inline void switch_light(void) {
    set_light(!g_light_on);
}

/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {

    ticos_iot_t* iot = ticos_dev(DEV_IOT);
    if (ticos_isdirty(iot, prop_switch)) {
        bool on = ticos_get(iot, prop_switch);
        set_light(on);
    }

    ticos_gpio_t* io_1 = ticos_dev(DEV_IO1);
    if (ticos_isdirty(io_1, level)) {
        if (!ticos_get(io_1, level)) {
            switch_light();
        }
    }

    return TICOS_OK;
}
