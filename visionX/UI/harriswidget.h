#ifndef HARRISWIDGET_H
#define HARRISWIDGET_H

#include <QWidget>
#include"Controllers/harriscontroller.h"
#include "config.h"

namespace Ui {
class HarrisWidget;
}

class HarrisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HarrisWidget(QWidget *parent = nullptr);
    ~HarrisWidget();
private slots:
    void on_threeByThreeKernelBtn_clicked();

    void on_fiveByFiveKernelBtn_clicked();
    void on_uploadImgBtn_clicked();

    void on_applyBtn_clicked();

    void on_resetFilterBtn_clicked();

private:
    Ui::HarrisWidget *ui;
    CornerDetectionParams cornerDetectionParams;
    HarrisController *harriscontroller;
    QPixmap originalImg;
    QPixmap processedImg;
    void changeButtonColors(QList<QPushButton*> list,QString style);
    QList<QPushButton*> kernels;
};

#endif // HARRISWIDGET_H
