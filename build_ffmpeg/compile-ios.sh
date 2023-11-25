ARCH="$1"

TARGET="darwin"
SDK="iPhoneOS"

TOOLCHAIN=""
TOOLCHAIN="$TOOLCHAIN --arch=$ARCH"  
TOOLCHAIN="$TOOLCHAIN --target-os=$TARGET"
TOOLCHAIN="$TOOLCHAIN --enable-cross-compile"

TARGET="arm64-apple-ios12.0"

CFLAGS=" -miphoneos-version-min=12.0"
CFLAGS=" -fembed-bitcode"

SYSTEM_INC="$"
#TOOLCHAIN="$TOOLCHAIN --sysroot=$SDKROOT --sysinclude=$SDKROOT/usr/include"
CXXFLAGS="$CFLAGS"

LDFLAGS=""

mkdir `pwd`/out/ffmpeg-$ARCH


CONFIG="--prefix=`pwd`/out/ffmpeg-$ARCH"
CONFIG="$CONFIG --disable-gpl"
CONFIG="$CONFIG --disable-nonfree "
CONFIG="$CONFIG --enable-runtime-cpudetect "
CONFIG="$CONFIG --disable-gray "
CONFIG="$CONFIG --disable-swscale-alpha "
CONFIG="$CONFIG --disable-programs "
CONFIG="$CONFIG --disable-ffmpeg "
CONFIG="$CONFIG --disable-ffplay "
CONFIG="$CONFIG --disable-ffprobe "
CONFIG="$CONFIG --disable-ffserver"
CONFIG="$CONFIG --disable-doc "
CONFIG="$CONFIG --disable-htmlpages "
CONFIG="$CONFIG --disable-manpages "
CONFIG="$CONFIG --disable-podpages "
CONFIG="$CONFIG --disable-txtpages "
CONFIG="$CONFIG --disable-avdevice "
CONFIG="$CONFIG --enable-avcodec "
CONFIG="$CONFIG --enable-avformat "
CONFIG="$CONFIG --enable-avutil "
CONFIG="$CONFIG --enable-swresample "
CONFIG="$CONFIG --enable-swscale "
CONFIG="$CONFIG --enable-postproc " 
CONFIG="$CONFIG --enable-avfilter "
CONFIG="$CONFIG --enable-network "
CONFIG="$CONFIG --disable-dxva2 "
CONFIG="$CONFIG --disable-vaapi "
CONFIG="$CONFIG --disable-vdpau " 
CONFIG="$CONFIG --disable-hwaccels "
CONFIG="$CONFIG --disable-devices "
CONFIG="$CONFIG --disable-iconv "
CONFIG="$CONFIG --enable-cross-compile "
CONFIG="$CONFIG --disable-stripping "
CONFIG="$CONFIG --enable-static "
CONFIG="$CONFIG --disable-shared "
CONFIG="$CONFIG --enable-pic "
CONFIG="$CONFIG --enable-neon "



if [ "$1" = "DEBUG" ]; then
    CONFIG=$CONFIG" --enable-optimizations" 
    CONFIG=$CONFIG" --enable-debug" 
    CONFIG=$CONFIG" --enable-small"
    
else
    CONFIG=$CONFIG" --disable-optimizations" 
    CONFIG=$CONFIG" --disable-debug" 
    CONFIG=$CONFIG" --disable-small"
fi

if [ "$ARCH" = "arm64" ]; then
    SDK="iPhoneOS"
    TARGET="arm64-apple-ios12.0"
elif [ "$ARCH" = "x86_64" ]; then
    SDK="iPhoneSimulator"
    TARGET="x86_64-apple-ios12.0-simulator"
fi
SDKROOT="/Applications/Xcode.app/Contents/Developer/Platforms/$SDK.platform/Developer/SDKs/$SDK""17.0.sdk"
echo "$SDKROOT"
SDK=`echo $SDK| tr '[:upper:]' '[:lower:]'`
CC="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang -target $TARGET -isysroot $SDKROOT"
echo "$CC"
CXX="/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang -x c++ -target $TARGET   -isysroot $SDKROOT"
echo "conpiling ........... \n"

./configure $CONFIG --cc="$CC" --cxx="$CXX" $TOOLCHAIN --extra-cflags="$CFLAGS" --extra-cxxflags="$CXXFLAGS" --extra-ldflags="$LDFLAGS"
make
make install
make clean