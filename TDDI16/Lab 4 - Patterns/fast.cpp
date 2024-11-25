#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "point.h"
#include "window.h"
#include <numeric>
using namespace std;

int main(int argc, const char* argv[]) {
    WindowPtr window = create_window(argc, argv);
    if (!window)
        return 1;

    // The array of points
    vector<Point> points;

    // Read tolerance from cin
    double tolerance = 0.001;
    cin >> tolerance;

    // Read points from cin
    int N{};
    cin >> N;

    for (int i{0}; i < N; ++i) {
        double x{}, y{};
        cin >> x >> y;
        points.push_back(Point{x, y});
    }

    // draw points to screen all at once
    window->draw_points(points);

    auto begin = chrono::high_resolution_clock::now();

    /////////////////////////////////////////////////////////////////////////////
    // Iterate over each point and set it as the origin, sort copy_points once
    /////////////////////////////////////////////////////////////////////////////
for (auto original : points)
{
    vector<Point> copy_points = points;
    sort(copy_points.begin(), copy_points.end(), PolarSorter(original));

    vector<Point> same_slope{copy_points[0]};

    for (int i = 1; i < int(copy_points.size()); i++)
    {
        if ((same_slope.size() != 3 && copy_points[0].sameSlope(copy_points[i - 1], copy_points[i], tolerance)) ||
            copy_points[0].sameSlope(copy_points[i - 2], copy_points[i], tolerance))
        {
            same_slope.push_back(copy_points[i]);
        }
        else
        {
            if (same_slope.size() >= 4)
            {
                window->draw_line(same_slope);
            }

            same_slope = {copy_points[0], copy_points[i]};
        }
    }
    if (same_slope.size() >= 4)
    {
        window->draw_line(same_slope);
    }
}


    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // Wait for user to terminate program
    window->run();

    return 0;
}
