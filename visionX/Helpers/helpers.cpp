#include "helpers.h"
#include "config.h"
#include "Models/filter.h"
#include "qapplication.h"

Helpers::Helpers() {}
Helpers::~Helpers() {}

/**
 * @brief Converts a cv::Mat image to a QPixmap.
 *
 * This function takes a cv::Mat image and converts it into a QPixmap,
 * which can be used for display purposes in Qt applications.
 *
 * @param imageMat Input cv::Mat image.
 * @return QPixmap representing the input image.
 */
QPixmap Helpers::convertMatToPixmap(Mat imageMat){

    QPixmap outputPixmap;

    // Check the image type
    switch(imageMat.type())
    {
    // Colored Image
    case CV_8UC3:
    {
        QImage qimage(imageMat.data, imageMat.cols, imageMat.rows, (imageMat.step), QImage::Format_BGR888);
        outputPixmap = QPixmap::fromImage(qimage);
        break;
    }
    // Grayscale Image
    case CV_8UC1:
    {
        QImage qimage(imageMat.data, imageMat.cols, imageMat.rows, (imageMat.step), QImage::Format_Grayscale8);
        outputPixmap = QPixmap::fromImage(qimage);
        break;
    }

        // float 32 Image
    case CV_32F:
    {
        // scaled image
        Mat scaled_image;
        double min_val, max_val;

        // get max & min value of the image
        minMaxLoc(imageMat, &min_val, &max_val);

        // convert image into grayscale 8bit image
        double scale_factor = 255.0 / (max_val - min_val);
        imageMat.convertTo(scaled_image, CV_8UC1, scale_factor, -scale_factor * min_val);

        QImage qimage(scaled_image.data,
                      scaled_image.cols,
                      scaled_image.rows,
                      static_cast<int>(scaled_image.step),
                      QImage::Format_Grayscale8);

        outputPixmap = QPixmap::fromImage(qimage.rgbSwapped());
    }
    }
    return outputPixmap;
}

/**
 * @brief Opens a file dialog to select an image file and returns the file path.
 *
 * @return QString representing the path of the selected image file.
 */
QString Helpers::openFile(){
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString path = QFileDialog::getOpenFileName(nullptr, "Choose an Image", appDirPath);
    return path;
}

/**
 * @brief Converts a QString to a float value.
 *
 * This function takes a QString input and converts it into a float value.
 *
 * @param input QString to be converted.
 * @return Float value converted from the input QString.
 */
float Helpers::convertQstringToFloat(const QString input){
    bool ok;
    float floatValue = input.toFloat(&ok);
    if (ok) {
        // Conversion successful
    } else {
        qDebug() << "Invalid input!";
    }
    return floatValue;
}


Mat Helpers::vectorToMat(const vector<vector<float>>& input) {
    Mat output(input.size(), input[0].size(), CV_32F);

    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = 0; j < input[i].size(); j++) {
            output.at<float>(i, j) = input[i][j];
        }
    }

    return output;
}
