#include "filter.h"
#include "config.h"

Filter::Filter(){}
/**
 * @brief Generates a Gaussian kernel.
 *
 * This function generates a Gaussian kernel of the specified size and sigma.
 *
 * @param kernelSize Size of the kernel (should be odd).
 * @param sigma Standard deviation of the Gaussian.
 * @return Mat representing the Gaussian kernel.
 */
Mat Filter::gaussianKernel(int kernelSize, float sigma){
    // The eq for the gaussian kernel is:
    // G(x,y) = 1/(2*pi*sigma^2) * e^(-((x^2 + y^2)/(2*sigma^2)))
    // The kernel is a 2D matrix with the center of the kernel at the center of the matrix
    Mat kernel = Mat::zeros(kernelSize, kernelSize, CV_32F);
    int center = kernelSize / 2;
    float sum = 0.0;
    for(int i = 0; i < kernelSize; i++){
        for(int j = 0; j < kernelSize; j++){
            int x = i - center;
            int y = j - center;
            kernel.at<float>(i, j) = exp(-((x * x + y * y) / (2 * sigma * sigma)));
            sum += kernel.at<float>(i, j);
        }
    }
    kernel /= sum; // Normalize the kernel
    return kernel;
}

/**
 * @brief Applies an average filter to the input image.
 *
 * This function applies an average filter to the input image using the specified kernel size.
 *
 * @param img Input image.
 * @param kernelSize Size of the kernel (should be odd).
 * @return Mat representing the filtered image.
 */

Mat Filter::avgFilter(Mat img, int kernelSize) {
    Mat result = img.clone();
    Mat kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
    filter2D(img, result, -1, kernel,Point(-1,-1), 0, BORDER_DEFAULT);
    return result;
}

/**
 * @brief Applies a Gaussian filter to the input image.
 *
 * This function applies a Gaussian filter to the input image using the specified kernel size and sigma.
 *
 * @param img Input image.
 * @param kernelSize Size of the kernel (should be odd).
 * @return Mat representing the filtered image.
 */

Mat Filter::gaussionFilter(Mat img, int kernelSize) {
    Mat result = img.clone();
        Mat kernel = gaussianKernel(kernelSize, 1.0);
        filter2D(result, result, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);

    return result;
}

// TODO: Implement median filter optimization , ET:10sec
// Mat Filter::medianFilter(Mat img, int kernelSize) {
//     Mat result = img.clone();
//     int center = kernelSize / 2;
//         for(int x = center; x < result.rows - center; x++){
//             for(int y = center; y < result.cols - center; y++){
//                 vector<int> values;
//                 for(int i = -center; i <= center; i++){
//                     for(int j = -center; j <= center; j++){
//                         values.push_back(result.at<uchar>(x + i, y + j));
//                     }
//                 }
//                 sort(values.begin(), values.end());
//                 result.at<uchar>(x, y) = values[values.size() / 2];
//             }
//         }


//     return result;
// }

/**
 * @brief Applies a median filter to the input image.
 *
 * This function applies a median filter to the input image using the specified kernel size.
 *
 * @param img Input image.
 * @param kernelSize Size of the kernel (should be odd).
 * @return Mat representing the filtered image.
 */

Mat Filter::medianFilter(Mat img, int kernelSize) {
    Mat result = img.clone();
    int center = kernelSize / 2;

    for (int x = center; x < result.rows - center; x++) {
        for (int y = center; y < result.cols - center; y++) {
            // Extract the kernel region
            Mat kernel = result(Rect(y - center, x - center, kernelSize, kernelSize)).clone();

            // Reshape the kernel to a column vector
            Mat kernelVec = kernel.reshape(1, kernelSize * kernelSize);

            // Sort the values along the column vector
            std::nth_element(kernelVec.data, kernelVec.data + kernelVec.rows * kernelVec.cols / 2, kernelVec.data + kernelVec.rows * kernelVec.cols);

            // Get the median value
            result.at<uchar>(x, y) = kernelVec.at<uchar>(kernelVec.rows * kernelVec.cols / 2);
        }
    }

    return result;
}

/**
 * @brief Applies Gaussian filtering to the input image.
 *
 * This function applies Gaussian smoothing to the input image using the specified kernel size.
 * Gaussian filtering is a widely used image processing technique for reducing noise and
 * blurring the image. It convolves the image with a Gaussian kernel to compute weighted averages
 * of neighboring pixels, effectively reducing high-frequency noise components.
 *
 * @param img The input image to be filtered.
 * @param kernelSize The size of the Gaussian kernel (should be an odd number).
 * @return The filtered image after applying Gaussian smoothing.
 */

