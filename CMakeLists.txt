cmake_minimum_required(VERSION 3.26)
project(libReidAnalyzer2)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    include_directories("C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8/include")
    link_directories("C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.8/lib/x64")
else()
    include_directories("/usr/local/cuda/include")
    link_directories("/usr/local/cuda/lib64")
endif()

include_directories("../Library/onetbb/include/tbb")
include_directories("../Library/opencv/include")
include_directories("../Library/ffmpeg/include")
include_directories("../Library/libIDL")
link_directories("../Library/onetbb/lib/intel64/vc14")
link_directories("../Library/opencv/lib")
link_directories("../Library/ffmpeg/lib")
link_directories("../Library/libIDL")

include_directories("../libFoundation")

add_library(libReidAnalyzer2 SHARED libReid/libReid.cpp
        Engine/ReidEngine.cpp
        Engine/ReidEngine.h
        Channel/ReidChannel.cpp
        Channel/ReidChannel.h
        GPU/GPUDevice/GPUDevice.cpp
        GPU/GPUDevice/GPUDevice.h
        GPU/ReID/ReidModelInstance.cpp
        GPU/ReID/ReidModelInstance.h
        libReid/definition.h
        libReid/definition.h
        Query/ReidQuery.cpp
        Query/ReidQuery.cpp
        Query/ReidQuery.h
        Query/ReidQuery.h
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(libReidAnalyzer2
            PRIVATE libFoundation
            PRIVATE nvcuvid
            PRIVATE cuda cudart nppicc nppc
            PRIVATE nvml
            #PRIVATE cuda cudart cudnn cublas nppial nppig npps
            PRIVATE avcodec avformat avutil avfilter avdevice swscale swresample
            PRIVATE tbb
            PRIVATE opencv_world460d
            PRIVATE libIDL
    )
else()
    target_link_libraries(libReidAnalyzer2
            PRIVATE libFoundation
            PRIVATE nvcuvid
            PRIVATE cuda cudart nppicc nppc
            PRIVATE nvml
            #PRIVATE cuda cudart cudnn cublas nppial nppig npps
            PRIVATE avcodec avformat avutil avfilter avdevice swscale swresample
            PRIVATE tbb
            PRIVATE opencv_world460
            PRIVATE libIDL
    )
endif()