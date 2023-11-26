cmake_minimum_required(VERSION 3.10)

project(ccmedia_program VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(PLATFORM "iphone" CACHE INTERNAL "")

set(THIRD_PARTY ${CMAKE_CURRENT_SOURCE_DIR}/../third_party_mac )

include_directories(${THIRD_PARTY}/include)

link_directories(${THIRD_PARTY}/lib)

add_subdirectory(core)

add_subdirectory(render)

add_subdirectory(ios)


list(APPEND EXTRA_LIBS 
        "-framework Foundation"
        "-framework CoreGraphics"
        "-framework AudioToolBox"
        "-framework VideoToolBox"
        "-framework CoreVideo"
        "-framework CoreMedia"
        "-framework Security"
        "-framework avfoundation"
    )

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
        lzma
        bz2
        x264
        ${EXTRA_LIBS}
    )



# add_executable(ccmedia main.cpp)
# target_link_libraries(
#     ccmedia 
#     ccmedia_core
#     ${ALL_LINK}
#     )




# add_executable(ccmedia_program main.cpp)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../export)

install(TARGETS ccmedia_core
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/encoder 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core
    FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/encoder
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core
    FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/player
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core
    FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/player
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core
    FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/util
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core
    FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/util
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/core
    FILES_MATCHING PATTERN "*.h"
)


install(TARGETS ccmedia_render
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/render 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/render
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.h"
)


install(TARGETS ccmedia_ios
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ios
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.hpp"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ios
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    FILES_MATCHING PATTERN "*.h"
)