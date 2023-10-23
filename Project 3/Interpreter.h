//
// Created by Jaclyn Palmer on 3/7/22.
//

#ifndef INC_236LAB1_INTERPRETER_H
#define INC_236LAB1_INTERPRETER_H
#include "Database.h"
#include "DatalogProgram.h"

class Interpreter{
private:
    DatalogProgram program;
    Database database;

public:
    Interpreter(DatalogProgram program) : program(program) {}

    void run(){
        evalSchemes();
        evalFacts();
        evalQueries();
        //cout << database.toString();
    }
    void evalSchemes(){
        for (Predicate p : program.getSchemes()){
            Relation newRelation;
            vector<string> contents;
            for (Parameter param : p.getParameters()){
                contents.push_back(param.getData());
            }
            newRelation.setScheme(Scheme(contents)); // new scheme object putting put into relation
            newRelation.setName(p.getName());// setting the name of the relation
            database.insert(newRelation); // inserting the new relation into the database
        }
    }
    void evalFacts(){
        for (Predicate p : program.getFacts()){
            Relation& r = database.getRelationReference(p.getName()); // relation r = newRelation
            vector<string> contents; //getting contents of the relation(the parameters)
            for (Parameter param : p.getParameters()){ // dont totally understand this for loop
                contents.push_back(param.getData());
            }
            r.addTuple(Tuple(contents)); // adding a tuple of those parameters
        }
    }
    void evalQueries(){
        for (Predicate p : program.getQueries()){
            Relation r = evalPredicate(p); //evaluating the predicates of each query

            cout << p.toString() << "? " << r.toString(); //outputting the answers to the queries (i think)
        }
    }
    Relation evalPredicate(Predicate predicate){
        // This function is evaluating individual queries
        Relation currRel = database.getRelationCopy(predicate.getName()); //grabs relation by its name ??
        //Does this mean its grabbing the fact thats being evaluated? Or its grabbing the query?
        //i think its grabbing the query
        vector<unsigned int> colsToKeep;
        vector<string> names;

        // checking all the parameters in the query
        for(size_t i = 0; i < predicate.getParameters().size(); i++){
            Parameter currParam = predicate.getParameters().at(i);
            //checking if the current param is constant
            //why?
            if(currParam.isConst()){
                //WHAT DOES THIS SELECT DO?????
                currRel = currRel.select(i, currParam.toString());
            }
            else {
                bool seenBefore = false;
                int j = 0;
                //loop that checks through names. if currParam is found set, seenBefore to true
                for(size_t k = 0; k < names.size(); k++) {
                    if (names.at(k) == currParam.toString()) {
                        seenBefore = true;
                        j = k;
                        break;
                    }
                }
                if (seenBefore){
                    currRel = currRel.select(i, colsToKeep.at(j));
                }
                else {
                    colsToKeep.push_back(i);
                    names.push_back(currParam.toString());
                }
            }
        }
        currRel = currRel.project(colsToKeep);
        currRel = currRel.rename(names);
        return currRel;
    }
};

#endif //INC_236LAB1_INTERPRETER_H
