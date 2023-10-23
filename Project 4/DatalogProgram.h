//
// Created by Jaclyn Palmer on 2/5/22.
//

#ifndef INC_236LAB1_DATALOGPROGRAM_H
#define INC_236LAB1_DATALOGPROGRAM_H

#include <iostream>
#include <vector>
#include <set>

#include "Predicate.h"
#include "Rule.h"

using namespace std;

//This class is where I will store the data structures produced by the Parser

class DatalogProgram{
public:
    vector<Predicate>schemes;
    vector<Predicate>facts;
    vector<Rule>rules;
    vector<Predicate>queries;
    set<string>domain;

    string datalogToString(){
        stringstream out;
        out << "Success!" << endl;
        out << "Schemes(" << schemes.size() << "):" << endl;
        for(size_t i = 0; i < schemes.size(); i++){
            out << "  " << schemes.at(i).toString() << endl;
        }
        out << "Facts(" << facts.size() << "):" << endl;
        for (size_t i = 0; i < facts.size(); i++){
            out << "  " << facts.at(i).toString() << "." << endl;
        }
        out << "Rules(" << rules.size() << "):" << endl;
        for (size_t i = 0; i < rules.size(); i++){
            out << "  " << rules.at(i).ruleToString();
        }
        out << "Queries(" << queries.size() << "):" << endl;
        for (size_t i = 0; i < queries.size(); i++){
            out << "  " << queries.at(i).toString() << "?" << endl;
        }
        out << "Domain(" << domain.size() << "):" << endl;
        for(string s : domain) {
            out << "  " << s << endl;
        }
        return out.str();
    }
    void addScheme(Predicate p){
        schemes.push_back(p);
    }
    void addFact(Predicate p){
        facts.push_back(p);
    }
    void addRule(Rule r){
        rules.push_back(r);
    }
    void addQuery(Predicate p){
        queries.push_back(p);
    }
    void findDomain(){
        // all strings in Fact objects go in one list, unique and alphabetically sorted.
        for(size_t i = 0; i < facts.size(); i++){
            for (size_t j = 0; j < facts.at(i).parameters.size(); j++){
                domain.insert(facts.at(i).parameters.at(j).getData());
            }
        }
    }
    vector <Predicate> getSchemes(){
        return schemes;
    }
    vector <Predicate> getFacts(){
        return facts;
    }
    vector<Predicate> getQueries(){
        return queries;
    }
    vector<Rule> getRules(){
        return rules;
    }

};

#endif //INC_236LAB1_DATALOGPROGRAM_H
