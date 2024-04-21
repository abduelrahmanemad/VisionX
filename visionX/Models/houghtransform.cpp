#include "houghtransform.h"
#include <bits/stdc++.h>


HoughTransform::HoughTransform() {}

Mat HoughTransform::detectEdge(Mat Image) {
  Mat output;
  Canny(Image, output, 50 , 150, 3);
  return output;
}

void HoughTransform::polarToCartesian(double rho, int theta, Point& p1, Point& p2) {

  int x0 = cvRound(rho * cos(theta));
  int y0 = cvRound(rho * sin(theta));

  p1.x = cvRound(x0 + 1000 * (-sin(theta)));
  p1.y = cvRound(y0 + 1000 * (cos(theta)));

  p2.x = cvRound(x0 - 1000 * (-sin(theta)));
  p2.y = cvRound(y0 - 1000 * (cos(theta)));
}

Mat HoughTransform::lineTransform(Mat edges, Mat output, int threshold ,double rho = 0, int theta = 0){

  int maxDistance = hypot(edges.rows, edges.cols);
  vector<vector<int>> votes(2 * maxDistance, vector<int>(180, 0));


  for(int i = 0; i < edges.rows; ++i) {
      for(int j = 0; j < edges.cols; ++j) {
          if(edges.at<uchar>(i, j) == 255) {
              for(theta = 0; theta <= 180; theta += 1) {
                  rho = round(j * cos(theta - 90) + i * sin(theta - 90)) + maxDistance;
                  votes[rho][theta]++;
                }
            }
        }
    }

  // find peaks
  for(int i = 0; i < int(votes.size()); ++i) {
      for(int j = 0; j <int(votes[0].size()); ++j) {
          if(votes[i][j] > threshold) {
              rho = i - maxDistance;
              theta = j - 90;
              Point p1, p2;
              polarToCartesian(rho, theta, p1, p2);
              line(output, p1, p2, Scalar(0, 0, 255), 2, LINE_AA);
            }
        }
    }

  return output;
}

Mat HoughTransform::detectLines(Mat Image,int threshold = 160){

  cvtColor(Image, Image, COLOR_BGR2GRAY);
  Mat edges = detectEdge(Image);
  Mat linesImage = lineTransform(edges, Image, threshold, 0, 0);
  return linesImage;
}

Mat HoughTransform::preProcessImg(Mat image,Mat &edges,Mat &grayImage,int canny_min_thresold, int canny_max_thresold){
    // Convert the image to grayscale
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    // Perform edge detection
    Canny(grayImage, edges, canny_min_thresold, canny_max_thresold);
    return grayImage;
}

Mat HoughTransform::Hough_Circle_Transform (Mat image , int threshold , int min_radius  , int max_radius  , int canny_min_thresold  , int canny_max_thresold  )
{
    Mat grayImage,edges;
    grayImage = HoughTransform::preProcessImg(image,edges,grayImage,canny_min_thresold,canny_max_thresold);
    // Perform Hough Circles Transform
    // rows is image height , cols is image width
    int rows = grayImage.rows;
    int cols = grayImage.cols;
    // Define Hough parameters
    int num_thetas = 100;
    double dtheta = (int) (360 / num_thetas);
    int theta_bins = 360;
    // Initialize 3D Accumulator
    vector<vector<vector<int>>> accumulator(cols+1, vector<vector<int>>(rows+1, vector<int>((max_radius-min_radius+1), 0)));
    /* Loop over edge points then raduis and theta values to incrment accumulator */
    // Loop over edge points
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            // Check if edge point
            if (edges.at<uchar>(y, x) > 0)
            {
                // Loop over r values
                for (int r = min_radius; r < max_radius; r++)
                {
                    // Loop over theta values
                    for (int theta = 0; theta < num_thetas; theta+= dtheta)
                    {
                        // Calculate x_center and y_center
                        double x_center = x - r * cos(theta * deg2rad);
                        double y_center = y - r * sin(theta * deg2rad);
                        // check that xcenter and ycenter is in valid range
                        if (x_center >= 0 && x_center < cols && y_center >= 0 && y_center < rows)
                        {
                            // Increment accumulator
                            accumulator[(int)x_center][(int)y_center][r-min_radius]++;
                        }
                    }
                }
            }
        }
    }

    Mat circles_img = image.clone();
    // Loop over accumulator to find circles
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            for  (int r = min_radius; r < max_radius; r++)
            {
                // int current_vote = accumulator[x][y][r-min_radius] ;
                // if (current_vote >= threshold)
                // Check For accumulator threshold
                if (accumulator[x][y][r-min_radius] > threshold)
                {
                // Draw circle
                    circle(circles_img, Point(x , y ), r -min_radius, Scalar(0, 0, 255), 1, LINE_AA);
                }
            }
        }
    }
    return circles_img;
}
/////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




