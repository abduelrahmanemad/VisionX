#include "edgedetectionwidget.h"
#include "ui_edgedetectionwidget.h"
#include "config.h"
#include "Helpers/helpers.h"

EdgeDetectionWidget::EdgeDetectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EdgeDetectionWidget)
{
    edgeController = new EdgeController();
    ui->setupUi(this);
}

EdgeDetectionWidget::~EdgeDetectionWidget()
{
    delete ui;
}

void EdgeDetectionWidget::on_apply_robert_detector_clicked()
{
    processedImg = edgeController->detectEdges(RobertDetector,50,250);
    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageDetected->setPixmap(processedImg);
}


void EdgeDetectionWidget::on_apply_prewitt_detector_clicked()
{
    processedImg = edgeController->detectEdges(PrewittDetector,50,250);
    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageDetected->setPixmap(processedImg);
}


void EdgeDetectionWidget::on_apply_sobel_detector_clicked()
{
    processedImg = edgeController->detectEdges(SobelDetector,50,250);
    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageDetected->setPixmap(processedImg);
}


void EdgeDetectionWidget::on_apply_canny_detector_clicked()
{
    processedImg = edgeController->detectEdges(CannyDetector,filterParams.CannyLowThreshold,filterParams.CannyHighThreshold);
    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageDetected->setPixmap(processedImg);

}


void EdgeDetectionWidget::on_uploadImgBtn_clicked()
{
    originalImg = edgeController->uploadImg();
    processedImg = edgeController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->imageOriginal->size(),Qt::IgnoreAspectRatio);
    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageOriginal->setPixmap(originalImg);
    ui->imageDetected->setPixmap(processedImg);
}


void EdgeDetectionWidget::on_resetFilterBtn_clicked()
{
    processedImg = edgeController->convertToGrayScale();
    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageDetected->setPixmap(processedImg);
}



void EdgeDetectionWidget::on_cannyHighEditLine_textChanged(const QString &arg1)
{
 filterParams.CannyHighThreshold = Helpers::convertQstringToFloat(arg1);
}


void EdgeDetectionWidget::on_cannyLowEditLine_textChanged(const QString &arg1)
{
 filterParams.CannyLowThreshold = Helpers::convertQstringToFloat(arg1);
}

