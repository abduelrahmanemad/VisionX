#include "hybridwidget.h"
#include "ui_hybridwidget.h"

HybridWidget::HybridWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HybridWidget)
{
    ui->setupUi(this);
    hybridController=new HybridController();
}

HybridWidget::~HybridWidget()
{
    delete ui;
}



void HybridWidget::on_lpImgBtn_clicked()
{
    originalImg = hybridController->uploadImg();
    processedImg = hybridController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->hybridLpImg->size(),Qt::IgnoreAspectRatio);
    processedImg = processedImg.scaled(ui->hybridLpImg->size(),Qt::IgnoreAspectRatio);
    ui->hybridLpImg->setPixmap(processedImg);
}


void HybridWidget::on_hpImgBtn_clicked()
{
    originalImg2 = hybridController->uploadImg2();
    processedImg2 = hybridController->convertToGrayScale2();
    originalImg2 = originalImg2.scaled(ui->hybridHpImg->size(),Qt::IgnoreAspectRatio);
    processedImg2 = processedImg2.scaled(ui->hybridHpImg->size(),Qt::IgnoreAspectRatio);
    ui->hybridHpImg->setPixmap(processedImg2);
}


void HybridWidget::on_mixImgBtn_clicked()
{
   MixedImg = hybridController->Mix(30,30);
   MixedImg = MixedImg.scaled(ui->hybridMixedImg->size(),Qt::IgnoreAspectRatio);
   MixedImg.save("hamooot.jpg");
   ui->hybridMixedImg->setPixmap(MixedImg);
}


void HybridWidget::on_pushButton_clicked()
{
   MixedImg.save("Mixed_Image.jpg");
}

