#pragma once
#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__
#include <iostream>
#include <string>
using namespace std;

enum RedBlackTreeColor { Black = 0, Red = 1 };

class RedBlackTreeNode {
	int64_t key;
	int recordNumber;
	RedBlackTreeNode* parent;
	RedBlackTreeNode* left = nullptr;
	RedBlackTreeNode* right = nullptr;
	RedBlackTreeColor color;
public:
	void invertSelf();

	RedBlackTreeNode(RedBlackTreeNode* parent, int64_t key, int recordNumber, RedBlackTreeColor color);
	
	void clearParent(); //sets parent to nullptr
	void setLeft(RedBlackTreeNode* left);
	void setRight(RedBlackTreeNode* right);
	void setColor(RedBlackTreeColor color);
	void setKey(int64_t key);
	void setRN(int RN);

	RedBlackTreeNode* getLeft();
	RedBlackTreeNode* getRight();
	RedBlackTreeNode* getParent();
	RedBlackTreeColor getColor();
	int64_t getKey();
	int getRN();

	void show(int level = 0);

	~RedBlackTreeNode();
};

class RedBlackTree {
	RedBlackTreeNode* root;

	void leftRotate(RedBlackTreeNode* pivot);
	void rightRotate(RedBlackTreeNode* pivot);

	void checkAddConditions(RedBlackTreeNode* startNode);
	void checkRemoveConditions(RedBlackTreeNode* startNode, bool deletedIsLeft);
	void checkRoot();

	int rotations = 0;
	int nodes = 0;
public:
	RedBlackTree(RedBlackTreeNode* root);
	void addElement(int64_t key, int RN);
	void removeElement(int64_t key);
	int findElement(int64_t key);
	void showTree();
	~RedBlackTree();
};
#endif