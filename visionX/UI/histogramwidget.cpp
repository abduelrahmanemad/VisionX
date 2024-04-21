#include "histogramwidget.h"
#include "ui_histogramwidget.h"


HistogramWidget::HistogramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistogramWidget)
{
    ui->setupUi(this);
    histogramController=new HistogramController;
}

HistogramWidget::~HistogramWidget()
{
    delete ui;
}

void HistogramWidget::on_normalizeBtn_clicked()
    {   /*processedImg=histogramController->convertToGrayScale();*/
    processedImg=histogramController->normalizeImg();
    processedHistogram=histogramController->getProcessedHistogram();
    originalHistogram=histogramController->getOriginalHistogram();

    processedImg = processedImg.scaled(ui->processedImgLabel->size(),Qt::IgnoreAspectRatio);
    processedHistogram=processedHistogram.scaled(ui->processedEqualizedHistogramLabel->size(),Qt::IgnoreAspectRatio);
    originalHistogram=originalHistogram.scaled(ui->originalEqualizedHistogramLabel->size(),Qt::IgnoreAspectRatio);

    ui->processedImgLabel->setPixmap(processedImg);
    ui->processedEqualizedHistogramLabel->setPixmap(processedHistogram);
    ui->originalEqualizedHistogramLabel->setPixmap(originalHistogram);
}


void HistogramWidget::on_equalizeImg_clicked()
{

    processedImg=histogramController->equalizeImg();
    processedHistogram=histogramController->getProcessedHistogram();
    originalHistogram=histogramController->getOriginalHistogram();

    processedImg = processedImg.scaled(ui->processedImgLabel->size(),Qt::IgnoreAspectRatio);
    processedHistogram=processedHistogram.scaled(ui->processedEqualizedHistogramLabel->size(),Qt::IgnoreAspectRatio);
    originalHistogram=originalHistogram.scaled(ui->originalEqualizedHistogramLabel->size(),Qt::IgnoreAspectRatio);

    ui->processedImgLabel->setPixmap(processedImg);
    ui->processedEqualizedHistogramLabel->setPixmap(processedHistogram);
    ui->originalEqualizedHistogramLabel->setPixmap(originalHistogram);


}


void HistogramWidget::on_uploadImgBtn_clicked()
{
    originalImg = histogramController->uploadImg();
    originalImg=histogramController->convertToGrayScale();
    processedImg = histogramController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->originalImgLabel->size(),Qt::IgnoreAspectRatio);
    processedImg = processedImg.scaled(ui->processedImgLabel->size(),Qt::IgnoreAspectRatio);
    ui->originalImgLabel->setPixmap(originalImg);
    ui->processedImgLabel->setPixmap(processedImg);

}
