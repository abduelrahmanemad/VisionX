#include "controller.h"
#include "Helpers/helpers.h"
#include "config.h"

/**
 * @brief Constructor for the Controller class.
 *
 * Initializes the Controller object.
 */
Controller::Controller() {
    img = new Image();
}

/**
 * @brief Uploads an image and returns a QPixmap.
 *
 * This function prompts the user to select an image file,
 * loads it, and converts it into a QPixmap for display.
 *
 * @return QPixmap representing the uploaded image.
 */
QPixmap Controller::uploadImg() {

    QString path = Helpers::openFile(); // Opens a file dialog to select an image file
    if(!path.isEmpty()){
        delete img; // Deletes any previous image
        img = new Image(path.toStdString()); // Loads the image from the selected path
        if(!img->isEmpty()){ // Checks if the image is successfully loaded
            return Helpers::convertMatToPixmap(img->getOriginalImg()); // Converts the image to QPixmap
        }
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if image loading fails
}

/**
 * @brief Converts the current image to grayscale and returns a QPixmap.
 *
 * This function converts the current image to grayscale using
 * OpenCV's cvtColor function and returns the result as a QPixmap.
 *
 * @return QPixmap representing the grayscale image.
 */
QPixmap Controller::convertToGrayScale() {
    if(!img->isEmpty()){ // Checks if there is a valid image
        processedImg = Filter::convertToGrayScale(img->getOriginalImg()); // Converts the image to grayscale
        img->setIsProcessed(true); // Marks the image as processed
        return Helpers::convertMatToPixmap(processedImg); // Converts the processed image to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if there is no valid image
}
