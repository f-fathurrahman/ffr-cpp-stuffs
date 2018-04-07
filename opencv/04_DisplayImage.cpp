#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char** argv )
{
  
  Mat img = imread( argv[1], -1 );

  if( img.empty() ) {
    return -1;
  }

  namedWindow( "04 DisplayImage", WINDOW_AUTOSIZE );

  imshow( "04 DisplayImage", img );

  waitKey( 0 );

  destroyWindow( "04 DisplayImage" );

  return 0;
}
