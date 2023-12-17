#include "REIDEngine.h"
#include "../Library/FileSystem.h"
#include "../Library/JsonObject.h"
#include "../libReid.h"

REIDEngine::REIDEngine()
{

}

REIDEngine::~REIDEngine()
{

}

bool REIDEngine::initialize()
{
    string config_path = FileSystem::get_app_path() + "//reid_config.json";

    if (FileSystem::exist(config_path) == false)
    {
        JsonObject config_json;
        config_json.set_string("Configuration/GPUs/GPU_IDs", 0);

    }
    return true;
}

bool REIDEngine::release()
{
    return true;
}

int REIDEngine::process()
{
    return 0;
}

int REIDEngine::get_result(reidFeatureResult_t* result)
{
    return 0;
}

int REIDEngine::release_result()
{
    return 0;
}

