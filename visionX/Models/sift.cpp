#include "sift.h"

SIFTX::SIFTX() {}

const float PI = acos(-1.0);

/**
 * @brief Converts a grayscale image represented as uchar (8-bit) to float (32-bit) format.
 * Each pixel value is normalized to the range [0, 1].
 * 
 * @param Image1 Input grayscale image of type CV_8UC1 (8-bit, single-channel uchar).
 * @param Image2 Output grayscale image of type CV_32FC1 (32-bit floating-point, single-channel float).
 */
void SIFTX:: char_to_float( Mat& Image1,  Mat&Image2) {
    Image2 =  Mat::zeros(Image1.rows, Image1.cols, CV_32FC1);

    for (int i = 0;i < Image1.rows;i++) {
        for (int j = 0;j < Image1.cols;j++) {
            Image2.at<float>(i, j) = Image1.at<uchar>(i, j) / 255.0;
        }
    }
}
/**
 * @brief Downsamples the input image by a specified factor using Gaussian pyramid downscaling.
 * 
 * @param I Input image to be downsampled.
 * @param factor Factor by which to downsample the input image. For example, a factor of 2 would halve the width and height of the image.
 * @return The downsampled image.
 */
Mat SIFTX:: subsample( Mat& I, float factor) {
    Mat tmp = I, dst = I;
    pyrDown(tmp, dst,  Size(tmp.cols / factor, tmp.rows / factor));
    return dst;
}

/**
 * @brief Constructs an image pyramid by downsampling the input image iteratively.
 * 
 * @param I Input image for constructing the pyramid.
 * @param levels Number of levels in the pyramid.
 * @return A vector of Mat objects representing the image pyramid, with each level downsampled from the previous one.
 */
vector< Mat>SIFTX:: get_pyramid( Mat& I, int levels) {
    Mat tmp = I, dst = I;
    vector<Mat> pyramid;

    // Pyramid ---> [dst, subsample(dst, 2), subsample(subsample(dst, 2), 2), ...]

    int level = 0;
    pyramid.push_back(dst);

    level++;

    while (level < levels) {
        dst = subsample(tmp, 2);
        pyramid.push_back(dst);
        level++;
        tmp = dst;
    }

    return pyramid;
}

/**
 * @brief Constructs a scale space representation of the input image by building an image pyramid and applying Gaussian blurring at different scales.
 * 
 * @param I Input image for constructing the scale space.
 * @param sigma Standard deviation of the Gaussian kernel for the initial blurring.
 * @param scale_space Output scale space representation of the image. It is a 2D vector where the first dimension corresponds to the level of the pyramid and the second dimension corresponds to different scales within each level.
 * @param k Factor by which the standard deviation of the Gaussian kernel is multiplied at each level of the pyramid.
 */
void SIFTX:: get_scale_space( Mat& I, float sigma,vector<vector< Mat>>& scale_space,float k) {
    vector<Mat> pyramid = SIFTX::get_pyramid(I, 4);
    for (int i = 0;i < 4;i++) {
        // Using Size(0, 0) makes the code more adaptable because you don't need to manually specify the kernel size.
        GaussianBlur(pyramid[i], pyramid[i],  Size(0, 0), sigma);
        scale_space[i][0] = pyramid[i];

        for (int j = 1;j < 5;j++) {
            Mat aux;
            GaussianBlur(pyramid[i], aux,  Size(0, 0), pow(k, j) * sigma);
            scale_space[i][j] = aux;
        }
    }
}

/**
 * @brief Computes the Difference of Gaussians (DoG) by subtracting adjacent scales within the provided scale space.
 * 
 * @param scale_space Input scale space representation of the image. It is a 2D vector where the first dimension corresponds to the level of the pyramid, and the second dimension corresponds to different scales within each level.
 * @param DoG Output vector representing the Difference of Gaussians (DoG). It is a 2D vector with the same dimensions as the scale space, where each element stores the difference between adjacent scales.
 */

void SIFTX:: get_DoG(vector<vector< Mat>>& scale_space, vector<vector< Mat>>& DoG) {
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            DoG[i][j] = abs(scale_space[i][j + 1] - scale_space[i][j]);
        }
    }
}

