//
// Created by Jaclyn Palmer on 3/28/22.
//

#ifndef INC_236PROJECT3_GRAPH_H
#define INC_236PROJECT3_GRAPH_H
#include "Node.h"
#include <stack>
#include <set>

class Graph {

private:

    map<int,Node> nodes;

    stack<unsigned int> workingStack;

    //which node have been marked or visited (use a set or vector)
    map<int, bool> visitedNodes;
    map<int, bool> visitedSCC;

public:

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }
    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }
    string toString(){
        stringstream out;
        for (auto& pair: nodes) {
            int nodeID = pair.first;
            out << "R" << nodeID << ":" << pair.second.toString();
        }
        out << endl;
        return out.str();
    }

    stack<unsigned int> DFS(unsigned int startNode){
        //check if start node has been visited
        //if it was, return an empty stack
        if (visitedNodes[startNode] == true){
            return workingStack;
        }

        //mark start has visited
        visitedNodes[startNode] = true;
        //for (child : nodes.at(startNode)):
        for (auto childID: nodes.at(startNode).getAdjacentNodeIDs()){
            //if child has not been visited
            if (visitedNodes[childID] == false){
                //call DFS(child)
                //add results of DFS to working stack
                DFS(childID);
                //is this an ok way to add DFS to working stack? Or do i need to push individual elements onto it
            }
        }
        //add the start node to the working stack
        workingStack.push(startNode);
        return workingStack;
    }
    stack<unsigned int> DFSF(){
        clearWorkingStack();
        for (unsigned int i = 0; i < nodes.size(); i++){
            //if current node i has not been marked call DFS
            if (visitedNodes[i] != true){
                DFS(i);
            }
        }

        return workingStack;
    }

    void clearWorkingStack() {
        stack<unsigned int> newStack;
        workingStack = newStack;
    }
    bool isSelfDependent(unsigned int nodeID) {
        if(nodes.at(nodeID).getAdjacentNodeIDs().count(nodeID) > 0) {
            return true;
        }
        return false;
    }

    //DFS the calls on the forward graphs
    void DFS_SCC(unsigned int startNode){
        //check if start node has been visited
        //if it was, return
        if(visitedSCC[startNode] == true){
            return;
        }
        visitedSCC[startNode] = true;
        //for (child : nodes.at(startNode)):
        //if child has not been visited
        // call tempResult = DFS(child)
        //add everything in tempResult into result
        for (auto childID : nodes.at(startNode).getAdjacentNodeIDs()){
            if (!visitedSCC[childID]){
                DFS_SCC(childID);
            }
        }
        //add the start node to the working stack
        workingStack.push(startNode);
        return;
    }
    vector<set<unsigned int>> DFSF_SCC(stack<unsigned int>postOrder){
        vector<set<unsigned int>>SCCs;
        while (postOrder.empty() != true){
            unsigned int startID = postOrder.top();
            postOrder.pop();
            //if current node i has not been marked
            if (visitedSCC[startID] == false){
                clearWorkingStack();
                // call DFS_SCC(i)
                //append the set returned bu called DFS onto your SCCs vector
                DFS_SCC(startID);
                //create set from working stack
                set<unsigned int> dfsSet;
                while(!workingStack.empty()) {
                    dfsSet.insert(workingStack.top());
                    workingStack.pop();
                }

                SCCs.push_back(dfsSet);
                //append the set returned bu called DFS onto your SCCs vector
            }

        }

        return SCCs;
    }
};

#endif //INC_236PROJECT3_GRAPH_H
