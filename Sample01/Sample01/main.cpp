//
//  main.cpp
//  Sample01
//
//  Created by CMBT on 18.11.21.
//

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
  // load the image
  string fileName = "resources/clara.bmp";
  Mat mat = cv::imread(fileName);
  // check if we were able to open it
  if (mat.data == NULL)
  {
    std::cout << "Can not load " << fileName << " wd: " << argv[0] << endl;
    return -1;
  }
  // show the image
  imshow(fileName, mat);
  // wait for a keyboard input
  waitKey();
  // that was it
  std::cout << "Done\n";
  return 0;
}
