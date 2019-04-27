cmake_minimum_required(VERSION 3.4.1)

project (MacDemo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
add_definitions("-DGLM_FORCE_SIZE_T_LENGTH -DGLM_FORCE_RADIANS")

set(Source_Common_Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../Source")
set(Source_ThridParty_Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../ThirdParty")
set(Source_Mac_Dir "${CMAKE_CURRENT_SOURCE_DIR}/MacSource")

file(GLOB srcSource "${Source_Common_Dir}/CoreObject/*.cpp"
                    "${Source_Common_Dir}/*.cpp"
                    "${Source_Common_Dir}/PostProcess/*.cpp"
                    "${Source_Common_Dir}/SkeletalAnimation/*.cpp"
                    "${Source_Common_Dir}/SkeletalAnimation/*.cpp"
                    "${Source_Common_Dir}/Mesh/*.cpp"
                    "${Source_Common_Dir}/File/*.cpp"
                    "${Source_Common_Dir}/Graph/*.cpp"
                    "${Source_Common_Dir}/Graph/gles/*.cpp"
                    "${Source_Common_Dir}/Sample/*.cpp"
                    "${Source_Mac_Dir}/*.cpp"
		    "${Source_Mac_Dir}/MacBridge/*.cpp"
    )

#包含glfw的gl窗口环境
include_directories(${${Source_ThridParty_Dir}/glfw/})
include_directories(${${Source_ThridParty_Dir}/glfw/GLFW/})
link_directories(${${Source_ThridParty_Dir}/glfw/})

#message(${Source_ThridParty_Dir}/)

include_directories({Source_Common_Dir}/)
include_directories(${Source_Common_Dir}/CoreObject/)
include_directories(${Source_Common_Dir}/Mesh/)
include_directories(${Source_Common_Dir}/File/)
include_directories(${Source_Common_Dir}/Graph/)
include_directories(${Source_Common_Dir}/Graph/gles/)
include_directories(${Source_Common_Dir}/Sample/)
include_directories(${Source_Common_Dir}/PostProcess/)
include_directories(${Source_Common_Dir}/SkeletalAnimation/)
include_directories(${Source_Common_Dir}/glm/)
include_directories(${Source_Common_Dir}/glm/gtc/)
include_directories(${Source_Common_Dir}/glm/gtx/)
include_directories(${Source_Common_Dir}/glm/detail/)
include_directories(${Source_Mac_Dir}/)
include_directories(${Source_Mac_Dir}/MacBridge/)

find_library(LIBCOCOA Cocoa)
if (NOT LIBCOCOA)
    message(FATAL_ERROR "Cocoa not found")
endif()

find_library(LIBOPENGL OpenGL)
if (NOT LIBCOCOA)
   message(FATAL_ERROR "OpenGL not found")
endif()

find_library(LIBIOKIT IOKit)
if (NOT LIBCOCOA)
   message(FATAL_ERROR "IOKit not found")
endif()

find_library(LIBCOREVIDEO CoreVideo)
if (NOT LIBCOCOA)
   message(FATAL_ERROR "CoreVideo not found")
endif()


add_executable(MacDemo ${srcSource})

SET(GL_LINK_LIBS glfw3 ${LIBCOCOA} ${LIBOPENGL} ${LIBIOKIT} ${LIBCOREVIDEO})

target_link_libraries(MacDemo ${GL_LINK_LIBS})