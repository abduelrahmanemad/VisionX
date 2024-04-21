#include "frequencycontroller.h"
#include "Helpers/helpers.h"
#include "config.h"

/**
 * @brief Constructor for FrequencyController class.
 *
 * Initializes a FrequencyController object.
 */
FrequencyController::FrequencyController():Controller() {}

/**
 * @brief Applies frequency domain filtering to the processed image and returns a QPixmap.
 *
 * This function converts the original image to grayscale, applies frequency domain filtering
 * with the specified radius and filter type, and returns the result as a QPixmap.
 *
 * @param radius Radius parameter for the frequency domain filtering.
 * @param Filter Type of frequency domain filter to be applied.
 * @return QPixmap representing the image after applying frequency domain filtering.
 */
QPixmap FrequencyController::frequencyFilter(int radius, int Filter){
    if(!img->isEmpty()&&img->isProcessed()){ // Checks if the image is not empty and has been processed
        Mat res;
        res = img->getOriginalImg(); // Retrieves the original image
        res= Filter::convertToGrayScale(res); // Converts the image to grayscale
        res = Filter::applyFrequencyFilter(res, radius, Filter); // Applies frequency domain filtering
        res.convertTo(res,CV_8UC1); // Converts the image to the appropriate format
        processedImg = res;
        return Helpers::convertMatToPixmap(processedImg); // Converts the processed image to QPixmap
    }
}
