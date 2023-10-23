//
// Created by Jaclyn Palmer on 1/28/22.
//

#ifndef UNTITLED26_PARSER_H
#define UNTITLED26_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
#include "DatalogProgram.h"

using namespace std;

class Parser {
private:
    vector<Token> tokens;

    string match(TokenType t) {
        if (tokenType() == t) {
            string returnVal = tokens.at(0).getValue();
            advanceToken();
            return returnVal;
        } else {
            throw tokens.at(0);
            return "";
        }
    }

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) { }

    DatalogProgram datalog;

    TokenType tokenType() {
        return tokens.at(0).getType();
    }
    void advanceToken() {
        tokens.erase(tokens.begin());
    }

    void parseDatalogProgram() {
        advanceToken();
        try {
            match(SCHEMES);
            match(COLON);
            datalog.addScheme(parseScheme());
            parseSchemeList();
            match(FACTS);
            match(COLON);
            parseFactsList();
            match(RULES);
            match(COLON);
            parseRulesList();
            match(QUERIES);
            match(COLON);
            parseQuery();
            parseQueriesList();
            match(END_OF_FILE);
        }
        catch(Token t){
            cout << "Failure!" << endl;
            cout << "  " << tokens.at(0).toString() << endl;
            return;
        }
        datalog.findDomain();
        //cout << datalog.datalogToString();
        return;
    }

    void parseIdList(Predicate &p) {
        if (tokenType() == COMMA) {
            match(COMMA);
            p.addValue((match(ID)));
            parseIdList(p);
        } else {
            return;
        }
    }
    //return predicate instead of void
    Predicate parseScheme() {
        //scheme -> ID LEFT PAREN ID isList RIGHT PAREN
        if (tokenType() == ID) {
            Predicate p(match(ID));
            match(LEFT_PAREN);
            p.addValue(match(ID));
            parseIdList(p);
            match(RIGHT_PAREN);
            return p;
        } else {
            throw(tokens.at(0));
        }
    }
    void parseSchemeList(){
        // schemeList -> scheme schemeList | lambda
        if(tokenType() == ID) {
            datalog.addScheme(parseScheme());
            parseSchemeList();
        }
        return;
    }
    void parseFactsList() {
        if (tokenType() == ID) {
            parseFact();
            parseFactsList();
        }
        return;
    }
    void parseFact(){
        // fact -> ID LEFT_PAREN STRING stringList RIGHT PAREN PERIOD
        if (tokenType() == ID) {
            Predicate p(match(ID));
            match(LEFT_PAREN);
            p.addValue(match(STRING));
            parseStringList(p);
            match(RIGHT_PAREN);
            match(PERIOD);
            datalog.addFact(p);
        } else {
            return;
        }
    }
    void parseStringList(Predicate& p){
        // stringList -> COMMA STRING stringList | lambda
        if (tokenType() == COMMA) {
            match(COMMA);
            p.addValue(match(STRING));
            parseStringList(p);
        } else {
            return;
        }
    }
    void parseRule(){
        // rule -> headPredicate COLON_DASH predicate predicateList PERIOD

        // first, parse headPredicate. HeadPredicate looks exactly like a scheme
        // Predicate headPredicate = parseScheme();
        Rule r = Rule(parseScheme());
        match(COLON_DASH);
        r.addPredicate(parsePredicate());
        parsePredicateList(r);
        match(PERIOD);
        datalog.addRule(r);
        return;
    }
    void parseRulesList(){
        //parseRulesList -> rule ruleList | lambda
        if(tokenType() == ID) {
            parseRule();
            parseRulesList();
        }else {
            return;
        }
    }
    void parseQuery(){
        // query -> predicate Q_MARK
        datalog.addQuery(parsePredicate());
        match(Q_MARK);
    }
    void parseQueriesList(){
        // queriesList -> query queryList | lambda
        if(tokenType() == ID){
            parseQuery();
            parseQueriesList();
        }
        return;
    }
    Predicate parsePredicate(){
        // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
        if(tokenType() == ID) {
            Predicate p(match(ID));
            match(LEFT_PAREN);
            if(tokenType() == ID || tokenType() == STRING) {
                p.addValue(tokens.at(0).getValue());
                advanceToken();
                parseParameterList(p);
                match(RIGHT_PAREN);
                return p;
            }
            else{
                throw(tokens.at(0));
            }
        }else {
            throw(tokens.at(0));
        }
    }
    void parsePredicateList(Rule& r){
        //predicateList -> COMMA predicate predicateList | lambda
        if(tokenType() == COMMA){
            match(COMMA);
            r.addPredicate(parsePredicate());
            parsePredicateList(r);
        }
        else{
            return;
        }
    }
    void parseParameterList(Predicate &p){
        // parameterList -> COMMA parameter parameterList | lambda
        if (tokenType() == COMMA){
            match(COMMA); // this will iterate it to the predicate
            if(tokenType() == ID || tokenType() == STRING) {
                p.addValue(tokens.at(0).getValue());
                advanceToken();
                parseParameterList(p);
            } else {
                throw(tokens.at(0));
            }
        }
    }

};

#endif //UNTITLED26_PARSER_H
