mkdir out/ffmpeg

cp -rf out/ffmpeg-x86_64/include out/ffmpeg/include

mkdir out/ffmpeg/lib

lipo -create out/ffmpeg-x86_64/lib/libswresample.a out/ffmpeg-arm64/lib/libswresample.a -output  out/ffmpeg/lib/libswresample.a

lipo -create out/ffmpeg-x86_64/lib/libswscale.a out/ffmpeg-arm64/lib/libswscale.a -output  out/ffmpeg/lib/libswscale.a

lipo -create out/ffmpeg-x86_64/lib/libavutil.a out/ffmpeg-arm64/lib/libavutil.a -output  out/ffmpeg/lib/libavutil.a

lipo -create out/ffmpeg-x86_64/lib/libavformat.a out/ffmpeg-arm64/lib/libavformat.a -output  out/ffmpeg/lib/libavformat.a

lipo -create out/ffmpeg-x86_64/lib/libavcodec.a out/ffmpeg-arm64/lib/libavcodec.a -output  out/ffmpeg/lib/libavcodec.a
