//
// Created by Dongmin on 2023-12-21.
//

#ifndef __REID_QUERY_H__
#define __REID_QUERY_H__

#include "Component.hpp"

class ReidQuery : public Component
{
public:
    ReidQuery();
    ~ReidQuery();
    bool initialize();
    bool release();
    bool set_gallery();
    bool get_similarity();
};

#endif //__REID_QUERY_H__
