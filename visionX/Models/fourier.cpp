#include "fourier.h"
#include "config.h"

Fourier::Fourier(){}

/**
 * @brief Applies the Discrete Fourier Transform (DFT) to the input image.
 *
 * This function applies the DFT to the input image.
 *
 * @param img Input image.
 * @return Mat representing the Fourier-transformed image.
 */
Mat Fourier::applyDFT(Mat img){
    Mat fourierTransform;
    dft(img, fourierTransform, DFT_SCALE|DFT_COMPLEX_OUTPUT);
    return fourierTransform;
}

/**
 * @brief Applies the Inverse Discrete Fourier Transform (IDFT) to the input image.
 *
 * This function applies the IDFT to the input image.
 *
 * @param img Input image.
 * @return Mat representing the inverse Fourier-transformed image.
 */
Mat Fourier::applyIDFT(Mat img){
    Mat inverseOut;
    dft(img, inverseOut, DFT_INVERSE|DFT_REAL_OUTPUT);
    return inverseOut;
}

/**
 * @brief Shifts the zero-frequency component to the center of the Fourier spectrum.
 *
 * This function shifts the zero-frequency component of the input image to the center of the Fourier spectrum.
 *
 * @param img Input image.
 * @return Mat representing the Fourier-transformed image with the zero-frequency component shifted to the center.
 */
Mat Fourier::applyShifting(Mat img){
    Mat tmp, q0, q1, q2, q3; // Quadrants that will be swapped

    Mat outputShift = img.clone();

    int centerX = img.cols / 2;
    int centerY = img.rows / 2;

    q0 = outputShift(Rect(0, 0, centerX, centerY)); // Upper left corner
    q1 = outputShift(Rect(centerX, 0, centerX, centerY)); // Upper right corner
    q2 = outputShift(Rect(0, centerY, centerX, centerY)); // Lower left corner
    q3 = outputShift(Rect(centerX, centerY, centerX, centerY)); // Lower right corner

    // Switching q0 by q3 and q1 by q2
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    return outputShift;
}
