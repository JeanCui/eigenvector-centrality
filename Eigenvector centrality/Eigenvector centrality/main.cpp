//
//  main.cpp
//  Eigenvector centrality
//
//  Created by JinCui on 3/13/14.
//  Copyright (c) 2014 JinCui. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <assert.h>
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
    
    while (infile >> a >> b) {
        Node *toNode = new Node();
        toNode->data = b;
        toNode->next = NULL;
        Node *tail = adjList[a].next;
        if(!tail)
        {
            adjList[a].next = toNode;
        }else
        {
            while (tail->next) {
                tail = tail->next;
            }
            tail->next = toNode;
        }
        
    }
    
    infile.close();
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

void eigenvectorCentrality(Node *adjList, float *centrality)
{
    // init centrality vector
    int i;
    int j;
    int k;
    unsigned int temp[NodeNum];
    for (i=0; i < NodeNum; ++i) {
        temp[i] = 1;
    }
    
    for (i = 0; i < Iteration; ++i) {
        unsigned int w[NodeNum] = {0};
        for (j = 0; j < NodeNum; ++j) {
            Node *p = adjList[j].next;
            while (p) {
                assert(p->data >= 0 && p->data < NodeNum);
                w[p->data] = w[p->data] + temp[j];
                p = p->next;
            }
        }
        // set temp = w
        for (k = 0; k < NodeNum; ++k) {
            temp[k] = w[k];
        }
    }
    
    unsigned int sum = 0;
    for (i = 0; i < NodeNum; ++i) {
        sum += temp[i];
    }
    assert(sum != 0);
    for (i = 0; i < NodeNum; ++i) {
        centrality[i] = (float)temp[i]/(float)sum;
    }
}

// free memory
// avoid memory leak
void freelist(Node *adjList)
{
    int i;
    for (i = 0; i < NodeNum; ++i) {
        Node *node = adjList[i].next;
        Node *p;
        if(node != NULL)
        {
            p = node->next;
            delete node;
            node = p;
        }
    }
}
int main(int argc, const char * argv[])
{
    //makeNodeStartFromZero("inputtest.txt", "outputtest.txt");
    Node adjList[NodeNum];
    float centrality[NodeNum];
    int i;
    for (i = 0; i < NodeNum; ++i) {
        adjList[i].data = i;
        adjList[i].next = NULL;
    }
    convert2AdjList(adjList, "outputtest.txt");
    eigenvectorCentrality(adjList, centrality);
#ifdef DEBUG
    for (i = 0; i < NodeNum; ++i) {
        cout << centrality[i] << "\n";
    }
#endif
    freelist(adjList);
    return 0;
}

