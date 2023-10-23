//
// Created by Jaclyn Palmer on 3/1/22.
//

#ifndef INC_236LAB1_RELATION_H
#define INC_236LAB1_RELATION_H

#include <iostream>
#include <string>
#include <vector>
#include "Scheme.h"
#include <sstream>
#include "Tuple.h"
#include <set>

using namespace std;

class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(const string& name, const Scheme& scheme) : name(name), scheme(scheme){}

    Relation(){}

    string toString() const {
        stringstream out;
        //out << "Tuples size " << tuples.size() << endl;
        if(tuples.empty()) {
            out << "No" << endl;
        } else {
            out << "Yes(" << tuples.size() << ")" << endl;
            if(scheme.size() > 0) {
                for (auto &tuple : tuples) {
                    out << tuple.toString(scheme) << endl;
                }
            }
        }

        return out.str();
    }

    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples)
            if (tuple.at(index) == value)
                result.addTuple(tuple);
        return result;
    }

    Relation select(unsigned int index1, unsigned int index2) {
        Relation result(name, scheme);
        for (auto& tuple : tuples)
            if (tuple.at(index1) == tuple.at(index2))
                result.addTuple(tuple);
        return result;
    }

    Relation project(vector<unsigned int> colsToKeep){
        //make new relation

        vector<string> newScheme;
        for(size_t i = 0; i < colsToKeep.size(); i++) {
            newScheme.push_back(scheme.at(colsToKeep.at(i)));
        }

        Relation result(name, newScheme);

        set<Tuple>::iterator it = tuples.begin();

        while (it != tuples.end()){
            vector<string> newTuple;
            for(size_t i = 0; i < colsToKeep.size(); i++) {
                newTuple.push_back((*it).at(colsToKeep.at(i)));
            }
            result.addTuple(newTuple);
            it++;
        }

        return result;
    }

    Relation rename(vector<string> newNames){
        setScheme(newNames);
        return *this;
    }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }
    string getName(){
        return name;
    }
    unsigned int size(){
        return tuples.size();
    }
    void setScheme(Scheme contents){
        scheme = contents;
    }
    void setName(string newName){
        name = newName;
    }
};

#endif //INC_236LAB1_RELATION_H
