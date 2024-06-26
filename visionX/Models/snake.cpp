#include "snake.h"
#include "Models/filter.h"
Snake::Snake()
{

}

// Energy
double Snake::calculate_internal_energy(Point point, Point previousPoint, Point nextPoint, double alpha) {
    double dx1 = point.x - previousPoint.x;
    double dy1 = point.y - previousPoint.y;
    double dx2 = nextPoint.x - point.x;
    double dy2 = nextPoint.y - point.y;
    double curvature = (dx1 * dy2 - dx2 * dy1) / pow(dx1*dx1 + dy1*dy1, 1.5);
    return alpha * curvature;
}

double Snake::calculate_external_energy(Mat image, Point point, double beta) {
    return -beta * image.at<uchar>(point.y, point.x);
}

double Snake::calculate_gradients(Point point, Point prevPoint, double gamma) {
    double dx = point.x - prevPoint.x;
    double dy = point.y - prevPoint.y;
    return gamma * (dx*dx + dy*dy);
}

double Snake::calculate_point_enegy(Mat image, Point point, Point prevPoint, Point nextPoint, double alpha, double beta, double gamma) {
    double internalEnergy = calculate_internal_energy(point, prevPoint, nextPoint, alpha);
    double externalEnergy = calculate_external_energy(image, point, beta);
    double gradients = calculate_gradients(point, prevPoint, gamma);
    return internalEnergy + externalEnergy + gradients;
}


//// Energy Gradient Descent (Minimize Loss)
void Snake::snake_operation(Mat image, vector<Point>& curve, int window_size, double alpha, double beta, double gamma) {
    int windowIndex = (window_size - 1) / 2;
    int numPoints = curve.size();
    vector<Point> newCurve(numPoints);

        for (int i = 0; i < numPoints; i++) {
            Point pt = curve[i];
            Point prevPt = curve[(i-1+numPoints)%numPoints];
            Point nextPt = curve[(i+1)%numPoints];
            double minEnergy = DBL_MAX; // max value can a double variable hold
            Point newPt = pt;
            // Try moving the point in different directions and choose the one with the minimum energy
            for (int dx = -windowIndex; dx <= windowIndex; dx++) {
                for (int dy = -windowIndex; dy <= windowIndex; dy++) {
                    Point movePt(pt.x + dx, pt.y + dy);
                    double energy = calculate_point_enegy(image, movePt, prevPt, nextPt, alpha, beta, gamma);
                    if (energy < minEnergy) {
                        minEnergy = energy;
                        newPt = movePt;
                    }
                }
            }
            newCurve[i] = newPt;
        }


    curve = newCurve;
}

vector<Point> Snake::initialize_contours(Point center, int radius, int numberOfPoints){
    vector<Point> curve;
    double current_angle = 0;
    double resolution = 360 / (double)numberOfPoints;

    for (int i = 0; i < numberOfPoints; i++)
        {
            std::vector<double> angle = {current_angle};
            std::vector<double> x = {};
            std::vector<double> y = {};
            cv::polarToCart(radius, angle, x, y, true);
            int x_p = (int)(x[0] + center.x);
            int y_p = (int)(y[0] + center.y);
            current_angle += resolution;
            curve.push_back(Point(x_p, y_p));
        }

    return curve;
}

double Snake::points_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

double Snake::calculate_contour_area(vector<Point> snake_points)
{
    double area = 0.0;
    // Calculate value of shoelace formula => 1/2 [ (x1y2 + x2y3 + … + xn-1yn + xny1) – (x2y1 + x3y2 + … + xnyn-1 + x1yn) ]
    int j = snake_points.size() - 1;
    for (int i = 0; i < snake_points.size(); i++)
    {
        area += (snake_points[j].x + snake_points[i].x) * (snake_points[j].y - snake_points[i].y);
        j = i; // j is previous vertex to i
    }
    return std::abs(area / 2.0);
}

double Snake::calculate_contour_perimeter(vector<Point> snake_points)
{
    double distance_sum = 0;
    for (int i = 0; i < snake_points.size(); i++)
    {
        int next_point = i + 1;
        if (i == snake_points.size() - 1)
        {
            next_point = 0;
        }

        double distance = points_distance(snake_points[i].x, snake_points[i].y, snake_points[next_point].x, snake_points[next_point].y);
        distance_sum += distance;
    }
    return distance_sum;
}

