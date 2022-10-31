/************************************************************************
 * @file 00_hello.c
 * @brief 项目程序入口
 * @author
 * @date 2022-10-24 17:34:10
 * @copyright
 ************************************************************************/

/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 1000

#include <ticos.h>
#include <ticos/log.h>

/************************************************************************
 * 向工程注册总线标识号，请将此标识号列表成员作为TICOS_BUS_ADD首参
 ************************************************************************/
TICOS_BUS_ID_BEGIN
    // TODO 更多总线标识号
TICOS_BUS_ID_END

/************************************************************************
 * 向工程注册设备标识号，请将此标识号列表成员作为TICOS_DEV_ADD首参
 ************************************************************************/
TICOS_DEV_ID_BEGIN
    // TODO 更多设备标识号
TICOS_DEV_ID_END

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    return TICOS_OK;
}

/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop() {
    static int counter;
    ticos_logi("ticos_onloop %d", counter++);
    return TICOS_OK;
}
