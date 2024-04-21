#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

#include "config.h"

#include "UI/filterswidget.h"

#include "UI/edgedetectionwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    index = FilterPage;
    ui->stackedWidget->addWidget(filterWidget);
    ui->stackedWidget->addWidget(edgeDetectionWidget);
    ui->stackedWidget->addWidget(histogramWidget);
    ui->stackedWidget->addWidget(plotWidget);
    ui->stackedWidget->addWidget(hybridWidget);
    ui->stackedWidget->addWidget(frequencyWidget);
    ui->stackedWidget->addWidget(thresholdWidget);
    ui->stackedWidget->addWidget(houghTransformWidget);
    ui->stackedWidget->addWidget(activeContourWidget);
     ui->stackedWidget->addWidget(matchWidget);
    ui->stackedWidget->addWidget(harrisWidget);
    ui->stackedWidget->addWidget(siftWidget);
    menuBtns.append(ui->filteringBtn);
    menuBtns.append(ui->frequencyBtn);
    menuBtns.append(ui->edgeDetectionBtn);
    menuBtns.append(ui->histogramsBtn);
    menuBtns.append(ui->thresholdingBtn);
    menuBtns.append(ui->equalizationBtn);
    menuBtns.append(ui->hybridBtn);
    menuBtns.append(ui->houghTransformBtn);
    menuBtns.append(ui->ActiveContourBtn);
    menuBtns.append(ui->matchingBtn);
    menuBtns.append(ui->harrisBtn);
    menuBtns.append(ui->siftBtn);

    style="\
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
            height: 40px;\
    }\
        QPushButton:hover {\
            background-color: rgba(118, 171, 174, 203);\
            text-decoration: none;\
    }\
        QPushButton:focus {\
            outline: 1px transparent;\
    }";
    ui->filteringBtn->setStyleSheet("background-color: #76ABAE;");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_filteringBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->filteringBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(filterWidget);
     setWindowState(Qt::WindowMaximized);

}


void MainWindow::on_edgeDetectionBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->edgeDetectionBtn->setStyleSheet("background-color: #76ABAE;");
   ui->stackedWidget->setCurrentWidget(edgeDetectionWidget);
    setWindowState(Qt::WindowMaximized);

}


void MainWindow::on_histogramsBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->histogramsBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(plotWidget);
     setWindowState(Qt::WindowMaximized);
}


void MainWindow::on_thresholdingBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->thresholdingBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(thresholdWidget);
     setWindowState(Qt::WindowMaximized);
}


void MainWindow::on_hybridBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->hybridBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(hybridWidget);
  setWindowState(Qt::WindowMaximized);
}

void MainWindow::on_frequencyBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->frequencyBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(frequencyWidget);
     setWindowState(Qt::WindowMaximized);
}

void MainWindow::setFrameIndex(int index){
    if(index <ui->stackedWidget->count()-1){

        ui->stackedWidget->setCurrentIndex(index);
    }

}

void MainWindow::onBtnPlus(){
    if (index < ui->stackedWidget->count()-1){
        ui->stackedWidget->setCurrentIndex(++index);
    }
}

void MainWindow::onBtnMinus(){
    if (index > 0){
        ui->stackedWidget->setCurrentIndex(--index);
    }
}

void MainWindow::on_equalizationBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->equalizationBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(histogramWidget);
     setWindowState(Qt::WindowMaximized);
}

void MainWindow::changeButtonColors(QList<QPushButton*> list, QString style){
    foreach (QPushButton *btn, list) {
        btn->setStyleSheet(style);
    }
}


void MainWindow::on_houghTransformBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->houghTransformBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(houghTransformWidget);
    setWindowState(Qt::WindowMaximized);
}


void MainWindow::on_ActiveContourBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->ActiveContourBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(activeContourWidget);
     setWindowState(Qt::WindowMaximized);
}


void MainWindow::on_matchingBtn_clicked()
{
     changeButtonColors(menuBtns,style);
     ui->matchingBtn->setStyleSheet("background-color: #76ABAE;");
     ui->stackedWidget->setCurrentWidget(matchWidget);
      setWindowState(Qt::WindowMaximized);
}


void MainWindow::on_harrisBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->harrisBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(harrisWidget);
     setWindowState(Qt::WindowMaximized);
}


void MainWindow::on_siftBtn_clicked()
{
    changeButtonColors(menuBtns,style);
    ui->siftBtn->setStyleSheet("background-color: #76ABAE;");
    ui->stackedWidget->setCurrentWidget(siftWidget);
     setWindowState(Qt::WindowMaximized);
}

