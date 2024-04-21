#include "histogramcontroller.h"
#include "Helpers/helpers.h"
#include "Models/histogram.h"
#include<opencv2/opencv.hpp>


/**
 * @brief Constructor for HistogramController class.
 *
 * Initializes a HistogramController object.
 */
HistogramController::HistogramController():Controller()
{

}

/**
 * @brief Retrieves the processed histogram and returns it as a QPixmap.
 *
 * This function calculates the histogram of the processed image, plots it,
 * and returns the result as a QPixmap.
 *
 * @return QPixmap representing the processed histogram.
 */
QPixmap HistogramController::getProcessedHistogram()
{
    Mat processedHistogram;
    if(!img->isEmpty()){ // Checks if the image is not empty
        processedHistogram=Histogram::calculateHistogram(processedImg); // Calculates histogram of processed image
        processedHistogram=Histogram::plotHistogram(processedHistogram,255,200,100); // Plots the histogram
        return Helpers::convertMatToPixmap(processedHistogram); // Converts the histogram to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if conditions are not met
}

/**
 * @brief Retrieves the original histogram and returns it as a QPixmap.
 *
 * This function calculates the histogram of the original image, plots it,
 * and returns the result as a QPixmap.
 *
 * @return QPixmap representing the original histogram.
 */
QPixmap HistogramController::getOriginalHistogram()
{
    Mat originalHistogram;
    Mat grayscaleImg;
    if(!img->isEmpty()){ // Checks if the image is not empty
        grayscaleImg=img->getOriginalImg();
        cvtColor(grayscaleImg, grayscaleImg, COLOR_BGR2GRAY);


        originalHistogram=Histogram::calculateHistogram(grayscaleImg); // Calculates histogram of original image
        originalHistogram=Histogram::plotHistogram(originalHistogram,255,200,100); // Plots the histogram
        return Helpers::convertMatToPixmap(originalHistogram); // Converts the histogram to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if conditions are not met
}

/**
 * @brief Normalizes the original image and returns it as a QPixmap.
 *
 * This function normalizes the original image and returns the result as a QPixmap.
 *
 * @return QPixmap representing the normalized image.
 */
QPixmap HistogramController::normalizeImg()
{
    Mat normalizedImg;
    if(!img->isEmpty()){ // Checks if the image is not empty
        normalizedImg= Histogram::normalizeImg(img->getOriginalImg()); // Normalizes the original image
        img->setIsProcessed(true); // Marks the image as processed
        processedImg=normalizedImg; // Updates the processed image
        return Helpers::convertMatToPixmap(processedImg); // Converts the normalized image to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if conditions are not met
}

/**
 * @brief Equalizes the original image and returns it as a QPixmap.
 *
 * This function equalizes the original image and returns the result as a QPixmap.
 *
 * @return QPixmap representing the equalized image.
 */
QPixmap HistogramController::equalizeImg()
{
    Mat equalizeImg;
    if(!img->isEmpty()){ // Checks if the image is not empty
        equalizeImg=Histogram::equalizeImg(img->getOriginalImg()); // Equalizes the original image
        img->setIsProcessed(true); // Marks the image as processed
        processedImg=equalizeImg; // Updates the processed image
        return Helpers::convertMatToPixmap(processedImg); // Converts the equalized image to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if conditions are not met
}

/**
 * @brief Computes the RGB histogram of the original image.
 *
 * This function computes the RGB histogram of the original image
 * and returns the result as a HistogramData object.
 *
 * @return HistogramData containing the RGB histogram data.
 */
HistogramData HistogramController::rgbHistogram()
{
    HistogramData data;
    if(!img->isEmpty()){ // Checks if the image is not empty
        data=Histogram::rgbHistogram(img->getOriginalImg()); // Computes the RGB histogram
    }
    return data; // Returns the RGB histogram data
}

/**
 * @brief Plots the grayscale histogram of the original image and returns it as a QPixmap.
 *
 * This function calculates the grayscale histogram of the original image, plots it,
 * and returns the result as a QPixmap.
 *
 * @return QPixmap representing the grayscale histogram.
 */
QPixmap HistogramController::plotgrayscaleHistogram()
{
    Mat grayscaleimg;
    if(!img->isEmpty()){ // Checks if the image is not empty
        grayscaleimg=Histogram::calculateHistogram(img->getOriginalImg()); // Calculates grayscale histogram
        grayscaleimg=Histogram::plotHistogram(grayscaleimg,255,255,100); // Plots the histogram
        return Helpers::convertMatToPixmap(grayscaleimg); // Converts the histogram to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if conditions are not met
}

/**
 * @brief Plots the grayscale distribution curve of the original image and returns it as a QPixmap.
 *
 * This function calculates the grayscale distribution curve of the original image, plots it,
 * and returns the result as a QPixmap.
 *
 * @return QPixmap representing the grayscale distribution curve.
 */
QPixmap HistogramController::plotgrayscaleDistribution()
{
    Mat grayscaleimg;
    if(!img->isEmpty()){ // Checks if the image is not empty
        grayscaleimg=Histogram::calculateHistogram(img->getOriginalImg()); // Calculates grayscale histogram
        grayscaleimg=Histogram::distributionCurve(grayscaleimg,255,255,100); // Plots the distribution curve
        return Helpers::convertMatToPixmap(grayscaleimg); // Converts the curve to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if conditions are not met
}

cumulativeData HistogramController:: plotCumulativeDistribution()
{
    cumulativeData hist;
    if(!img->isEmpty()){
         hist=Histogram::plot_rgb_distribution_function(img->getOriginalImg());
    }
    return hist;

}
