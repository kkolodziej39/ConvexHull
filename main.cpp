//
// Created by Kyle on 5/4/2020.
// Updated by Kyle on 5/6/2020.
//

#include <iostream>
#include <fstream>
#include <ostream>
#include "Runner.h"
using namespace std;

vector<Point> generatePointSet(const vector<string> &d){
    vector<string> data = d;
    string numElements = data[0];

    if (numElements[numElements.size() - 1] == '\r'){
        //Windows carriage return checker to erase the \r if it contains it
        numElements.erase(numElements.size()-1, 1);
    }

    //Need to erase the [] around numElements
    //For example, transformation: [26] ---> 26
    numElements.erase(0,1);
    numElements.erase(numElements.size()-1, 1);
    int numCoordPairs = stoi(numElements);

    vector<Point> returningPointSet;

    for(int i = 1; i <= numCoordPairs; i++) {
        string str = data[i];
        if (str[str.size() - 1] == '\r') {
            //Windows carriage return checker to erase the \r if it contains it
            str.erase(str.size() - 1, 1);
        }
        std::size_t pos = str.find(",");
        string first = str.substr(0, pos);
        str.erase(0, pos + 1); //Str will now contain the y-coordinate
        int xCoord = stoi(first);
        int yCoord = stoi(str);
        Point tempPoint = {xCoord, yCoord}; //Create Point with the integer values of the coordinates
        returningPointSet.push_back(tempPoint); //Add the point to the vector which will be returned
    }
    return returningPointSet;
}

