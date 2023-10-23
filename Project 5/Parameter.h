//
// Created by Jaclyn Palmer on 2/5/22.
//

#ifndef INC_236LAB1_PARAMETER_H
#define INC_236LAB1_PARAMETER_H

// holds whats inside the parenthesis as a string

#include <iostream>

using namespace std;

class Parameter {
public:
    string data;

    Parameter(const string &data) : data(data){}

    string getData(){
        return data;
    }

    bool isConst(){
        if (data.at(0) == '\''){
            return true;
        }
        else{
            return false;
        }
    }
    string toString(){
        return data;
    }
};

#endif //INC_236LAB1_PARAMETER_H
