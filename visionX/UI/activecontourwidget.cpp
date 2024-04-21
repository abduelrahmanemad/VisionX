#include "activecontourwidget.h"
#include "ui_activecontourwidget.h"
#include "config.h"
#include "Helpers/helpers.h"
#include "Models/snake.h"
#include <QString>
ActiveContourWidget::ActiveContourWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveContourWidget)
{
    ui->setupUi(this);
    activeContourController = new ActiveContourController();
}

ActiveContourWidget::~ActiveContourWidget()
{
    delete ui;
}

void ActiveContourWidget::on_upload_btn_clicked()
{
       originalImg = activeContourController->uploadImg();
       scene = new Scene(false);
       scene->setRad(ui->raduis->value());
       reloadInitialContour();
}


void ActiveContourWidget::on_clear_clicked()
{
    reloadInitialContour();
    scene->setDrawFlag(false);
}

void ActiveContourWidget::reloadInitialContour(){
    if (originalImg != QImage(0)) {
        scene->addPixmap(QPixmap::fromImage(originalImg));
        ui->graphicsView->setScene(scene);
        ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    }
}

void ActiveContourWidget::on_raduis_valueChanged(int arg1)
{
    scene->setRad(arg1);
    reloadInitialContour();
    scene->drawCircle(false);
}

void ActiveContourWidget::resizeEvent(QResizeEvent *e)
{
  reloadInitialContour();
}

void ActiveContourWidget::on_generate_btn_clicked()
{
    Mat imageCv = activeContourController->getMatImg();
    Mat output;
    Point center=  Point_<double>(scene->getCenter().x(), scene->getCenter().y());

    vector<Point> s_vector =Snake::active_contour(imageCv,output,center,ui->raduis->value(),ui->numItr->value(),ui->num_points->value(),
                                                  ui->window_size->value(),ui->alpha->value(),ui->beta->value(),ui->gamma->value());

    double area = Snake::calculate_contour_area(s_vector);
    double perimeter=Snake::calculate_contour_perimeter(s_vector);
    ui->area->setMaximum(area+10.0);
    ui->perimeter->setMaximum((perimeter+10.0));
    ui->area->setValue(area);
    ui->perimeter->setValue(perimeter);

    QImage qimage(output.data, output.cols, output.rows,output.step,QImage::Format_BGR888);
    QPixmap* image = new QPixmap(QPixmap::fromImage(qimage));
    int w = ui->output_label->width();
    int h = ui->output_label->height();
    ui->output_label->setPixmap(image->scaled(w,h,Qt::KeepAspectRatio));
}

