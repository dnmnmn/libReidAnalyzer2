#ifndef __LIB_REID_ENGINE_H__
#define __LIB_REID_ENGINE_H__

#include "Component.hpp"
#include "concurrent_queue.h"
#include "../Channel/ReidChannel.h"
#include "../libReid/libReid.h"
#include "../GPU/GPUDevice/GPUDevice.h"
#include <thread>
#include <mutex>
#include <map>

using namespace tbb::detail::d2;

class ReidChannel;
class GPUDevice;
class ReidEngine : public Component
{
private:
    map<int, wptr<GPUDevice>> gpu_map;
    map<size_t, wptr<ReidChannel>> channel_map;
public:
    ReidEngine();
    ~ReidEngine();
    bool initialize();
    bool release();
    size_t make_channel();
    int release_channel(size_t channel_handle);
};

#endif //__LIB_REID_ENGINE_H__
