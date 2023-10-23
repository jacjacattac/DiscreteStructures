//
// Created by Jaclyn Palmer on 3/28/22.
//

#ifndef INC_236PROJECT3_NODE_H
#define INC_236PROJECT3_NODE_H
#include "Rule.h"
#include "Relation.h"
#include "Interpreter.h"

class Node {

private:
    //int nodeID;
    set<unsigned int> adjacentNodeIDs;

public:
    //Node(int nodeId) : nodeID(nodeId) {}

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }
    bool contains(int nodeID){
        return (adjacentNodeIDs.find(nodeID) != adjacentNodeIDs.end());
    }
    const set<unsigned int> &getAdjacentNodeIDs() const{
        return adjacentNodeIDs;
    }
    void setAdjacentNodeIDs(const set<unsigned int> &adjacentNodeIDs){
        Node::adjacentNodeIDs = adjacentNodeIDs;
    }

    string toString() {
        stringstream out;
        size_t i = 0;
        for (auto& nodeID : adjacentNodeIDs) {
            i++;
            out << "R" << nodeID;
            if (i != adjacentNodeIDs.size()){
                out << ",";
            }
        }
        out << endl;
        return out.str();
    }

};
#endif //INC_236PROJECT3_NODE_H