Mat Filter::opencvGaussianFilter(Mat img, int kernelSize) {
    Mat result = img.clone();
    GaussianBlur(img, result, Size(kernelSize, kernelSize), 0, 0, BORDER_DEFAULT);
    return result;
}

/**
 * @brief Applies median filtering to the input image.
 *
 * This function applies median filtering to the input image using the specified kernel size.
 * Median filtering is a non-linear filtering technique used for removing noise from images
 * while preserving edges. It replaces each pixel's value with the median value of the intensities
 * in its neighborhood, effectively reducing the effect of outliers or salt-and-pepper noise.
 *
 * @param img The input image to be filtered.
 * @param kernelSize The size of the median filtering kernel (should be an odd number).
 * @return The filtered image after applying median filtering.
 */

Mat Filter::opencvMedianFilter(Mat img, int kernelSize) {
    Mat result = img.clone();
    medianBlur(img, result, kernelSize);
    return result;
}
/**
 * @brief Applies average (mean) filtering to the input image.
 *
 * This function applies average (mean) filtering to the input image using the specified kernel size.
 * Average filtering is a simple smoothing technique where each pixel's value is replaced by the
 * average of the intensities in its neighborhood. It helps in reducing noise and blurring the image.
 *
 * @param img The input image to be filtered.
 * @param kernelSize The size of the averaging kernel (should be an odd number).
 * @return The filtered image after applying average filtering.
 */
Mat Filter::opencvAvgFilter(Mat img, int kernelSize) {
    Mat result = img.clone();
    blur(img, result, Size(kernelSize, kernelSize), Point(-1, -1), BORDER_DEFAULT);
    return result;
}

/**
 * @brief Detects edges using Sobel operator.
 *
 * This function applies the Sobel operator to detect edges in the input image.
 * The Sobel operator performs edge detection by computing the gradient magnitude
 * of the image intensity at each pixel. It calculates approximations of the gradient
 * for the X and Y directions separately using convolution with specific kernels.
 * The resulting edge magnitude image represents the detected edges using the Sobel
 * operator.
 *
 * @param img The input image.
 * @return The resulting image with detected edges using the Sobel operator.
 */
Mat Filter::detectEdgeSobel(Mat img){

    Mat sobelX = detectEdgeSobelX(img);
    Mat sobelY = detectEdgeSobelY(img);
    Mat magnitude = edgeMagnitude(sobelX,sobelY);
    return magnitude;

}
/**
 * @brief Detects edges in the horizontal direction using Sobel operator.
 *
 * This function applies the Sobel operator to detect edges in the horizontal
 * direction of the input image. The Sobel operator calculates the gradient
 * in the X direction by performing convolution with a specific kernel. The
 * resulting image represents the detected edges in the horizontal direction.
 *
 * @param img The input image.
 * @return The resulting image with detected edges in the horizontal direction.
 */
Mat Filter::detectEdgeSobelX(Mat img){
    // Mat xFilter= (Mat_<float>(3,3)<<-1, 0, 1,
    //                                -2, 0, 2,
    //                                -1, 0, 1);
    Mat xFilter= (Mat_<float>(3,3)<<-1, 0, 1,
                                   -2, 0, 2,
                                   -1, 0, 1);

    Mat result;
    filter2D(img, result,CV_32F,xFilter,Point(-1,-1),0,BORDER_DEFAULT);
    return result;

}
/**
 * @brief Detects edges in the vertical direction using Sobel operator.
 *
 * This function applies the Sobel operator to detect edges in the vertical
 * direction of the input image. The Sobel operator calculates the gradient
 * in the Y direction by performing convolution with a specific kernel. The
 * resulting image represents the detected edges in the vertical direction.
 *
 * @param img The input image.
 * @return The resulting image with detected edges in the vertical direction.
 */

Mat Filter::detectEdgeSobelY(Mat img){
    // Mat yFilter= (Mat_<float>(3,3)<<   1,2,1,
    //                                    0,0,0,
    //                                   -1,-2,-1);
    Mat yFilter= (Mat_<float>(3,3)<<   -1,-2,-1,
                                           0,0,0,
                                           1,2,1);
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);

    return result;
}

