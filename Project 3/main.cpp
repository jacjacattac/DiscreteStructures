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

using namespace std;

int main(int argc, char** argv) {
    string wholeFile;
    ifstream file;
    if(argc == 2) {
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

    }

    return 0;
}
