#include "Component.hpp"
#include "FileSystem.h"
#include "JsonObject.h"
#include "../Channel/ReidChannel.h"
#include "../libReid/libReid.h"
#include "ReidEngine.h"

ReidEngine::ReidEngine()
{

}

ReidEngine::~ReidEngine()
{

}

bool ReidEngine::initialize()
{
    string config_path = FileSystem::get_app_path() + "//reid_config.json";

    if (FileSystem::exist(config_path) == false)
    {
        JsonObject config_json;
        config_json.set_string("Configuration/reid_instance/GPU_IDs", "0");
        config_json.set_int("Configuration/reid_instance/count", 2);
        config_json.set_int("Configuration/reid_instance/main/use", 1);
        config_json.set_string("Configuration/reid_instance/main/model_name", (string)"reid_CTLv2.aix");
        config_json.set_string("Configuration/reid_instance/main/model_weight", (string)"reid_Resnet50_fp32");

        config_json.save(config_path);
    }
    JsonObject config_json;
    config_json.load(config_path);
    string gpu_str = config_json.get_string("Configuration/reid_instance/GPU_IDs");
    auto gpu_id = FileSystem::split(gpu_str, ",");

    for (int i = 0; i < gpu_id.size(); i++)
    {
        int id = atoi(gpu_id[i].c_str());
        auto device = add_component<GPUDevice>("Device", false);
        device.lock()->initialize(id, &config_json);
        gpu_map.insert(pair<int, wptr<GPUDevice>>(id, device));
    }

    return true;
}

bool ReidEngine::release()
{
    return true;
}

size_t ReidEngine::make_channel()
{
    weak_ptr<ReidChannel> channel;
    channel = add_component<ReidChannel>("ReidChannel", false);
    channel.lock()->initialize();
    auto channel_ptr = (size_t)channel.lock().get();
    channel_map.insert(pair<size_t, wptr<ReidChannel>>(channel_ptr, channel));
    return channel_ptr;
}

int ReidEngine::release_channel(size_t channel_handle)
{
    auto channel = channel_map.find(channel_handle);
    if(channel != channel_map.end())
    {
        channel->second.lock()->release();
        delete_component<ReidEngine>(channel->second.lock()->get_component_id());
        channel_map.erase(channel);
    }
    return 0;
}