int main() {
    Runner runner;
    ifstream inputFile;
    vector<string> inputLines0, inputLines1, inputLines2, inputLines3, inputLines4;
    vector<string> inputLines5, inputLines6, inputLines7, inputLines8, inputLines9;
    ofstream out0, out1, out2, out3, out4, out5, out6, out7, out8, out9;
    string str;

    //Open and read the first data set in Input file #1
    inputFile.open("ConvexInputFiles/Input1.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 1" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines0.push_back(str);
    }
    inputFile.close();


    //Now on to Input file #2
    inputFile.open("ConvexInputFiles/Input2.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 2" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines1.push_back(str);
    }
    inputFile.close();


    //Now on to Input file #3
    inputFile.open("ConvexInputFiles/Input3.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 3" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines2.push_back(str);
    }
    inputFile.close();

    //Now on to Input file #4
    inputFile.open("ConvexInputFiles/Input4.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 4" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines3.push_back(str);
    }
    inputFile.close();

    //Now on to Input file #5
    inputFile.open("ConvexInputFiles/Input5.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 5" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines4.push_back(str);
    }
    inputFile.close();

    //Now on to Input file #6
    inputFile.open("ConvexInputFiles/Input6.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 6" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines5.push_back(str);
    }
    inputFile.close();

    //Now on to Input file #7
    inputFile.open("ConvexInputFiles/Input7.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 7" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines6.push_back(str);
    }
    inputFile.close();

    //Now on to Input file #8
    inputFile.open("ConvexInputFiles/Input8.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 8" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines7.push_back(str);
    }
    inputFile.close();

    //Now on to Input file #9
    inputFile.open("ConvexInputFiles/Input9.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 9" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines8.push_back(str);
    }
    inputFile.close();

    //Now on to Input file #10
    inputFile.open("ConvexInputFiles/Input10.txt");
    if(!inputFile.is_open())
    {
        cout << "ERROR Opening Input File 10" << endl;
        return 0;
    }

    while(getline(inputFile, str)) //Get all of the lines from the input file
    {
        inputLines9.push_back(str);
    }
    inputFile.close();


    /* Now send all the parsed input files' data to Runner
     * Here it will determine the Convex Hull by both
     * Graham's Scan and Jarvis' March/Gift Wrapping
     * Then, it will print the results to an output file
     *
     * Each output file will contain (broken into a separate section for each algorithm):
     * 1.) The number of elements the algorithm performed on
     * 2.) The time elapsed to run the algorithm
     * 3.) The hull points (coordinate pairs that are apart of the Convex Hull)
     */
    vector<Point> pointVect = generatePointSet(inputLines0);
    Point pointSet1[pointVect.size()];
    for(int i = 0; i < pointVect.size(); i++){
        pointSet1[i] = pointVect[i];
    }
    int size = sizeof(pointSet1)/sizeof(pointSet1[0]);

    out0.open("Convex1_Output.txt");
    runner.grahamScan(pointSet1, size, out0);
    runner.giftWrapping(pointSet1, size, out0);
    out0.close();


    vector<Point> pointVect2 = generatePointSet(inputLines1);
    Point pointSet2[pointVect2.size()];
    for(int i = 0; i < pointVect2.size(); i++){
        pointSet2[i] = pointVect2[i];
    }
    size = sizeof(pointSet2)/sizeof(pointSet2[0]);

    out1.open("Convex2_Output.txt");
    runner.grahamScan(pointSet2, size, out1);
    runner.giftWrapping(pointSet2, size, out1);
    out1.close();


    vector<Point> pointVect3 = generatePointSet(inputLines2);
    Point pointSet3[pointVect3.size()];
    for(int i = 0; i < pointVect3.size(); i++){
        pointSet3[i] = pointVect3[i];
    }
    size = sizeof(pointSet3)/sizeof(pointSet3[0]);

    out2.open("Convex3_Output.txt");
    runner.grahamScan(pointSet3, size, out2);
    runner.giftWrapping(pointSet3, size, out2);
    out2.close();


    vector<Point> pointVect4 = generatePointSet(inputLines3);
    Point pointSet4[pointVect4.size()];
    for(int i = 0; i < pointVect4.size(); i++){
        pointSet4[i] = pointVect4[i];
    }
    size = sizeof(pointSet4)/sizeof(pointSet4[0]);

    out3.open("Convex4_Output.txt");
    runner.grahamScan(pointSet4, size, out3);
    runner.giftWrapping(pointSet4, size, out3);
    out3.close();


    vector<Point> pointVect5 = generatePointSet(inputLines4);
    Point pointSet5[pointVect5.size()];
    for(int i = 0; i < pointVect5.size(); i++){
        pointSet5[i] = pointVect5[i];
    }
    size = sizeof(pointSet5)/sizeof(pointSet5[0]);

    out4.open("Convex5_Output.txt");
    runner.grahamScan(pointSet5, size, out4);
    runner.giftWrapping(pointSet5, size, out4);
    out4.close();


    vector<Point> pointVect6 = generatePointSet(inputLines5);
    Point pointSet6[pointVect6.size()];
    for(int i = 0; i < pointVect6.size(); i++){
        pointSet6[i] = pointVect6[i];
    }
    size = sizeof(pointSet6)/sizeof(pointSet6[0]);

    out5.open("Convex6_Output.txt");
    runner.grahamScan(pointSet6, size, out5);
    runner.giftWrapping(pointSet6, size, out5);
    out5.close();


    vector<Point> pointVect7 = generatePointSet(inputLines6);
    Point pointSet7[pointVect7.size()];
    for(int i = 0; i < pointVect7.size(); i++){
        pointSet7[i] = pointVect7[i];
    }
    size = sizeof(pointSet7)/sizeof(pointSet7[0]);

    out6.open("Convex7_Output.txt");
    runner.grahamScan(pointSet7, size, out6);
    runner.giftWrapping(pointSet7, size, out6);
    out6.close();


    vector<Point> pointVect8 = generatePointSet(inputLines7);
    Point pointSet8[pointVect8.size()];
    for(int i = 0; i < pointVect8.size(); i++){
        pointSet8[i] = pointVect8[i];
    }
    size = sizeof(pointSet8)/sizeof(pointSet8[0]);

    out7.open("Convex8_Output.txt");
    runner.grahamScan(pointSet8, size, out7);
    runner.giftWrapping(pointSet8, size, out7);
    out7.close();


    vector<Point> pointVect9 = generatePointSet(inputLines8);
    Point pointSet9[pointVect9.size()];
    for(int i = 0; i < pointVect9.size(); i++){
        pointSet9[i] = pointVect9[i];
    }
    size = sizeof(pointSet9)/sizeof(pointSet9[0]);

    out8.open("Convex9_Output.txt");
    runner.grahamScan(pointSet9, size, out8);
    runner.giftWrapping(pointSet9, size, out8);
    out8.close();


    vector<Point> pointVect10 = generatePointSet(inputLines9);
    Point pointSet10[pointVect10.size()];
    for(int i = 0; i < pointVect10.size(); i++){
        pointSet10[i] = pointVect10[i];
    }
    size = sizeof(pointSet10)/sizeof(pointSet10[0]);

    out9.open("Convex10_Output.txt");
    runner.grahamScan(pointSet10, size, out9);
    runner.giftWrapping(pointSet10, size, out9);
    out9.close();

    return 0;

}