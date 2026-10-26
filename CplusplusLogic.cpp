//
//  CplusplusLogic.cpp
//  ArduiMatorNew
//
//  Created by AnshuDiya on 8/20/26.
//

#include "CplusplusLogic.hpp"
#include <vector>
#include <cmath>
#include <memory>

Tester::Tester(){
    TesterValue = 43;
}

void GraphingApplication::AddGrapherInstance(std::string_view EquationType, float xRangeValue, float yRangeValue, float resolutionValue){
    
    //add different child classes like calc and trig later
    if(EquationType == "Polynomial"){
        std::unique_ptr<Grapher> TempUnique = std::make_unique<Grapher>(EquationType, xRangeValue, yRangeValue, resolutionValue = 1.0);
        
        CurrentGraphingInstance = TempUnique.get();
        
        GrapherPointerArray.push_back(std::move(TempUnique));
    }
    
}



//create an object of the specific Graphing subclass like Polynomial graph. whatever the equation aligns to.
Grapher::Grapher(std::string_view EquationType,float xRangeValue, float yRangeValue, float resolutionValue){ //add types of graphs as they are created as classes. stores only polynomial for now.
    
    //SINCE INITIALIZED AS EMPTY CONSTRUCTOR NEED TO SET INITIAL VALUES!!!
    PolynomialGrapherInstance->setInitValues(xRangeValue, yRangeValue, resolutionValue);
    //CalculusGrapher = ...
    //TrigGrapher = ...
    //PolarGrapher = ...
    
    if(EquationType == "Polynomial"){
        CurrentGraphingSubtypePointer = PolynomialGrapherInstance.get();
    }
}

void Grapher::obtainFunctionCoords(std::vector<std::vector<float>> ExpressionArray, int theRangeOfX, int PointsToCalculate){
    std::vector<float> temporaryVector;
    temporaryVector = CurrentGraphingSubtypePointer->CoordinatesUpdater(ExpressionArray, theRangeOfX, PointsToCalculate);//must remain same across all virtuals
    
    GraphingCoordsStruct.XYcoordsVector = temporaryVector;
}

void Grapher::printCurrentCoords(){
    auto NumberOfPointsToBePrinted = GraphingCoordsStruct.XYcoordsVector.size();
    auto xIntervalTemp = GraphingCoordsStruct.xInterval;
    float currentYvalue = 0.0;
    float currentXvalue = 0.0;
    
    for(int ty = 0; ty < NumberOfPointsToBePrinted; ty++){
        
        currentYvalue = GraphingCoordsStruct.XYcoordsVector[ty];
        currentXvalue = (ty * xIntervalTemp);
        
        std::cout << "X: ";
        std::cout << currentXvalue;
        std::cout << "   Y: ";
        std::cout << currentYvalue;
        std::cout << "\n";
        
    }
}





std::vector<int>* Tester::DangerousVectorTransformer(){
    for(int ez = 0; ez < 4; ez++){         //creates five elements in each vector array matching the for loop variable
        for(int hi = 0; hi < (4-ez); hi++)
        VectorArray[ez].push_back(ez);
        
    }
    std::vector<int>* ReturnPointer = &VectorArray[0];  //takes first element of first vector and sets that memory adress equal to ReturnPointer
    
    return ReturnPointer;
    
}

void Tester::DangerousVectorCaller(){ //experiments: make array of vectors with each vector having different sizes. create pointer of vector type to first vector. increment pointer by 1 each time and print out first element of that vector. Does the pointer succesfully jump from vector to vector or does the difference in vector sizes cause it to accidentally get stuck in one vector more than once as it leaps forward a fixed amountt? Answer: C++ is smart.
    std::vector<int>* PointerBeingUsed = DangerousVectorTransformer();
    
    for(int yu = 0; yu < 4; yu++){
        std::vector<int> CurrentVector;
        CurrentVector = *(PointerBeingUsed + yu);
        
        int PrintedNumber = 0;
        PrintedNumber = CurrentVector[0];
        
        std::cout << "\n" << std::endl;
        std::cout << PrintedNumber << std::endl;
        
    }
}


PolynomialGrapher::PolynomialGrapher(float xRangeValue, float yRangeValue, float resolutionValue) {
    
    PointerToCoordStruct = &PolynomialCoordsObject;
    
    
    xRange = xRangeValue;
    yRange = yRangeValue;
    resolution = resolutionValue;
    
    
}

void PolynomialGrapher::setInitValues(float InitRangeX, float InitRangeY, float InitRangeResol){
    xRange = InitRangeX;
    yRange = InitRangeY;
    resolution = InitRangeResol;
}

