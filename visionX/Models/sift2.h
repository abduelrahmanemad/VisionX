#ifndef SIFT2_H
#define SIFT2_H

#include <config.h>
#include <vector>

using namespace std;


struct ScaleSpacePyramid
{
    int numOctaves;
    int numScales; // Number of scales per octave. (images per octave)
    vector<vector<Mat>> octaves;
};



class SIFT2
{
public:
    SIFT2();
    ScaleSpacePyramid generateGaussianPyramid(const Mat img, float sigmaMin=SIGMA_MIN,int numOctaves=N_OCT, int scalesPerOctave=N_SPO);
    ScaleSpacePyramid generateDogPyramid(const ScaleSpacePyramid img_pyramid);
    ScaleSpacePyramid generateGradientPyramid(const ScaleSpacePyramid pyramid);
    vector<KeyPoint> detectKeypoints(const ScaleSpacePyramid dog_pyramid,float contrastThresh=C_DOG, float edgeThresh=C_EDGE);
    vector<float> computeOrientation(const Mat img, const KeyPoint keypoint, float lambdaOri=LAMBDA_ORI,float lambdaDesc=LAMBDA_DESC);
    vector<float> computeDescriptor(const Mat img, const KeyPoint keypoint, const vector<float> orientation, float lambdaDesc=LAMBDA_DESC);
    vector<KeyPoint> findKeyPointsAndDescriptors(const Mat img, float sigma_min=SIGMA_MIN,
                                                     int num_octaves=N_OCT, 
                                                     int scales_per_octave=N_SPO, 
                                                     float contrast_thresh=C_DOG,
                                                     float edge_thresh=C_EDGE,
                                                     float lambda_ori=LAMBDA_ORI,
                                                     float lambda_desc=LAMBDA_DESC);
    vector<Point> getMatchedPoints(const vector<KeyPoint> keypoints1, const vector<KeyPoint> keypoints2, double thresh_relative,
                                                       double thresh_absolute,int index);
    Mat drawKeypoints(const Mat img, const vector<KeyPoint> keypoints);
    Mat drawMatches(const Mat img1, const Mat img2, const vector<Point> matchedPoints);
    double crossCorrelation(const vector<float> desc1, const vector<float> desc2);
    Mat drawRectangles(const Mat img, const vector<KeyPoint> keypoints);
    Mat drawMatchesRectangle(const Mat img1, const Mat img2, const vector<Point> matchedPoints);
    double ssd(const vector<float> desc1, const vector<float> desc2);
    bool isExtremum(const vector<Mat> octave, int scale, int row, int col);
    tuple<float, float, float, float> fitQuadratic(KeyPoint keypoint, const vector<Mat> octave, int scale);
};

#endif // SIFT2_H
