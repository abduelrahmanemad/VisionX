#include "matchwidget.h"
#include "ui_matchwidget.h"
#include "Models/matching.h"
#include "Helpers/helpers.h"

MatchWidget::MatchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchWidget)
{
    ui->setupUi(this);
    matchController = new MatchController();
}

MatchWidget::~MatchWidget()
{
    delete ui;
}



void MatchWidget::on_uploadBtn1_clicked()
{
    originalImg = matchController->uploadImg();
   // processedImg = matchController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->imageOriginal1->size(),Qt::IgnoreAspectRatio);
    ui->imageOriginal1->setPixmap(originalImg);
//    ui->imageDetected->setPixmap(processedImg);
}


void MatchWidget::on_uploadBtn2_clicked()
{
    originalImg = matchController->uploadImg2();
   // processedImg = matchController->convertToGrayScale2();
    originalImg = originalImg.scaled(ui->imageOriginal2->size(),Qt::IgnoreAspectRatio);
//    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageOriginal2->setPixmap(originalImg);
//    ui->imageDetected->setPixmap(processedImg);
}


void MatchWidget::on_applyBtn_clicked()
{
      cv::Rect roi;
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      matchController->applyMatching(ui->comboBox->currentIndex(),roi);
      cv::Mat outImg = matchController->getOriginalImgMat();
     //  cvtColor(outImg, outImg, COLOR_BGR2GRAY);
      cv::rectangle(outImg, roi, cv::Scalar(0, 0, 255), 2);
      processedImg = Helpers::convertMatToPixmap(outImg);
      processedImg = processedImg.scaled(ui->imageProcessed->size(),Qt::IgnoreAspectRatio);
      ui->imageProcessed->setPixmap(processedImg);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::string time="Time Elapsed:  "+std::to_string(std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count()) + "  µsec" ;
      ui->time_label->setText( QString::fromStdString(time));


}

