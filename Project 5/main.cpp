#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

int main(int argc, char** argv) {
    string wholeFile;
    ifstream file;
    if (argc == 2) {
        file.open(argv[1]);
        if (file.is_open()) {
            stringstream ss;
            while (file.peek() != EOF) {
                ss << (char) file.get();
            }
            file.close();
            wholeFile = ss.str();
        }
        Scanner fileScanner = Scanner(wholeFile);
        fileScanner.scan();
        //fileScanner.printTokens();

        Parser parseFile = Parser(fileScanner.getTokens());
        parseFile.parseDatalogProgram();

        Interpreter interpreter = Interpreter(parseFile.datalog);
        interpreter.run();

//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "B" } },
//            { "B", { "B", "A" } },
//    };
//
//    vector<Rule> rules;
//
//    for (auto& rulePair : ruleNames) {
//        string headName = rulePair.first;
//        Rule rule = Rule(Predicate(headName));
//        vector<string> bodyNames = rulePair.second;
//        for (auto& bodyName : bodyNames)
//            rule.addPredicate(Predicate(bodyName));
//        rules.push_back(rule);
//    }
//
//    Graph graph1 = Interpreter::makeGraph(rules);
//    Graph graph2 = Interpreter::makeReverseGraph(rules);
//    cout << graph1.toString();
//    cout << graph2.toString();

        return 0;
    }
}
