#include <cstdio>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main( int argc, char** argv )
{

  if( argc != 2 ) {
    printf("Need one parameter: video_path\n");
    return -1;
  }

  cv::namedWindow( "05_PlayVideo", cv::WINDOW_AUTOSIZE );

  cv::VideoCapture cap;

  cap.open( std::string(argv[1]) );

  cv::Mat frame;
  for(;;) {
    cap >> frame;
    if( frame.empty() ) break;
    cv::imshow( "05_PlayVideo", frame );
    if( cv::waitKey(33) >= 0 ) break;
  }

  cv::destroyWindow( "05_PlayVideo" );

  return 0;
}
