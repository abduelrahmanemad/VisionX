#ifndef ACTIVECONTOURWIDGET_H
#define ACTIVECONTOURWIDGET_H

#include <QWidget>
#include "Controllers/activecontourcontroller.h"
#include "config.h"
#include "Helpers/scene.h"

namespace Ui {
class ActiveContourWidget;
}

class ActiveContourWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ActiveContourWidget(QWidget *parent = nullptr);
    ~ActiveContourWidget();

private slots:
    void on_upload_btn_clicked();

    void on_clear_clicked();
    void reloadInitialContour();

    void on_raduis_valueChanged(int arg1);
    void on_generate_btn_clicked();

protected:
    void resizeEvent(QResizeEvent* e);
private:
    Ui::ActiveContourWidget *ui;
    ActiveContourController *activeContourController;
    Scene *scene;
    QImage originalImg;
    QPixmap processedImg;
};

#endif // ACTIVECONTOURWIDGET_H
