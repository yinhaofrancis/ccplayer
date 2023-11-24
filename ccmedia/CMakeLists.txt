cmake_minimum_required(VERSION 3.10)

project(ccmedia VERSION 0.1.0 LANGUAGES C CXX OBJC OBJCXX)

add_compile_definitions("GLES_SILENCE_DEPRECATION")

add_compile_definitions("AL_SILENCE_DEPRECATION")

set(CMAKE_SYSTEM_NAME iOS)

set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_FIND_ROOT_PATH "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk")

set(TOOLCHAIN "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain")

set(CMAKE_OSX_SYSROOT ${CMAKE_FIND_ROOT_PATH})

set(CMAKE_OSX_ARCHITECTURES arm64)

set(CMAKE_IPHONEOS_DEPLOYMENT_TARGET 12.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER ${TOOLCHAIN}/usr/bin/cc)

set(CMAKE_C_FLAGS "-target arm64-apple-ios12.0 -g")

set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/usr/bin/c++)

set(CMAKE_CXX_FLAGS "-target arm64-apple-ios12.0 -g")

set(CMAKE_OBJCXX_COMPILER ${TOOLCHAIN}/usr/bin/c++)

set(CMAKE_OBJCXX_FLAGS "-target arm64-apple-ios12.0 -fobjc-arc -fobjc-weak -g")

set(THIRD_PARTY ${CMAKE_CURRENT_SOURCE_DIR}/../third_party)

include_directories(${THIRD_PARTY}/include)

link_directories(${THIRD_PARTY}/lib)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


set (SOURCES_ROOT ccmedia)

file(GLOB_RECURSE SOURCE_FILES 
"${SOURCES_ROOT}/*.h" 
"${SOURCES_ROOT}/*.cpp"
"${SOURCES_ROOT}/*.hpp"
"${SOURCES_ROOT}/*.c"
"${SOURCES_ROOT}/*.mm"
)


add_library(ccmedia  "${SOURCE_FILES}")

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

target_include_directories(ccmedia PUBLIC "type.h" "CCPlayer.h")



set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../export)

install(TARGETS ccmedia
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
# Install the header files
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ios
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/include
#     FILES_MATCHING PATTERN "*.h"
# )
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/type
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/include
#     FILES_MATCHING PATTERN "*.h"
# )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ccmedia
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ccmedia
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.h"
)