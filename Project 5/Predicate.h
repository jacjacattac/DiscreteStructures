//
// Created by Jaclyn Palmer on 2/5/22.
//

// store the schemes, facts, and queries

#ifndef INC_236LAB1_PREDICATE_H
#define INC_236LAB1_PREDICATE_H
#include <string>
#include <vector>
#include <sstream>
#include "Token.h"
#include "Parameter.h"
#include "Parser.h"

using namespace std;

class Predicate {
public:
    string name;
    vector <Parameter> parameters;

    Predicate(const string &name) : name(name){}

    string toString(){
        stringstream out;
        out << name << "(";
        for (size_t i = 0; i < parameters.size(); i++) {
            if (i != 0) {
                out << ",";
            }
            out << parameters.at(i).getData();
        }
        out << ")";
        return out.str();
    }

    void addValue(string value) {
        parameters.push_back(Parameter(value));
    }
    string getName(){
        return name;
    }
    vector <Parameter> getParameters(){
        return parameters;
    }
};

#endif //INC_236LAB1_PREDICATE_H
