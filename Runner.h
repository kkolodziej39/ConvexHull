//
// Created by Kyle on 5/4/2020.
//

#ifndef CONVEXHULL_RUNNER_H
#define CONVEXHULL_RUNNER_H

#include <iostream>
using namespace std;

struct Point{
    int x, y;
};


class Runner {
public:
    void grahamScan(Point pointSet [], int n);
    void giftWrapping(Point pointSet [], int n);
    int orientation(Point p1, Point p2, Point p3);
};


#endif //CONVEXHULL_RUNNER_H
