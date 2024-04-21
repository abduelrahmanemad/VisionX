#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<opencv2/core/core.hpp>

#include "UI/filterswidget.h"
#include "UI/edgedetectionwidget.h"
#include "UI/frequencywidget.h"
#include "UI/plotswidget.h"
#include "UI/histogramwidget.h"
#include "UI/hybridwidget.h"
#include "UI/thresholdwidget.h"
#include "UI/houghtransormwidget.h"
#include "UI/activecontourwidget.h"
#include "UI/matchwidget.h"
#include "UI/harriswidget.h"
#include "UI/siftwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    FiltersWidget *filterWidget = new FiltersWidget();
    EdgeDetectionWidget *edgeDetectionWidget = new EdgeDetectionWidget();
    FrequencyWidget *frequencyWidget = new FrequencyWidget();
    HistogramWidget *histogramWidget=new HistogramWidget();
    PlotsWidget *plotWidget =new PlotsWidget();
    HybridWidget *hybridWidget = new HybridWidget();
    ThresholdWidget *thresholdWidget = new ThresholdWidget();
    HoughTransormWidget *houghTransformWidget = new HoughTransormWidget();
    ActiveContourWidget *activeContourWidget = new ActiveContourWidget();
    MatchWidget *matchWidget = new MatchWidget();
    HarrisWidget *harrisWidget = new HarrisWidget();
    SiftWidget   *siftWidget   = new SiftWidget();


private slots:
    void onBtnPlus();

    void onBtnMinus();

    void on_filteringBtn_clicked();

    void on_edgeDetectionBtn_clicked();

    void on_histogramsBtn_clicked();

    void on_thresholdingBtn_clicked();

    void on_hybridBtn_clicked();

    void on_frequencyBtn_clicked();

    void on_equalizationBtn_clicked();

    void on_houghTransformBtn_clicked();

    void on_ActiveContourBtn_clicked();

    void on_matchingBtn_clicked();

    void on_harrisBtn_clicked();


    void on_siftBtn_clicked();

private:
    Ui::MainWindow *ui;
    int index;
    void setFrameIndex(int index);
    void changeButtonColors(QList<QPushButton*> list,QString style);
    QList<QPushButton*> menuBtns;
    QString style;
};
#endif // MAINWINDOW_H
