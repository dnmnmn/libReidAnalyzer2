cmake_minimum_required(VERSION 3.26)
project(libReidAnalyzer2)

set(CMAKE_CXX_STANDARD 17)

add_library(libReidAnalyzer2 SHARED libReid.cpp
        Engine/REIDEngine.cpp
        Engine/REIDEngine.h
        Library/Component.h++
        Library/FileSystem.cpp
        Library/FileSystem.h
        Library/Json.h++
        Library/concurrent_queue.h
        Library/concrt.h
        Library/pplinterface.h
        Library/JsonObject.h
        Library/JsonObject.cpp)
