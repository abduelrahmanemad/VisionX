#ifndef FILTERSWIDGET_H
#define FILTERSWIDGET_H

#include <QWidget>
#include "Controllers/filtercontroller.h"
#include "config.h"
namespace Ui {
class FiltersWidget;
}

class FiltersWidget : public QWidget
{
    Q_OBJECT

private:
    FilterController *filterController;
    QPixmap originalImg;
    QPixmap processedImg;

public:
    explicit FiltersWidget(QWidget *parent = nullptr);
    ~FiltersWidget();



private slots:
    void on_apply_gaussian_noise_clicked();

    void on_apply_uniform_noise_clicked();

    void on_apply_saltpeper_noise_clicked();

    void on_apply_avg_filter_clicked();

    void on_apply_gaussian_filter_clicked();

    void on_apply_median_filter_clicked();

    void on_resetFilterBtn_clicked();

    void on_uploadImgBtn_clicked();

    void on_sigmaLineEdit_textChanged(const QString &arg1);

    void on_meanNoiseLineEdit_textChanged(const QString &arg1);

    void on_sigmaNoiseLineEdit_textChanged(const QString &arg1);

    void on_rNoiseLineEdit_textChanged(const QString &arg1);

    void on_threeByThreeKernelBtn_clicked();

    void on_fiveByFiveKernelBtn_clicked();

private:
    Ui::FiltersWidget *ui;
    FilterAndEdgeParams filterParams;
    void changeButtonColors(QList<QPushButton*> list,QString style);
    QList<QPushButton*> kernels;
};

#endif // FILTERSWIDGET_H
