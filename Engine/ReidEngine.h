#ifndef __LIB_REID_ENGINE_H__
#define __LIB_REID_ENGINE_H__

#include "../Library/Component.h++"
#include "../Library/concurrent_queue.h"
#include "../Channel/ReidChannel.h"
#include <thread>
#include <mutex>
#include <map>

class ReidEngine : public Component {
private:
    map<int, wptr<GPUDevice>> gpu_map;
    map<size_t, wptr<ReidChannel>> channel_map;

public:
    ReidEngine();
    ~ReidEngine();
    bool initialize();
    bool release();
    int make_channel();
    int release_channel(size_t channel_handle);
public:
    int release_result();
    int process();
    int get_result(reidFeatureResult_t* result);
};

#endif //__LIB_REID_ENGINE_H__
