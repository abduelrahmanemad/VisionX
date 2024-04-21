#include "houghtransormwidget.h"
#include "ui_houghtransormwidget.h"
#include "config.h"
#include "Helpers/helpers.h"

HoughTransormWidget::HoughTransormWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HoughTransormWidget)
{
    ui->setupUi(this);
    shapes.append(ui->EllipseShapeBtn);
    shapes.append(ui->circleShapeBtn);
    shapes.append(ui->lineShapeBtn);

    style ="\
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
    ui->lineShapeBtn->setStyleSheet("background-color: #76ABAE;");
    houghController = new HoughController();
    type = Line;

}

HoughTransormWidget::~HoughTransormWidget()
{
    delete ui;
}

void HoughTransormWidget::changeButtonColors(QList<QPushButton*> list, QString style){
    foreach (QPushButton *btn, list) {
        btn->setStyleSheet(style);
    }
}

void HoughTransormWidget::on_uploadImgBtn_clicked()
{
    originalImg = houghController->uploadImg();
    processedImg = houghController->convertToGrayScale();
    originalImg = originalImg.scaled(ui->imageOriginal->size(),Qt::IgnoreAspectRatio);
    processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
    ui->imageOriginal->setPixmap(originalImg);
    ui->imageDetected->setPixmap(processedImg);
}


void HoughTransormWidget::on_lineShapeBtn_clicked()
{
    changeButtonColors(shapes,style);
    ui->lineShapeBtn->setStyleSheet("background-color: #76ABAE;");
    type = Line;
}


void HoughTransormWidget::on_circleShapeBtn_clicked()
{
    changeButtonColors(shapes,style);
    ui->circleShapeBtn->setStyleSheet("background-color: #76ABAE;");
    type = Circle;
}


void HoughTransormWidget::on_EllipseShapeBtn_clicked()
{
    changeButtonColors(shapes,style);
    ui->EllipseShapeBtn->setStyleSheet("background-color: #76ABAE;");
    type = Ellipse;
}


void HoughTransormWidget::on_lineThresholdSlider_valueChanged(int value)
{
    ui->lineThresholdValue->clear();
    double r = (((double) value+1) / 100.0 )*200;
    ui->lineThresholdValue->setNum((int) r-1);
}


void HoughTransormWidget::on_minRadiusSlider_valueChanged(int value)
{
    ui->minRadiusValue->clear();
    double r = (((double) value+1) / 100.0 )*150;
    ui->minRadiusValue->setNum((int) r-1);
}


void HoughTransormWidget::on_maxRadiusSlider_valueChanged(int value)
{
    ui->maxRadiusValue->clear();
    double r = (((double) value+1) / 100.0 )*150;
    ui->maxRadiusValue->setNum((int) r-1);
}


void HoughTransormWidget::on_circleThresholdSlider_valueChanged(int value)
{
    ui->circleThresholdValue->clear();
    double r = (((double) value+1) / 100.0 )*150;
    ui->circleThresholdValue->setNum((int) r-1);
}


void HoughTransormWidget::on_applyBtn_clicked()
{
    int threshold = (int) Helpers::convertQstringToFloat(ui->circleThresholdValue->text());
    int minRadius = (int) Helpers::convertQstringToFloat(ui->minRadiusValue->text());
    int maxRadius = (int) Helpers::convertQstringToFloat(ui->maxRadiusValue->text());
    int elipseThreshold = (int) Helpers::convertQstringToFloat(ui->elipseThresholdValue->text());
    int elipseMinRadius = (int) Helpers::convertQstringToFloat(ui->minElipseRadiusValue->text());
    int elipseMaxRadius = (int) Helpers::convertQstringToFloat(ui->maxElipseRadiusValue->text());
    switch (type) {
        case Line:

            processedImg = houghController->detectLines((int) Helpers::convertQstringToFloat(ui->lineThresholdValue->text()));
            processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
            ui->imageDetected->setPixmap(processedImg);
            break;

        case Circle:

            processedImg = houghController->detectCircles(threshold,minRadius,maxRadius);
            processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
            ui->imageDetected->setPixmap(processedImg);
            break;
        case Ellipse:
            processedImg = houghController->detectEllipses(elipseThreshold,elipseMinRadius,elipseMaxRadius);
            processedImg = processedImg.scaled(ui->imageDetected->size(),Qt::IgnoreAspectRatio);
            ui->imageDetected->setPixmap(processedImg);
            break;
        default:
            break;
    }
}


void HoughTransormWidget::on_minElipseRadiusSlider_valueChanged(int value)
{
    ui->minElipseRadiusValue->clear();
    double r = (((double) value+1) / 100.0 )*150;
    ui->minElipseRadiusValue->setNum((int) r-1);
}


void HoughTransormWidget::on_maxElipseRadiusSlider_valueChanged(int value)
{
    ui->maxElipseRadiusValue->clear();
    double r = (((double) value+1) / 100.0 )*150;
    ui->maxElipseRadiusValue->setNum((int) r-1);
}


void HoughTransormWidget::on_elipseThresholdSlider_valueChanged(int value)
{
    ui->elipseThresholdValue->clear();
     ui->elipseThresholdValue->setNum((int) value);
}

