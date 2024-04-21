#include "edgedetection.h"
#include"filter.h"
//#include<QDebug>


EdgeDetection::EdgeDetection() {}

/**
 * @brief Detects edges using Sobel operator.
 *
 * This function detects edges in the input image using Sobel operator.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image.
 */
Mat EdgeDetection::detectEdgeSobel(Mat img){
    Mat sobelX = detectEdgeSobelX(img);
    Mat sobelY = detectEdgeSobelY(img);
    Mat magnitude = edgeMagnitude(sobelX,sobelY);
    magnitude.convertTo(magnitude, CV_8U);
    return magnitude;
}

Mat EdgeDetection::Phase_Gradient( Mat gradient_x,Mat gradient_y)
{
    Mat phase_gradient = Mat::zeros(Size(gradient_x.cols, gradient_y.rows), CV_32FC1);
    for (int i = 0; i < phase_gradient.rows; i++)
    {
        for (int j = 0; j < phase_gradient.cols; j++)
        {
            phase_gradient.at<float>(i, j) = atan2(gradient_y.at<float>(i, j), gradient_x.at<float>(i, j));
        }
    }
    phase_gradient = phase_gradient * 180 / M_PI;
    return phase_gradient;
}

/**
 * @brief Detects edges using Sobel operator along the X-axis.
 *
 * This function detects edges in the input image using Sobel operator along the X-axis.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image along the X-axis.
 */
Mat EdgeDetection::detectEdgeSobelX(Mat img){
    std::cout<<"mourad 4";

    Mat xFilter= (Mat_<float>(3,3)<<-1, 0, 1,
                   -2, 0, 2,
                   -1, 0, 1);
    Mat result;
    filter2D(img, result,CV_32F,xFilter,Point(-1,-1),0,BORDER_DEFAULT);
    return result;
}

/**
 * @brief Detects edges using Sobel operator along the Y-axis.
 *
 * This function detects edges in the input image using Sobel operator along the Y-axis.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image along the Y-axis.
 */
Mat EdgeDetection::detectEdgeSobelY(Mat img){
    Mat yFilter= (Mat_<float>(3,3)<<   -1,-2,-1,
                   0,0,0,
                   1,2,1);
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);
    return result;
}

/**
 * @brief Detects edges using Robert operator.
 *
 * This function detects edges in the input image using Robert operator.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image.
 */
Mat EdgeDetection::detectEdgeRobert(Mat img){
    Mat robertX = detectEdgeRobertX(img);
    Mat robertY = detectEdgeRobertY(img);
    Mat magnitude = edgeMagnitude(robertX,robertY);
    magnitude.convertTo(magnitude, CV_8U);
    return magnitude;
}

/**
 * @brief Detects edges using Robert operator along the X-axis.
 *
 * This function detects edges in the input image using Robert operator along the X-axis.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image along the X-axis.
 */
Mat EdgeDetection::detectEdgeRobertX(Mat img){
    Mat yFilter= (Mat_<float>(2,2)<< 1,0,0,-1);
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);
    return result;
}

/**
 * @brief Detects edges using Robert operator along the Y-axis.
 *
 * This function detects edges in the input image using Robert operator along the Y-axis.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image along the Y-axis.
 */
Mat EdgeDetection::detectEdgeRobertY(Mat img){
    Mat yFilter= (Mat_<float>(2,2)<< 0,1,-1,0);
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);
    return result;
}

/**
 * @brief Detects edges using Prewitt operator.
 *
 * This function detects edges in the input image using Prewitt operator.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image.
 */
Mat EdgeDetection::detectEdgePrewitt(Mat img){
    Mat PrewittX = detectEdgePrewittX(img);
    Mat PrewittY = detectEdgePrewittY(img);
    Mat magnitude = edgeMagnitude(PrewittX,PrewittY);
    magnitude.convertTo(magnitude, CV_8U);
    return magnitude;
}

/**
 * @brief Detects edges using Prewitt operator along the X-axis.
 *
 * This function detects edges in the input image using Prewitt operator along the X-axis.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image along the X-axis.
 */
Mat EdgeDetection::detectEdgePrewittX(Mat img){
    Mat yFilter= (Mat_<float>(3,3)<< -1,0,1,-1,0,1,-1,0,1);
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);
    return result;
}

/**
 * @brief Detects edges using Prewitt operator along the Y-axis.
 *
 * This function detects edges in the input image using Prewitt operator along the Y-axis.
 *
 * @param img Input image.
 * @return Mat representing the edge-detected image along the Y-axis.
 */
Mat EdgeDetection::detectEdgePrewittY(Mat img){
    Mat yFilter= (Mat_<float>(3,3)<<-1,-1,-1,0,0,0,1,1,1 );
    Mat result;
    filter2D(img, result,CV_32F,yFilter,Point(-1,-1),0,BORDER_DEFAULT);
    return result;
}

/**
 * @brief Detects edges using Canny edge detection.
 *
 * This function detects edges in the input image using Canny edge detection algorithm.
 *
 * @param img Input image.
 * @param t_low Lower threshold for Canny edge detection.
 * @param t_high Upper threshold for Canny edge detection.
 * @return Mat representing the edge-detected image.
 */
