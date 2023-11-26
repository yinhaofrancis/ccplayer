cmake_minimum_required(VERSION 3.10)

project(ccmedia_ios VERSION 0.1.0 LANGUAGES C CXX OBJC OBJCXX)

add_compile_definitions("GLES_SILENCE_DEPRECATION")

add_compile_definitions("AL_SILENCE_DEPRECATION")

set(CMAKE_CXX_STANDARD 17)


set (RANGE "apple_mobile")

if(RANGE STREQUAL "apple_mobile")
    if(PLATFORM STREQUAL "iphone")
        set(TARGET "arm64-apple-ios12.0")
        set(SDK "iPhoneOS")
        set(ARCH "arm64")
        set(CMAKE_SYSTEM_PROCESSOR aarch64)
        message("iPhone  ")
    elseif(PLATFORM STREQUAL "x86simulator")
        set(TARGET "x86_64-apple-ios12.0-simulator")
        set(SDK "iPhoneSimulator")
        set(ARCH "x86_64")
        set(CMAKE_SYSTEM_PROCESSOR x86_64)
        message("iPhone Simulator ")
    else()
        set(TARGET "arm64-apple-ios12.0-simulator")
        set(SDK "iPhoneSimulator")
        set(ARCH "arm64")
        set(CMAKE_SYSTEM_PROCESSOR aarch64)
        message("iPhone arm Simulator ")
    endif()


    set(CMAKE_SYSTEM_NAME iOS)

    

    set(CMAKE_FIND_ROOT_PATH "/Applications/Xcode.app/Contents/Developer/Platforms/${SDK}.platform/Developer/SDKs/${SDK}.sdk")

    set(TOOLCHAIN "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain")

    set(CMAKE_OSX_SYSROOT ${CMAKE_FIND_ROOT_PATH})

    set(CMAKE_OSX_ARCHITECTURES ${ARCH})

    set(CMAKE_IPHONEOS_DEPLOYMENT_TARGET 12.0)

    set(CMAKE_C_COMPILER ${TOOLCHAIN}/usr/bin/cc)

    set(CMAKE_C_FLAGS "-target ${TARGET} -g")

    set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/usr/bin/c++)

    set(CMAKE_CXX_FLAGS "-target ${TARGET} -g")

    set(CMAKE_OBJCXX_COMPILER ${TOOLCHAIN}/usr/bin/c++)

    set(CMAKE_OBJCXX_FLAGS "-target ${TARGET} -fobjc-arc -fobjc-weak -g")

    set(THIRD_PARTY ${CMAKE_CURRENT_SOURCE_DIR}/../../third_party)

    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

    include_directories(${THIRD_PARTY}/include)

    add_library(ccmedia_ios  CCPlayer.h CCPlayer.mm)

    
    # add_subdirectory(core)
    
    # add_subdirectory(render)

    # set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../export)

    # install(TARGETS ccmedia_ios
    #     ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    # )

    # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ccmedia
    #     DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    #     FILES_MATCHING PATTERN "*.hpp"
    # )
    # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ccmedia
    #     DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    #     FILES_MATCHING PATTERN "*.h"
    # )

endif()


