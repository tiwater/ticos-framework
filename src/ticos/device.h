#ifndef __TICOS_DEVICE_H
#define __TICOS_DEVICE_H

#include "ticos/common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TICOS_DEV_VTABLE(cls) \
    int (*open) (struct cls* self); \
    int (*close) (struct cls* self); \
    int (*power_mode_changed) (struct cls* self, ticos_power_mode_t mode); \
    int (*sync_from_cache) (struct cls* self); \
    int (*post_to_cache) (struct cls* self); \
    int (*sync_from_dev) (struct cls* self); \
    int (*post_to_dev) (struct cls* self); \
    const char* name; \
    bool opened

#define TICOS_DEV_SET_VTABLE(cls) \
    .open = cls##_open, \
    .close = cls##_close, \
    .power_mode_changed = cls##_power_mode_changed, \
    .sync_from_cache = cls##_sync_from_cache, \
    .post_to_cache = cls##_post_to_cache, \
    .sync_from_dev = cls##_sync_from_dev, \
    .post_to_dev = cls##_post_to_dev

#define TICOS_DEV_CLASS_BEGIN(cls) \
    struct cls##_t; \
    typedef struct cls##_t cls##_t; \
    int cls##_open(cls##_t* self); \
    int cls##_close(cls##_t* self); \
    int cls##_power_mode_changed(cls##_t* self, ticos_power_mode_t mode); \
    int cls##_sync_from_cache(cls##_t* self); \
    int cls##_post_to_cache(cls##_t* self); \
    int cls##_sync_from_dev(cls##_t* self); \
    int cls##_post_to_dev(cls##_t* self); \
    struct cls##_t { \
        TICOS_DEV_VTABLE(cls##_t)

#define TICOS_DEV_CLASS_END() }

typedef enum {
    TICOS_POWER_MODE_UNKNOWN,
} ticos_power_mode_t;

typedef struct ticos_device_t {
    TICOS_DEV_VTABLE(ticos_device_t);
} ticos_device_t;

#define TICOS_VAR(type, v)  \
    type _##v##_var;        \
    type _##v##_cache_var;  \
    bool _##v##_dirty;      \
    bool _##v##_cache_dirty

#define ticos_sync_from_cache(self, v)                       \
    if ((self)->_##v##_var != ticos_get((self), v##_cache))  \
        ticos_set((self), v, (self)->_##v##_cache_var)

#define ticos_post_to_cache(self, v)                         \
    if ((self)->_##v##_cache_var != ticos_get((self), v))    \
        ticos_set((self), v##_cache, (self)->_##v##_var)

/**
  * @brief ????????????????????? public ???????????????????????????
  * @param[in] self ????????????
  * @param[in] v ????????????????????????????????? public ????????????
  * @return true????????????false????????????
  */
#define ticos_isdirty(self, v)   \
    ((self)->_##v##_dirty)

/**
  * @brief ????????????????????? public ???????????????
  * @param[in] self ????????????
  * @param[in] v ????????????????????????????????? public ????????????
  * @return ???????????????
  */
#define ticos_get(self, v)       \
    ((self)->_##v##_dirty = false, (self)->_##v##_var)

/**
  * @brief ????????????????????? public ???????????????
  * @param[in] self ????????????
  * @param[in] v ????????????????????????????????? public ????????????
  * @param[in] d ???????????????????????????
  */
#define ticos_set(self, v, d)           \
    if ((self)->_##v##_var != (d)) {    \
        (self)->_##v##_dirty = true;    \
        (self)->_##v##_var = (d);       \
    }

/**
  * @brief ????????????????????? public ?????????????????????????????????
  * @attention ???????????????????????????????????????????????????
  * @param[in] self ????????????
  * @param[in] v ????????????????????????????????? public ????????????
  * @return true????????????false????????????
  */
#define ticos_cache_isdirty(self, v)    \
    ticos_isdirty((self), v##_cache)

/**
  * @brief ????????????????????? public ?????????????????????
  * @attention ???????????????????????????????????????????????????
  * @param[in] self ????????????
  * @param[in] v ????????????????????????????????? public ????????????
  * @return ?????????????????????
  */
#define ticos_cache_get(self, v)    \
    ticos_get((self), v##_cache)

/**
  * @brief ????????????????????? public ?????????????????????
  * @attention ???????????????????????????????????????????????????
  * @param[in] self ????????????
  * @param[in] v ????????????????????????????????? public ????????????
  * @param[in] d ?????????????????????????????????
  */
#define ticos_cache_set(self, v, d)     \
    ticos_set((self), v##_cache, (d))

#ifdef __cplusplus
}
#endif

#endif // __TICOS_DEVICE_H
