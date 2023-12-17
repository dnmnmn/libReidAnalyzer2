#include "libReid.h"
#include "Engine/REIDEngine.h"

shared_ptr<REIDEngine> reid_handle = nullptr;
shared_ptr<REIDQuery> reid_query_handle = nullptr;

int reid_set_model(int32_t device = -1)
{
    if(reid_handle == nullptr)
    {
        reid_handle = make_shared<REIDEngine>();
        if (reid_handle->initialize() == true) return 0;
        else
        {
            reid_handle.reset();
            reid_handle = nullptr;
        }
    }
    return -1;
}

int reid_process()
{
    if (reid_handle == nullptr) return -1;
    return reid_handle->process();
}

int reid_get_result(reidFeatureResult_t* result)
{
    if (reid_handle == nullptr) return -1;
    return reid_handle->get_result(result);
}

int reid_release_result()
{
    if (reid_handle == nullptr) return -1;
    return reid_handle->release_result();
}

int reid_release_model()
{
    if (reid_handle == nullptr) return 0;
    if (reid_handle->release() == false) return -1;
    reid_handle.reset();
    reid_handle = nullptr;
    return 0;
}

int reid_set_query()
{
    if(reid_query_handle == nullptr)
    {
        reid_query_handle = make_shared<REIDQuery>();
        if (reid_query_handle->reid_query_initialize() == true) return 0;
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
    if (reid_query_handle == nullptr) return 0;
    if (reid_query_handle->release() == false) return -1;
    reid_query_handle.reset();
    reid_query_handle = nullptr;
    return reid_query_handle->release_query();
}