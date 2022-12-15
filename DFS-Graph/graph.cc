/* 	Cesar Caballero
	z1944013	
	CS340 - 2
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include "graph.h"
#include <fstream>
#include<iostream>
#include<string>

std::vector<bool> visited; //keep track of what has been visited
std::vector<std::pair<int,int>> edges;//store the edges of traversal
std::vector<int> path; //store path taken for traversal
int previousNode;// keep track of previous node

void Graph::Depthfirst(int v) 
{
    //current node visited
    visited[v] = true; 
    if(previousNode != v)
    {
        edges.push_back(std::make_pair(previousNode,v));
    }

    path.push_back(v); //store path taken for traversal

    //process all adjacent vertices recursively
    std::list<int>::iterator i;
    for(i = adj_list[v].begin(); i != adj_list[v].end(); ++i)
    {
        if(!visited[*i])
        {
            previousNode = v;
            Depthfirst(*i);
        }
    }
}

Graph::Graph(const char* filename)
{
    //open file with ifstream
    std::ifstream input;
    input.open(filename);

    //collect size of input
    input >> size;

    for(int i = 0; i<size; i++)
    {
        char l;
        input >> l;
        labels.push_back(l); //store labels
    }

    while(!input.eof())//read while the end of file is not reached
    {
        //store edges
        char l;
        input >> l;
        std::list<int> vals;
        int check;

        for(int i=0; i<size; i++)
        {
            input >> check;
            if(check == 1)
            {
                vals.push_back(i);
            }
        }
        adj_list.push_back(vals);
    } 
    input.close();      
}

//destructor
Graph::~Graph()
{

}

//return size of graph
int Graph::Getsize() const 
{ 
    return size;
}

void Graph::Traverse() 
{
    visited.clear();//reset visited vector
    std::cout << "------- traverse of graph ------" << std::endl;
    
    for(int i=0; i<size; i++)
    {
        visited.push_back(false); //none of the first vertices are visited
    }

    //recursively check each node 
    for(int i=0; i<size; i++)
    {
        if(!visited[i])
        {
            previousNode = i;
            Depthfirst(i);
        }
    }

    // print the path of dfs
    for(auto i:path)
    {
        std::cout << labels[i] << " " ; 
    }
    std::cout << std::endl;

    //print edges of dfs
    for(auto i:edges)
    {
        std::cout << "(" << labels[i.first] << ", " << labels[i.second] << ") ";
    }
    std::cout << std::endl;
    std::cout << "--------- end of traverse -------" << std::endl;
  
}

//print original graph without dfs traversal
void Graph::Print() const 
{
    int i = 0;
    std::cout << std::endl;
    std::cout << "Number of vertices in the graph: " << Getsize() << std::endl << std::endl;
    std::cout << "-------- graph -------" << std::endl;

    //print out adj_list
    for(std::list<int> l : adj_list)
    {
        bool first = true; //to not have comma at last element

        std::cout << (char) ('A' + i++) << ": ";//print out first letters from the input
        for(int c : l)
        {
            //allow last element to not have a comma at the end
            if(first)
            {
                first = false;
            }
            else std::cout << ", ";
            
            std::cout << labels[c]; //print out said labels from input
            
        }
        std::cout << std::endl;
    }    
   
    std::cout << "------- end of graph ------" << std::endl << std::endl;
}