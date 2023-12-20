#include "ReidModelInstance.h"

ReidModelInstance::ReidModelInstance()
{

}

ReidModelInstance::~ReidModelInstance()
{

}

void ReidModelInstance::initialize(weak_ptr<GPUDevice> gpu_device)
{
    this->gpu_device = gpu_device;
    this->gpu_id = gpu_device.lock()->get_gpu_id();
    this->device = gpu_device.lock()->get_gpu_device();
    this->stop_flag = false;
}

void ReidModelInstance::release()
{
    this->stop_flag = true;
}