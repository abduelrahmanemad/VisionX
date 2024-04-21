#include "siftwidget.h"
#include "ui_siftwidget.h"
#include "Models/matching.h"
#include "Helpers/helpers.h"
#include <Models/sift.h>
#include<Helpers/helpers.h>

SiftWidget::SiftWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SiftWidget)
{
    ui->setupUi(this);
    matchController = new MatchController();
    siftController  = new SiftController();
}

SiftWidget::~SiftWidget()
{
    delete ui;
}

void SiftWidget::on_uploadBtn1_clicked()
{
    originalImg = siftController->uploadImg();
   // processedImg = matchController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->imageOriginal1->size(),Qt::IgnoreAspectRatio);
    ui->imageOriginal1->setPixmap(originalImg);
//    ui->imageDetected->setPixmap(processedImg);
}


void SiftWidget::on_uploadBtn2_clicked()
{
    originalImg = siftController->uploadImg2();
   // processedImg = matchController->convertToGrayScale2();
    originalImg = originalImg.scaled(ui->imageOriginal2->size(),Qt::IgnoreAspectRatio);
//    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageOriginal2->setPixmap(originalImg);
//    ui->imageDetected->setPixmap(processedImg);
}


void SiftWidget::on_pushButton_clicked()
{
    Mat image1,image2;
    image1=siftController->getOriginalImgMat().clone();
    image2=siftController->getOriginalImgMat2().clone();

    int min_width = std::min(image1.cols, image2.cols);
    int min_height = std::min(image1.rows, image2.rows);

    // Resize image1 to match the minimum width or height
    cv::Mat resized_image1, resized_image2;
    cv::resize(image1, image1, cv::Size(min_width, min_height));

    // Resize image2 to match the minimum width or height
    cv::resize(image2, image2, cv::Size(min_width, min_height));

    std::vector<std::vector<cv::Mat>> keypoints1;
       std::vector<std::vector<cv::Mat>>scale_space1;
       std::vector<std::vector<float>> descriptors1;
       std::vector<std::vector<cv::Mat>> keypoints2;
       std::vector<std::vector<cv::Mat>>scale_space2;
       std::vector<std::vector<float>> descriptors2;
          cv::Mat keypoints_img1;
          std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

       SIFTX::sift_keypoints(image1,keypoints_img1, keypoints1, scale_space1,ui->sigmaSpin->value(), ui->ContrastSpin->value(), ui->EdgeSpin->value(), ui->KSpin->value());
       SIFTX::SIFT_descriptors(descriptors1, scale_space1, keypoints1,ui->MagSpin->value(), ui->sigmaSpin->value(),ui->KSpin->value());

      cv::Mat keypoints_img2;
       SIFTX::sift_keypoints(image2, keypoints_img2, keypoints2, scale_space2,ui->sigmaSpin->value(), ui->ContrastSpin->value(), ui->EdgeSpin->value(), ui->KSpin->value());
       SIFTX::SIFT_descriptors(descriptors2, scale_space2, keypoints2,ui->MagSpin->value(), ui->sigmaSpin->value(),ui->KSpin->value());

       cv::Mat des1 = Helpers::vectorToMat(descriptors1);
       cv::Mat des2 = Helpers::vectorToMat(descriptors2);

       std::vector<cv::Vec3d> matches;
       Matching::applyMatching(des1, des2, matches);
       cv::Mat output;
       cv::hconcat(image1, image2, output);

       vector<cv::Point> keys1;
       SIFTX::extract_keypoints(keys1,keypoints1);

       vector<cv::Point> keys2;
       SIFTX::extract_keypoints(keys2,keypoints2);
       for(int i = 1; i < matches.size(); i++){
           if(matches[i][2]>0.2){
           cv::Point point1 =keys1[matches[i][0]];
           cv::Point point2 =keys2[matches[i][1]];
           if(point1.x==0 && point1.y==0) continue;
           if(point2.x==0 && point2.y==0) continue;
           point2.x+=image1.size().width ;
           cv::circle(image1,point1,5,cv::Scalar(0,0,255),1);
          //  cv::circle(output,point2,5,cv::Scalar(0,0,255),1);
          //  cv::line(output,point1,point2,cv::Scalar(255,0,0),1);
           }

       }
       processedImg = Helpers::convertMatToPixmap(image1);
       processedImg = processedImg.scaled(ui->imageProcessed->size(),Qt::IgnoreAspectRatio);
       ui->imageProcessed->setPixmap(processedImg);
       std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
       std::string time="Time Elapsed:  "+std::to_string(std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count()) + "  µsec" ;
       ui->time_label->setText( QString::fromStdString(time));
      // imwrite("yaah.png",image1);
}


