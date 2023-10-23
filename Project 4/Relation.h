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


    Relation natJoin(Relation r1, Relation r2){
       // cout << "In natural join function" << endl;
        Relation output;
        output.setName(r1.getName() + "+" + r2.getName());
        vector<pair<unsigned int, unsigned int>> overlap; // could be a map
        vector<unsigned int> uniqueColumns;

        for (unsigned int i = 0; i < r2.getScheme().size(); i++){
            bool isUnique = true;
            for (unsigned int j = 0; j < r1.getScheme().size(); j++){
                if (r2.getScheme().at(i) == r1.getScheme().at(j)){
                    overlap.push_back({j,i});
                    isUnique = false;
                }
            }
            if (isUnique){
                uniqueColumns.push_back(i);
            }
        }
        output.setScheme(combineSchemes(r1.getScheme(), r2.getScheme(), uniqueColumns));

        for (Tuple t1 : r1.getTuples()) {
            for (Tuple t2 : r2.getTuples()){
                if (canJoin(t1, t2, overlap)){
                    output.addTuple(combineTuples(t1, t2, uniqueColumns));
                }
            }
        }
        return output;
    }

    Scheme combineSchemes(Scheme& s1, Scheme& s2, vector<unsigned int>& uniqueColumns){
       // cout << "in combine schemes" << endl;
        Scheme output;
        for(unsigned int i = 0; i < s1.size(); i++){
            output.push_back(s1.at(i));
        }
        for (unsigned int i = 0; i < uniqueColumns.size(); i++){
            output.push_back(s2.at(uniqueColumns.at(i)));
        }
        return output;
    }

    bool canJoin(Tuple& t1, Tuple& t2, vector<pair<unsigned int, unsigned int>> &overlap){
        for (pair<unsigned int, unsigned int> p : overlap){
            if (t1.at(p.first) != t2.at(p.second)){
                return false;
            }
        }
        return true;
    }
    Tuple combineTuples(Tuple& t1, Tuple & t2, vector<unsigned int>&uniqueColumns){
        vector<string>values;
        for (unsigned int i = 0; i < t1.size(); i++){
            values.push_back(t1.at(i));
        }
        for (unsigned int i = 0; i < uniqueColumns.size(); i++){
            values.push_back(t2.at(uniqueColumns.at(i)));
        }
        Tuple newTuple(values);
        //cout << "leaving combine tuples" << endl;
      return newTuple;
    }

    void unionize(Relation toAdd){
        //cout << "In the unionize function" << endl;
        if (this->scheme != toAdd.getScheme()){
            throw "cannot combine bc the schemes are different";
        }
        for (Tuple tuple : toAdd.getTuples()){
            if(addTuple(tuple)) {
                if (tuple.size() > 0) {
                    cout << tuple.toString(scheme) << endl;
                }
            }
        }
        //cout << "leaving the unionize function" << endl;
    }


    Relation rename(vector<string> newNames){
        setScheme(newNames);
        return *this;
    }

    bool addTuple(const Tuple& tuple) {
        return tuples.insert(tuple).second;
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
    Scheme &getScheme(){
        return scheme;
    }
    set<Tuple> getTuples(){
        return tuples;
    }
};

#endif //INC_236LAB1_RELATION_H
