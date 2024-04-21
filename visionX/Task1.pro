```QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += link_pkgconfig
PKGCONFIG += opencv4


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/activecontourcontroller.cpp \
    Controllers/controller.cpp \
    Controllers/filtercontroller.cpp \
    Controllers/frequencycontroller.cpp \
    Controllers/harriscontroller.cpp \
    Controllers/histogramcontroller.cpp \
    Controllers/houghcontroller.cpp \
    Controllers/imagecontroller.cpp \
    Controllers/edgecontroller.cpp  \
    Controllers/hybridcontroller.cpp \
    Controllers/matchcontroller.cpp \
    Controllers/siftcontroller.cpp \
    Controllers/thresholdcontroller.cpp \
    Helpers/helpers.cpp \
    Helpers/scene.cpp \
    Helpers/clickable.cpp\
    Models/edgedetection.cpp \
    Models/filter.cpp \
    Models/fourier.cpp \
    Models/harris.cpp \
    Models/matching.cpp \
    Models/noise.cpp \
    Models/image.cpp \
    Models/histogram.cpp \
    Models/hybrid.cpp   \
    Models/sift.cpp \
    Models/snake.cpp \
    Models/threshold.cpp \
    Models/houghtransform.cpp \
    UI/activecontourwidget.cpp \
    UI/edgedetectionwidget.cpp \
    UI/filterswidget.cpp \
    UI/frequencywidget.cpp \
    UI/harriswidget.cpp \
    UI/histogramwidget.cpp \
    UI/matchwidget.cpp \
    UI/plotswidget.cpp \
    UI/hybridwidget.cpp \
    UI/mainwindow.cpp \
    UI/siftwidget.cpp \
    UI/thresholdwidget.cpp \
    UI/houghtransormwidget.cpp \
    config.cpp \
    main.cpp

HEADERS += \
    Controllers/activecontourcontroller.h \
    Controllers/controller.h \
    Controllers/filtercontroller.h \
    Controllers/frequencycontroller.h \
    Controllers/harriscontroller.h \
    Controllers/histogramcontroller.h \
    Controllers/edgecontroller.h  \
    Controllers/houghcontroller.h \
    Controllers/imagecontroller.h \
    Controllers/hybridcontroller.h \
    Controllers/matchcontroller.h \
    Controllers/siftcontroller.h \
    Controllers/thresholdcontroller.h \
    Helpers/helpers.h \
    Helpers/scene.h \
    Helpers/clickable.h\
    Models/edgedetection.h \
    Models/filter.h \
    Models/fourier.h \
    Models/harris.h \
    Models/image.h \
    Models/matching.h \
    Models/noise.h \
    Models/histogram.h \
    Models/hybrid.h   \
    Models/sift.h \
    Models/snake.h \
    Models/threshold.h \
    Models/houghtransform.h \
    UI/activecontourwidget.h \
    UI/edgedetectionwidget.h \
    UI/filterswidget.h \
    UI/frequencywidget.h \
    UI/harriswidget.h \
    UI/histogramwidget.h \
    UI/matchwidget.h \
    UI/plotswidget.h \
    UI/hybridwidget.h \
    UI/mainwindow.h \
    UI/siftwidget.h \
    UI/thresholdwidget.h \
    UI/houghtransormwidget.h \
    config.h \


FORMS += \
    UI/activecontourwidget.ui \
    UI/edgedetectionwidget.ui \
    UI/filterswidget.ui \
    UI/frequencywidget.ui \
    UI/harriswidget.ui \
    UI/histogramwidget.ui \
    UI/MatchWidget.ui \
    UI/plotswidget.ui \
    UI/hybridwidget.ui \
    UI/siftwidget.ui \
    UI/thresholdwidget.ui  \
    UI/houghtransormwidget.ui \
    UI/mainwindow.ui \


DISTFILES += \
    Gallery/baby with a ball.jpg \
    Gallery/bird.jpg \
    Gallery/cat.jpg \
    Gallery/cutie.jpg \
    Gallery/forest and mountain.jpg \
    Gallery/happy dog.jpg \
    Gallery/hiker 2.jpg \
    Gallery/palestine.jpg \
    Gallery/pyramids and a photographer.jpg \
    Gallery/whale.jpg \
    gitignore.txt \
    Icons/DropDownIcon.png \
    Icons/FilterIcon.png \
    Icons/Histogram.png \
    Icons/NoiseIcon.png \
    Icons/Sidebar.png \
    Icons/UploadIcon.png \
    Icons/close.png \
    Icons/contrast.png \
    Icons/convert_color_to_gray.png \
    Icons/edge_detection.png \
    Icons/sidebar-2-512.png \

# INCLUDEPATH += D:\tools\opencv\release\install\include

# LIBS += -LD:\tools\opencv\release\lib\
#     -lopencv_calib3d490                 \
#     -lopencv_core490                    \
#     -lopencv_features2d490              \
#     -lopencv_flann490                   \
#     -lopencv_highgui490                 \
#     -lopencv_imgproc490                 \
#     -lopencv_imgcodecs490               \
#     -lopencv_photo490                   \
#     -lopencv_stitching490               \
#     -lopencv_ts490                      \
#     -lopencv_video490                   \
#     -lopencv_videoio490                 \
#     -lopencv_objdetect490               \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
```
