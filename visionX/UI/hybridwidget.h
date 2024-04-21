#ifndef HYBRIDWIDGET_H
#define HYBRIDWIDGET_H

#include <QWidget>
#include"Controllers/hybridcontroller.h"

namespace Ui {
class HybridWidget;
}

class HybridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HybridWidget(QWidget *parent = nullptr);
    ~HybridWidget();

private slots:
    void on_lpImgBtn_clicked();

    void on_hpImgBtn_clicked();

    void on_mixImgBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::HybridWidget *ui;
    HybridController* hybridController;
    QPixmap originalImg;
    QPixmap originalImg2;
    QPixmap processedImg;
    QPixmap processedImg2;
    QPixmap MixedImg;
};

#endif // HYBRIDWIDGET_H
