//
//  ObjectiveCFile.mm
//  ArduiMatorNew
//
//  Created by AnshuDiya on 8/20/26.
//

#import <Foundation/Foundation.h>
#include "CplusplusLogic.hpp"
#include <vector>
#include <cmath>


//static Tester Testing;


GraphingApplication GraphingApplicationInstance;

extern "C" {
    int GetDaValue(){
        Tester Testing;
        return Testing.TesterValue;
    }
    
    void DangerousVectorFunctionTester(){
        Tester Testable;
        Testable.DangerousVectorCaller();
    }
    
    void CalculatePolynomialCoordsAndPrintAlias(const char* EquationTypeName, float term1Exponent, float term2Exponent, float term3Exponent, float xRangeValue, float yRangeValue, float resolutionValue = 1.0, int PointsToCalculate = 300) {
        
        if(EquationTypeName != nullptr){
            GraphingApplication GraphingApplicationInstance;
            
            std::string_view StringViewToBePassed(EquationTypeName);
            
            GraphingApplicationInstance.AddGrapherInstance(StringViewToBePassed, xRangeValue, yRangeValue);
            
            GraphingApplicationInstance.CalculatePolynomialCoordsAndPrint(term1Exponent, term2Exponent, term3Exponent, xRangeValue, yRangeValue, resolutionValue, PointsToCalculate);
        }
    }
}