inline double distance_square(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

inline pair<int,int> compute_center(int x1, int y1, int x2, int y2)
{
    return make_pair(cvRound((x1 + x2)/2), cvRound((y1 + y2)/2));
}

inline double major_axis_length_sq(int x1, int y1, int x2, int y2)
{
    return distance_square(x1, y1, x2, y2) / 4;
}

inline double orientation(double x1, double y1, double x2, double y2) {
    if (x1 == x2)
        return CV_PI / 2;
    return atan((y2 - y1) / (x2 - x1));
}

vector<vector<vector<short> > > HoughTransform::store_hiearchical_pyramid(Mat& edgesM, int min_size) //create hierarchical pyramid of minimized images
{
    int log2h = (int)floor(log2(edgesM.rows));
    int log2w = (int)floor(log2(edgesM.cols));
    int log2min = min(log2h, log2w);
    unsigned int max_size = pow(2, log2min);
    Mat resized = Mat(max_size,max_size,edgesM.type());
    resize(edgesM, resized, resized.size()); //resize to square

    unsigned int steps = (unsigned int)log2min - (unsigned int)floor(log2(min_size)) + 1;
    vector<vector<vector<short> > > pyramid = vector<vector<vector<short> > >(steps);
    pyramid[0] = vector<vector<short> >(max_size,vector<short>(max_size,0)); //creating the first image (original size)
    for (int i = 0; i < max_size; ++i) {
        for (int j = 0; j < max_size; ++j) {
            uchar p = resized.at<uchar>(i,j);
            if (p > 0)
                pyramid[0][i][j] = 1;
        }
    }

    unsigned int sz = max_size; //create next levels by summing pixels of previous ones.
    for (int i = 1; i < steps; i++)
    {
        sz /= 2;
        pyramid[i] = vector<vector<short> >(sz,vector<short>(sz,0));
        for (int j = 0; j < sz; j++)
        {
            for (int k = 0; k < sz; ++k) {
                pyramid[i][j][k] = pyramid[i-1][j*2][k*2] + pyramid[i-1][j*2+1][k*2] + pyramid[i-1][j*2][k*2+1] + pyramid[i-1][j*2+1][k*2+1];
            }
        }
    }
    return pyramid;
}

bool compr2(pair<HoughTransform::ellipse_data, int> a, pair<HoughTransform::ellipse_data, int> b) {
    return a.second < b.second;
}

inline bool can_belong_to_ellipse(int x, int y, HoughTransform::ellipse_data e, double eps = 0.1) //for cleaning the image
{
    double _x = cos(e.orient) * (x - e.x0) + sin(e.orient) * (y - e.y0);
    double _y = sin(e.orient) * (x - e.x0) - cos(e.orient) * (y - e.y0);
    double eqt = (_x * _x)/(e.a*e.a) + (_y * _y)/(e.b*e.b);
    return abs(eqt - 1) < eps;
}

void HoughTransform::voting(vector<pair<ellipse_data, int> > &ellipses, const vector<vector<short> > &data, pair<int, int> xbounds,
            pair<int, int> ybounds, int min_dist, int min_vote, pair<int, int> p0, pair<int, int> p1) {
    int maxlen = cvRound(sqrt(data.size() * data.size() + data[0].size() * data[0].size()));
    int acc[maxlen];
    for (int i = 0; i < maxlen; ++i) { //clear the accumulator array
        acc[i] = 0;
    }
    int x1 = p0.first;
    int y1 = p0.second;
    int x2 = p1.first;
    int y2 = p1.second;

    pair<int, int> center = compute_center(x1, y1, x2, y2); //get the center point of the ellipse

    int x0 = center.first;
    int y0 = center.second;

    double a_sq = major_axis_length_sq(x1, y1, x2, y2); //major axis (half)
    double a = sqrt(a_sq);

    if (a < min_dist)
        return;

    double orient = orientation(x1, y1, x2, y2); //ellipse can be rotated


    for (int y = ybounds.first; y < ybounds.second; y++) {
        for (int x = xbounds.first; x < xbounds.second; x++) //point of the ellipse (x,y)
        {
            if (((x == x1) && (y == y1)) ||
                ((x == x2) && (y == y2)) ||
                (data[y][x] == 0)) //the same as one of the side points or not a boundary point
                continue;

            double d_sq = distance_square(x, y, x0, y0);
            double d = sqrt(d_sq); //distance from the center

            if ((d < min_dist) || (d > a)) //if it's too small - it is probably a line
                //if bigger than the major axis - not an ellipse point
                continue;


            double f_sq = min(distance_square(x, y, x1, y1),
                              distance_square(x, y, x2, y2)); //distance to the nearest side point
            double costau = (a_sq + d_sq - f_sq) / (2 * a * d);
            double costau_sq = costau * costau;
            if (costau_sq > 1) {
                costau_sq = 1;
            }
            if (costau_sq < 0) {
                costau_sq = 0;
            }
            double sintau_sq = 1 - costau_sq;
            double b_sq = (a_sq * d_sq * sintau_sq) / (a_sq - d_sq * costau_sq);
            int b = cvRound(sqrt(b_sq));
            if (b > min_dist) { //voting
                acc[b] += data[y][x];
            }
        }
    }
    //here we get the most-likely minor axis length of the assumed ellipse and how many points would such an ellipse contain
    int maxlength = 0;
    int maxvote = 0;
    for (int k = 0; k < maxlen; ++k) {
        if (acc[k] >= maxvote) {
            maxvote = acc[k];
            maxlength = k;
        }
        //acc[k] = 0;
    }

    if (maxvote > min_vote) {
        ellipses.push_back(make_pair(ellipse_data(x0, y0, a, maxlength, orient, x1, y1, x2, y2), maxvote));
    }
}

//First search (should be made on the minimized image)
vector<pair<HoughTransform::ellipse_data, int> > HoughTransform::hough_transform(vector<vector<short> > &data, int min_vote, int min_dist)
{
    pair<int, int> xbounds = make_pair(0, (int) data.size());
    pair<int, int> ybounds = make_pair(0, (int) data[0].size());
    vector<pair<ellipse_data, int> > res = vector<pair<ellipse_data, int> >();

    for (int y1 = ybounds.first; y1 < ybounds.second; y1++)
    {
        for (int x1 = xbounds.first; x1 < xbounds.second; x1++) //point (x1, y1) - side point of major axis
        {
            if (data[y1][x1] == 0) //not a boundary point
                continue;

            for (int y2 = y1; y2 < ybounds.second; y2++)
            {
                for (int x2 = xbounds.first; x2 < xbounds.second; x2++) //point (x2, y2) - side point of major axis
                {
                    if (((y2 == y1) && (x2 <= x1)) ||
                        (data[y2][x2] == 0)) //already been selected OR not a boundary point
                        continue;

                    voting(res, data, xbounds, ybounds, min_dist, min_vote, make_pair(x1, y1), make_pair(x2, y2));
                }
            }
        }
    }
    return res;
}

HoughTransform::ellipse_data relocate_ellipse(vector<vector<short> > &data, HoughTransform::ellipse_data prev, int min_vote = 1, int min_dist = 0)
{
    //The area where we search for ellipse points (basically, all the image)
    pair<int, int> xbounds = make_pair(0, (int) data.size());
    pair<int, int> ybounds = make_pair(0, (int) data[0].size());
    vector<pair<HoughTransform::ellipse_data, int> > res;

    int maxlen = cvRound(sqrt(data.size() * data.size() + data[0].size() * data[0].size()));

    int acc[maxlen];
    for (int i = 0; i < maxlen; ++i) { //clear the accumulator array
        acc[i] = 0;
    }


    //This time, we search for side points only as far as +- pixel from previously found ones
    //Okay, +-2 pixels for a little bit higher accuracy (I believe).
    int sidex1_start = max(xbounds.first, 2 * prev.x1 - 2);
    int sidex1_fin = min(xbounds.second, 2 * prev.x1 + 2);
    int sidex2_start = max(xbounds.first, 2 * prev.x2 - 2);
    int sidex2_fin = min(xbounds.second, 2 * prev.x2 + 2);
    int sidey1_start = max(ybounds.first, 2 * prev.y1 - 2);
    int sidey1_fin = min(ybounds.second, 2 * prev.y1 + 2);
    int sidey2_start = max(ybounds.first, 2 * prev.y2 - 2);
    int sidey2_fin = min(ybounds.second, 2 * prev.y2 + 2);

    for (int y1 = sidey1_start; y1 <= sidey1_fin; y1++) {
        for (int x1 = sidex1_start; x1 <= sidex1_fin; x1++) //point (x1, y1) - side point of major axis
        {
            if (data[y1][x1] == 0)
                continue;

            for (int y2 = sidey2_start; y2 <= sidey2_fin; y2++) {
                for (int x2 = sidex2_start; x2 <= sidex2_fin; x2++) //point (x2, y2) - side point of major axis
                {
                    if (((y2 == y1) && x2 <= x1) || (data[y2][x2] == 0))
                        continue;

                    HoughTransform::voting(res, data, xbounds, ybounds, min_dist, min_vote, make_pair(x1, y1), make_pair(x2, y2));
                }
            }
        }
    }
    pair<HoughTransform::ellipse_data, int> e = *max_element(res.begin(), res.end(), compr2);
    return e.first;
}

void clear_picture(Mat& edges, HoughTransform::ellipse_data elp)
{
    for (int x = 0; x < edges.cols; x++)
        for (int y = 0; y < edges.rows; y++)
        {
            if (can_belong_to_ellipse(x, y, elp, 0.2))
            {
                edges.at<uchar>(y,x) = 0;
            }
        }
}


HoughTransform::ellipse_data HoughTransform::ellipse_detection(Mat edges, int minimized_size , int min_vote, int min_dist )
{
    vector<vector<vector<short> > > pyramid = HoughTransform::store_hiearchical_pyramid(edges, minimized_size);

    int n = (int)pyramid.size();
    vector<pair<HoughTransform::ellipse_data, int> > ellipses =HoughTransform::hough_transform(pyramid[n - 1], min_vote, min_dist);

    if (ellipses.size() < 1) {
        cout << "Didn't find anything" << endl;
        return HoughTransform::ellipse_data(-1, -1, -1, -1, 0);
    }
    cout << "Step 1 of " << n << endl;
    HoughTransform::ellipse_data found = (*max_element(ellipses.begin(), ellipses.end(), compr2)).first;
    for (int i = n-2; i >= 0; i--)
    {
        cout << "Step " << n - i << " of " << n << endl;
        found = relocate_ellipse(pyramid[i], found);
    }
    return found;
}

vector<HoughTransform::ellipse_data> HoughTransform::detect_ellipses(Mat src, int minimized_size , unsigned int number_of_ellipses )
{
    vector<HoughTransform::ellipse_data> ellipses = vector<HoughTransform::ellipse_data>(number_of_ellipses);
    Mat edges;
    Canny(src, edges, 50, 200, 3);
    //Probably some other transformation should be performed here, such as blurring
    for (int i = 0; i < number_of_ellipses; i++)
    {
        HoughTransform::ellipse_data elp = HoughTransform::ellipse_detection(edges, minimized_size, 5, 15);
        ellipses[i] = elp;
        cout << "Found: (x_0 = " << elp.x0 << ", y_0 = " << elp.y0 << ", a = " << elp.a << ", b = " << elp.b <<
        ", A = " << elp.orient << ") " << endl;
        clear_picture(edges, elp);
    }
    return ellipses;

}


Mat HoughTransform::elipseTransform(Mat img,unsigned int nmb_of_ellipses,unsigned int minimised_size){
    Mat ellipses_draw = img.clone();
      vector<HoughTransform::ellipse_data> ellipses = detect_ellipses(img, 128, 1);
      for (int i = 0; i < ellipses.size(); i++)
      {
          HoughTransform::ellipse_data elp = ellipses[i];
          if ((elp.x0 >= 0) && (elp.y0 >=0))
          {
              ellipse(ellipses_draw, Point_<int>(elp.x0, elp.y0), Size_<double>(elp.a, elp.b), elp.orient * 180 / CV_PI,
                      0, 360, Scalar(0, 0, 255), 4, LINE_AA);
          }
      }
      return ellipses_draw;
}



HoughTransform::ellipse_data::ellipse_data(int _x0, int _y0, double _a, double _b, double th): x0(_x0), y0(_y0), a(_a), b(_b), orient(th){
}

HoughTransform::ellipse_data::ellipse_data(int _x0, int _y0, double _a, double _b, double th, int _x1, int _y1, int _x2, int _y2): x0(_x0), y0(_y0), a(_a), b(_b), orient(th), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
}


