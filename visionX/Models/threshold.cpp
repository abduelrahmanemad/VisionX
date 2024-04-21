#include "threshold.h"

Threshold::Threshold() {}

Mat Threshold::globalThresholding(Mat img, int thresholdValue){
    Mat res =img.clone();
    for(int i = 0;i<res.rows;i++){
        for(int j=0;j<res.cols;j++){
            if(res.at<uchar>(i,j) >= thresholdValue ){
                res.at<uchar>(i,j)= 255;
            }else{
                res.at<uchar>(i,j)=0;
            }
        }
    }
    return res;
}

Mat Threshold::localThresholding(Mat img, int kernelSize, int C){
    Mat res =img.clone();
      Mat mean_window = local_threshold_mean_calculation(img, 9, C);
    for (int i = 0; i < img.rows; i++)
       {
           for (int  j = 0; j < img.cols; j++)
           {
                   if (img.at<uchar>(i, j) >= mean_window.at<uchar>(i, j))
                   {
                       res.at<uchar>(i, j) = 255;
                   }
                   else
                   {
                       res.at<uchar>(i, j) = 0;
                   }
           }
       }
    return res;
}

Mat Threshold::Padd_Mono(const Mat &src, int padding_margin , int data_type)
{
    Mat padding_img;
    if (data_type == UCHAR_FLAG)
    {
        padding_img =  Mat::zeros(Size(src.cols + padding_margin * 2, src.rows + padding_margin * 2), src.type());
    }
    else if (data_type == FLOAT_FLAG)
    {
        padding_img =  Mat::zeros(Size(src.cols + padding_margin * 2, src.rows + padding_margin * 2), CV_32FC1);
    }
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            if (data_type == UCHAR_FLAG)
            {
                padding_img.at<uchar>(i + padding_margin, j + padding_margin) = src.at<uchar>(i, j);
            }
            else if (data_type == FLOAT_FLAG)
            {
                padding_img.at<float>(i + padding_margin, j + padding_margin) = src.at<float>(i, j);
            }
        }
    }
    return padding_img;
}


Mat adaptive_padding_function(Mat src){

    Mat dst;
    dst = Threshold::Padd_Mono(src, 1);

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            if( i == 0  && j == 0 ) {
                dst.at<uchar>(i, j) = src.at<uchar>(i, j);
            }
            if(i == src.rows - 1 && j == src.cols - 1){
                dst.at<uchar>(i + 2, j + 2) = src.at<uchar>(i, j);
            }
            if(i == 0 &&  j == src.cols - 1){
                dst.at<uchar>(i , j + 2) = src.at<uchar>(i, j);
            }
            if(i == src.rows - 1 && j == 0){
                dst.at<uchar>(i + 2 , j) = src.at<uchar>(i, j);
            }
            if( i == 0 ){
                dst.at<uchar>(i , j + 1) = src.at<uchar>(i, j);
            }
            if ( j == 0 ){
                dst.at<uchar>(i + 1, j) = src.at<uchar>(i, j);
            }
            if( j == src.cols - 1){
                dst.at<uchar>(i + 1, j + 2) = src.at<uchar>(i, j);
            }
            if( i == src.rows - 1){
                dst.at<uchar>(i + 2 , j + 1) = src.at<uchar>(i, j);
            }
        }
    }

    return dst;
}

Mat Threshold::local_threshold_mean_calculation(const Mat &src, int target_app, int C)
{
    std::vector<int> mean_values;
    Mat padded_img = adaptive_padding_function(src);
    Mat convoluted_img = Mat::zeros(Size(src.cols, src.rows), src.type());

    float window_values[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Mat mean_window = Mat(3, 3, CV_32F, window_values);

    int h = mean_window.rows / 2;
    int w = mean_window.cols / 2;

    float window_sum;
    for (int i = 1; i < (padded_img.rows - 1); i++)
    {
        for (int j = 1; j < (padded_img.cols - 1); j++)
        {
            window_sum = 0;
            for (int m = 0; m < mean_window.rows; m++)
            {
                for (int n = 0; n < mean_window.cols; n++)
                {
                    window_sum += padded_img.at<uchar>(i + m - h, j + n - w) * mean_window.at<float>(m, n);

                }
            }
            convoluted_img.at<uchar>(i - 1, j - 1) = window_sum/target_app - C;

        }
    }
    return convoluted_img;
}

