//
// Created by Dongmin on 2023-12-20.
//

#ifndef __REID_MODEL_INSTANCE_H__
#define __REID_MODEL_INSTANCE_H__

#include "Component.hpp"
#include "../GPUDevice/GPUDevice.h"
#include <mutex>
class ReidModelInstance : public Component
{
private:
    std::mutex instance_mtx;
    wptr<GPUDevice> gpu_device;
    int gpu_id;
    size_t device;
    size_t handle;
private:
    atomic<bool> stop_flag;
public:
    ReidModelInstance();
    ~ReidModelInstance();
    void initialize(wptr<GPUDevice> gpu_device);
    void release();
};

#endif //__REID_MODEL_INSTANCE_H__
