#ifndef __LIB_REID_ENGINE_H__
#define __LIB_REID_ENGINE_H__

#include "../Library/Component.h++"
#include "../Library/concurrent_queue.h"
#include <thread>
#include <mutex>

class REIDEngine : public Component
{
public:
    REIDEngine();
    ~REIDEngine();
    bool initialize();
    bool release();
public:
    int release_result();
    int process();
    int get_result(reidFeatureResult_t* result);
};

#endif //__LIB_REID_ENGINE_H__
