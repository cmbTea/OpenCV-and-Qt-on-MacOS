# OpenCV and Qt on MacOS

## Introduction

Starting with OpenCV and Qt on MacOS is a bit of difficult if you haven't installed and used libraries in XCode. This tutorial will help you to get up and running quickly and it helps in avoiding common mistakes.  

## Installing OpenCV on MacOS

There are two choices to install OpenCV on your system. The most simple one is to install it using  <a href="https://brew.sh" target="blank">homebrew/</a>. On the website you will find a detailed description on how to install homebrew on your system and I recommend using it as some sort of general tool to install different packages on your system even when I don't recommend it to install OpenCV. More on the reasons for this will follow soon after describing the setup using homebrew.

### Using homebrew

After installing homebrew we can use the ```brew``` command. Start a terminal and enter:

```bash
brew info opencv
```

This will output information about the OpenCV homebrew package such as this:

```bash
opencv: stable 4.5.3 (bottled)
Open source computer vision library
https://opencv.org/
Not installed
From: https://github.com/Homebrew/homebrew-core/blob/HEAD/Formula/opencv.rb
License: Apache-2.0
==> Dependencies
Build: cmake ✔, pkg-config ✔
Required: ceres-solver ✔, eigen ✔, ffmpeg ✔, glog ✔, harfbuzz ✔, jpeg ✔, libpng ✔, libtiff ✔, numpy ✘, openblas ✔, openexr ✔, protobuf ✘, python@3.9 ✔, tbb ✔, vtk ✔, webp ✔
==> Analytics
install: 10,459 (30 days), 36,463 (90 days), 198,212 (365 days)
install-on-request: 10,111 (30 days), 35,184 (90 days), 188,859 (365 days)
build-error: 0 (30 days)
```

It's important to know that OpenCV has different packages. There is the core package as well as the so called **Contrib Package** that includes some more algorithms which are perhaps not released or fully tested as well as some algorithms that are patented and therefore some more difficult to use in terms of licensing. There are also some e.g. **cuda** optimized versions of the libraries that you might want to use. The following shows the brew command to install opencv together with some of those options that was working for a long time: 

```bash
brew install opencv --with-contrib --with-examples --with-ffmpeg --with-gstreamer --with-cuda --with-qt5
```

Unfortunately the optional components are no longer installable using the command above so that you can only install the OpenCV standard binaries with:  

```bash
brew install opencv
```

This is the reason why I recommend to use install OpenCV by building it from the sources available on <a href="https://github.com/opencv" target="blank">GitHub</a>.

### Building OpenCV from source

You can use the following procedure to build OpenCV from source code as it is also described on <a href="https://www.pyimagesearch.com/2018/08/17/install-opencv-4-on-macos/" target="blank">PyImageSearch.com</a>. The article is pretty good but it is concentrating on OpenCV for Python.  
It includes many helpful information which I modified slightly leaving out the Python installation using *virtualenv* and *virtualenvwrapper* as a virtual Python environment. Indeed I prefer and use *PyEnv* for this and if you like you may look at <a href="http://mb.cmbt.de/system-setup/installing-python/" target="blank">another project to which I contribute</a>. There you will find a documentation on how to install homebrew and PyEnv on MacOS as well as setting up a Raspberry Pi and/or Odroid system to make use of Docker to host a website as well as a Rest API.  

The procedure to build OpenCV from source is not very difficult and the Python integration is simple as well. Maybe I will write about that later as well. Of course you will need XCode installed on your Mac or at least Apples *XCode Command Line Tools* which are installed automatically with XCode versions >6.1. The command line tools are required to use *make*, *gcc* and *clang*. If you don't want to install the big XCode package you can install the *XCode Command Line Tools* separately via:

```bash
sudo xcode-select --install
```

I recommend installing XCode as this documentation will describe how to build OpenCV and Qt projects using it.  
To generate a makefile to build the sources we need *CMake*. If you haven't installed *CMake* yet you should do it now using:

```bash
brew install cmake
```

Now go to the OpenCV GitHub repository under <a href="https://github.com/opencv" target="blank">https://github.com/opencv</a>.  
We need to download two components in source code, *OpenCV* and *OpenCV_Contrib*:

<img src="doc/01.png" width="55%">

Click on *OpenCV* and then under *Releases* on *OpenCV-4.5.4 Latest*:

<img src="doc/02.jpg" width="55%">  

