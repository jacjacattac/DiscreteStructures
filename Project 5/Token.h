//
// Created by Jaclyn Palmer on 1/13/22.
//

#ifndef INC_236LAB1_TOKEN_H
#define INC_236LAB1_TOKEN_H
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum TokenType {
    COMMA, ID, STRING, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN,
    COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES,
    COMMENT, UNDEFINED, END_OF_FILE
};


class Token {
private:
    TokenType type;
    string value;
    int line;

public:
    Token(TokenType type, string value, int line)
        : type(type), value(value), line(line) { }

        string toString(){
        stringstream out;
        out << "(" << typeName(type) << ",\"" << value << "\"," << line << ")";
        return out.str();
    }
    string getValue(){
        return value;
    }
    string typeName(TokenType type) const {
        switch (type) {
            case COMMA:
                return "COMMA";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case COMMENT:
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case END_OF_FILE:
                return "EOF";
        }
        return "Didn't match a case";
    }
    TokenType getType(){
        return type;
    }
};
#endif //INC_236LAB1_TOKEN_H