void SiftWidget::on_pushButton_2_clicked()
{
    Mat image1,image2;
    image1=siftController->getOriginalImgMat().clone();
    image2=siftController->getOriginalImgMat2().clone();

    int min_width = std::min(image1.cols, image2.cols);
    int min_height = std::min(image1.rows, image2.rows);

    // Resize image1 to match the minimum width or height

    cv::resize(image1, image1, cv::Size(min_width, min_height));

    // Resize image2 to match the minimum width or height
    cv::resize(image2, image2, cv::Size(min_width, min_height));

    std::vector<std::vector<cv::Mat>> keypoints1;
       std::vector<std::vector<cv::Mat>>scale_space1;
       std::vector<std::vector<float>> descriptors1;
       std::vector<std::vector<cv::Mat>> keypoints2;
       std::vector<std::vector<cv::Mat>>scale_space2;
       std::vector<std::vector<float>> descriptors2;
          cv::Mat keypoints_img1;
          std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

       SIFTX::sift_keypoints(image1,keypoints_img1, keypoints1, scale_space1,ui->sigmaSpin->value(), ui->ContrastSpin->value(), ui->EdgeSpin->value(), ui->KSpin->value());
       SIFTX::SIFT_descriptors(descriptors1, scale_space1, keypoints1,ui->MagSpin->value(), ui->sigmaSpin->value(),ui->KSpin->value());

      cv::Mat keypoints_img2;
       SIFTX::sift_keypoints(image2, keypoints_img2, keypoints2, scale_space2,ui->sigmaSpin->value(), ui->ContrastSpin->value(), ui->EdgeSpin->value(), ui->KSpin->value());
       SIFTX::SIFT_descriptors(descriptors2, scale_space2, keypoints2,ui->MagSpin->value(), ui->sigmaSpin->value(),ui->KSpin->value());

       cv::Mat des1 = Helpers::vectorToMat(descriptors1);
       cv::Mat des2 = Helpers::vectorToMat(descriptors2);

       std::vector<cv::Vec3d> matches;
       Matching::applyMatching(des1, des2, matches);
       cv::Mat output;
       cv::hconcat(image1, image2, output);

       vector<cv::Point> keys1;
       SIFTX::extract_keypoints(keys1,keypoints1);

       vector<cv::Point> keys2;
       SIFTX::extract_keypoints(keys2,keypoints2);
       for(int i = 1; i < matches.size(); i++){
           if(matches[i][2]>0.2){
           cv::Point point1 =keys1[matches[i][0]];
           cv::Point point2 =keys2[matches[i][1]];
           if(point1.x==0 && point1.y==0) continue;
           if(point2.x==0 && point2.y==0) continue;
           point2.x+=image1.size().width ;
           cv::circle(output,point1,5,cv::Scalar(0,0,255),1);
           cv::circle(output,point2,5,cv::Scalar(0,0,255),1);
           cv::line(output,point1,point2,cv::Scalar(255,0,0),1);
           }

       }
       processedImg = Helpers::convertMatToPixmap(output);
       processedImg = processedImg.scaled(ui->imageProcessed->size(),Qt::IgnoreAspectRatio);
       ui->imageProcessed->setPixmap(processedImg);
       std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
       std::string time="Time Elapsed:  "+std::to_string(std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count()) + "  µsec" ;
       ui->time_label->setText( QString::fromStdString(time));
  //     imwrite("yaah.png",output);

}

