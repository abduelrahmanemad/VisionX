#ifndef FREQUENCYWIDGET_H
#define FREQUENCYWIDGET_H

#include <QWidget>
#include "Controllers/frequencycontroller.h"

namespace Ui {
class FrequencyWidget;
}

class FrequencyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FrequencyWidget(QWidget *parent = nullptr);
    ~FrequencyWidget();

private:
    Ui::FrequencyWidget *ui;
    FrequencyController *frequencyController;
    QPixmap originalImg;
    QPixmap processedImg;
    

private slots:
    void on_browseBtn_clicked();

    void on_highPassRadio_toggled(bool checked);

    void on_lowPassRadio_toggled(bool checked);

    void on_radiusSLider_sliderReleased();
};

#endif // FREQUENCYWIDGET_H
