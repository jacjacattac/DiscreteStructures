//
// Created by Jaclyn Palmer on 3/7/22.
//

#ifndef INC_236LAB1_DATABASE_H
#define INC_236LAB1_DATABASE_H

#include "Relation.h"
#include <map>

class Database {
private:
    map<string, Relation> relations;

public:
    string toString() {
        stringstream out;
        for (auto pairP : relations) {
            out << pairP.first << endl;
            out << pairP.second.toString() << endl;
        }
        return out.str();
    }

    void insert(Relation r){
        relations.insert({r.getName(), r});
    }

    Relation getRelationCopy(string name){
        return relations.at(name);
    }
    Relation& getRelationReference(string name){
        return relations.at(name);
    }
    unsigned int size(){
        unsigned int count = 0;
        for (auto pairP : relations){
            count += pairP.second.size();
        }
        return count;
    }

};

#endif //INC_236LAB1_DATABASE_H
