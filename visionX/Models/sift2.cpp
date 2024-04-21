#include "sift2.h"

SIFT2::SIFT2() {}


/**
 * Generates a scale space pyramid of Gaussian blurred images.
 *
 * @param img The input image.
 * @param sigmaMin Minimum sigma value for Gaussian blur.
 * @param numOctaves Number of octaves in the scale space pyramid.
 * @param scalesPerOctave Number of scales (or images) per octave.
 * @return ScaleSpacePyramid containing the scale space pyramid.
 */
ScaleSpacePyramid SIFT2::generateGaussianPyramid(const Mat img, float sigmaMin,int numOctaves, int scalesPerOctave) {
    // assume initial sigma is 1.0 (after resizing) and smooth
    // the image with sigmaDiff to reach requried baseSigma
    float baseSigma = sigmaMin/MIN_PIX_DIST;
    Mat baseMat;
    // resize the image to double its size
    resize(img,baseMat,Size(img.cols*2,img.rows*2),0,0,BILINEAR);
    float sigmaDiff = sqrt(baseSigma*baseSigma - 1.0); // sigmaDiff is the difference between the sigma of the first image and the base sigma.
    // Apply Gaussian blur to the image.
    GaussianBlur(baseMat,baseMat,Size(3,3),sigmaDiff,sigmaDiff);

    int imgsPerOctave = scalesPerOctave + 3;

    // determine sigma values for bluring
    // sigma_i = k^(i-1) * sigma_0
    float k = pow(2,1.0/scalesPerOctave);
    vector<float> sigmas(imgsPerOctave);
    sigmas[0] = baseSigma;
    for(int i=1;i<imgsPerOctave;i++) {
        float sigmaPrev = baseSigma * pow(k,i-1);
        float sigmaTotal = sigmaPrev * k;
        sigmas[i] = sqrt(sigmaTotal*sigmaTotal - sigmaPrev*sigmaPrev);
    }

    // create a scale space pyramid of gaussian images
    // images in each octave are half the size of images in the previous one
    ScaleSpacePyramid pyramid;
    pyramid.numOctaves = numOctaves;
    pyramid.numScales = scalesPerOctave;
    pyramid.octaves = vector<vector<Mat>>(numOctaves);

    for (int i = 0; i < numOctaves; i++)
    {
        pyramid.octaves[i].reserve(imgsPerOctave);
        // add the first image to the octave
        // TODO: zxz
        pyramid.octaves[i].push_back(baseMat);
        for (int j = 1; j < sigmas.size(); j++)
        {
            const Mat prevMat = pyramid.octaves[i].back();
            Mat img;
            GaussianBlur(prevMat, img, Size(3, 3), sigmas[j], sigmas[j]);
            pyramid.octaves[i].push_back(img);
        }
        // prepare base image for next octave
        const Mat nextBaseMat = pyramid.octaves[i][imgsPerOctave - 3];
        resize(nextBaseMat, baseMat, Size(nextBaseMat.cols / 2, nextBaseMat.rows / 2), 0, 0, NEAREST);
    }

    return pyramid;
}

/**
 * Generates a scale space pyramid of Difference of Gaussian (DoG) images.
 *
 * @param img_pyramid The scale space pyramid of Gaussian blurred images.
 * @return ScaleSpacePyramid containing the scale space pyramid of DoG images.
 */

ScaleSpacePyramid SIFT2::generateDogPyramid(const ScaleSpacePyramid img_pyramid){
    ScaleSpacePyramid dog_pyramid;
    dog_pyramid.numOctaves = img_pyramid.numOctaves;
    dog_pyramid.numScales = img_pyramid.numScales - 1;
    dog_pyramid.octaves = vector<vector<Mat>>(dog_pyramid.numOctaves);

    for (int i = 0; i < dog_pyramid.numOctaves; i++)
    {
        dog_pyramid.octaves[i].reserve(dog_pyramid.numScales);
        for (int j = 1; j < img_pyramid.numScales; j++)
        {
            Mat dog;
            subtract(img_pyramid.octaves[i][j], img_pyramid.octaves[i][j - 1], dog);
            dog_pyramid.octaves[i].push_back(dog);
        }
    }

    return dog_pyramid;
}

/**
 * Generates a scale space pyramid of gradient images.
 *
 * @param pyramid The scale space pyramid of Gaussian blurred images.
 * @return ScaleSpacePyramid containing the scale space pyramid of gradient images.
 */

