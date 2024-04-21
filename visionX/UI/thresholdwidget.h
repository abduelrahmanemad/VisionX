#ifndef THRESHOLDWIDGET_H
#define THRESHOLDWIDGET_H

#include <QWidget>
#include "Controllers/thresholdcontroller.h"
#include "config.h"
namespace Ui {
class ThresholdWidget;
}

class ThresholdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThresholdWidget(QWidget *parent = nullptr);
    ~ThresholdWidget();

private:
    Ui::ThresholdWidget *ui;
    ThresholdController *thresholdController;
    QPixmap originalImg;
    QPixmap processedImg;
    QPixmap thresholdedImg;
    ThresholdParams thresholdParams;
private slots:
    void on_globalThresholdBtn_clicked();

    void on_localThresholdBtn_clicked();

    void on_uploadBtn_clicked();


    void on_radiusSLider_sliderReleased();
};

#endif // THRESHOLDWIDGET_H



