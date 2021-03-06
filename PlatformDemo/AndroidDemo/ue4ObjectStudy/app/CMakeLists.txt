cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions("-DGLM_FORCE_SIZE_T_LENGTH -DGLM_FORCE_RADIANS")

SET(Source_Common_Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../../Source")
SET(Source_TP_Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../../ThirdParty")
SET(Source_Android_Dir "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp")

file(GLOB srcSource "${Source_Common_Dir}/CoreObject/*.cpp"
                    "${Source_Common_Dir}/RenderCore/*.cpp"
                    "${Source_Common_Dir}/ShaderCore/*.cpp"
                    "${Source_Common_Dir}/Container/*.cpp"
                    "${Source_Common_Dir}/*.cpp"
                    "${Source_Common_Dir}/PostProcess/*.cpp"
                    "${Source_Common_Dir}/SkeletalAnimation/*.cpp"
                    "${Source_Common_Dir}/SkeletalAnimation/*.cpp"
                    "${Source_Common_Dir}/Math/*.cpp"
                    "${Source_Common_Dir}/Mesh/*.cpp"
                    "${Source_Common_Dir}/File/*.cpp"
                    "${Source_Common_Dir}/Graph/*.cpp"
                    "${Source_Common_Dir}/Graph/gles/*.cpp"
                    "${Source_Common_Dir}/Sample/AppSystem/*.cpp"
                    "${Source_Common_Dir}/Sample/Demo/*.cpp"
                    "${Source_Common_Dir}/Engine/*.cpp"
                    "${Source_Common_Dir}/Resource/*.cpp"
                    "${Source_Common_Dir}/Scene/*.cpp"
                    "${Source_Common_Dir}/OpenGLESCase/*.cpp"
                    "${Source_Common_Dir}/OpenGLESCase/PBR/*.cpp"
                    "${Source_Common_Dir}/OpenGLESCase/ShadowMap/*.cpp"
                    "${Source_Common_Dir}/OpenGLESCase/MTRender/*.cpp"
                    "${Source_Common_Dir}/OpenGLESCase/ImageAlgoritm/*.cpp"
                    "${Source_TP_Dir}/stbImage/*.cpp"
                    "${Source_TP_Dir}/glm/detail/*.cpp"
                    "${Source_TP_Dir}/PugiXml/*.cpp"
                    "${Source_Android_Dir}/Android/*.cpp"
    )

add_library(StudyCoreObjec SHARED ${srcSource})

target_include_directories( StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/CoreObject/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Container/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/RenderCore/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/ShaderCore/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Engine/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Scene/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Math/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Mesh/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/File/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Resource/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Graph/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Graph/gles/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Sample/AppSystem/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Sample/Demo/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/PostProcess/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/SkeletalAnimation/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/OpenGLESCase/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/OpenGLESCase/PBR/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/OpenGLESCase/ShadowMap/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/OpenGLESCase/MTRender/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/OpenGLESCase/ImageAlgoritm/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/PugiXml/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm/gtc/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm/gtx/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm/detail/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/stbImage/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Android_Dir}/Android/>
                          )

target_link_libraries(StudyCoreObjec
     android
     GLESv3
     log
     )