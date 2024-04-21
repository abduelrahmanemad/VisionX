# VisionX: Advanced Image Processing and Edge Detection Tool

VisionX is a sophisticated desktop application crafted in C++ utilizing the Qt framework. It offers a variety of options for manipulating images,with an easy to use interface, including noise addition, filtering, edge detection, histogram analysis, image equalization and normalization, thresholding, frequency domain filters, and the creation of hybrid images.

## Features

1. **Noise Addition**
   - Uniform, Gaussian, and Salt and Pepper Noise

2. **Filtering**
   - Low Pass Filters
   - Average, Gaussian, and Median Filters

3. **Edge Detection**
   - Sobel, Roberts, Prewitt, and Canny Edge Detection

4. **Histogram Analysis**
   - Generation and Visualization of Histograms
   - Plotting of Distribution Curves

5. **Image Equalization**

6. **Image Normalization**

7. **Thresholding**
   - Local and Global Thresholding Techniques

8. **Color Image Transformation**
   - Conversion to Grayscale
   - Plotting of RGB Histograms with Distribution Functions

9. **Frequency Domain Filters**
   - Highpass and Lowpass Filters

10. **Hybrid Image Creation**
    - Blending of Images to Create Hybrid Effects

## Getting Started

## Dependenices
    - Qt Version 6.4.2
    - OpenCV 4.9.0
    
### Installation

1. Ensure Qt is installed on your system.
2. Clone the VisionX repository to your local machine.

## How to run the project
- Download and Install Qt from the online installer using minGW 64 architecture.
```
www.qt.io
```
- Download and build openCV 4.7.0 from their website
```
www.opencv.org/releases/
```
- if you don't know how to build OpenCV on your PC please refer to the installCV.md

- Go to the Task1.pro file and ensure that openCV libraries are referred to in your pc like that.

Windows
``` 
INCLUDEPATH += <yourCV build folder path>\install\include

LIBS += -L<yourCV build folder path>\release\lib \
    -lopencv_calib3d490                 \
    -lopencv_core490                    \
    -lopencv_features2d490              \
    -lopencv_flann490                   \
    -lopencv_highgui490                 \
    -lopencv_imgproc490                 \
    -lopencv_imgcodecs490               \
    -lopencv_photo490                   \
    -lopencv_stitching490               \
    -lopencv_ts490                      \
    -lopencv_video490                   \
    -lopencv_videoio490                 \
    -lopencv_objdetect490               \
```

Linux
```
CONFIG += link_pkgconfig
PKGCONFIG += opencv4
```
### Building

1. Open the project in Qt Creator.
2. Make sure your profile matches commonpro.txt file
3. Build the project to generate the executable.

### Usage

1. Launch the application.
2. Open an image file.
3. Select desired operations from the menu.
4. Adjust parameters as needed.
5. View and save the processed image.

## Acknowledgments

We extend our gratitude to the Qt framework developers and the open-source community for their invaluable contributions to desktop application development.
