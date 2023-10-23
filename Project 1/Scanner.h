//
// Created by Jaclyn Palmer on 1/14/22.
//

#ifndef INC_236LAB1_SCANNER_H
#define INC_236LAB1_SCANNER_H
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "Token.h"

using namespace std;

class Scanner {
private:
    string input;
    size_t index;
    string value;
    char ch;
    int line;
    vector<Token>tokenList;
public:
    Scanner(const string& input) : input(input) {
        line = 1;
        index = 0;
    }

    void scan() {
        while (index < input.length()){
            ch = input.at(index);

            switch (ch) {
                case '\n':
                    line++;
                    break;
                case '\'':
                    stringScan(input);
                    break;
                case ':':
                    colonScan(input);
                    break;
                case '#':
                    commentScan(input);
                    break;
                default:
                    if(isalpha(ch)){
                        keywordScanner(input);
                        break;
                    } else if (isspace(ch)){
                        break;
                    }else {
                        singleCharReader(input);
                        break;
                    }
            }

            index++;
        }
        // EOF; make EOF token
        Token token(END_OF_FILE, "", line);
        tokenList.push_back(token);
    }

    void colonScan(string input){
        if (index+1 < input.length() && input.at(index+1) == '-') {
            Token token(COLON_DASH, ":-", line);
            tokenList.push_back(token);
            index++;
            return;
        }
        else {
            Token token(COLON, ":", line);
            tokenList.push_back(token);
            return;
        }
    }

    void stringScan(string input){
        int startLine = line;
        value = "\'";
        index++;
        while(index < input.length()){
            ch = input.at(index);
            value += ch;
            if (ch == '\''){
                Token token(STRING, value, startLine);
                tokenList.push_back(token);
                return;
            }
            else if (ch == '\n'){
                line++;
            }
            index++;
        }
        Token token(UNDEFINED, value, startLine);
        tokenList.push_back(token);
        return;
    }

    void commentScan(string input){
        int startLine;
        value = '#';
        index++;
        startLine = line;
        if (input.at(index) != '|'){
            while(index < input.length()){
                ch = input.at(index);
                if (ch == '\n'){
                    Token token(COMMENT, value, line);
                    tokenList.push_back(token);
                    line++;
                    return;
                }
                value += ch;
                index++;
            }
        }
        else{
            while(index < input.length()){
                ch = input.at(index);
                value += ch;
                if(index+1 < input.length() && ch == '|' && input.at(index +1) == '#'){
                    value += "#";
                    index++;
                   Token token(COMMENT, value, startLine);
                   tokenList.push_back(token);
                   return;
                } else if (ch == '\n'){
                    line++;
                }
                index++;
            }
        }
        Token token(UNDEFINED, value, startLine);
        tokenList.push_back(token);
        return;
    }

    void singleCharReader(string input){
        TokenType type;
        string value;
        switch (ch) {
            case ',':
                type = COMMA;
                break;
            case '.':
                type = PERIOD;
                break;
            case '?':
                type = Q_MARK;
                break;
            case '(':
                type = LEFT_PAREN;
                break;
            case ')':
                type = RIGHT_PAREN;
                break;
            case '*':
                type = MULTIPLY;
                break;
            case '+':
                type = ADD;
                break;
            default:
                type = UNDEFINED;
                break;
        }
        value = ch;
        Token token(type, value, line);
        tokenList.push_back(token);
    }
    void keywordScanner(string input) {
        value = ch;
        index++;
        while (index < input.length()) {
            ch = input.at(index);
            if (isalnum(ch)) {
                value += ch;
                index++;
            } else {
                index--;
                break;
            }
        }
        if (value == "Facts") {
            Token token(FACTS, value, line);
            tokenList.push_back(token);
            return;
        } else if (value == "Schemes") {
            Token token(SCHEMES, value, line);
            tokenList.push_back(token);
            return;
        } else if (value == "Rules") {
            Token token(RULES, value, line);
            tokenList.push_back(token);
            return;
        } else if (value == "Queries") {
            Token token(QUERIES, value, line);
            tokenList.push_back(token);
            return;
        } else {
            Token token(ID, value, line);
            tokenList.push_back(token);
            return;
        }
    }
    void printTokens(){
        for(size_t i = 0; i < tokenList.size(); i++){
            cout << tokenList.at(i).toString() << endl;
        }
        cout << "Total Tokens = " << tokenList.size() << endl;
    }

};

#endif //INC_236LAB1_SCANNER_H
