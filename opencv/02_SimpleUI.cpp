#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main( int argc, char** argv)
{

  Mat lena = imread("./lena.jpg");
  Mat photo = imread("./Bee_on_Yellow_Flower.jpg");

  // windows
  namedWindow("Lena", CV_GUI_NORMAL);
  namedWindow("Photo", WINDOW_AUTOSIZE);

  // move window
  moveWindow("Lena", 10, 10);
  moveWindow("Photo", 520, 10);

  imshow("Lena", lena);
  imshow("Photo", photo);

  // resize window
  resizeWindow("Lena", 512, 512);

  waitKey(0);

  destroyWindow("Lena");
  destroyWindow("Photo");

  // create 10 windows
  for( int i = 0; i < 10; i++ ) {
    ostringstream ss;
    ss << "Lena " << i;
    cout << ss.str() << endl;
    namedWindow(ss.str());
    moveWindow(ss.str(), 20*i, 20*i);
    imshow(ss.str(), lena);
  }

  waitKey(0);
  destroyAllWindows();

  return 0;

}
