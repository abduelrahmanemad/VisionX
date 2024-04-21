#ifndef HOUGHTRANSORMWIDGET_H
#define HOUGHTRANSORMWIDGET_H

#include "qpushbutton.h"
#include <QWidget>
#include "Controllers/houghcontroller.h"

namespace Ui {
class HoughTransormWidget;
}

class HoughTransormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HoughTransormWidget(QWidget *parent = nullptr);
    ~HoughTransormWidget();

private slots:
    void on_uploadImgBtn_clicked();

    void on_lineShapeBtn_clicked();

    void on_circleShapeBtn_clicked();

    void on_EllipseShapeBtn_clicked();


    void on_lineThresholdSlider_valueChanged(int value);

    void on_minRadiusSlider_valueChanged(int value);

    void on_maxRadiusSlider_valueChanged(int value);

    void on_circleThresholdSlider_valueChanged(int value);

    void on_applyBtn_clicked();

    void on_minElipseRadiusSlider_valueChanged(int value);

    void on_maxElipseRadiusSlider_valueChanged(int value);

    void on_elipseThresholdSlider_valueChanged(int value);

private:
    Ui::HoughTransormWidget *ui;
    QList<QPushButton*> shapes;
    void changeButtonColors(QList<QPushButton*> list,QString style);
    QString style;
    QPixmap originalImg;
    QPixmap processedImg;
    HoughController *houghController;
    int type;
};

#endif // HOUGHTRANSORMWIDGET_H