Copy the file to your user directory and then do the same with *OpenCV_contrib*:

<img src="doc/03.png" width="55%">
<img src="doc/04.png" width="55%">

Finally unpack the archives and rename their directories to ```opencv``` and ```opencv_contrib```:

<img src="doc/05.png" width="55%">

Open a terminal and cd into the ```opencv``` directory to create a new directory named ```build```:

```bash
cd ~/opencv
mkdir build
cd build
```

Finally we can create the makefile using:

```bash
cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
-D PYTHON3_LIBRARY=`python -c 'import subprocess ; import sys ; s = subprocess.check_output("python-config --configdir", shell=True).decode("utf-8").strip() ; (M, m) = sys.version_info[:2] ; print("{}/libpython{}.{}.dylib".format(s, M, m))'` \
-D PYTHON3_INCLUDE_DIR=`python -c 'import distutils.sysconfig as s; print(s.get_python_inc())'` \
-D PYTHON3_EXECUTABLE=$VIRTUAL_ENV/bin/python \
-D BUILD_opencv_python2=OFF \
-D BUILD_opencv_python3=ON \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D INSTALL_C_EXAMPLES=OFF \
-D OPENCV_ENABLE_NONFREE=ON \
-D BUILD_EXAMPLES=ON ..
```

CMake will generate the make file and we can invoke the make process now:

```bash
make
````

It takes up to 2 hours to build all libraries and samples but beside waiting it was very simple. At the end of the process you will find the libraries in the build/lib directory and all the executables of the samples in the /bin directory.

Finally the include files and libraries need to be installed on the system. Execute the following:

```bash
make install
```

This will copy the OpenCV dynamic libraries to the ```/usr/lib``` directory and include files to ```/usr/local/include/opencv4```:

<img src="doc/06.png" width="55%">  

<img src="doc/07.png" width="55%">  

As we installed and built the samples as well we can test our system now by starting one of the OpenCV example programs from the OpenCV ```bin``` directory:  

```bash
cd bin
./example_cpp_edge
````

<img src="doc/08.png" width="55%"> 

Our system is finally ready to start developing with OpenCV.  

## A first OpenCV application in XCode

Now we can start with a first, very simple, example using Xcode. Start Xcode and select *MacOS* as the platform and *Command Line Tool* as the application type:  

<img src="doc/09.png" width="55%"> 

Click *Next* and select *Sample01* as the product name and *C++* as the language:  

<img src="doc/10.png" width="55%"> 

End the generator with *Finish*. XCode will create a new project workspace for us. The first thing to do is to add the /usr/local/include/openCV directory to our search path for header files. The project settings are already open and we need to click *Build Settings*:

<img src="doc/11.png" width="55%"> 

Select the *Search* box and type *search*, the search results will include the *Header Search Paths*. Double click the empty item right of it and add the line ```/usr/local/include/opencv4```. Ensure to select *recursive* as we need to recursively include files from this root directory:

<img src="doc/12.png" width="55%"> 

Of course we need to add the OpenCV libraries to our project as well. In the *Project Navigator* right click the project folder icon and select *New Group*. Name it *openCV:

<img src="doc/13.png" width="25%"> 

Open the *Finder* and go to the ```usr/local/lib``` folder. Select all the dynamic loadable libraries of OpenCV. Be sure not to select the aliases that are installed in this directory as well. You can see the *Type* column in Finder:

<img src="doc/14.png" width="55%"> 

Drag all of these files to the newly created group in XCode:

<img src="doc/15.png" width="25%"> 

For the convenience we add a folder called ```resources```. In there you will find some sample images and in this first sample we want to use one of them. To enable access to that folder we need to make it the *custom working folder* for our application. Click the *Sample01* folder icon in the top of the XCode window and select *Edit Scheme...*:

<img src="doc/16.png" width="55%"> 

Click the *Run* icon and check the *Use custom working directory* option. Use the path to this repository as the working directory:

<img src="doc/17.png" width="55%"> 

Now let's edit *main.cpp*. First we need to include some OpenCV header and make use of its namespace. Within the main function we load an image and show it. This is the code:

```cpp
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
```

Press <kbd>CMD</kbd> + <kbd>B</kbd> to build it and <kbd>CMD</kbd> + <kbd>R</kbd> to run it:

<img src="doc/18.png" width="25%"> 

End it by pressing any key on the keyboard.
