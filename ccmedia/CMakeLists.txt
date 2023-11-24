cmake_minimum_required(VERSION 3.10)

project(ccmedia VERSION 0.1.0 LANGUAGES C CXX OBJC OBJCXX)

set(CMAKE_SYSTEM_NAME iOS)

set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_FIND_ROOT_PATH "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk")

set(TOOLCHAIN "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain")

set(CMAKE_OSX_SYSROOT ${CMAKE_FIND_ROOT_PATH})

set(CMAKE_OSX_ARCHITECTURES arm64)

set(CMAKE_IPHONEOS_DEPLOYMENT_TARGET 12.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions("GL_SILENCE_DEPRECATION")

add_compile_definitions("AL_SILENCE_DEPRECATION")

set(CMAKE_C_COMPILER ${TOOLCHAIN}/usr/bin/cc)

set(CMAKE_C_FLAGS "-target arm64-apple-ios12.0")

set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/usr/bin/c++)

set(CMAKE_CXX_FLAGS "-target arm64-apple-ios12.0")

set(CMAKE_OBJCXX_COMPILER ${TOOLCHAIN}/usr/bin/c++)

set(CMAKE_OBJCXX_FLAGS "-target arm64-apple-ios12.0 -fobjc-arc -fobjc-weak")

set(THIRD_PARTY ${CMAKE_CURRENT_SOURCE_DIR}/../third_party)

include_directories(${THIRD_PARTY}/include)

link_directories(${THIRD_PARTY}/lib)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_library(ccmedia 
player/player.cpp
player/player.hpp
player/format.cpp
player/format.hpp
type/type.h
util/container.h
util/cc_util.hpp
shader/shader_import.h
shader/shader_import.c
ios/CCPlayer.h
ios/CCPlayer.mm
gles/render.cpp 
gles/render.hpp 
gles/video.cpp 
gles/video.hpp 
al/audio.hpp 
al/audio.cpp
)

list(APPEND EXTRA_LIBS 
    "-framework Foundation"
    "-framework CoreGraphics"
    "-framework OpenGLES"
    "-framework AudioToolBox"
    "-framework VideoToolBox"
    "-framework CoreVideo"
    "-framework CoreMedia"
    "-framework Security"
    "-framework avfoundation")

list(APPEND ALL_LINK
    avcodec 
    avdevice 
    avfilter 
    avformat 
    avutil 
    swresample
    swscale
    iconv
    z
    bz2
    ${EXTRA_LIBS}
)
target_include_directories(ccmedia PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/type
${CMAKE_CURRENT_SOURCE_DIR}/player
${CMAKE_CURRENT_SOURCE_DIR}/util
${CMAKE_CURRENT_SOURCE_DIR}/shader
${CMAKE_CURRENT_SOURCE_DIR}/al 
${CMAKE_CURRENT_SOURCE_DIR}/gles
${CMAKE_CURRENT_SOURCE_DIR}/ios)

target_include_directories(ccmedia PUBLIC "type.h" "ios/CCPlayer.h")



set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../export)

install(TARGETS ccmedia
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
# Install the header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ios
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/type
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.h"
)