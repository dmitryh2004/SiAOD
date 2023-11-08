#pragma once
#include "BinTree.h"

BinTreeNode::BinTreeNode(BinTreeNode* parent, int64_t key, int recordNumber) :
parent(parent), key(key), recordNumber(recordNumber)
{

}

int64_t BinTreeNode::getKey() {
	return this->key;
}

int BinTreeNode::getRecordNumber() {
	return this->recordNumber;
}

BinTreeNode* BinTreeNode::getParent() {
	return this->parent;
}

BinTreeNode* BinTreeNode::getLeft() {
	return this->left;
}

BinTreeNode* BinTreeNode::getRight() {
	return this->right;
}

void BinTreeNode::setKey(int64_t key)
{
	this->key = key;
}

void BinTreeNode::setRecordNumber(int recordNumber)
{
	this->recordNumber = recordNumber;
}

void BinTreeNode::setParent(BinTreeNode * parent)
{
	this->parent = parent;
}

void BinTreeNode::setLeft(BinTreeNode* left) {
	this->left = left;
	if (left)
		left->setParent(this);
}

void BinTreeNode::setRight(BinTreeNode* right) {
	this->right = right;
	if (right)
		right->setParent(this);
}

void BinTreeNode::show(int level) {
	if (this->right) {
		this->right->show(level + 1);
	}
	for (int i = 0; i < level; i++)
	{
		cout << "-----|";
	}
	cout << "< " << this->key << " >\n";
	if (this->left) {
		this->left->show(level + 1);
	}
}

BinTreeNode::~BinTreeNode() {
	if (this->left)
		delete this->left;
	if (this->right)
		delete this->right;
}

BinTree::BinTree(int64_t startValue, int startRN)
{
	this->root = new BinTreeNode(nullptr, startValue, startRN);
}

void BinTree::addElement(int64_t key, int RN)
{
	if (!findElement(key))
	{
		if (this->root == nullptr) {
			this->root = new BinTreeNode(nullptr, key, RN);
		}
		else {
			BinTreeNode* cur = this->root;
			while (cur)
			{
				if (key < cur->getKey())
				{
					if (cur->getLeft() == nullptr)
					{
						cur->setLeft(new BinTreeNode(cur, key, RN));
						break;
					}
					else {
						cur = cur->getLeft();
					}
				}
				else
				{
					if (cur->getRight() == nullptr)
					{
						cur->setRight(new BinTreeNode(cur, key, RN));
						break;
					}
					else {
						cur = cur->getRight();
					}
				}
			}
		}
	}
	else
	{
		cout << "Ёлемент с ключом " << key << " уже существует в дереве." << endl;
	}
}

void BinTree::removeElement(int64_t key)
{
	if (findElement(key))
	{
		BinTreeNode* cur = this->root;
		while (cur) {
			if (cur->getKey() == key)
			{
				BinTreeNode* par = cur->getParent();
				if (par) //если удал€емый узел - не корень
				{
					if ((cur->getLeft() == nullptr) && (cur->getRight() == nullptr))
					{
						if (par->getLeft() == cur)
							par->setLeft(nullptr);
						else
							par->setRight(nullptr);
						delete cur;
					}
					else if (cur->getRight() == nullptr)
					{
						if (par->getLeft() == cur)
							par->setLeft(cur->getLeft());
						else
							par->setRight(cur->getLeft());
						cur->setLeft(nullptr);
						delete cur;
					}
					else if (cur->getLeft() == nullptr)
					{
						if (par->getLeft() == cur)
							par->setLeft(cur->getRight());
						else
							par->setRight(cur->getRight());
						cur->setRight(nullptr);
						delete cur;
					}
					else {
						BinTreeNode* temp = cur->getRight();
						while (temp->getLeft())
							temp = temp->getLeft();
						int64_t tempKey = temp->getKey();
						int tempRN = temp->getRecordNumber();
						this->removeElement(tempKey);
						cur->setKey(tempKey);
						cur->setRecordNumber(tempRN);
					}
				}
				else { //если удал€емый узел - корень
					if ((cur->getLeft() == nullptr) && (cur->getRight() == nullptr))
					{
						this->root = nullptr;
						delete cur;
					}
					else if (cur->getRight() == nullptr)
					{
						this->root = cur->getLeft();
						this->root->setParent(nullptr);
						cur->setLeft(nullptr);
						delete cur;
					}
					else if (cur->getLeft() == nullptr)
					{
						this->root = cur->getRight();
						this->root->setParent(nullptr);
						cur->setRight(nullptr);
						delete cur;
					}
					else {
						BinTreeNode* temp = cur->getRight();
						while (temp->getLeft())
							temp = temp->getLeft();
						int64_t tempKey = temp->getKey();
						int tempRN = temp->getRecordNumber();
						this->removeElement(tempKey);
						cur->setKey(tempKey);
						cur->setRecordNumber(tempRN);
					}
				}
				break;
			}
			else if (key < cur->getKey())
			{
				cur = cur->getLeft();
			}
			else
			{
				cur = cur->getRight();
			}
		}
	}
	else {
		cout << "Ёлемент с ключом " << key << " не существует в дереве." << endl;
	}
}

int BinTree::findElement(int64_t key)
{
	BinTreeNode* cur = this->root;
	bool found = false;
	while (cur)
	{
		if (cur->getKey() == key)
		{
			found = true;
			break;
		}
		else if (key < cur->getKey())
		{
			cur = cur->getLeft();
		}
		else
		{
			cur = cur->getRight();
		}
	}
	if (found)
	{
		return cur->getRecordNumber();
	}
	return 0;
}

void BinTree::showTree()
{
	if (this->root)
		this->root->show();
	else
		cout << "ƒерево пусто." << endl;
}

BinTree::~BinTree()
{
	delete root;
}