/**
 * @brief Determines if a pixel in the middle image is a local maximum among its neighbors within the same scale and adjacent scales.
 * 
 * @param I1 Upper adjacent image in the scale space.
 * @param I2 Middle image in the scale space.
 * @param I3 Lower adjacent image in the scale space.
 * @param row Row index of the pixel to be checked.
 * @param col Column index of the pixel to be checked.
 * @return True if the pixel is a local maximum, otherwise false.
 */

bool SIFTX::is_max( Mat& I1,  Mat& I2,  Mat& I3, int row, int col) {
    for (int i = -1;i <= 1;i++) {
        for (int j = -1;j <= 1;j++) {
            if (i == 0 && j == 0) continue;

            if (I2.at<float>(row, col) < I2.at<float>(row + i, col + j)) return false;
        }
    }

    for (int i = -1;i <= 1;i++) {
        for (int j = -1;j <= 1;j++) {
            if (I2.at<float>(row, col) < I1.at<float>(row + i, col + j) ||
                I2.at<float>(row, col) < I3.at<float>(row + i, col + j)) return false;
        }
    }

    return true;
}

/**
 * @brief Determines if a pixel in the middle image is a local minimum among its neighbors within the same scale and adjacent scales.
 * 
 * @param I1 Upper adjacent image in the scale space.
 * @param I2 Middle image in the scale space.
 * @param I3 Lower adjacent image in the scale space.
 * @param row Row index of the pixel to be checked.
 * @param col Column index of the pixel to be checked.
 * @return True if the pixel is a local minimum, otherwise false.
 */

bool SIFTX:: is_min( Mat& I1,  Mat& I2,  Mat& I3, int row, int col) {
    for (int i = -1;i <= 1;i++) {
        for (int j = -1;j <= 1;j++) {
            if (i == 0 && j == 0) continue;

            if (I2.at<float>(row, col) > I2.at<float>(row + i, col + j)) return false;
        }
    }

    for (int i = -1;i <= 1;i++) {
        for (int j = -1;j <= 1;j++) {
            if (I2.at<float>(row, col) > I1.at<float>(row + i, col + j) ||
                I2.at<float>(row, col) > I3.at<float>(row + i, col + j)) return false;
        }
    }

    return true;
}


/**
 * @brief Detects keypoints in each level of the Difference of Gaussians (DoG) pyramid.
 * 
 * @param DoG Difference of Gaussians (DoG) pyramid representing scale space.
 * @param keypoints Output vector containing detected keypoints. It is a 2D vector where the first dimension corresponds to the level of the pyramid, and the second dimension contains two matrices representing keypoints detected as maxima and minima.
 */
void SIFTX:: get_keypoints(vector<vector< Mat>>& DoG, vector<vector< Mat>>&keypoints) {

    // Iterate over each level of the DoG pyramid
    for (int i = 0;i < 4;i++) {
        Mat first = DoG[i][0];
        Mat second = DoG[i][1];
        Mat third = DoG[i][2];
        Mat fourth = DoG[i][3];
        // Initialize matrices to store keypoints detected as maxima and minima
        Mat keypoints1 =  Mat::zeros(first.rows, first.cols, CV_32FC1);
        Mat keypoints2 =  Mat::zeros(first.rows, first.cols, CV_32FC1);
        
        // Iterate over pixels in the second DoG image
        for (int row = 1; row < second.rows - 1; row++) {
            for (int col = 1; col < second.cols - 1; col++) {
                if (is_max(first, second, third, row, col) || is_min(first, second, third, row, col))
                    keypoints1.at<float>(row, col) = 1;

                if (is_max(second, third, fourth, row, col) || is_min(second, third, fourth, row, col))
                    keypoints2.at<float>(row, col) = 1;
            }
        }

        keypoints[i][0] = keypoints1;
        keypoints[i][1] = keypoints2;
    }

}

