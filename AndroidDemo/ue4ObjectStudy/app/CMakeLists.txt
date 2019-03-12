cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
add_definitions("-DGLM_FORCE_SIZE_T_LENGTH -DGLM_FORCE_RADIANS")

SET(Source_Dir "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp")

file(GLOB srcSource "${Source_Dir}/CoreObject/*.cpp"
                    "${Source_Dir}/*.cpp"
                    "${Source_Dir}/PostProcess/*.cpp"
                    "${Source_Dir}/Android/*.cpp"
    )

add_library(StudyCoreObjec SHARED ${srcSource})

target_include_directories( StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Dir}>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Dir}/CoreObject/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Dir}/PostProcess/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Dir}/Android/>
                          )

target_link_libraries(StudyCoreObjec
     GLESv2
     android
     log
     )