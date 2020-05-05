//
// Created by Kyle on 5/4/2020.
//

#include "Runner.h"

Point globalPoint;

void Runner::grahamScan(Point *pointSet, int n) {
    cout << "In here" << endl;
    if(n < 3)
    {
        cout << "Error! Convex hull must contain at least 3 points!" << endl;
    }

    /* Start with an exterior point --> leftmost, rightmost, topmost, bottommost
     * Going to be getting the bottommost point
     * Doing this by setting the index of bottommost to 0
     * Then, will loop through the set of points with i as the index value
     * If it comes across a point farther to the left (pointSet[i].y < pointSet[bottommost].y),
     * then will need to update bottommost value with the new index by setting bottommost = i
     *
     * In case of a tie, get the leftmost point of the two points with the same y values
     */
    int bottommost = 0;
    for(int i = 1; i < n; i++){
        if((pointSet[i].y < pointSet[bottommost].y) ||
            (pointSet[i].y == pointSet[bottommost].y && pointSet[i].x < pointSet[bottommost].x)){
            bottommost = i;
        }
    }
    /*
     * Now need to put this bottommost point at the front and sort around it
     * Sorting the rest of the points in angular order around this point
     * Will be using qsort() as well as comparison as a fourth parameter which will be used
     * in checking this angle with type Point
     * and referencing the bottommost point found with variable globalPoint
     */
    Point temp = pointSet[0];
    pointSet[0] = pointSet[bottommost];
    pointSet[bottommost] = temp;
    globalPoint = pointSet[0]; //Global point is used in comparison call below to sort in angular order
    qsort(&pointSet[1], n-1, sizeof(Point), comparison);


    stack<Point> stack;
    for(int i = 0; i < 3; i++)
    {
        stack.push(pointSet[i]);
    }

}

void Runner::giftWrapping(Point *pointSet, int n) {
    //Implementaion of Jarvis' March/Gift Wrapping
    if(n < 3) //Need at least 3 points for a convex hull
    {
        cout << "Error! Convex hull must contain at least 3 points!" << endl;
    }

    /* Start with an exterior point --> leftmost, rightmost, topmost, bottommost
     * Going to be getting the leftmost point
     * Doing this by setting the index of leftmost to 0
     * Then, will loop through the set of points with i as the index value
     * If it comes across a point farther to the left (pointSet[i].x < pointSet[leftmost].x),
     * then will need to update leftmost value with the new index by setting leftmost = i
     */
    int leftmost = 0;
    for(int i = 1; i < n; i++){
        if(pointSet[i].x < pointSet[leftmost].x)
            leftmost = i;
    }
    vector<Point> convexHull; //Will contain all of the hull points (vertexes of the convex hull)

    /*
     * After getting the leftmost point, will need to get a "new leftmost" point
     * while using this "old leftmost" point as the point of reference
     *
     * Continue doing this until we reach the original leftmost point
     * Once that point is reached, need to stop searching for points because
     * all points in the convex hull would be added to the vector convexHull
     */
    int p1 = leftmost;
    do{

        convexHull.push_back(pointSet[p1]); //Adding leftmost point
        int p3 = (p1 + 1) % n; //Get a new point in the pointSet
        /*
         * This will check through all of the points in the pointSet
         * and get the "new leftmost" point in reference to the "old leftmost" point
         *
         * It does this by checking the orientation of p1, p2, and p3
         * such that p1 = old leftmost, p2 = iterator traversing through pointSet, and p3 = new leftmost
         *
         * If this orientation is counterclockwise (orientation = 2), then p2 is farther left than p3
         * and would need to update p3 by setting equal to p2
         */
        for(int p2 = 0; p2 < n; p2++)
        {
            if(orientation(pointSet[p1], pointSet[p2], pointSet[p3]) == 2) //p2 is more counterclockwise than p3
                p3 = p2; //Need to update p3 to leftmost point
        }
        p1 = p3; //Once have leftmost point, need to update p1
    } while(p1 != leftmost); //Keep loop going until back at initial leftmost point

    //Print the convex hull
    for(int i = 0; i < convexHull.size(); i++)
    {
        cout << "(" << convexHull[i].x << ", " << convexHull[i].y << ")" << endl;
    }


}

int Runner::orientation(Point p1, Point p2, Point p3) {
    /*
     * Referenced https://www.geeksforgeeks.org/orientation-3-ordered-points/
     * for calculating orientation between 3 points
     *
     * 0 --> p1, p2, and p3 are collinear
     * 1 --> Clockwise
     * 2 --> Counterclockwise
     *
     * Calculates the orientation by looking at the slope between the 3 points
     * Equation for slope between two points = (y2 - y1) / (x2 - x1)
     * W = p1 to p2 slope = (p2.y - p1.y) / (p2.x - p1.x)
     * Z = p2 to p3 slope = (p3.y - p2.y) / (p3.x - p2.x)
     *
     * Now that we have both of the slope calculations, time to determine the orientation by comparing these slopes...
     * If Z = W --> Collinear
     * If Z < W --> Clockwise
     * If Z > W --> Counterclockwise
     *
     * To make this comparison, will set a variable called slopeValue = Z - W
     * slopeValue = 0 --> Collinear
     * slopeValue < 0 --> Clockwise
     * slopeValue > 0 --> Counterclockwise
     *
     * Z - W = ((p3.y - p2.y) / (p3.x - p2.x)) - ((p2.y - p1.y) / (p2.x - p1.x))
     * Through cross multiplication (multiply everything by (p3.x - p2.x) and (p2.x - p1.x)) we get...
     * Z - W = ((p3.y - p2.y) * (p2.x - p1.x)) - ((p2.y - p1.y) * (p3.x - p2.x)) = slopeValue
     */
    int slopeValue = ((p3.y - p2.y) * (p2.x - p1.x)) - ((p2.y - p1.y) * (p3.x - p2.x));

    if (slopeValue == 0) return 0;  // Collinear

    /*
     * https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/operators/conditional-operator
     * is this condition true ? yes : no
     * 1 --> Clockwise
     * 2 --> Counterclockwise
     */
    return(slopeValue < 0)? 1:2;

}

int Runner::distanceBetwnPoints(Point p1, Point p2) {
    //Distance formula is sqrt( (x2 - x1)^2 + (y2-y1)^2 )
    int squaredDist = ((p2.x - p1.x)*(p2.x - p1.x)) + ((p2.y - p1.y)*(p2.y - p1.y));
    return squaredDist;
}

int Runner::comparison(const void *p1, const void *p2) {
    Point *first = (Point *) p1;
    Point *sec = (Point *) p2;

    int val = orientation(globalPoint, *first, *sec);
    if (val == 0) //If Collinear points, compare the distance between the two
        return (distanceBetwnPoints(globalPoint, *sec) >= distanceBetwnPoints(globalPoint, *first)) ? -1 : 1;

    //Else look if it is counterclockwise or clockwise
    return (val == 2) ? -1 : 1;
}