/**
 * @brief Removes keypoints with low contrast in each level of the Difference of Gaussians (DoG) pyramid.
 * 
 * @param keypoints Vector containing detected keypoints. It is a 2D vector where the first dimension corresponds to the level of the pyramid, and the second dimension contains two matrices representing keypoints detected as maxima and minima.
 * @param DoG Difference of Gaussians (DoG) pyramid representing scale space.
 * @param contrast_threshold Threshold value for contrast. Keypoints with a contrast below this threshold will be removed.
 */

void SIFTX:: remove_low_contrast(vector<vector< Mat>>& keypoints, vector<vector< Mat>>& DoG, float contrast_threshold) {
    // Iterate over each level of the DoG pyramid
    for (int i = 0;i < 4;i++) {

        Mat second = DoG[i][1]; // Current DoG image
        Mat third = DoG[i][2]; // Next DoG image

        // Iterate over pixels in the second DoG image
        for (int row = 0; row < second.rows; row++) {

            for (int col = 0; col < second.cols; col++) {

                if (keypoints[i][0].at<float>(row, col) == 1 && second.at<float>(row, col) < contrast_threshold)

                    keypoints[i][0].at<float>(row, col) = 0;

                if (keypoints[i][1].at<float>(row, col) == 1 && third.at<float>(row, col) < contrast_threshold)

                    keypoints[i][1].at<float>(row, col) = 0;
            }
        }
    }
}


/**
 * @brief Removes keypoints likely to be located on edges in each level of the Difference of Gaussians (DoG) pyramid.
 * 
 * @param keypoints Vector containing detected keypoints. It is a 2D vector where the first dimension corresponds to the level of the pyramid, and the second dimension contains two matrices representing keypoints detected as maxima and minima.
 * @param DoG Difference of Gaussians (DoG) pyramid representing scale space.
 * @param edge_threshold Threshold value for edge detection. Keypoints with Hessian eigenvalues indicating edge-like structures above this threshold will be removed.
 */
void SIFTX::remove_edges(vector<vector<Mat>>& keypoints, vector<vector<Mat>>& DoG, float edge_threshold) {
    // Iterate over each level of the DoG pyramid
    for (int i = 0; i < 4; i++) {
        Mat second = DoG[i][1]; // Current DoG image
        Mat third = DoG[i][2]; // Next DoG image

        // Iterate over pixels in the second DoG image, excluding borders
        for (int row = 1; row < second.rows - 1; row++) {
            for (int col = 1; col < second.cols - 1; col++) {
                // Compute elements of the Hessian matrix
                float dxx = second.at<float>(row, col + 1) + second.at<float>(row, col - 1) - 2 * second.at<float>(row, col);
                float dyy = second.at<float>(row + 1, col) + second.at<float>(row - 1, col) - 2 * second.at<float>(row, col);
                float dxy = (second.at<float>(row + 1, col + 1) + second.at<float>(row - 1, col - 1) - second.at<float>(row - 1, col + 1) - second.at<float>(row + 1, col - 1)) / 4;

                // Compute trace and determinant of the Hessian matrix
                float trH = dxx + dyy;
                float detH = dxx * dyy - dxy * dxy;

                // Check if the pixel is likely to be on an edge
                if (detH < 0 || ((trH * trH) / detH) > (((edge_threshold + 1) * (edge_threshold + 1)) / edge_threshold))
                    keypoints[i][0].at<float>(row, col) = 0; // Remove the keypoint

                // Repeat the process for the next DoG image
                dxx = third.at<float>(row, col + 1) + third.at<float>(row, col - 1) - 2 * third.at<float>(row, col);
                dyy = third.at<float>(row + 1, col) + third.at<float>(row - 1, col) - 2 * third.at<float>(row, col);
                dxy = (third.at<float>(row + 1, col + 1) + third.at<float>(row - 1, col - 1) - third.at<float>(row - 1, col + 1) - third.at<float>(row + 1, col - 1)) / 4;
                trH = dxx + dyy;
                detH = dxx * dyy - dxy * dxy;

                if (detH < 0 || ((trH * trH) / detH) > (((edge_threshold + 1) * (edge_threshold + 1)) / edge_threshold))
                    keypoints[i][1].at<float>(row, col) = 0; // Remove the keypoint
            }
        }
    }
}

