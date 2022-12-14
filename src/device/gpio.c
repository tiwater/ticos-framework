/************************************************************************
 * @file ticos_gpio
 * @brief 设备接口实现
 * @author
 * @date 2022-10-24 16:56:15
 * @copyright
 ************************************************************************/

#include "ticos/device/gpio.h"
#include <Arduino.h>

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备“打开”操作，
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_gpio_open(ticos_gpio_t* self) {
    switch (self->mode) {
        case TICOS_GPIO_MODE_INPUT:
            pinMode(self->pin, INPUT_PULLUP);
            break;
        case TICOS_GPIO_MODE_OUTPUT:
            pinMode(self->pin, OUTPUT);
            break;
        default:
            break;
    }
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备“关闭”操作，
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_gpio_close(ticos_gpio_t* self) {
    /* 填充代码内容后请删除TICOS_UNUSED函数调用 */
    TICOS_UNUSED(self);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，系统改变“电源模式”时被动触发，
 * @param[in] self 类实例
 * @param[in] mode 更改后的电源模式
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_gpio_power_mode_changed(ticos_gpio_t* self, ticos_power_mode_t mode) {
    /* 填充代码内容后请删除TICOS_UNUSED函数调用 */
    TICOS_UNUSED(self);
    TICOS_UNUSED(mode);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从缓存复制到应用层的复制操作
 * @attention 此函数为自动生成，请不要更改函数内容
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_gpio_sync_from_cache(ticos_gpio_t* self) {
    ticos_sync_from_cache(self, level);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从应用层到缓存的复制操作
 * @attention 此函数为自动生成，请不要更改函数内容
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_gpio_post_to_cache(ticos_gpio_t* self) {
    ticos_post_to_cache(self, level);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从传感器到缓存的获取操作
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_gpio_sync_from_dev(ticos_gpio_t* self) {
    if (self->mode & TICOS_GPIO_MODE_INPUT) {
        bool lv = digitalRead(self->pin);
        ticos_cache_set(self, level, lv);
    }
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从缓存到传感器的提交操作
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_gpio_post_to_dev(ticos_gpio_t* self) {
    if ((self->mode & TICOS_GPIO_MODE_OUTPUT)
        && ticos_cache_isdirty(self, level)) {
       bool level = ticos_cache_get(self, level);
       digitalWrite(self->pin, level);
    }
    return TICOS_OK;
}