//one variable/symbol at a time
std::vector<std::vector<float>> PolynomialGrapher::ExpressionArrayUpdater(bool addOrDelete, int termPosition, float termExponent){
    
    if(!(addOrDelete)){
        PointerToCoordStruct->TermsAndExponents.erase(PointerToCoordStruct->TermsAndExponents.begin() + termPosition); //when erasing a vector also pass its termPosition. termPosition should start at 0 and count from the left.
        //addOrDelete = false = DELETE
    } else {
        std::vector<float> RowToBeInserted = {termExponent};
        PointerToCoordStruct->TermsAndExponents.insert(PointerToCoordStruct->TermsAndExponents.begin() + termPosition, RowToBeInserted);
    }
    
    return (PointerToCoordStruct->TermsAndExponents);
}

std::vector<float> PolynomialGrapher::CoordinatesUpdater(std::vector<std::vector<float>> ExpressionArray, int theRangeOfX, int PointsToCalculate) {
    PointsToCalculate = int( float(PointsToCalculate) * resolution); //converts given value to float, multiplies by resolution factor, converts back to int for use in for loop
    PointerToCoordStruct->XYcoordsVector.resize(PointsToCalculate); //resizes coordinate vector to number of points needed
    auto numberOfTerms = PointerToCoordStruct->TermsAndExponents.size();
    PointerToCoordStruct->xInterval = (float(theRangeOfX) / float(PointsToCalculate)); //sets xInterval to x-axis range divided by total number of points
    
    for(int ou = 0; ou < PointsToCalculate; ou++){
        
        float currentXvalue = (float(ou) * PointerToCoordStruct->xInterval); //increments x-value by xInterval each time
        float CalculatedValue = 0.0;
        
        for(int iw = 0; iw < numberOfTerms; iw++){ //takes size of (# of terms) of expression and adds to current y-coord for each expression
            
            float CalculatedTermValue; //calculates y-value for a single term
            CalculatedTermValue = PointerToCoordStruct->TermsAndExponents[iw][0]; //sets a variable equal to the current term's exponent
            CalculatedTermValue = std::pow(currentXvalue,CalculatedTermValue); //takes xValue and raises it to the power of exponent and sets it equal to Calculated Value
            CalculatedValue += CalculatedTermValue; //adds term's contirbution to that point's calculated value
            
        }
        
        PointerToCoordStruct->XYcoordsVector[ou] = CalculatedValue; //sets the value of the current point to what was calculated
        
    }
    
    PointerToCoordStruct->XYcoordsVector.clear();
    
    return PointerToCoordStruct->XYcoordsVector;
}

std::vector<std::vector<float>> PolynomialGrapher::returnExpressionArray(){
    return PointerToCoordStruct->TermsAndExponents;
}

std::vector<float> PolynomialGrapher::returnCoordinatesArray() {
    return PolynomialCoordsObject.XYcoordsVector;
}

int PolynomialGrapher::returnXinterval() {
    return PolynomialCoordsObject.xInterval;
}


void GraphingApplication::CalculatePolynomialCoordsAndPrint(float term1Exponent, float term2Exponent, float term3Exponent, float xRangeValue, float yRangeValue, int theRangeOfX, float resolutionValue, int PointsToCalculate) {
    
    CurrentGraphingInstance->CurrentGraphingSubtypePointer->ExpressionArrayUpdater(true, 1, term1Exponent);
    CurrentGraphingInstance->CurrentGraphingSubtypePointer->ExpressionArrayUpdater(true, 2, term2Exponent);
    CurrentGraphingInstance->CurrentGraphingSubtypePointer->ExpressionArrayUpdater(true, 3, term3Exponent);
    
    std::vector<std::vector<float>> tempVectorArray = CurrentGraphingInstance->CurrentGraphingSubtypePointer->returnExpressionArray();
    
    CurrentGraphingInstance->CurrentGraphingSubtypePointer->CoordinatesUpdater(tempVectorArray, xRangeValue, 310);
    
    std::vector<float> tempCoordinatesArray = CurrentGraphingInstance->CurrentGraphingSubtypePointer->returnCoordinatesArray();
    auto sizeOfCoordinatesArray = tempCoordinatesArray.size();
    auto CurrentXinterval = CurrentGraphingInstance->CurrentGraphingSubtypePointer->returnXinterval();
    
    for (int k = 0; k < sizeOfCoordinatesArray; k++) {
        std::cout << "X: ";
        std::cout << (CurrentXinterval*k);
        std::cout << "\n Y: ";
        std::cout << tempCoordinatesArray[k];
        std::cout << "\n";
    }
    
}