/**
 * @brief Draws keypoints on the input image, with varying size and color based on the level at which they were detected.
 * 
 * @param I Input image on which keypoints are to be drawn.
 * @param keypoints Vector containing detected keypoints. It is a 2D vector where the first dimension corresponds to the level of the pyramid, and the second dimension contains two matrices representing keypoints detected as maxima and minima.
 */
void SIFTX:: draw_keypoints( Mat& I, vector<vector< Mat>>& keypoints) {
    for (int k = 0;k < 4;k++) {
        for (int i = 0;i < keypoints[k][0].rows;i++) {
            for (int j = 0;j < keypoints[k][0].cols;j++) {
                if (keypoints[k][0].at<float>(i, j) == 1.0 || keypoints[k][1].at<float>(i, j) == 1.0) {
                    if (k == 0) circle(I,  Point(((int)pow(2, k)) * j, ((int)pow(2, k)) * i), 8,  Scalar(255, 0, 0));
                    else if (k == 1) circle(I,  Point(((int)pow(2, k)) * j, ((int)pow(2, k)) * i), 7,  Scalar(0, 255, 0));
                    else if (k == 1) circle(I,  Point(((int)pow(2, k)) * j, ((int)pow(2, k)) * i), 6,  Scalar(0, 0, 255));
                    else if (k == 2) circle(I,  Point(((int)pow(2, k)) * j, ((int)pow(2, k)) * i), 5,  Scalar(255, 255, 0));
                    else circle(I,  Point(((int)pow(2, k)) * j, ((int)pow(2, k)) * i), 4,  Scalar(0, 255, 255));
                }
            }
        }
    }
}



/**
 * @brief Performs the Scale-Invariant Feature Transform (SIFT) algorithm to detect keypoints in the input image.
 * 
 * @param input_img Input image for which keypoints are to be detected.
 * @param keypoints_img Output image with keypoints visualized.
 * @param keypoints Vector containing detected keypoints. It is a 2D vector where the first dimension corresponds to the level of the pyramid, and the second dimension contains two matrices representing keypoints detected as maxima and minima.
 * @param scale_space Output scale space representation of the input image.
 * @param sigma Standard deviation of the Gaussian kernel for image blurring.
 * @param contrast_threshold Threshold value for contrast to remove low-contrast keypoints.
 * @param edge_threshold Threshold value for edge detection to remove keypoints likely to be located on edges.
 * @param k Scale factor between adjacent levels of the scale space.
 */
void SIFTX:: sift_keypoints(Mat& input_img,Mat& keypoints_img, vector<vector<Mat>>&keypoints, vector<vector<Mat>>&scale_space,float sigma, float contrast_threshold, float edge_threshold, float k) {
    Mat gray_img_converted;
    char_to_float(input_img, gray_img_converted);
    scale_space= vector<vector<Mat>>(4, vector<Mat>(5));
    get_scale_space(gray_img_converted, sigma,scale_space,k);
    vector<vector<Mat>> DoG(4, vector<Mat>(4));
    get_DoG(scale_space,DoG);
    keypoints= vector<vector<Mat>>(4, vector<Mat>(2));
    get_keypoints(DoG,keypoints);
    remove_low_contrast(keypoints, DoG,contrast_threshold);
    remove_edges(keypoints, DoG, edge_threshold);
    keypoints_img = input_img.clone();
    draw_keypoints(keypoints_img, keypoints);
}



float SIFTX::get_angle(float x, float y) {
    float ang = atan2(y, x);

    if (ang < 0) ang += 2 * PI;

    return (ang * 180.0) / PI;
}

/**
 * @brief Extracts the coordinates of keypoints from the detected keypoints matrices.
 * 
 * @param key_points Vector to store the extracted keypoints coordinates.
 * @param keypoints Vector containing detected keypoints. It is a 2D vector where the first dimension corresponds to the level of the pyramid, and the second dimension contains two matrices representing keypoints detected as maxima and minima.
 */
