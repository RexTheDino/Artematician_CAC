//
//  CplusplusLogic.hpp
//  ArduiMatorNew
//
//  Created by AnshuDiya on 8/20/26.
//

#ifndef CplusplusLogic_hpp
#define CplusplusLogic_hpp

#include <stdio.h>

#endif /* CplusplusLogic_hpp */
#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

#pragma once

struct XYcoords{
    std::vector<float> XYcoordsVector; //assumes each y-coord is a fixed distance away. pass this interval as an argument
    float xInterval;
    int gh;
    
    std::vector<std::vector<float>> TermsAndExponents; //each vector corresponds to the term Number and the vector element contains the term's power. Should be dynamically resized with the number of terms
};

class Tester {
public:
    int TesterValue;
    Tester();
    
    std::vector<int> VectorArray[4]; //creates an array of Vectors
    
    std::vector<int>* DangerousVectorTransformer();
    void  DangerousVectorCaller();
};
class GraphingApplication;
class PolynomialGrapher;
class Grapher;
class GraphingSubtypeInterface;



class GraphingApplication {

    int xRangeOfApplication;
    int yRangeOfApplication;
    
    Grapher* CurrentGraphingInstance = nullptr;
    std::vector<std::unique_ptr<Grapher>> GrapherPointerArray;
    
    friend class Grapher;
    
public:
    
    //adds a grapher instance and sets current pointer to that one
    void AddGrapherInstance(std::string_view EquationType, float xRangeValue, float yRangeValue, float resolutionValue = 1.0);
    
    void CalculatePolynomialCoordsAndPrint(float term1Exponent, float term2Exponent, float term3Exponent, float xRangeValue, float yRangeValue, int theRangeOfX, float resolutionValue = 1.0, int PointsToCalculate = 300);
    
    GraphingApplication();
    
};


//put XYcoords struct in here for child classes to use.
//graph constructor also have resolution, xRange, and yRange as arguments. when user clicks zoom button the coordinates are passed into a function that map the given coordinates into pixel coords that are recalculated with every zoom in/out/. when zoom exceeds graph's original x/y values graph is destroyed and reconstructed as a new objecct with greater x/y ranges as original paameters.
class Grapher { //to contain all kinds of graphing classes like trig, calculus, polynomials. initialize them at the START. also have a mixed class for different combos.
    std::unique_ptr<PolynomialGrapher> PolynomialGrapherInstance = std::make_unique<PolynomialGrapher>();
    

    
    
    XYcoords GraphingCoordsStruct; //current classes create their seperate structs but upload final data to this struct
    XYcoords* PointerToGraphingCoordsStruct;
    
    void obtainFunctionCoords(std::vector<std::vector<float>> ExpressionArray, int theRangeOfX, int PointsToCalculate = 300); //copies coords onto XY struct vector
    
    void printCurrentCoords();
    
    //set pointer to XYcoords struct as well
public:
    //SINCE CHILD CLASSES INITIALIZED WITHOUT DEFAULT VALUES NEEDS TO ALSO PASS DEFAULT VALUES TO CHILD CLASSES!
    Grapher(std::string_view EquationType,float xRangeValue, float yRangeValue, float resolutionValue = 1.0); //constructor-- sets parent pointer to the child class thats been already initialized.
    
    GraphingSubtypeInterface* CurrentGraphingSubtypePointer;
    
};

class GraphingSubtypeInterface {
    
    //we'll simplify all of these NVI's into one simple one later. it doesnt matter for now that these NVI's arent non-virtual since they do not modify anything.
public:
    virtual std::vector<std::vector<float>> ExpressionArrayUpdater(bool addOrDelete, int termPosition, float termExponent);
    
    virtual std::vector<float> CoordinatesUpdater(std::vector<std::vector<float>> ExpressionArray, int theRangeOfX, int PointsToCalculate = 300);
    
    virtual void setInitValues(float InitRangeX, float InitRangeY, float InitRangeResol = 1.0);
    
    virtual std::vector<std::vector<float>> returnExpressionArray();
    
    virtual std::vector<float> returnCoordinatesArray();
    
    virtual int returnXinterval();
    
};

class PolynomialGrapher: public GraphingSubtypeInterface { //to output coordinates for a graph of a polynomial
    float xRange;
    float yRange;
    float resolution;  //at resolution of 1.0, there is an interval of 0.01x for every y-coordinate point
    
    
    
    
    XYcoords PolynomialCoordsObject;
    XYcoords* PointerToCoordStruct;
    
    
    //also used for FIRST TIME CONSTRUCTION not just updating
    //ExpressionArrayUpdater is called every single time a term/exponent is updated
    //addOrdelete is true when user adds a term and false when a term is deleted. NOT exponent change, TERM change. unchanged when signs like +/-/*/ '/' / are added
    //termPosition indicates the term that was modified not including SIGNS as position indices. termExponent returns current Exponent of modified term. if term is deleted addOrDelete is FALSE
    //returns the 2D vector expression array from struct XYcoords
    std::vector<std::vector<float>> ExpressionArrayUpdater(bool addOrDelete, int termPosition, float termExponent) override;
    
    std::vector<float> CoordinatesUpdater(std::vector<std::vector<float>> ExpressionArray, int theRangeOfX, int PointsToCalculate = 300) override; //calculates 300 points by default values
public:
    PolynomialGrapher(float xRangeValue, float yRangeValue, float resolutionValue = 1.0);
    PolynomialGrapher();
    
    void setInitValues(float InitRangeX, float InitRangeY, float InitRangeResol = 1.0) override;
    
    //we'll simplify all these individual return functions later. kinda takes away from the simplicity of polymorphism
    std::vector<std::vector<float>> returnExpressionArray() override;
    
    std::vector<float> returnCoordinatesArray() override;
    
    int returnXinterval() override;
    
};