/**
 * @brief Detects edges in the horizontal direction using Robert's operator.
 *
 * This function applies Robert's operator to detect edges in the horizontal direction
 * of the input image. The Robert's operator is a simple edge detection algorithm that
 * calculates the gradient of the image using a pair of 2x2 convolution kernels. The
 * horizontal edge detection kernel is:
 *      | 1  0 |
 *      | 0 -1 |
 * The function performs 2D convolution between the input image and the horizontal
 * edge detection kernel to produce the result.
 *
 * @param img The input image.
 * @return The resulting image with detected edges in the horizontal direction.
 */
Mat Filter::detectEdgeRobertX(Mat img){
    Mat yFilter= (Mat_<float>(2,2)<< 1,0,0,-1);
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);

    return result;
}
/**
 * @brief Detects edges in the vertical direction using Robert's operator.
 *
 * This function applies Robert's operator to detect edges in the vertical direction
 * of the input image. The Robert's operator is a simple edge detection algorithm that
 * calculates the gradient of the image using a pair of 2x2 convolution kernels. The
 * vertical edge detection kernel is:
 *      | 0  1 |
 *      | -1 0 |
 * The function performs 2D convolution between the input image and the vertical
 * edge detection kernel to produce the result.
 *
 * @param img The input image.
 * @return The resulting image with detected edges in the vertical direction.
 */
Mat Filter::detectEdgeRobertY(Mat img){

    Mat yFilter= (Mat_<float>(2,2)<< 0,1,-1,0);

    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);

    return result;
}
/**
 * @brief Detects edges using Robert's operator.
 *
 * This function applies Robert's operator to detect edges in both horizontal and
 * vertical directions of the input image. It calculates the edge magnitudes by
 * combining the results of applying Robert's operator in both directions. The
 * magnitude is obtained by taking the square root of the sum of squares of the
 * horizontal and vertical edge gradients. The resulting edge magnitude image
 * represents the detected edges using Robert's operator.
 *
 * @param img The input image.
 * @return The resulting image with detected edges using Robert's operator.
 */
Mat Filter::detectEdgeRobert(Mat img){

    Mat robertX = detectEdgeRobertX(img);
    Mat robertY = detectEdgeRobertY(img);
    Mat magnitude = edgeMagnitude(robertX,robertY);
    return magnitude;

}

/**
 * @brief Detects edges in the horizontal direction using the Prewitt operator.
 *
 * This function applies the Prewitt operator in the horizontal direction to detect edges
 * in the input image. The Prewitt operator is a simple gradient-based edge detector that
 * computes the gradient approximation along the horizontal axis. It convolves the input
 * image with a 3x3 kernel [-1, 0, 1; -1, 0, 1; -1, 0, 1] to detect vertical edges.
 *
 * @param img The input image.
 * @return The image containing detected edges in the horizontal direction.
 */
Mat Filter::detectEdgePrewittX(Mat img){

    Mat yFilter= (Mat_<float>(3,3)<< -1,0,1,-1,0,1,-1,0,1);

    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);

    return result;
}
/**
 * @brief Detects edges in the vertical direction using the Prewitt operator.
 *
 * This function applies the Prewitt operator in the vertical direction to detect edges
 * in the input image. The Prewitt operator is a simple gradient-based edge detector that
 * computes the gradient approximation along the vertical axis. It convolves the input
 * image with a 3x3 kernel [-1, -1, -1; 0, 0, 0; 1, 1, 1] to detect horizontal edges.
 *
 * @param img The input image.
 * @return The image containing detected edges in the vertical direction.
 */
Mat Filter::detectEdgePrewittY(Mat img){
    Mat yFilter= (Mat_<float>(3,3)<<-1,-1,-1,0,0,0,1,1,1 );
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);

    return result;
}
/**
 * @brief Detects edges using the Prewitt operator.
 *
 * This function applies the Prewitt operator to detect edges in the input image. It first
 * computes the horizontal edges using `detectEdgePrewittX`, then computes the vertical
 * edges using `detectEdgePrewittY`, and finally calculates the magnitude of edges using
 * `edgeMagnitude` function. The resulting image contains detected edges in both horizontal
 * and vertical directions.
 *
 * @param img The input image.
 * @return The image containing detected edges using the Prewitt operator.
 */
