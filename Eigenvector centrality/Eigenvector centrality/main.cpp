//
//  main.cpp
//  Eigenvector centrality
//
//  Created by JinCui on 3/13/14.
//  Copyright (c) 2014 JinCui. All rights reserved.
//

#include <iostream>
#include <fstream>
//#include <string.h>
#include <map>
#define NodeNum 34546
#define Iteration 100
using namespace std;

struct Node{
    int data;
    Node *next;
    //int centrality;
};

void convert2AdjList(Node *adjList, char *filename)
{
    ifstream infile(filename);
    
    int a, b;
    
    
}

void makeNodeStartFromZero(char *inputname, char *outputname)
{
    int incre = 0;
    ifstream infile(inputname);
    ofstream outfile;
    outfile.open(outputname, ios::out | ios::app);
    int a, b;
    map<int, int> nodeHash;
    
    while (infile >> a >> b) {
        // read
        if(nodeHash.find(a) == nodeHash.end())
        {
            // not found
            nodeHash[a] = incre;
            incre++;
        }
        if(nodeHash.find(b) == nodeHash.end())
        {
            // not found
            nodeHash[b] = incre;
            incre++;
        }
        
        //write
        outfile << nodeHash[a] << "\t" << nodeHash[b] << "\n";
    }
    
    infile.close();
    outfile.close();
    
}

void eigenvectorCentrality(Node *adjList, int *centrality)
{
    // init centrality vector
//    int i;
//    int j;
//    for (i=0; i < NodeNum; ++i) {
//        centrality[i] = 1;
//    }
    
//    for (i = 0; i < Iteration; ++i) {
//        int w[NodeNum] = {0};
//        for (j = 0; j < NodeNum; ++j) {
//            Node *p = adjList[j].next;
//            while (p) {
//                w[] = adjList[j]
//            }
//            
//        }
//    }
}

int main(int argc, const char * argv[])
{
    //makeNodeStartFromZero("inputtest.txt", "outputtest.txt");
    return 0;
}

