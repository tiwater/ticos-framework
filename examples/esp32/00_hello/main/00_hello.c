/*************************************************************************
  * @file 00_hello.c
  * @brief 项目程序入口
  * @author
  * @date 2022-10-24 17:36:37
  * @copyright
  ************************************************************************/

/*************************************************************************
  * 设置noda_onloop函数触发间隔，若不设置，则默认为200毫秒
  ************************************************************************/
#define NODA_HEARTBEAT_MILLIS 1000

#include <noda.h>
#include <noda/log.h>

/*************************************************************************
  * 向工程注册总线标识号，请将此标识号列表成员作为NODA_BUS_ADD首参
  ************************************************************************/
NODA_BUS_ID_BEGIN
    // TODO 更多总线标识号
NODA_BUS_ID_END

/*************************************************************************
  * 向工程注册设备标识号，请将此标识号列表成员作为NODA_DEVICE_ADD首参
  ************************************************************************/
NODA_DEV_ID_BEGIN
    // TODO 更多设备标识号
NODA_DEV_ID_END

/*************************************************************************
  * 生命周期函数，负责系统启动后的自定义初始化工作
  ************************************************************************/
int noda_onboot(void) {
    return NODA_OK;
}

/*************************************************************************
  * 生命周期函数，按照一定时间间隔(NODA_HEARTBEAT_MILLIS)触发
  ************************************************************************/
int noda_onloop() {
    static int counter;
    noda_logi("noda_onloop %d", counter++);
    return NODA_OK;
}