bool SIFT2::isExtremum(const vector<Mat> octave, int scale, int row, int col) {
    Mat img = octave[scale];
    Mat img_prev = octave[scale - 1];
    Mat img_next = octave[scale + 1];
    bool isMax = true;
    bool isMin = true;
    float val = img.at<float>(row, col);
    float neighborVal;

    for (int dx = -1; dx <= 1; i++){
        for (int dy = -1; dy <= 1; j++){
            neighborVal = img_prev.at<float>(row + dx, col + dy);
            if (val < neighborVal){
                isMax = false;
            }
            if (val > neighborVal){
                isMin = false;
            }
            neighborVal = img.at<float>(row + dx, col + dy);
            if (val < neighborVal){
                isMax = false;
            }
            if (val > neighborVal){
                isMin = false;
            }
            neighborVal = img_next.at<float>(row + dx, col + dy);
            if (val < neighborVal){
                isMax = false;
            }
            if (val > neighborVal){
                isMin = false;
            }

            if (!isMax && !isMin){
                return false;
            }

        }
    }

    return true;
}


/**
 * Fits a quadratic function to the neighborhood of a keypoint in the scale space pyramid.
 *
 * @param keypoint The keypoint around which the quadratic function is fitted.
 * @param octave A vector of images representing the octave in the scale space pyramid.
 * @param scale The scale index within the octave at which the keypoint is located.
 * @return A tuple containing the offsets in x, y, and scale dimensions, and the value of the interpolated extremum.
 */

tuple<float, float, float,float> SIFT2::fitQuadratic(KeyPoint keypoint, const vector<Mat> octave, int scale) {
    const Mat img = octave[scale];
    const Mat img_prev = octave[scale - 1];
    const Mat img_next = octave[scale + 1];

    float g1, g2, g3;
    float h11, h12, h13, h22, h23, h33;

    float x = keypoint.pt.x;
    float y = keypoint.pt.y;

    g1 = 0.5 * (img_next.at<float>(x,y) - img_prev.at<float>(x,y));
    g2 = 0.5 * (img.at<float>(x+1,y) - img.at<float>(x-1,y));
    g3 = 0.5 * (img.at<float>(x, y+1) - img.at<float>(x, x - 1));

    h11 = img_next.at<float>(x, y) - 2 * img.at<float>(x, y) + img_prev.at<float>(x, y);
    h22 = img.at<float>(x+1, y) - 2 * img.at<float>(x, y) + img.at<float>(x-1, y);
    h33 = img.at<float>(x, y+1) - 2 * img.at<float>(x, y) + img.at<float>(x, y-1);
    h12 = 0.25 * (img_next.at<float>(x+1, y) - img_next.at<float>(x-1, y) - img_prev.at<float>(x+1, y) + img_prev.at<float>(x-1, y));
    h13 = 0.25 * (img_next.at<float>(x, y+1) - img_next.at<float>(x, y-1) - img_prev.at<float>(x, y+1) + img_prev.at<float>(x, y-1));
    h23 = 0.25 * (img.at<float>(x+1, y+1) - img.at<float>(x+1, y-1) - img.at<float>(x-1, y+1) + img.at<float>(x-1, y-1));

    float det = h11*h22*h33 - h11*h23*h23 - h12*h12*h33 + 2*h12*h13*h23 - h13*h13*h22;

    float hInve11 =  (h22*h33 - h23*h23) / det;
    float hInve12 =  ( h13*h23 - h12*h33 ) / det;
    float hInve13 =  ( h12*h23 - h13*h22 ) / det;
    float hInve22 = ( h11*h33 - h13*h13 ) / det;
    float hInve23 = ( h12*h13 - h11*h23 ) / det;
    float hInve33 = ( h11*h22 - h12*h12 ) / det;

    // Find offsets of the interpolated extremum from the discrete extremum
    float offset_x = - hInve11 * g1 - hInve12 * g2 - hInve13 * g3;
    float offset_y = - hInve12 * g1 - hInve22 * g2 - hInve23 * g3;
    float offset_s = - hInve13 * g1 - hInve23 * g2 - hInve33 * g3;

    float interpolatedExtremaVal = img.at<float>(x, y) + 0.5 * (g1 * offset_x + g2 * offset_y + g3 * offset_s);
    return make_tuple(offset_x, offset_y, offset_s, interpolatedExtremaVal);

}


    
