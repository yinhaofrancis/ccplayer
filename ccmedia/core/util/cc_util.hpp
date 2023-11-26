//
//  util.h
//  CCRender
//
//  Created by wenyang on 2023/11/21.
//

#ifndef util_h
#define util_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <queue>
#include <deque>
#include <optional>
#include <algorithm>
#include <list>
#include <OpenAL/OpenAL.h>
 
extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}



namespace cc
{
    struct error
    {
        std::string msg;
        int code;

        error(std::string &msg, int code) : msg(msg), code(code)
        {
            std::cout << msg << std::endl;
        }

        error(std::string &&msg, int code) : msg(msg), code(code)
        {
            std::cout << msg << std::endl;
        }

        error(int err)
        {
            char buff[512];
            av_strerror(err, buff, 512);
            std::string cppmsg = msg;
            code = err;
            msg = cppmsg;
            std::cout << msg << std::endl;
        }
    };
};



#endif /* util_h */


