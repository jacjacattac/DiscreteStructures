//
// Created by Jaclyn Palmer on 3/1/22.
//

#ifndef INC_236LAB1_TUPLE_H
#define INC_236LAB1_TUPLE_H
#include <iostream>
#include <string>
#include <vector>
#include "Scheme.h"
#include <sstream>

using namespace std;

class Tuple : public vector<string> {

public:

    Tuple(vector<string> values) : vector<string>(values) { }

    string toString(const Scheme& scheme) const {
        stringstream out;
        out << "  ";
        for (size_t i = 0; i < size(); i++) {
            if (i > 0)
                out << ", ";
            const string& name = scheme.at(i);
            const string& value = at(i);
            out << name << "=" << value;
        }
        return out.str();
    }

};

#endif //INC_236LAB1_TUPLE_H
