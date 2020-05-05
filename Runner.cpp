//
// Created by Kyle on 5/4/2020.
//

#include "Runner.h"

void Runner::grahamScan(Point *pointSet, int n) {
    cout << "In here" << endl;
    if(n < 3)
    {
        cout << "Error! Convex hull must contain at least 3 points!" << endl;
    }
}

void Runner::giftWrapping(Point *pointSet, int n) {
    //Implementaion of Jarvis' March/Gift Wrapping
    if(n < 3) //Need at least 3 points for a convex hull
    {
        cout << "Error! Convex hull must contain at least 3 points!" << endl;
    }

    //Start with an exterior point --> leftmost, rightmost, topmost, bottommost
    //Going to be getting the leftmost point
    int leftmost = 0;
    for(int i = 1; i < n; i++){

    }

}

int Runner::orientation(Point p1, Point p2, Point p3) {
    /*
     * Referenced https://www.geeksforgeeks.org/orientation-3-ordered-points/
     * for calculating orientation between 3 points
     *
     * 0 --> p1, p2, and p3 are colinear
     * 1 --> Clockwise
     * 2 --> Counterclockwise
     *
     * Calculates the orientation by looking at the slope between the 3 points
     * Equation for slope between two points = (y2 - y1) / (x2 - x1)
     * W = p1 to p2 slope = (p2.y - p1.y) / (p2.x - p1.x)
     * Z = p2 to p3 slope = (p3.y - p2.y) / (p3.x - p2.x)
     *
     * Now that we have both of the slope calculations, time to determine the orientation by comparing these slopes...
     * If Z = W --> Colinear
     * If Z < W --> Clockwise
     * If Z > W --> Counterclockwise
     *
     * To make this comparison, will set a variable called slopeValue = Z - W
     * slopeValue = 0 --> Colinear
     * slopeValue < 0 --> Clockwise
     * slopeValue > 0 --> Counterclockwise
     *
     * Z - W = ((p3.y - p2.y) / (p3.x - p2.x)) - ((p2.y - p1.y) / (p2.x - p1.x))
     * Through cross multiplication (multiply everything by (p3.x - p2.x) and (p2.x - p1.x)) we get...
     * Z - W = ((p3.y - p2.y) * (p2.x - p1.x)) - ((p2.y - p1.y) * (p3.x - p2.x)) = slopeValue
     */
    int slopeValue = ((p3.y - p2.y) * (p2.x - p1.x)) - ((p2.y - p1.y) * (p3.x - p2.x));

    if (slopeValue == 0) return 0;  // Colinear

    /*
     * https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/operators/conditional-operator
     * is this condition true ? yes : no
     * 1 --> Clockwise
     * 2 --> Counterclockwise
     */
    return(slopeValue < 0)? 1:2;

}
