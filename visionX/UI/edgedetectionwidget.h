#ifndef EDGEDETECTIONWIDGET_H
#define EDGEDETECTIONWIDGET_H

#include <QWidget>
#include "Controllers/edgecontroller.h"
#include "config.h"
namespace Ui {
class EdgeDetectionWidget;
}

class EdgeDetectionWidget : public QWidget
{
    Q_OBJECT

private:
    EdgeController *edgeController;
    QPixmap originalImg;
    QPixmap processedImg;


public:
    explicit EdgeDetectionWidget(QWidget *parent = nullptr);
    ~EdgeDetectionWidget();

private slots:
    void on_apply_robert_detector_clicked();

    void on_apply_prewitt_detector_clicked();

    void on_apply_sobel_detector_clicked();

    void on_apply_canny_detector_clicked();

    void on_uploadImgBtn_clicked();

    void on_resetFilterBtn_clicked();


    void on_cannyHighEditLine_textChanged(const QString &arg1);

    void on_cannyLowEditLine_textChanged(const QString &arg1);

private:
    Ui::EdgeDetectionWidget *ui;
    FilterAndEdgeParams filterParams;
};

#endif // EDGEDETECTIONWIDGET_H