Mat Filter::detectEdgePrewitt(Mat img){

    Mat PrewittX = detectEdgePrewittX(img);
    Mat PrewittY = detectEdgePrewittY(img);
    Mat magnitude = edgeMagnitude(PrewittX,PrewittY);
    return magnitude;

    /**
 * @brief Detects edges using the Canny edge detector.
 *
 * This function applies the Canny edge detector to detect edges in the input image. The
 * Canny edge detector is a multi-stage algorithm that involves smoothing the image with
 * a Gaussian filter, finding the intensity gradients, applying non-maximum suppression,
 * and hysteresis thresholding. It takes two threshold parameters: low and high, to determine
 * which edges are strong and which are weak.
 *
 * @param img The input image.
 * @return The image containing detected edges using the Canny edge detector.
 */
}
Mat Filter::detectEdgeCanny(Mat img){
    int t_low = 50;
    int t_high= 250;
    Mat edges;
    cv::Canny(img,edges,t_low,t_high);
    return edges;
}


/**
 * @brief Computes the magnitude of edges from edge gradients.
 *
 * This function computes the magnitude of edges from the gradients along X and Y directions.
 *
 * @param edgeX Gradient along the X direction.
 * @param edgeY Gradient along the Y direction.
 * @return Mat representing the edge magnitude.
 */

Mat Filter::edgeMagnitude(Mat edgeX, Mat edgeY){
    Mat magnitude_Gradient = Mat::zeros(edgeX.rows,edgeX.cols,edgeX.type());
    magnitude(edgeX,edgeY,magnitude_Gradient);
    // cout <<Magnitude_Gradient.size();
    return magnitude_Gradient;
}
/**
 * @brief Converts a color image to grayscale.
 *
 * This function converts an input color image to grayscale using the weighted sum method,
 * where the weights for each color channel are provided by the formula:
 *      Y = 0.299 * R + 0.587 * G + 0.114 * B
 * It creates a new grayscale image with the same dimensions as the input image and iterates
 * over each pixel of the input image to calculate the corresponding grayscale value using
 * the specified weights. The resulting grayscale image is returned.
 *
 * @param img The input color image.
 * @return The grayscale image.
 */
Mat Filter::convertToGrayScale(Mat img)
{
    Mat greyScaledImg(img.rows, img.cols, CV_8UC1);
    float weights[3]  = {0.299, 0.587, 0.114};
    for(int i = 0; i < img.rows; i++){
        for(int j = 0; j < img.cols; j++){
            Vec3b currentPixel = img.at<Vec3b>(i, j); // Access pixel from input image
            float currentGreyValue = weights[0] * currentPixel[2] + weights[1] * currentPixel[1]
                                     + weights[2] * currentPixel[0];
            greyScaledImg.at<uchar>(i, j) = static_cast<uchar>(currentGreyValue);
        }
    }
    return greyScaledImg;
}

/**
 * @brief Applies frequency domain filtering to an image.
 *
 * This function applies frequency domain filtering to an input image using the Discrete Fourier Transform (DFT).
 * It first converts the image to 32-bit floating point format and then computes the DFT, splitting it into its real and imaginary parts.
 * A circular mask is created based on the specified radius to define the region for filtering.
 * Depending on the type of filter specified (LowPassFilter or HighPassFilter), the appropriate filtering operation is applied.
 * Finally, the inverse DFT is applied to obtain the filtered image.
 *
 * @param img The input image.
 * @param radius The radius of the circular mask for filtering.
 * @param Filter The type of filter to apply (LowPassFilter or HighPassFilter).
 * @return The filtered image.
 */

Mat Filter::applyFrequencyFilter(Mat img,int radius,int Filter){

    img.convertTo(img,CV_32F);
    // Get DFT and split it to real and imaginary
    Mat complexDftImage = Fourier::applyDFT(img);
    Mat real, imag;
    Mat planes[2];

    split(complexDftImage,planes);

    real = Fourier::applyShifting(planes[0]);
    imag = Fourier::applyShifting(planes[1]);

    // Create a circle mask
    int centerX = real.cols/2;
    int centerY = real.rows/2;
    Mat mask = Mat::zeros(real.size(),CV_8U);
    Mat alteredMask;
    circle(mask, Point(centerX,centerY), radius,Scalar(255),-1);
    bitwise_not(mask, alteredMask);

    // Apply the filter
    switch (Filter) {
    case LowPassFilter:
        real.setTo(Scalar(0), ~mask);
        imag.setTo(Scalar(0), ~mask);
        break;
    case HighPassFilter:
        real.setTo(Scalar(0), ~alteredMask);
        imag.setTo(Scalar(0), ~alteredMask);
    default:
        break;
    }

    // Shift the dft to its original
    real = Fourier::applyShifting(real);
    imag = Fourier::applyShifting(imag);

    planes[0]=real;
    planes[1]=imag;
    merge(planes, 2, img);

    // INVERSE DFT
    img = Fourier::applyIDFT(img);
    return img;

}

