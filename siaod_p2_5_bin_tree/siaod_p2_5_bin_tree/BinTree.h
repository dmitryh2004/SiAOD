#pragma once
#ifndef __BIN_TREE_H__
#define __BIN_TREE_H__
#include <iostream>
#include <string>

using namespace std;

class BinTreeNode {
	int64_t key;
	int recordNumber = -1;
	BinTreeNode* parent = nullptr;
	BinTreeNode* left = nullptr;
	BinTreeNode* right = nullptr;
public:
	BinTreeNode(BinTreeNode* parent, int64_t key, int recordNumber);
	int64_t getKey();
	int getRecordNumber();
	BinTreeNode* getParent();
	BinTreeNode* getLeft();
	BinTreeNode* getRight();
	void setKey(int64_t key);
	void setRecordNumber(int recordNumber);
	void setParent(BinTreeNode* parent);
	void setLeft(BinTreeNode* left);
	void setRight(BinTreeNode* right);
	void show(int level = 0);
	~BinTreeNode();
};

class BinTree {
	BinTreeNode* root = nullptr;
public:
	BinTree(int64_t startValue, int startRN);
	void addElement(int64_t key, int RN);
	void removeElement(int64_t key);
	int findElement(int64_t key);
	void showTree();
	~BinTree();
};
#endif