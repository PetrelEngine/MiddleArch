cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
add_definitions("-DGLM_FORCE_SIZE_T_LENGTH -DGLM_FORCE_RADIANS")

SET(Source_Common_Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../../Source")
SET(Source_Android_Dir "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp")

file(GLOB srcSource "${Source_Common_Dir}/CoreObject/*.cpp"
                    "${Source_Common_Dir}/RenderCore/*.cpp"
                    "${Source_Common_Dir}/*.cpp"
                    "${Source_Common_Dir}/PostProcess/*.cpp"
                    "${Source_Common_Dir}/SkeletalAnimation/*.cpp"
                    "${Source_Common_Dir}/SkeletalAnimation/*.cpp"
                    "${Source_Common_Dir}/Mesh/*.cpp"
                    "${Source_Common_Dir}/File/*.cpp"
                    "${Source_Common_Dir}/Graph/*.cpp"
                    "${Source_Common_Dir}/Graph/gles/*.cpp"
                    "${Source_Common_Dir}/Sample/*.cpp"
                    "${Source_Android_Dir}/Android/*.cpp"
    )

add_library(StudyCoreObjec SHARED ${srcSource})

target_include_directories( StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/CoreObject/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/RenderCore/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Mesh/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/File/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Graph/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Graph/gles/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Sample/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/PostProcess/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/SkeletalAnimation/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/glm/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/glm/gtc/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/glm/gtx/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/glm/detail/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Android_Dir}/Android/>
                          )

target_link_libraries(StudyCoreObjec
     GLESv2
     android
     log
     )