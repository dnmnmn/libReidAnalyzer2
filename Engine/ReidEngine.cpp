#include "Component.hpp"
#include "FileSystem.h"
#include "JsonObject.h"
#include "../Channel/ReidChannel.h"
#include "../libReid.h"
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
        config_json.set_string("Configuration/GPUs/GPU_IDs", 0);
    }
    return true;
}

bool ReidEngine::release()
{
    return true;
}

int ReidEngine::make_channel()
{
    weak_ptr<ReidChannel> channel;
    channel = add_component<ReidChannel>();
    channel.lock()->initialize();
    channel_map.insert(make_pair(channel.lock()->get_component_id(), channel));
    return 0;
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