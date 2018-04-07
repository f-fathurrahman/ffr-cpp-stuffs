#!/bin/bash
basn=`basename $1 .cpp`

PRE=/home/efefer/mysoftwares/opencv-3.4.1
PRELIB=$PRE/lib

CORE=$PRELIB/libopencv_core.a
IMGPROC=$PRELIB/libopencv_imgproc.a
IMGCODECS=$PRELIB/libopencv_imgcodecs.a
HIGHGUI=$PRELIB/libopencv_highgui.a

ITT=$PRE/share/OpenCV/3rdparty/lib/libittnotify.a
IPROTO=$PRE/share/OpenCV/3rdparty/lib/liblibprotobuf.a

INC="-I$PRE/include"

LIBS="$IMGCODECS $HIGHGUI $IMGPROC $CORE $ITT \
-lblas -llapack -ltiff -ljpeg -lgtk-3 -lgdk-3 -lcairo -lgdk_pixbuf-2.0 \
-lgobject-2.0 -lglib-2.0 -lpng12 -ljasper -lIlmImf -lwebp -lpthread -lz -ldl"

rm -vf $basn.x

g++ -Wall $INC $1 -o $basn.x $LIBS

echo "Executable: $basn.x"