void SIFTX::extract_keypoints(vector<Point> &key_points, vector<vector<Mat> > &keypoints)
{
    for (int k = 0;k < 4;k++) {
        for (int i = 0;i < keypoints[k][0].rows;i++) {
            for (int j = 0;j < keypoints[k][0].cols;j++) {

                if (keypoints[k][0].at<float>(i, j) == 1.0 || keypoints[k][1].at<float>(i, j) == 1.0) {
                    key_points.push_back(Point(((int)pow(2, k)) * j, ((int)pow(2, k)) * i));

                }
            }
        }
    }
}
/**
 * @brief Computes the magnitudes of gradients for each level of the scale space representation.
 * 
 * @param scale_space Scale space representation of the input image.
 * @param magnitudes Output vector containing the computed magnitudes of gradients.
 * @param sigma Standard deviation of the Gaussian kernel for image blurring.
 * @param k Scale factor between adjacent levels of the scale space.
 */
void SIFTX:: get_magnitudes(vector<vector<Mat>>& scale_space, vector<vector<Mat>>& magnitudes,float sigma,float k) {
    magnitudes = vector<vector<Mat>>(4, vector<Mat>(5));
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 5;j++) {
            Mat L = scale_space[i][j];
            Mat mag = Mat::zeros(L.rows, L.cols, CV_32FC1);

            for (int row = 1;row < L.rows - 1;row++) {
                for (int col = 1;col < L.cols - 1;col++) {
                    float dx = L.at<float>(row, col + 1) - L.at<float>(row, col - 1);
                    float dy = L.at<float>(row + 1, col) - L.at<float>(row - 1, col);

                    mag.at<float>(row, col) = sqrt(dx * dx + dy * dy);
                }
            }

            /*
            Localization: After computing gradient magnitudes,
             the subsequent steps of the SIFT algorithm involve detecting keypoints and describing their local features. 
             Smoothing the gradient magnitudes with a Gaussian kernel helps to localize keypoint positions more accurately by reducing the influence 
             of minor variations in intensity.
            */

            GaussianBlur(mag, mag, Size(0, 0), 1.5 * sigma * pow(k, j));
            magnitudes[i][j] = mag;
        }
    }


}


/**
 * @brief Computes the orientations of gradients for each level of the scale space representation.
 * 
 * @param scale_space Scale space representation of the input image.
 * @param orientations Output vector containing the computed orientations of gradients.
 */
void SIFTX:: get_orientations(vector<vector<Mat>>& scale_space, vector<vector<Mat>> &orientations) {
     orientations= vector<vector<Mat>>(4, vector<Mat>(5));

    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 5;j++) {
            Mat L = scale_space[i][j];
            Mat orient = Mat::zeros(L.rows, L.cols, CV_32FC1);

            for (int row = 1;row < L.rows - 1;row++) {
                for (int col = 1;col < L.cols - 1;col++) {
                    float dx = L.at<float>(row, col + 1) - L.at<float>(row, col - 1);
                    float dy = L.at<float>(row + 1, col) - L.at<float>(row - 1, col);

                    orient.at<float>(row, col) = get_angle(dx, dy);
                }
            }

            orientations[i][j] = orient;
        }
    }
}

int SIFTX:: get_kernel_size(float var) {
    int size = 39;

    for (int i = 1;i < 20;i++) {
        if (exp(-((float)(i * i)) / (2.0 * var * var)) < 0.001) {
            size = 2 * i - 1;
            break;
        }
    }

    return size;
}


int SIFTX:: get_pos_histogram1(float ang) {
    for (int i = 0;i < 36;i++) {
        if (ang >= 10.0 * i && ang < 10.0 * (i + 1)) return i;
    }
}

/**
 * @brief Calculates orientations for each keypoint detected in the image.
 * 
 * @param magnitudes Magnitudes of gradients for each level of the scale space representation.
 * @param orientations Orientations of gradients for each level of the scale space representation.
 * @param keypoints Detected keypoints.
 * @param final_keypoints Output vector containing the calculated orientations for each keypoint.
 * @param sigma Standard deviation of the Gaussian kernel for image blurring.
 * @param k Scale factor between adjacent levels of the scale space.
 */
