#include "ReidChannel.h"
#include "../Engine/ReidEngine.h"
#include "FileSystem.h"
#include "JsonObject.h"

ReidChannel::ReidChannel()
{

}

ReidChannel::~ReidChannel()
{

}

void ReidChannel::initialize()
{
    engine = find_component<ReidEngine>("engine", true);

    JsonObject config_json;
    string config_path = FileSystem::get_app_path() + "//reid_config.json";
    config_json.load(config_path);

}

void ReidChannel::release()
{

}

int ReidChannel::process()
{
    return 0;
}

int ReidChannel::get_result(reidFeatureResult_t* result)
{
    return 0;
}

int ReidChannel::release_result()
{
    return 0;
}