/////////////////////////////////////// Elipse Detection Imp2

void HoughTransform::HoughEllipse(cv::Mat img, std::vector<cv::Vec6d> &ellipses, int threshold, int minRadius, int maxRadius)
{
    std::vector<cv::Vec2d> nonZeroImg;
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++) {
            if (img.at<uchar>(x, y) == 255) {
                nonZeroImg.push_back(cv::Vec2d(y, x));
            }
        }
    }
    std::vector<std::thread> threadVec;
    std::mutex myMutex;
    int size = nonZeroImg.size();
    int threadN = 30;
    for (int i = 0; i < threadN; i++) {
        threadVec.push_back(std::thread(HoughTransform::oneThreadHough, nonZeroImg, std::ref(ellipses), std::ref(myMutex), threshold, minRadius, maxRadius, (int)(((double)i / threadN) * size), (int)(((double)(i + 1) / threadN) * size)));
    }
    for (int i = 0; i < threadVec.size(); i++) {
        if (threadVec[i].joinable())
            threadVec[i].join();
    }
}

void HoughTransform::drawEllipse(cv::Mat &img, std::vector<cv::Vec6d> ellipses, cv::Scalar color)
{
    for (int i = 0; i < ellipses.size(); i++)
    {
        cv::Point center = cv::Point(ellipses[i][0], ellipses[i][1]);
        cv::Size axes(ellipses[i][2], ellipses[i][3]);
        cv::ellipse(img, center,axes,ellipses[i][4]*180/CV_PI, 0 , 360, color, 5);


    }
}

