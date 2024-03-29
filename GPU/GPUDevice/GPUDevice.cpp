#include "GPUDevice.h"
#include "FileSystem.h"
#include "libIDL.h"
#include <cuda_runtime_api.h>

GPUDevice::GPUDevice()
{

}

GPUDevice::~GPUDevice()
{

}

void GPUDevice::initialize(int _gpu_id, JsonObject* config_json)
{
    cudaSetDevice(_gpu_id);
    this->gpu_id = _gpu_id;
    engine = find_component<ReidEngine>("engine", true);

    // Initialize IDL Device
    device = IDL::make_device(0, gpu_id);
    // Initialize Inference Model
    auto dev = static_pointer_cast<GPUDevice>(Component::shared_from_this());
    int reid_count = config_json->get_int("Configuration/reid_instance/count");
    for(int i = 0; i < reid_count; i++)
    {
        reid_model_instance.push_back(add_component<ReidModelInstance>("reid_instance", false));
        reid_model_instance[i].lock()->initialize(dev);
    }
    // NVML Initialize
    nvmlReturn_t result;
    unsigned int device_count;
    result = nvmlInit_v2();
    if (NVML_SUCCESS != result)
    {
        printf("Failed to initialize NVML\n");
    }
    result = nvmlDeviceGetCount(&device_count);
    result = nvmlDeviceGetHandleByIndex(gpu_id, &nvml_device);

    unsigned int curr_link_gen, curr_link_width;
    nvmlDeviceGetCurrPcieLinkGeneration(nvml_device, &curr_link_gen);
    nvmlDeviceGetCurrPcieLinkWidth(nvml_device, &curr_link_width);
    printf("GPU %d PCI-E Gen %d x%d\n", gpu_id, curr_link_gen, curr_link_width);
}

void GPUDevice::release()
{
    for(int i = 0; i < reid_model_instance.size(); i++)
    {
        reid_model_instance[i].lock()->release();

    }
    reid_model_instance.clear();
    IDL::release_device(device);
    engine.reset();
}

inline int GPUDevice::get_gpu_id()
{
    return gpu_id;
}

inline size_t GPUDevice::get_gpu_device()
{
    return device;
}