void SIFTX::get_keypoints_orientations(vector<vector<Mat>>& magnitudes, vector<vector<Mat>>& orientations, vector<vector<Mat>>& keypoints, vector<vector<vector<vector<vector<float>>>>>& final_keypoints, float sigma, float k) {
    // Initialize the output vector for final keypoints orientations
    final_keypoints = vector<vector<vector<vector<vector<float>>>>>(4, vector<vector<vector<vector<float>>>>(5));

    // Iterate over each level of the scale space representation
    for (int i = 0; i < 4; i++) {
        Mat keypoints1 = keypoints[i][0];
        Mat keypoints2 = keypoints[i][1];

        for (int j = 0; j < 5; j++) {
            int kernel_size = get_kernel_size(sigma * pow(k, j));
            Mat mag = magnitudes[i][j];
            Mat orient = orientations[i][j];
            vector<vector<vector<float>>> keys_mat(mag.rows, vector<vector<float>>(mag.cols));

            // Iterate over each pixel in the magnitude and orientation matrices
            for (int row = 0; row < mag.rows - kernel_size; row++) {
                for (int col = 0; col < mag.cols - kernel_size; col++) {
                    // Check if the pixel is marked as a keypoint
                    if (keypoints1.at<float>(row + (kernel_size / 2), col + (kernel_size / 2)) == 1 || keypoints2.at<float>(row + (kernel_size / 2), col + (kernel_size / 2)) == 1) {
                        vector<float> keys;
                        Mat window_image_mag(mag, Rect(col, row, kernel_size, kernel_size));
                        Mat window_image_orient(orient, Rect(col, row, kernel_size, kernel_size));
                        vector<float> histogram(36);

                        // Compute histogram of gradient orientations within the window
                        for (int k = 0; k < window_image_mag.rows; k++) {
                            for (int m = 0; m < window_image_mag.cols; m++) {
                                int pos_hist = get_pos_histogram1(window_image_orient.at<float>(k, m));
                                histogram[pos_hist] += window_image_mag.at<float>(k, m);
                            }
                        }

                        // Find the peak value in the histogram
                        float peak = -1.0;
                        for (int k = 0; k < 36; k++) {
                            if (histogram[k] > peak) peak = histogram[k];
                        }

                        // Store orientations as keypoints for which histogram value exceeds 80% of the peak
                        for (int k = 0; k < 36; k++) {
                            if (histogram[k] > 0.8 * peak) {

                                // median between 10 * k and 10 * (k + 1)

                                //represents a vector that stores the orientations (or angles) of gradients for a particular keypoint
                                keys_mat[row][col].push_back(10.0 * k + 5.0);
                            }
                        }
                    }
                }
            }

            // Store the calculated orientations in the output vector
            final_keypoints[i][j] = keys_mat;
        }
    }
}

/**
 * @brief Calculates the Gaussian weight at a specific position within a given window.
 * 
 * @param row The row index of the position for which the Gaussian weight is computed.
 * @param col The column index of the position for which the Gaussian weight is computed.
 * @param row_begin The starting row index of the window.
 * @param row_end The ending row index of the window.
 * @param col_begin The starting column index of the window.
 * @param col_end The ending column index of the window.
 * @param var The variance of the Gaussian distribution.
 * @return The Gaussian weight at the specified position within the window.
 */
float SIFTX::get_gaussian_weight(int row, int col, int row_begin, int row_end, int col_begin, int col_end, float var) {
    float row_med = (1.0 * (row_begin + row_end)) / 2;
    float col_med = (1.0 * (col_begin + col_end)) / 2;
    float row_trans = 1.0 * row - row_med;
    float col_trans = 1.0 * col - col_med;

    return (exp(-(row_trans * row_trans + col_trans * col_trans) / (2.0 * var * var))) / (2.0 * PI * var * var);
}
/**
 * @brief Generates a circular Gaussian kernel within a specified region of an input matrix.
 * 
 * @param I The input matrix.
 * @param row_begin The starting row index of the circular region.
 * @param row_end The ending row index of the circular region.
 * @param col_begin The starting column index of the circular region.
 * @param col_end The ending column index of the circular region.
 * @param var The variance of the Gaussian distribution.
 * @return A circular Gaussian kernel within the specified region of the input matrix.
 */