void HoughTransform::oneThreadHough(std::vector<cv::Vec2d> nonZeroImg, std::vector<cv::Vec6d> &ellipses, std::mutex &myMutex, int threshold, int minRadius, int maxRadius, int start, int end)
{
    int size = nonZeroImg.size();
    double max_sqaured_b = maxRadius * maxRadius;
    std::vector<double> acc;
    for (int i = start; i < end; i++) {

        cv::Vec2d P1 = nonZeroImg[i];
        for (int j = 0; j < i; j++) {
            cv::Vec2d P2 = nonZeroImg[j];

            double dx = P1[0] - P2[0];
            double dy = P1[1] - P2[1];

            double MajorR = 0.5 * std::sqrt(dx * dx + dy * dy);
            if (MajorR > 0.5 * minRadius) {

                cv::Vec2d Pc(0.5 * (P1[0] + P2[0]), 0.5 * (P1[1] + P2[1]));
                for (int z = 0; z < size; z++) {
                    cv::Vec2d P3 = nonZeroImg[z];
                    dx = P3[0] - Pc[0];
                    dy = P3[1] - Pc[1];
                    double d = std::sqrt(dx * dx + dy * dy);
                    if (d > minRadius) {
                        dx = P3[0] - P1[0];
                        dy = P3[1] - P1[1];
                        double cos_tau = (MajorR * MajorR + d * d - dx * dx - dy * dy) / (2 * MajorR * d);
                        cos_tau *= cos_tau;
                        double k = MajorR * MajorR - d * d * cos_tau;
                        if (k > 0 && cos_tau < 1) {
                            double MinorR_squared = MajorR * MajorR * d * d * (1 - cos_tau) / k;
                            if (MinorR_squared <= max_sqaured_b)
                                acc.push_back(MinorR_squared);
                        }
                    }
                }


                if (!acc.empty()) {
                    int maxVal = -1;
                    for (int i = 0; i < acc.size(); i++)
                        if (std::round(acc[i]) > maxVal)
                            maxVal = std::round(acc[i]);

                    std::vector<int>pdf(maxVal + 1, 0);

                    for (int i = 0; i < acc.size(); i++)
                        pdf[std::round(acc[i])]++;

                    maxVal = 0;
                    int maxIdx = -1;
                    for (int i = 0; i < pdf.size(); i++)
                        if (pdf[i] > maxVal) {
                            maxVal = pdf[i];
                            maxIdx = i;
                        }

                    if (maxVal > threshold) {
                        double angle = std::atan2(P1[1] - P2[1], P1[0] - P2[0]);
                        double MinorR = std::sqrt(maxIdx);
                        if (angle != 0) {
                            //angle = CV_PI - angle;

                            if (angle > CV_PI) {
                                angle = angle - CV_PI / 2;
                                std::swap(MajorR, MinorR);
                            }
                        }
                        if (MinorR > minRadius && MajorR > minRadius && MajorR < maxRadius && MinorR < maxRadius) {

                            cv::Vec6d ellipse(Pc[0], Pc[1], MajorR, MinorR, angle, maxVal);
                            std::lock_guard<std::mutex> lock(myMutex);

                            ellipses.push_back(ellipse);
                        }

                    }

                    acc.clear();


                }

            }
        }

    }
}
