#include <opencv2/opencv.hpp>
#include <iostream>

int main( int argc, char** argv ) {
	
	cv::namedWindow( "Example2_10", cv::WINDOW_AUTOSIZE );
	cv::VideoCapture cap;
	if (argc==1) {
          cap.open(0);
	} else {
          std::cout << "Trying to open camera" << std::endl;
		cap.open(argv[1]);
          std::cout << "Camera is opened" << std::endl;
	}

	if( !cap.isOpened() ) { // check if we succeeded
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	cv::Mat frame;
	for(;;) {
		cap >> frame;
		if( frame.empty() ) break;
		cv::imshow( "Example2_10", frame );
		if( cv::waitKey(33) >= 0 ) break;
	}
	// Ran out of film
	return 0;
}
