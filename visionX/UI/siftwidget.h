#ifndef SIFTWIDGET_H
#define SIFTWIDGET_H

#include <QWidget>
#include"Controllers/matchcontroller.h"
#include"Controllers/siftcontroller.h"

namespace Ui {
class SiftWidget;
}

class SiftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SiftWidget(QWidget *parent = nullptr);
    ~SiftWidget();

private slots:
    void on_uploadBtn1_clicked();

    void on_uploadBtn2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SiftWidget *ui;
    MatchController *matchController;
    SiftController  *siftController ;
    QPixmap originalImg;
    QPixmap originalImg2;
    QPixmap processedImg;
};

#endif // SIFTWIDGET_H
