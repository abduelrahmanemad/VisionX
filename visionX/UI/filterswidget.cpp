#include "filterswidget.h"
#include "ui_filterswidget.h"
#include "config.h"
#include "Helpers/helpers.h"

FiltersWidget::FiltersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FiltersWidget)
{
    filterController = new FilterController();
    ui->setupUi(this);
    kernels.append(ui->threeByThreeKernelBtn);
    kernels.append(ui->fiveByFiveKernelBtn);
}

FiltersWidget::~FiltersWidget()
{
    delete ui;
}


void FiltersWidget::on_apply_gaussian_noise_clicked()
{
    processedImg = filterController->addNoise(GaussianNoise,filterParams.SaltToPepperNoise ,filterParams.MeanNoise ,filterParams.SigmaNoise );
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageFiltered->setPixmap(processedImg);
}


void FiltersWidget::on_apply_uniform_noise_clicked()
{
    processedImg = filterController->addNoise(UniformNoise,filterParams.SaltToPepperNoise ,filterParams.MeanNoise ,filterParams.SigmaNoise );
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageFiltered->setPixmap(processedImg);

}


void FiltersWidget::on_apply_saltpeper_noise_clicked()
{
    processedImg = filterController->addNoise(SaltAndPepperNoise,filterParams.SaltToPepperNoise ,filterParams.MeanNoise ,filterParams.SigmaNoise );
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageFiltered->setPixmap(processedImg);
}


void FiltersWidget::on_apply_avg_filter_clicked()
{
    processedImg = filterController->filterImg(AvgFilter, filterParams.kernelSize);
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageFiltered->setPixmap(processedImg);

}


void FiltersWidget::on_apply_gaussian_filter_clicked()
{
    processedImg = filterController->filterImg(GaussianFilter, filterParams.kernelSize);
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageFiltered->setPixmap(processedImg);

}


void FiltersWidget::on_apply_median_filter_clicked()
{
    processedImg = filterController->filterImg(MedianFilter, filterParams.kernelSize);
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageFiltered->setPixmap(processedImg);
}



void FiltersWidget::on_resetFilterBtn_clicked()
{
    processedImg = filterController->convertToGrayScale();
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageFiltered->setPixmap(processedImg);
    ui->meanNoiseLineEdit->clear();
    ui->rNoiseLineEdit->clear();
    ui->sigmaNoiseLineEdit->clear();
    ui->sigmaLineEdit->clear();

}


void FiltersWidget::on_uploadImgBtn_clicked()
{
    originalImg = filterController->uploadImg();
    processedImg = filterController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->imageOriginal->size(),Qt::IgnoreAspectRatio);
    processedImg = processedImg.scaled(ui->imageFiltered->size(),Qt::IgnoreAspectRatio);
    ui->imageOriginal->setPixmap(originalImg);
    ui->imageFiltered->setPixmap(processedImg);
}




void FiltersWidget::on_sigmaLineEdit_textChanged(const QString &arg1)
{
   filterParams.SigmaFilter = Helpers::convertQstringToFloat(arg1);
   qDebug()<<   filterParams.SigmaFilter;
}


void FiltersWidget::on_meanNoiseLineEdit_textChanged(const QString &arg1)
{
 filterParams.MeanNoise = Helpers::convertQstringToFloat(arg1);
}


void FiltersWidget::on_sigmaNoiseLineEdit_textChanged(const QString &arg1)
{
 filterParams.SigmaNoise = Helpers::convertQstringToFloat(arg1);
}


void FiltersWidget::on_rNoiseLineEdit_textChanged(const QString &arg1)
{
 filterParams.SaltToPepperNoise = Helpers::convertQstringToFloat(arg1);
}

void FiltersWidget::changeButtonColors(QList<QPushButton*> list, QString style){
    foreach (QPushButton *btn, list) {
        btn->setStyleSheet(style);
    }
}


void FiltersWidget::on_threeByThreeKernelBtn_clicked()
{
    QString style ="\
        QPushButton {\
            background-color: #316669;\
            border: none;\
            border-radius: 6px;\
            color: #EEEEEE;\
            font-size: 14px;\
            font-weight: 500;\
            line-height: 20px;\
            list-style: none;\
            padding: 4px 12px;\
            height: 30px;\
    }\
        QPushButton:hover {\
            background-color: rgba(118, 171, 174, 203);\
            text-decoration: none;\
    }\
        QPushButton:focus {\
            outline: 1px transparent;\
    }";
    changeButtonColors(kernels,style);

    ui->threeByThreeKernelBtn->setStyleSheet("background-color: #76ABAE;");
     filterParams.kernelSize = 3;
}


void FiltersWidget::on_fiveByFiveKernelBtn_clicked()
{
    QString style ="\
        QPushButton {\
            background-color: #316669;\
            border: none;\
            border-radius: 6px;\
            color: #EEEEEE;\
            font-size: 14px;\
            font-weight: 500;\
            line-height: 20px;\
            list-style: none;\
            padding: 4px 12px;\
            height: 30px;\
    }\
        QPushButton:hover {\
            background-color: rgba(118, 171, 174, 203);\
            text-decoration: nonethreeByThreeKernelBtn;\
    }\
        QPushButton:focus {\
            outline: 1px transparent;\
    }";
    changeButtonColors(kernels,style);
    ui->fiveByFiveKernelBtn->setStyleSheet("background-color: #76ABAE;");
    filterParams.kernelSize = 5;
}

