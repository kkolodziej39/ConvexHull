//
// Created by Kyle on 5/4/2020.
// Updated by Kyle on 5/6/2020.
//

#include "Runner.h"

Point globalPoint; //Global variable of type Point to be used as reference in Graham's Scan sort

void Runner::grahamScan(Point *pointSet, int n, ofstream &out) {
    // Implementation of Graham's Scan algorithm below
    if(n < 3) //Need at least 3 elements for a convex hull
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
    auto start = std::chrono::high_resolution_clock::now();
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

    //Need to remove collinear points
    int m = 1; // Will contain new size of array
    for (int i=1; i<n; i++)
    {
        while (i < n-1 && orientation(globalPoint, pointSet[i],pointSet[i+1]) == 0){
            i++;
        }
        pointSet[m] = pointSet[i];
        m++;  // Update size of new array
    }

    //Put the first three elements on the stack
    stack<Point> stack;
    for(int i = 0; i < 3; i++)
    {
        stack.push(pointSet[i]);
    }

    /*
     * This for loop below generates the stack full of all hull points
     * It evaluates the orientation of
     * 1.) The second Point from the top of the stack (previous point)
     * to
     * 2.) The top Point on the stack (current point)
     * to
     * 3.) The next point from the set of Points (next point)
     *
     * If these 3 Points produce a non-clockwise orientation, then that means one or more points in the stack is
     * a left turn from a previous point to get to this Point. Points that don't have a counterclockwise orientation
     * are not going to be a hull point as this left turn will result in skipping points in the dataset and/or
     * an interior angle greater than 180 degrees (which would not fit the requirements for a convex hull).
     *
     * To get rid of these left turn points, we pop the Points off of the stack until we return to a counterclockwise
     * orientation of:
     * 1.) The second Point from the top of the stack (previous point)
     * to
     * 2.) The top Point on the stack (current point)
     * to
     * 3.) The next point from the set of Points (next point)
     *
     * Once this is accomplished, we add the "next point" to the stack and repeat this process until
     * we are fully through the set of Points
     */
    for(int i = 3; i < m; i++){
        while(orientation(secondStackElement(stack), stack.top(), pointSet[i]) != 2){
            stack.pop();
        }
        stack.push(pointSet[i]);
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long timeInLong = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    /* Conversion from microseconds to seconds:
     * double time = timeInLong /1000000.00;
     * Didn't use this as the algorithm was running fast enough on these dataset sizes
     * that the smaller unit of measure was more appropriate
     */

    //Print Graham's Scan to the output file
    out << "**************************************************************************************************" << endl;
    out << "---------------------------------" << "GRAHAM'S SCAN" << "----------------------------------" << endl;
    out << "Algorithm Performed on " << n << " Elements" << endl;
    out << "Time elapsed: " << timeInLong << " microsecond(s)" << endl;
    out << "Printing the Hull Points..." << endl;
    while(!stack.empty()){
        Point temp = stack.top();
        out << "(" << temp.x << ", " << temp.y << ")" << endl;
        stack.pop();
    }

}

void Runner::giftWrapping(Point *pointSet, int n, ofstream &out) {
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
    auto start = std::chrono::high_resolution_clock::now();
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

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long timeInLong = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    /* Conversion from microseconds to seconds:
     * double time = timeInLong /1000000.00;
     * Didn't use this as the algorithm was running fast enough on these dataset sizes
     * that the smaller unit of measure was more appropriate
     */
    out << "**************************************************************************************************" << endl;
    out << "---------------------------" << "JARVIS' MARCH/GIFT WRAPPING" << "---------------------------" << endl;
    out << "Algorithm Performed on " << n << " Elements" << endl;
    out << "Time elapsed: " << timeInLong << " microsecond(s)" << endl;
    out << "Printing the Hull Points..." << endl;
    //Print the convex hull
    for(int i = 0; i < convexHull.size(); i++)
    {
        out << "(" << convexHull[i].x << ", " << convexHull[i].y << ")" << endl;
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

Point Runner::secondStackElement(stack<Point> &stacker) {
    /*
     * Will get the second element from the top of the stack passed in as a parameter
     * It does this by getting the top element and then storing this in a temp variable
     * Then, it pops this top element off from the stack
     * Next, it gets the next element in the stack, which is the second element from the top of the original stack
     * Then, it adds back the temp Point variable containing the top element in the stack
     * Finally, the stack is returned to its normal form and it returns the second element from the top of the stack
     */
    Point topElement = stacker.top();
    stacker.pop();
    Point secondElement = stacker.top();
    stacker.push(topElement);
    return secondElement;
}
