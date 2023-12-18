//
// Created by Dongmin on 2023-12-18.
//

#ifndef __LIB_REID_CHANNEL_H__
#define __LIB_REID_CHANNEL_H__

#include "Component.hpp"
#include "concurrent_queue.h"

class ReidChannel : public Component
{
public:
    ReidChannel();
    ~ReidChannel();
    void initialize();
    void release();
public:
    int process();
    int get_result(reidFeatureResult_t* result);
    int release_result();
};

#endif //__LIB_REID_CHANNEL_H__
