//
// Created by Kyle on 5/4/2020.
//

#include <iostream>
#include "Runner.h"
using namespace std;

int main() {
    cout << "Hello" << endl;
    Point errorPoints[] = {{0, 3}, {1, 1}};
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    Runner runner;
    //Point p1 = {0, 0}, p2 = {4, 4}, p3 = {1, 2};
    Point p1 = {0, 0}, p2 = {4, 4}, p3 = {1, 1};
    int o = runner.orientation(p1, p2, p3);
    cout << "O value is: " << o << endl;
    // Finds size of arr[] and stores in 'size'
//    int size = sizeof(errorPoints)/sizeof(errorPoints[0]);
//    runner.giftWrapping(errorPoints, size);
}