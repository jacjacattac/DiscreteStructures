//
// Created by Jaclyn Palmer on 2/5/22.
//

#ifndef INC_236LAB1_RULE_H
#define INC_236LAB1_RULE_H
#include "Predicate.h"
#include <sstream>
#include <vector>

//Stores head predicate and list of predicates
class Rule {
public:
    Predicate headPredicate;
    vector<Predicate> predicates;

    Rule(Predicate headPredicate) : headPredicate(headPredicate) {}

    void addPredicate(Predicate p) {
        predicates.push_back(p);
    }

    string ruleToString() {
        stringstream out;
        out << headPredicate.getName() << "(";
        for (size_t i =0; i < headPredicate.parameters.size(); i++) {
            if (i != 0) {
                out << ",";
            }
            out << headPredicate.parameters.at(i).getData();
        }
        out << ") :- ";
        for(size_t i = 0; i < predicates.size(); i++){
            if (i != 0) {
                out << ",";
            }
            out << predicates.at(i).toString();
        }
        out << "." << endl;
        return out.str();
    }
};

#endif //INC_236LAB1_RULE_H
