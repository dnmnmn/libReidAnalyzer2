#ifndef __LIB_REID_INTERFACE_H__
#define __LIB_REID_INTERFACE_H__
#ifndef LIBREID_EXPORTS
#define REID_C_EXPORT extern "C" __declspec(dllimport)
#else
#define REID_C_EXPORT extern "C" __declspec(dllexport)
#endif

typedef unsigned char uchar;
#include <string>
#include <vector>
#include <cstdint>

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
    int32_t model_version;
    int32_t FeatureCount;
    int32_t Similarity_formula;
}reidFeatureInfo_t;

typedef struct reidFeatureResult_t {
    reidFeatureParam_t param;
    reidFeatureInfo_t info;
}reidFeatureResult_t;

/* ReID 분석 엔진 스레드를 실행하는 함수
 * @param device : GPU 번호
 * @return 성공 시 0, 실패 시 -1      */
REID_C_EXPORT int reid_set_model();
REID_C_EXPORT int reid_process();
REID_C_EXPORT int reid_get_result();
REID_C_EXPORT int reid_release_result();
REID_C_EXPORT int reid_release_model();

REID_C_EXPORT int reid_set_query();
REID_C_EXPORT int reid_compare_gallery();
REID_C_EXPORT int reid_compare_gallery_one();
REID_C_EXPORT int reid_release_query();


//REID_C_EXPORT size_t Reid_Initialize(int32_t device = 0, int32_t model_count_per_gpu = 4, bool blocking = false, bool nonblocking = true);
//REID_C_EXPORT reidFeatureResult_t Reid_ProcessFeatureOne(size_t reid_handle, reidFeatureParam_t reid_param, char* jpegThumbnail, int32_t ThumbnailByteSize);
//REID_C_EXPORT int32_t Reid_ProcessFeature(size_t reid_handle, reidFeatureParam_t reid_param, char* jpegThumbnail, int32_t ThumbnailByteSize);
//REID_C_EXPORT int32_t Reid_GetFeature(size_t reid_handle, std::vector<reidFeatureResult_t>* result);
//REID_C_EXPORT void Reid_Release(size_t reid_handle);
//REID_C_EXPORT size_t Reid_QueryInitialize(reidFeatureResult_t queryResult);
//REID_C_EXPORT float Reid_CompareGalleryOne(size_t query_handle, reidFeatureResult_t galleryResult);
//REID_C_EXPORT void Reid_CompareGallery(size_t query_handle, std::vector<reidFeatureResult_t> galleryResult, std::vector<float>* result);
//REID_C_EXPORT void Reid_QueryRelease(size_t query_handle);

#endif