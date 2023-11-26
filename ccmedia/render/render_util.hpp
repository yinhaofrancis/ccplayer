#ifndef RENDER_UTIL_H

#define RENDER_UTIL_H
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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include<OpenAL/OpenAL.h>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}


#endif