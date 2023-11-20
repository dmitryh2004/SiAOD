#pragma once
#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Graph {
	bool isDirected = false;
	int size;
	int** matrix;
	vector<string> names;
public:
	//common methods
	Graph(bool isDirected, int size, vector<string> names);
	~Graph();
	void show();
	bool addPath(int verticeA, int verticeB, int weight);
	bool addPath(string nameA, string nameB, int weight);
	bool removePath(int verticeA, int verticeB);
	bool removePath(string nameA, string nameB);

	//find all chains
	void showChainsFromVertice(int verticeIndex, string currentChain);
	void showAllChains();

	//shortest path
	void getAllChains(int verticeIndex, string currentChain, int currentLength, vector<string>& output, vector<int>& lengthOutput);
	int getShortestPath(int verticeA, int verticeB);
	int getShortestPath(string verticeA, string verticeB);
};

#endif