Mat EdgeDetection::detectEdgeCanny(Mat img, int t_low ,int t_high){
//    Mat edges;
//    cv::Canny(img,edges,t_low,t_high);
//    edges.convertTo(edges,CV_8U);
//    return edges;
    // Convert the image to grayscale
    Mat edges=img.clone();

    // smooth the image
    Mat smoothed=Filter::gaussionFilter(edges,5);

//    // gradients
    Mat sobel_x=detectEdgeSobelX(smoothed);
    Mat sobel_y=detectEdgeSobelY(smoothed);
    Mat magnitude_gradient=edgeMagnitude(sobel_x,sobel_y);

    Mat phase_gradient=Phase_Gradient(sobel_x,sobel_y);

//    // supress non max values
    Mat suppressed=supressionNonMax(magnitude_gradient,phase_gradient);

    Mat thresholded=doubleThresholding(suppressed,t_low,t_high);

    Mat canny=hysteresis(thresholded);

    canny.convertTo(canny, CV_8U);
    return canny;
//return edges;


}

/**
 * @brief Computes edge magnitude from edge gradients.
 *
 * This function computes the edge magnitude from the gradients along X and Y directions.
 *
 * @param edgeX Gradient along the X direction.
 * @param edgeY Gradient along the Y direction.
 * @return Mat representing the edge magnitude.
 */
Mat EdgeDetection::edgeMagnitude(Mat edgeX, Mat edgeY){
    std::cout<<"mourad 5";

    Mat Magnitude_Gradient = Mat::zeros(Size(edgeX.cols, edgeX.rows), edgeX.type());
    for (int i = 0; i < edgeX.rows; i++) {
        for (int j = 0; j < edgeX.cols; j++) {
            Magnitude_Gradient.at<float>(i, j) = sqrt(pow(edgeX.at<float>(i, j), 2) + pow(edgeY.at<float>(i, j), 2));
        }
    }
    return Magnitude_Gradient;
}

Mat EdgeDetection::hysteresis(Mat thresholded)
{
    Mat hysteresis = thresholded.clone(); // Create a clone of the thresholded matrix

       // Iterate over the interior pixels of the image
       for (int i = 1; i < thresholded.rows - 1; ++i) {
           for (int j = 1; j < thresholded.cols - 1; ++j) {
               if (thresholded.at<float>(i, j) == WEAK_EDGE) { // Check if the pixel is a weak edge
                   // Check if any of the neighboring pixels are strong edges
                   if ((thresholded.at<float>(i + 1, j - 1) == STRONG_EDGE) ||
                       (thresholded.at<float>(i + 1, j) == STRONG_EDGE) ||
                       (thresholded.at<float>(i + 1, j + 1) == STRONG_EDGE) ||
                       (thresholded.at<float>(i, j - 1) == STRONG_EDGE) ||
                       (thresholded.at<float>(i, j + 1) == STRONG_EDGE) ||
                       (thresholded.at<float>(i - 1, j - 1) == STRONG_EDGE) ||
                       (thresholded.at<float>(i - 1, j) == STRONG_EDGE) ||
                       (thresholded.at<float>(i - 1, j + 1) == STRONG_EDGE)) {
                       hysteresis.at<float>(i, j) = STRONG_EDGE; // Promote the weak edge to a strong edge
                   } else {
                       hysteresis.at<float>(i, j) = 0; // Otherwise, set it to 0
                   }
               }
           }
       }

       return hysteresis;
}

Mat EdgeDetection::doubleThresholding(Mat suppressed, float lowThreshold, float HighThreshold)
{
//    qDebug()<<"mourad 2";

    Mat thresholded = Mat::zeros(Size(suppressed.cols, suppressed.rows), suppressed.type());

      for (int i = 0; i < suppressed.rows - 1; i++)
      {
          for (int j = 0; j < suppressed.cols - 1; j++)
          {
              if (suppressed.at<float>(i, j) > HighThreshold)
              {
                  thresholded.at<float>(i, j) = STRONG_EDGE;
              }
              else if ((suppressed.at<float>(i, j) < HighThreshold) && (suppressed.at<float>(i, j) > lowThreshold))
              {
                  thresholded.at<float>(i, j) = WEAK_EDGE;
              }
              else
              {
                  thresholded.at<float>(i, j) = 0;
              }
          }
      }
      return thresholded;
}

Mat EdgeDetection::supressionNonMax(Mat magnitudeGradient, Mat phaseGradient)
{
    Mat suppressed=Mat::zeros(magnitudeGradient.size(),CV_32F);

    for(int i=1;i<magnitudeGradient.rows-1;i++){
        for(int j=1;j<magnitudeGradient.cols-1;j++){
            float mag=magnitudeGradient.at<float>(i,j);
            float angle=phaseGradient.at<float>(i,j);
            float val1=0.0f,val2=0.0f;

            // Horizontal edge
            if((angle>=-22.5&&angle<22.5)||(angle>=157.5&&angle<=180)||(angle>=-180&&angle<-157.5)){
                val1=magnitudeGradient.at<float>(i,j+1);
                val2=magnitudeGradient.at<float>(i,j-1);
            }

            // 45-degree edge
            else if((angle>=22.5&&angle<67.5)||(angle>=-157.5&&angle<-112.5)){
                val1=magnitudeGradient.at<float>(i-1,j+1);
                val2=magnitudeGradient.at<float>(i+1,j-1);
            }

            // vertical edge (90 degree)
            else if((angle>=67.5&&angle<112.5)||(angle>=-112.5&&angle<-67.5)){
                val1=magnitudeGradient.at<float>(i-1,j);
                val2=magnitudeGradient.at<float>(i+1,j);
            }
            // 135 degree edge
            else{
                val1=magnitudeGradient.at<float>(i+1,j+1);
                val2=magnitudeGradient.at<float>(i-1,j-1);
            }
            // perform non maximum suppression
            if(mag>=val1&&mag>=val2){
                suppressed.at<float>(i,j)=mag;
            }
        }
    }

    return suppressed;

}
