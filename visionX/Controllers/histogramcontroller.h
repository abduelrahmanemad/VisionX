#ifndef HISTOGRAMCONTROLLER_H
#define HISTOGRAMCONTROLLER_H
#include "controller.h"
#include "config.h"



class HistogramController : public Controller
{
public:
    HistogramController();
    HistogramController(string path);
    QPixmap getProcessedHistogram();
    QPixmap getOriginalHistogram();
    QPixmap normalizeImg();
    QPixmap equalizeImg();
    QPixmap plotgrayscaleHistogram();
    QPixmap plotgrayscaleDistribution();
    cumulativeData plotCumulativeDistribution();
    HistogramData rgbHistogram();






};

#endif // HISTOGRAMCONTROLLER_H