Mat SIFTX:: get_gaussian_circle(Mat& I, int row_begin, int row_end, int col_begin, int col_end, float var) {
    Mat gaussian_circle = Mat::zeros(row_end - row_begin + 1, col_end - col_begin + 1, CV_32FC1);

    for (int i = 0;i < gaussian_circle.rows;i++) {
        for (int j = 0;j < gaussian_circle.cols;j++) {
            float weight = get_gaussian_weight(row_begin + i, col_begin + j, row_begin, row_end, col_begin, col_end, var);
            gaussian_circle.at<float>(i, j) = weight * I.at<float>(row_begin + i, col_begin + j);
        }
    }

    return gaussian_circle;
}



/**
 * @brief Generates a matrix representing renewed orientations within a specified region of an input matrix.
 * 
 * @param I The input matrix containing original orientations.
 * @param row_begin The starting row index of the region.
 * @param row_end The ending row index of the region.
 * @param col_begin The starting column index of the region.
 * @param col_end The ending column index of the region.
 * @param keypoint_orientation The orientation of the keypoint to be subtracted from the original orientations.
 * @return A matrix representing renewed orientations within the specified region of the input matrix.
 */

Mat SIFTX:: renew_orientations(Mat& I, int row_begin, int row_end, int col_begin, int col_end, float keypoint_orientation) {
    Mat orientations = Mat::zeros(row_end - row_begin + 1, col_end - col_begin + 1, CV_32FC1);

    for (int i = 0;i < orientations.rows;i++) {
        for (int j = 0;j < orientations.cols;j++) {
            orientations.at<float>(i, j) = I.at<float>(row_begin + i, col_begin + j) - keypoint_orientation;
            if (orientations.at<float>(i, j) < 0) orientations.at<float>(i, j) += 360.0;
        }
    }

    return orientations;
}


pair<int, int> SIFTX::get_initial_pos(int i, int j) {
    int row, col;

    if (i == 0 || i == 1) row = 4 * i;
    else row = 4 * i + 1;

    if (j == 0 || j == 1) col = 4 * j;
    else col = 4 * j + 1;

    return { row, col };
}


int SIFTX ::get_pos_histogram2(float ang) {
    for (int i = 0;i < 8;i++) {
        if (ang >= 45 * i && ang < 45 * (i + 1)) return i;
    }
}

/**
 * @brief Computes descriptors for keypoints based on orientations and magnitudes.
 * 
 * @param orientations Vector of matrices representing orientations.
 * @param magnitudes Vector of matrices representing magnitudes.
 * @param keypoints_orientations Vector of vectors of vectors of vectors of vectors of floats representing keypoints orientations.
 * @param descriptors Vector of vectors of floats to store computed descriptors.
 */
void SIFTX::get_descriptors(vector<vector<Mat>>& orientations, vector<vector<Mat>>& magnitudes, vector<vector<vector<vector<vector<float>>>>>& keypoints_orientations, vector<vector<float>>& descriptors) {
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 5;j++) {
            // magnitudes[i][j].rows - 17 represents the number of rows in the region of interest
            for (int row = 0;row < magnitudes[i][j].rows - 17;row++) {
                for (int col = 0;col < magnitudes[i][j].cols - 17;col++) {
                    if (keypoints_orientations[i][j][row + 8][col + 8].size() > 0) {
                        for (int k = 0;k < (int)keypoints_orientations[i][j][row + 8][col + 8].size();k++) {
                            vector<vector<float>> histograms;
                            Mat gaussian_circle = get_gaussian_circle(magnitudes[i][j], row, row + 16, col, col + 16, 8.5);
                            Mat orient = renew_orientations(orientations[i][j], row, row + 16, col, col + 16, keypoints_orientations[i][j][row + 8][col + 8][k]);

                            for (int k = 0;k < 4;k++) {
                                for (int m = 0;m < 4;m++) {
                                    vector<float> histogram(8);
                                    pair<int, int> initial_pos = get_initial_pos(k, m);
                                    int row_begin = initial_pos.first;
                                    int col_begin = initial_pos.second;

                                    for (int row_inside = row_begin; row_inside < row_begin + 4; row_inside++) {
                                        for (int col_inside = col_begin; col_inside < col_begin + 4; col_inside++) {
                                            int pos_hist = get_pos_histogram2(orient.at<float>(row_inside, col_inside));
                                            histogram[pos_hist] += gaussian_circle.at<float>(row_inside, col_inside);
                                        }
                                    }

                                    histograms.push_back(histogram);
                                }
                            }

                            vector<float> descriptor;

                            for (int k = 0;k < (int)histograms.size();k++) {
                                for (int m = 0;m < (int)histograms[k].size();m++) {
                                    descriptor.push_back(histograms[k][m]);
                                }
                            }

                            descriptors.push_back(descriptor);
                        }
                    }
                }
            }
        }
    }
}


