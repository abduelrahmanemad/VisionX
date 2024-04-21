#include "activecontourcontroller.h"
#include "config.h"
#include "Helpers/helpers.h"

ActiveContourController::ActiveContourController():Controller()
{

}

QImage ActiveContourController::uploadImg(){
 QString path = Helpers::openFile();
 if(!path.isEmpty()){
     QImage image(path);
     img = new Image(path.toStdString());
     return image;
 }

 return QImage(0);
}

Mat ActiveContourController::getMatImg(){
    return img->getOriginalImg();
}
