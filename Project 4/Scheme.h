//
// Created by Jaclyn Palmer on 3/1/22.
//

#ifndef INC_236LAB1_SCHEME_H
#define INC_236LAB1_SCHEME_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) { }

    Scheme(){}


};
#endif //INC_236LAB1_SCHEME_H
