#include "thresholdwidget.h"
#include "ui_thresholdwidget.h"
#include "config.h"

ThresholdWidget::ThresholdWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThresholdWidget)
{
    ui->setupUi(this);
    thresholdController = new ThresholdController();
    ui->radiusSLider->setMinimum(0);
    ui->radiusSLider->setMaximum(250);
    ui->radiusSLider->setValue(210);
}

ThresholdWidget::~ThresholdWidget()
{
    delete ui;
}




void ThresholdWidget::on_globalThresholdBtn_clicked()
{
  thresholdedImg = thresholdController->ThresholdingFilter(GlobalThresholding,ui->radiusSLider->value(), thresholdParams.ThresholdKernelSize, thresholdParams.CParam);
  thresholdedImg = thresholdedImg.scaled(ui->processedImage->size(),Qt::IgnoreAspectRatio);
  ui->processedImage->setPixmap(thresholdedImg);
  ui->processedImage->setAlignment(Qt::AlignCenter);
}


void ThresholdWidget::on_localThresholdBtn_clicked()
{
    thresholdedImg = thresholdController->ThresholdingFilter(LocalThresholding,thresholdParams.ThresholdValue, thresholdParams.ThresholdKernelSize, thresholdParams.CParam);
    thresholdedImg = thresholdedImg.scaled(ui->processedImage->size(), Qt::IgnoreAspectRatio);
    ui->processedImage->setPixmap(thresholdedImg);
    ui->processedImage->setAlignment(Qt::AlignCenter);
}



void ThresholdWidget::on_uploadBtn_clicked()
{
    originalImg = thresholdController->uploadImg();
    processedImg = thresholdController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->originalImage->size(),Qt::IgnoreAspectRatio);
    processedImg = processedImg.scaled(ui->processedImage->size(),Qt::IgnoreAspectRatio);
    ui->originalImage->setPixmap(originalImg);
    ui->processedImage->setPixmap(processedImg);
}


void ThresholdWidget::on_radiusSLider_sliderReleased()
{
     on_globalThresholdBtn_clicked();
}

