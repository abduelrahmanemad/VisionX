#ifndef MATCHWIDGET_H
#define MATCHWIDGET_H

#include <QWidget>
#include"Controllers/matchcontroller.h"

namespace Ui {
class MatchWidget;
}

class MatchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatchWidget(QWidget *parent = nullptr);
    ~MatchWidget();

private slots:


    void on_uploadBtn1_clicked();

    void on_uploadBtn2_clicked();

    void on_applyBtn_clicked();

private:
    Ui::MatchWidget *ui;
    MatchController *matchController;
    QPixmap originalImg;
    QPixmap originalImg2;
    QPixmap processedImg;
};

#endif // MATCHWIDGET_H