//void Snake::draw_contours(Mat image, Mat &outputimage, vector<Point> snake_points, vector<int>& chain_code){
//    outputimage = image.clone();
//    for (int i = 0; i < snake_points.size(); i++) {
//        circle(outputimage, snake_points[i], 4, Scalar(0, 0, 255), -1);
//        if (i > 0) {
//            line(outputimage, snake_points[i-1], snake_points[i], Scalar(255, 0, 0), 2);
//        }
//    }
//    line(outputimage, snake_points[0], snake_points[snake_points.size()-1], Scalar(255, 0, 0), 2);
//}

void Snake::draw_contours(Mat image, Mat &outputimage, vector<Point> snake_points, vector<int>& chain_code) {
    outputimage = image.clone();
    chain_code.clear(); // Clear the chain code vector before generating new one
    for (int i = 0; i < snake_points.size(); i++) {
        circle(outputimage, snake_points[i], 4, Scalar(0, 0, 255), -1);
        if (i > 0) {
            line(outputimage, snake_points[i - 1], snake_points[i], Scalar(255, 0, 0), 2);
        }
        line(outputimage, snake_points[0], snake_points[snake_points.size() - 1], Scalar(255, 0, 0), 2);

        // Generate chain code while drawing the contour
        int dx = snake_points[(i + 1) % snake_points.size()].x - snake_points[i].x;
        int dy = snake_points[(i + 1) % snake_points.size()].y - snake_points[i].y;

        // Convert the relative motion to a chain code
        int code;
        if (dx == 0 && dy == 1)
            code = 0;
        else if (dx == 1 && dy == 1)
            code = 1;
        else if (dx == 1 && dy == 0)
            code = 2;
        else if (dx == 1 && dy == -1)
            code = 3;
        else if (dx == 0 && dy == -1)
            code = 4;
        else if (dx == -1 && dy == -1)
            code = 5;
        else if (dx == -1 && dy == 0)
            code = 6;
        else if (dx == -1 && dy == 1)
            code = 7;

        chain_code.push_back(code);
    }
}

vector<int> Snake::generate_chain_code(vector<Point> snake_points) {
    vector<int> chain_code;
    for (int i = 0; i < snake_points.size(); i++) {
        int dx = snake_points[(i + 1) % snake_points.size()].x - snake_points[i].x;
        int dy = snake_points[(i + 1) % snake_points.size()].y - snake_points[i].y;

        // Convert the relative motion to a chain code
        int code;
        if (dx == 0 && dy == 1)
            code = 0;
        else if (dx == 1 && dy == 1)
            code = 1;
        else if (dx == 1 && dy == 0)
            code = 2;
        else if (dx == 1 && dy == -1)
            code = 3;
        else if (dx == 0 && dy == -1)
            code = 4;
        else if (dx == -1 && dy == -1)
            code = 5;
        else if (dx == -1 && dy == 0)
            code = 6;
        else if (dx == -1 && dy == 1)
            code = 7;

        chain_code.push_back(code);
    }
    return chain_code;
}

vector<Point> Snake::active_contour(Mat inputimage, Mat &outputimage,
                            Point center, int radius,
                            int numOfIterations, int numOfPoints,
                            int window_size, double alpha, double beta, double gamma){

    cout << center << endl;
    cout << (inputimage.cols / 2) << " " << (inputimage.rows / 2) << endl;


    vector<Point> curve = initialize_contours(center, radius, numOfPoints);

    // Convert image to grayscale
    Mat grayimage;
  //  Convert_To_Gray(inputimage, grayimage);
    grayimage = Filter::convertToGrayScale(inputimage);
    blur(grayimage, grayimage, Size(5,5));

    // Iterate for multiple iterations
    for (int i = 0; i < numOfIterations; i++) {
        snake_operation(grayimage, curve, window_size, alpha, beta, gamma);
    }

    vector<int> chain_code;
    draw_contours(inputimage, outputimage, curve , chain_code);
    for(int i=0;i<chain_code.size();i++){
        cout<<chain_code[i];
    }
    cout<<endl;
    return curve;
}

