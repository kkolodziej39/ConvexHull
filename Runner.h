//
// Created by Kyle on 5/4/2020.
// Updated by Kyle on 5/6/2020.
//

#ifndef CONVEXHULL_RUNNER_H
#define CONVEXHULL_RUNNER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ostream>
#include <cstdlib>
#include <chrono>
#include <stack>
using namespace std;

struct Point{
    int x, y;
};

class Runner {
public:
    void grahamScan(Point pointSet [], int n, ofstream &out);
    void giftWrapping(Point pointSet [], int n, ofstream & out);
    static int orientation(Point p1, Point p2, Point p3);
    static int comparison(const void * p1, const void * p2);
    static int distanceBetwnPoints(Point p1, Point p2);
    Point secondStackElement(stack<Point> & stacker);
};


#endif //CONVEXHULL_RUNNER_H
