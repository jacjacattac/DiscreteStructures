//
// Created by Jaclyn Palmer on 3/7/22.
//

#ifndef INC_236LAB1_INTERPRETER_H
#define INC_236LAB1_INTERPRETER_H
#include "Database.h"
#include "DatalogProgram.h"
#include "Graph.h"

class Interpreter{
private:
    DatalogProgram program;
    Database database;

public:
    Interpreter(DatalogProgram program) : program(program) {}

    void run(){
        evalSchemes();
        evalFacts();
        evalRules();
        cout << endl << "Query Evaluation" << endl;
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

    void evalRules() {
        //cout << "In evalRules function" << endl;
        //evalRuleListFixedPointAlg(program.getRules());
        Graph graph = makeGraph(program.getRules());
        Graph rGraph = makeReverseGraph(program.getRules());
        cout << "Dependency Graph" << endl;
        cout << graph.toString();
//        cout << "Reverse graph: " << endl;
//        cout << rGraph.toString() << endl;
        stack <unsigned int> postOrder = rGraph.DFSF();

        vector<set<unsigned int>> SCCs = graph.DFSF_SCC(postOrder);

        cout << "Rule Evaluation" << endl;

        for (unsigned int i = 0; i < SCCs.size(); i++) {
            cout << "SCC: ";
            vector<unsigned int> SCCIDs;
            vector<Rule> SCCRules;
            for (auto index : SCCs.at(i)) {
                SCCIDs.push_back(index);
                SCCRules.push_back(program.getRules().at(index));
            }
            printSCC(SCCIDs);
            cout << endl;

            //run the rules in the SCC
            //check for single, non-dependent SCCs
            if (SCCIDs.size() == 1) {
                if(!graph.isSelfDependent(SCCIDs.at(0))) {
                    evalRuleListOnce(SCCRules);
                    cout << "1 passes: ";
                    printSCC(SCCIDs);
                    cout << endl;
                    continue;
                }
            }

            evalRuleListFixedPointAlg(SCCRules);
            printSCC(SCCIDs);
            cout << endl;
        }

//        for(int i = 0; i < SCCs.size(); i++) {
//            cout << "SCC " << i << ": ";
//            for( auto item : SCCs.at(i)) {
//                cout << item << " ";
//            }
//            cout << endl;
//        }


    }
    void evalRuleListFixedPointAlg(vector<Rule> rules){
        //cout << "In fixed point algorithm" << endl;
        unsigned int sizeBefore = 0;
        unsigned int sizeAfter = 0;
        int numPasses = 0;
        do {
            numPasses++;
            sizeBefore = database.size();
            evalRuleListOnce(rules);
            sizeAfter = database.size();
        } while(sizeBefore != sizeAfter);
        cout << numPasses << " passes: ";
        //cout << endl << "Schemes populated after " << numPasses << " passes through the Rules." << endl << endl;
    }

    void evalRuleListOnce(vector<Rule>rules){ // once again where is this being used?
        //cout << "In evalRuleListOnce function" << endl;

        for (Rule currRule : rules) {
            cout << currRule.ruleToString() << "." << endl;
            vector<Relation> bodyRelations;
            for (Predicate currPredicate : currRule.getBody()){
                Relation currRelation = evalPredicate(currPredicate);
                bodyRelations.push_back(currRelation);
            }
            Relation resultRelation = bodyRelations.at(0);
            for(unsigned int i = 1; i < bodyRelations.size(); i++){
                resultRelation = resultRelation.natJoin(resultRelation, bodyRelations.at(i));
            }
            vector<unsigned int> colsToKeep;
            for (unsigned int i = 0; i < currRule.getHeadPredicate().getParameters().size(); i++){
                Parameter p = currRule.getHeadPredicate().getParameters().at(i);
                for (unsigned int j = 0; j < resultRelation.getScheme().size(); j++){
                    Parameter s = resultRelation.getScheme().at(j);
                    if (p.getData() == s.getData()){
                        colsToKeep.push_back(j);
                    }
                }
            }
            resultRelation = resultRelation.project(colsToKeep);
            string name = currRule.getHeadPredicate().getName();
            resultRelation = resultRelation.rename(database.getRelationReference(name).getScheme());
            database.getRelationReference(name).unionize(resultRelation);
        }
    }

    static Graph makeGraph(vector<Rule> rules) { //argument might need to be pass by reference
    Graph graph(rules.size());

        for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
            Rule fromRule = rules.at(fromID);
            //cout << "from rule R" << fromID << ": " << fromRule.ruleToString() << endl;
            for (int pred = 0; pred < fromRule.size(); pred++) {
                Predicate bodyPred = fromRule.getBody().at(pred);
                //cout << "from body predicate: " << bodyPred.toString() << endl;
                for (unsigned toID = 0; toID < rules.size(); toID++) {
                    Rule toRule = rules.at(toID);
                    //cout << "to rule R" << toID << ": " << toRule.ruleToString() << endl;
                    if (toRule.getHeadPredicate().getName() == bodyPred.getName()){
                        graph.addEdge(fromID, toID);
                        //cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                    }

                }
            }
        }
        return graph;
    }
    static Graph makeReverseGraph(vector<Rule> rules) { // argument might need to be pass by reference
        Graph reverseGraph(rules.size());

        for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
            Rule fromRule = rules.at(fromID);
            //cout << "from rule R" << fromID << ": " << fromRule.ruleToString() << endl;
            for (int pred = 0; pred < fromRule.size(); pred++) {
                Predicate bodyPred = fromRule.getBody().at(pred);
                //cout << "from body predicate: " << bodyPred.toString() << endl;
                for (unsigned toID = 0; toID < rules.size(); toID++) {
                    Rule toRule = rules.at(toID);
                    //cout << "to rule R" << toID << ": " << toRule.ruleToString() << endl;
                    if (toRule.getHeadPredicate().getName() == bodyPred.getName()){
                        reverseGraph.addEdge(toID, fromID);
                        //cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                    }

                }
            }
        }
        return reverseGraph;
    }

    void printSCC(vector<unsigned int> SCC) {
        for(unsigned int i = 0; i < SCC.size(); i++) {
            if(i != 0) {
                cout << ",";
            }
            cout << "R" << SCC.at(i);
        }
    }
};

#endif //INC_236LAB1_INTERPRETER_H