/**
 * @brief Normalizes a vector by dividing each element by its Euclidean norm.
 * 
 * @param descriptor The vector to be normalized.
 */
void SIFTX::normalize_vector(vector<float>& descriptor) {
    float norm = 0.0;

    // Calculate the squared Euclidean norm of the vector
    for (int i = 0; i < (int)descriptor.size(); i++)
        norm += descriptor[i] * descriptor[i];

    // Compute the square root of the norm
    norm = sqrt(norm);

    // Normalize the vector by dividing each element by the norm
    for (int i = 0; i < (int)descriptor.size(); i++)
        descriptor[i] /= norm;
}

/**
 * @brief Reduces large magnitudes in a descriptor to a specified threshold.
 * 
 * @param descriptor The descriptor to be processed.
 * @param magnitude_threshold The threshold value for reducing large magnitudes.
 */
void SIFTX::reduce_large_magnitudes(vector<float>& descriptor, float magnitude_threshold) {
    // Iterate over each element of the descriptor
    for (int i = 0; i < (int)descriptor.size(); i++)
        // Reduce large magnitudes to the specified threshold value
        descriptor[i] = min(descriptor[i], magnitude_threshold);
}

/**
 * @brief Applies luminosity invariance to a set of descriptors.
 * 
 * @param descriptors The set of descriptors to be processed.
 * @param magnitude_threshold The threshold value for reducing large magnitudes.
 */
void SIFTX::get_luminosity_invariance(vector<vector<float>>& descriptors, float magnitude_threshold) {
    // Iterate over each descriptor in the set
    for (int i = 0; i < (int)descriptors.size(); i++) {
        // Normalize the descriptor vector
        normalize_vector(descriptors[i]);
        // Reduce large magnitudes in the descriptor
        reduce_large_magnitudes(descriptors[i], magnitude_threshold);
        // Normalize the descriptor vector again
        normalize_vector(descriptors[i]);
    }
}

/**
 * @brief Computes SIFT descriptors for keypoints.
 * 
 * @param descriptors Output parameter to store computed descriptors.
 * @param scale_space Vector of matrices representing the scale space pyramid.
 * @param keypoints Vector of matrices representing keypoints.
 * @param magnitude_threshold The threshold value for reducing large magnitudes in descriptors.
 * @param sigma Standard deviation of Gaussian blur for scale space generation.
 * @param k Multiplicative factor for scale space generation.
 */
void SIFTX::SIFT_descriptors(vector<vector<float>>& descriptors, vector<vector<Mat>> scale_space, vector<vector<Mat>>& keypoints, float magnitude_threshold, float sigma, float k) {
    vector<vector<Mat>> magnitudes;
    vector<vector<Mat>> orientations;
    vector<vector<vector<vector<vector<float>>>>> keypoints_orientations;

    // Compute magnitudes, orientations, and keypoints orientations
    get_magnitudes(scale_space, magnitudes, sigma, k);
    get_orientations(scale_space, orientations);
    get_keypoints_orientations(magnitudes, orientations, keypoints, keypoints_orientations, sigma, k);
    
    // Compute descriptors and apply luminosity invariance
    get_descriptors(orientations, magnitudes, keypoints_orientations, descriptors);
    get_luminosity_invariance(descriptors, magnitude_threshold);
}

