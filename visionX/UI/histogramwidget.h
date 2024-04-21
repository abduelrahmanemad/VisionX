#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>
#include"Controllers/histogramcontroller.h"


namespace Ui {
class HistogramWidget;
}

class HistogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = nullptr);
    ~HistogramWidget();

private slots:
    void on_normalizeBtn_clicked();

    void on_equalizeImg_clicked();

    void on_uploadImgBtn_clicked();

private:
    Ui::HistogramWidget *ui;
    HistogramController* histogramController;
    QPixmap originalImg;
    QPixmap processedImg;
    QPixmap originalHistogram;
    QPixmap processedHistogram;
    QPixmap redHistogram;
    QPixmap greenHistogram;
    QPixmap blueHistorgram;
    QPixmap rgbDistributionCurve;
};

#endif // HISTOGRAMWIDGET_H
