#ifndef PLOTSWIDGET_H
#define PLOTSWIDGET_H

#include <QWidget>
#include"Controllers/histogramcontroller.h"


namespace Ui {
class PlotsWidget;
}

class PlotsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotsWidget(QWidget *parent = nullptr);
    ~PlotsWidget();

private slots:
    void on_uploadImgBtn_clicked();

    void on_comboBox_currentIndexChanged(int index);
    void loadHistoPlots();

private:
    Ui::PlotsWidget *ui;
    HistogramController*histogramContoller;
    QPixmap image;
    QPixmap redHistogram;
    QPixmap greenHistogram;
    QPixmap blueHistorgram;
    QPixmap rgbDistributionCurve;
    QPixmap grayscaleImgHistogram;
    QPixmap grayscaleImgDistributionCurve;
    QPixmap cumulativePlot;
    bool alreadyUploaded=0;

};

#endif // PLOTSWIDGET_H
