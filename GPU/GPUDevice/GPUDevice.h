//
// Created by Dongmin on 2023-12-20.
//

#ifndef __GPU_DEVICE_H__
#define __GPU_DEVICE_H__

#include "Component.hpp"
#include "concurrent_queue.h"
#include "../../Engine/ReidEngine.h"
#include <nvml.h>
#include "../ReID/ReidModelInstance.h"

using namespace tbb::detail::d2;

class GPUDevice : public Component
{
private:
    wptr<ReidEngine> engine;
    nvmlDevice_t nvml_device;
private:
    vector<wptr<ReidModelInstance>> reid_model_instance;
    size_t device;
private:
    concurrent_queue<wptr<ReidChannel>> gpu_reid_queue;
    int gpu_id = -1;
    bool use_reid = false;

public:
    GPUDevice();
    ~GPUDevice();
    void initialize(int gpu_id, int reid_model_instance_count);
    void release();
public:
    int get_gpu_id();
    size_t get_gpu_device();
public:
    void attach_channel(wptr<ReidChannel> channel);
    void detach_channel(wptr<ReidChannel> channel);
};



#endif //__GPU_DEVICE_H__
