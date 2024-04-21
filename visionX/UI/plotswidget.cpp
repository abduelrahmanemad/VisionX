#include "plotswidget.h"
#include "ui_plotswidget.h"
#include "Helpers/helpers.h"


PlotsWidget::PlotsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotsWidget)
{
    ui->setupUi(this);
    histogramContoller=new HistogramController;
}

PlotsWidget::~PlotsWidget()
{
    delete ui;
}
void PlotsWidget::loadHistoPlots(){
    HistogramData data;
    data=histogramContoller->rgbHistogram();
    Mat hist_image,plot_b_hist,plot_g_hist,plot_r_hist;
    grayscaleImgHistogram=histogramContoller->plotgrayscaleHistogram();
    grayscaleImgDistributionCurve=histogramContoller->plotgrayscaleDistribution();

    hist_image=data.hist_image;
    plot_b_hist=data.plot_b_hist;
    plot_g_hist=data.plot_g_hist;
    plot_r_hist=data.plot_r_hist;

    rgbDistributionCurve=Helpers::convertMatToPixmap(hist_image);

    blueHistorgram=Helpers::convertMatToPixmap(plot_b_hist);
    greenHistogram=Helpers::convertMatToPixmap(plot_g_hist);
    redHistogram= Helpers::convertMatToPixmap(plot_r_hist);

    rgbDistributionCurve=rgbDistributionCurve.scaled(ui->rgbDistributionHistogramLabel->size(),Qt::IgnoreAspectRatio);

    blueHistorgram=blueHistorgram.scaled(ui->blueHistogramLabel->size(),Qt::IgnoreAspectRatio);
    greenHistogram=greenHistogram.scaled(ui->greenHistogramLabel->size(),Qt::IgnoreAspectRatio);
    redHistogram=redHistogram.scaled(ui->redHistogramLabel->size(),Qt::IgnoreAspectRatio);


    grayscaleImgHistogram=grayscaleImgHistogram.scaled(ui->grayscaleHistogramlabel->size(),Qt::IgnoreAspectRatio);
    grayscaleImgDistributionCurve=grayscaleImgDistributionCurve.scaled(ui->grayscaleDistributionCurveLabel->size(),Qt::IgnoreAspectRatio);

    ui->rgbDistributionHistogramLabel->setPixmap(rgbDistributionCurve);

    ui->blueHistogramLabel->setPixmap(blueHistorgram);
    ui->greenHistogramLabel->setPixmap(greenHistogram);
    ui->redHistogramLabel->setPixmap(redHistogram);

    ui->grayscaleHistogramlabel->setPixmap(grayscaleImgHistogram);
    ui->grayscaleDistributionCurveLabel->setPixmap(grayscaleImgDistributionCurve);
     setWindowState(Qt::WindowMaximized);
}

void PlotsWidget::on_uploadImgBtn_clicked()
{

    image=histogramContoller->uploadImg();
    loadHistoPlots();
}

void PlotsWidget::on_comboBox_currentIndexChanged(int index)
{
    cumulativeData hist;
    QPixmap red,blue,green;
    if(index==1){
        hist=histogramContoller->plotCumulativeDistribution();
        red=Helpers::convertMatToPixmap(hist.red);
        blue=Helpers::convertMatToPixmap(hist.blue);
        green=Helpers::convertMatToPixmap(hist.green);


        red=red.scaled(ui->rgbDistributionHistogramLabel->size(),Qt::IgnoreAspectRatio);
        ui->rgbDistributionHistogramLabel->setPixmap(red);

        blue=blue.scaled(ui->grayscaleDistributionCurveLabel->size(),Qt::IgnoreAspectRatio);
        ui->grayscaleDistributionCurveLabel->setPixmap(blue);

        green=green.scaled(ui->grayscaleHistogramlabel->size(),Qt::IgnoreAspectRatio);
        ui->grayscaleHistogramlabel->setPixmap(green);

    }
    if(index==0){
        loadHistoPlots();
    }
}

