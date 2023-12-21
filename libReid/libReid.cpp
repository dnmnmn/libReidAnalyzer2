#include "libReid.h"
#include "Component.hpp"
#include "../Engine/ReidEngine.h"
#include "../Channel/ReidChannel.h"
#include "../Query/ReidQuery.h"

sptr<ReidEngine> reid_handle = nullptr;
sptr<ReidQuery> reid_query_handle = nullptr;

int reid_set_model(int32_t device = -1)
{
    if(reid_handle == nullptr)
    {
        reid_handle = make_shared<ReidEngine>();
        if (reid_handle->initialize() == true) return 0;
        else
        {
            reid_handle.reset();
            reid_handle = nullptr;
        }
    }
    return -1;
}

int reid_release_model()
{
    if (reid_handle == nullptr) return 0;
    if (reid_handle->release() == false) return -1;
    reid_handle.reset();
    reid_handle = nullptr;
    return 0;
}

size_t reid_set_channel()
{
    if (reid_handle == nullptr) return -1;
    return reid_handle->make_channel();
}

int reid_release_channel(size_t channel_handle)
{
    if (reid_handle == nullptr) return -1;
    return reid_handle->release_channel(channel_handle);
}

int reid_process(size_t channel_handle, reidFeatureParam_t reid_param, char* jpegThumbnail, int32_t ThumbnailByteSize)
{
    if (reid_handle == nullptr) return -1;
    return ((ReidChannel*)channel_handle)->process();
}

int reid_get_result(size_t channel_handle, reidFeatureResult_t* result)
{
    if (reid_handle == nullptr) return -1;
    return ((ReidChannel*)channel_handle)->get_result(result);
}

int reid_release_result(size_t channel_handle)
{
    if (reid_handle == nullptr) return -1;
    return ((ReidChannel*)channel_handle)->release_result();
}

size_t reid_set_query()
{
    if(reid_query_handle == nullptr)
    {
        reid_query_handle = make_shared<ReidQuery>();
        if (reid_query_handle->initialize() == true) return 0;
        else
        {
            reid_query_handle.reset();
            reid_query_handle = nullptr;
        }
    }
    return -1;
}

int reid_compare_gallery()
{
    if (reid_query_handle == nullptr) return -1;
    return reid_query_handle->compare_gallery();
}

int reid_compare_gallery_one()
{
    if (reid_query_handle == nullptr) return -1;
    return reid_query_handle->compare_gallery_one();
}

int reid_release_query()
{
    if (reid_query_handle != nullptr)
    {
        if (reid_query_handle->release() == false) return -1;
        reid_query_handle.reset();
        reid_query_handle = nullptr;
    }
    return 0;
}