//
// Created by Dongmin on 2023-12-21.
//

#ifndef __REID_DEFINITION_H__
#define __REID_DEFINITION_H__

enum enumSimilarity
{
    cosine,
    euclidean,
};

enum enumModelver
{
    reid_CTLv1,
    reid_CTLv2,
};

typedef struct reidFeatureParam_t
{
    int32_t vmsId;
    int32_t devSerial;
    int32_t dchCh;
    int32_t dchSerial;
    int64_t thumbTime;
    int64_t objectID;
}reidFeatureParam_t;

typedef struct reidFeatureInfo_t {
    char* Features;
    int32_t FeatureSize;
    int32_t FeatureCount;
    enumModelver model_version;
    enumSimilarity Similarity_formula;
}reidFeatureInfo_t;

typedef struct reidFeatureResult_t {
    reidFeatureParam_t param;
    reidFeatureInfo_t info;
}reidFeatureResult_t;

#endif //__REID_DEFINITION_H__
