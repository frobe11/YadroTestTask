cmake_minimum_required(VERSION 3.28)

project(YadroTestTask)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_SCAN_FOR_MODULES
#        TapeEmulationController
#        ITapeController
#        DefaultSorter
#        KnowingMemoryCapacitySorter
#        main
#)


add_executable(YadroTestTask main.cpp)
add_library(modules)
target_sources(modules
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        controller/ITapeController.cpp
        controller/TapeEmulationController.cpp
        sorter/KnowingMemoryCapacitySorter.cpp
        sorter/TapeMerger.cpp
        config/ConfigReader.cpp
)
include(FetchContent)
FetchContent_Declare(
        cfg
        GIT_REPOSITORY https://github.com/hyperrealm/libconfig
        GIT_TAG v1.7.3
)
FetchContent_MakeAvailable(cfg)
find_package(libconfig CONFIG REQUIRED)
target_link_libraries(modules PRIVATE libconfig::libconfig libconfig::libconfig++)
target_link_libraries(YadroTestTask PRIVATE libconfig::libconfig libconfig::libconfig++)
target_link_libraries(YadroTestTask PRIVATE modules)
