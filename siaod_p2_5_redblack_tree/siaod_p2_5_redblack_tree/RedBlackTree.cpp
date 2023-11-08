#include "RedBlackTree.h"

void RedBlackTreeNode::invertSelf()
{
	if (this->color == RedBlackTreeColor::Red)
		this->color = RedBlackTreeColor::Black;
	else
		this->color = RedBlackTreeColor::Red;
}

RedBlackTreeNode::RedBlackTreeNode(RedBlackTreeNode* parent, int64_t key, int recordNumber, RedBlackTreeColor color)
{
	this->parent = parent;
	this->key = key;
	this->recordNumber = recordNumber;
	this->color = color;
}

void RedBlackTreeNode::clearParent()
{
	this->parent = nullptr;
}

void RedBlackTreeNode::setLeft(RedBlackTreeNode* left)
{
	this->left = left;
	if (left)
		left->parent = this;
}

void RedBlackTreeNode::setRight(RedBlackTreeNode* right)
{
	this->right = right;
	if (right)
		right->parent = this;
}

void RedBlackTreeNode::setColor(RedBlackTreeColor color)
{
	this->color = color;
}

void RedBlackTreeNode::setKey(int64_t key) {
	this->key = key;
}

void RedBlackTreeNode::setRN(int RN) {
	this->recordNumber = RN;
}

RedBlackTreeNode* RedBlackTreeNode::getLeft() {
	return this->left;
}

RedBlackTreeNode* RedBlackTreeNode::getRight() {
	return this->right;
}

RedBlackTreeNode* RedBlackTreeNode::getParent() {
	return this->parent;
}

RedBlackTreeColor RedBlackTreeNode::getColor() {
	return this->color;
}

int64_t RedBlackTreeNode::getKey() {
	return this->key;
}

int RedBlackTreeNode::getRN() {
	return this->recordNumber;
}

void RedBlackTreeNode::show(int level)
{
	if (this->right) {
		this->right->show(level + 1);
	}
	for (int i = 0; i < level; i++)
	{
		cout << "-----|";
	}
	cout << "< " << this->key << " > ";
	if (this->color == RedBlackTreeColor::Black) {
		cout << "Black\n";
	}
	else {
		cout << "Red\n";
	}
	if (this->left) {
		this->left->show(level + 1);
	}
}

RedBlackTreeNode::~RedBlackTreeNode() {
	if (this->left)
		delete left;
	if (this->right)
		delete right;
}

RedBlackTree::RedBlackTree(RedBlackTreeNode* root) {
	this->root = root;
}

RedBlackTree::~RedBlackTree() {
	delete root;
}

void RedBlackTree::showTree() {
	if (root)
	{
		root->show();
		cout << "—реднее число поворотов (повороты / число узлов): " << (double)rotations / nodes << endl;
	}
	else
		cout << "ƒерево пусто.\n";
}

void RedBlackTree::leftRotate(RedBlackTreeNode* pivot) {
	rotations++;
	RedBlackTreeNode* pivotParent = pivot->getParent();
	RedBlackTreeNode* temp = pivot->getRight();
	pivot->setRight(temp->getLeft());
	if (temp)
		temp->setLeft(pivot);
	if (pivotParent)
	{
		bool isLeft = (pivotParent->getLeft() == pivot);
		if (isLeft)
			pivotParent->setLeft(temp);
		else
			pivotParent->setRight(temp);
	}
	else {
		temp->clearParent();
		this->root = temp;
	}
}

void RedBlackTree::rightRotate(RedBlackTreeNode* pivot) {
	rotations++;
	RedBlackTreeNode* pivotParent = pivot->getParent();
	RedBlackTreeNode* temp = pivot->getLeft();
	pivot->setLeft(temp->getRight());
	if (temp)
		temp->setRight(pivot);
	if (pivotParent)
	{
		bool isLeft = (pivotParent->getLeft() == pivot);
		if (isLeft)
			pivotParent->setLeft(temp);
		else
			pivotParent->setRight(temp);
	}
	else {
		temp->clearParent();
		this->root = temp;
	}
}

int RedBlackTree::findElement(int64_t key)
{
	RedBlackTreeNode* cur = this->root;
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
		return cur->getRN();
	}
	return 0;
}

void RedBlackTree::addElement(int64_t key, int RN) {
	if (!findElement(key))
	{
		if (this->root == nullptr) {
			this->root = new RedBlackTreeNode(nullptr, key, RN, RedBlackTreeColor::Black);
		}
		else {
			RedBlackTreeNode* cur = this->root;
			while (cur)
			{
				if (key < cur->getKey())
				{
					if (cur->getLeft() == nullptr)
					{
						cur->setLeft(new RedBlackTreeNode(cur, key, RN,
							RedBlackTreeColor::Red));
						checkAddConditions(cur->getLeft());
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
						cur->setRight(new RedBlackTreeNode(cur, key, RN,
							RedBlackTreeColor::Red));
						checkAddConditions(cur->getRight());
						break;
					}
					else {
						cur = cur->getRight();
					}
				}
			}
		}
		nodes++;
	}
	else {
		cout << "Ёлемент с ключом " << key << " уже существует в дереве.\n";
	}
}

void RedBlackTree::removeElement(int64_t key)
{
	if (findElement(key))
	{
		RedBlackTreeNode* cur = this->root;
		while (cur)
		{
			if (cur->getKey() == key)
				break;
			else if (key < cur->getKey())
				cur = cur->getLeft();
			else
				cur = cur->getRight();
		}
		bool isRed = (cur->getColor() == Red);
		RedBlackTreeNode* par = cur->getParent();
		bool isLeft = false;
		if (isRed)
		{
			if (par) //если удал€емый узел - не корень
			{
				isLeft = (par->getLeft() == cur);
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
					RedBlackTreeNode* temp = cur->getRight();
					while (temp->getLeft())
						temp = temp->getLeft();
					int64_t tempKey = temp->getKey();
					int tempRN = temp->getRN();
					this->removeElement(tempKey);
					cur->setKey(tempKey);
					cur->setRN(tempRN);
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
					this->root->clearParent();
					cur->setLeft(nullptr);
					delete cur;
				}
				else if (cur->getLeft() == nullptr)
				{
					this->root = cur->getRight();
					this->root->clearParent();
					cur->setRight(nullptr);
					delete cur;
				}
				else {
					RedBlackTreeNode* temp = cur->getRight();
					while (temp->getLeft())
						temp = temp->getLeft();
					int64_t tempKey = temp->getKey();
					int tempRN = temp->getRN();
					this->removeElement(tempKey);
					cur->setKey(tempKey);
					cur->setRN(tempRN);
				}
			}
		}
		else {
			if (par) //если удал€емый узел - не корень
			{
				isLeft = (par->getLeft() == cur);
				if ((cur->getLeft() == nullptr) && (cur->getRight() == nullptr))
				{
					if (par->getLeft() == cur)
						par->setLeft(nullptr);
					else
						par->setRight(nullptr);
					delete cur;
					checkRemoveConditions(par, isLeft);
				}
				else if (cur->getRight() == nullptr)
				{
					RedBlackTreeNode* temp = cur->getLeft();
					cur->setKey(temp->getKey());
					cur->setRN(temp->getRN());
					cur->setLeft(nullptr);
					delete temp;
				}
				else if (cur->getLeft() == nullptr)
				{
					RedBlackTreeNode* temp = cur->getRight();
					cur->setKey(temp->getKey());
					cur->setRN(temp->getRN());
					cur->setRight(nullptr);
					delete temp;
				}
				else {
					RedBlackTreeNode* temp = cur->getRight();
					while (temp->getLeft())
						temp = temp->getLeft();
					int64_t tempKey = temp->getKey();
					int tempRN = temp->getRN();
					this->removeElement(tempKey);
					cur->setKey(tempKey);
					cur->setRN(tempRN);
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
					RedBlackTreeNode* temp = cur->getLeft();
					cur->setKey(temp->getKey());
					cur->setRN(temp->getRN());
					cur->setLeft(nullptr);
					delete temp;
				}
				else if (cur->getLeft() == nullptr)
				{
					RedBlackTreeNode* temp = cur->getRight();
					cur->setKey(temp->getKey());
					cur->setRN(temp->getRN());
					cur->setRight(nullptr);
					delete temp;
				}
				else {
					RedBlackTreeNode* temp = cur->getRight();
					while (temp->getLeft())
						temp = temp->getLeft();
					int64_t tempKey = temp->getKey();
					int tempRN = temp->getRN();
					this->removeElement(tempKey);
					cur->setKey(tempKey);
					cur->setRN(tempRN);
				}
			}
		}
	}
	else {
		cout << "Ёлемент с ключом " << key << " не существует в дереве.\n";
	}
}

void RedBlackTree::checkAddConditions(RedBlackTreeNode* startNode) 
{
	if (!startNode) return;
	RedBlackTreeNode* parent = startNode->getParent();
	if (!parent)
	{
		if (startNode->getColor() == Red)
			startNode->setColor(Black);
	}
	else {
		if (parent->getColor() == RedBlackTreeColor::Black) {
			return;
		}
		RedBlackTreeNode* gp = parent->getParent();
		if (gp)
		{
			RedBlackTreeNode* uncle = (gp->getLeft() == startNode->getParent()) ?
				gp->getRight() : gp->getLeft();
			if (uncle)
			{
				if (uncle->getColor() == RedBlackTreeColor::Red) {
					gp->setColor(Red);
					parent->setColor(Black);
					uncle->setColor(Black);
					checkAddConditions(gp);
				}
				else {
					bool parentIsLeft = gp->getLeft() == parent;
					bool nodeIsLeft = parent->getLeft() == startNode;
					if (parentIsLeft && nodeIsLeft)
					{
						rightRotate(gp);
						gp->invertSelf();
						parent->invertSelf();
					}
					else if (parentIsLeft && !nodeIsLeft)
					{
						leftRotate(parent);
						checkAddConditions(parent);
					}
					else if (!parentIsLeft && nodeIsLeft)
					{
						rightRotate(parent);
						checkAddConditions(parent);
					}
					else {
						leftRotate(gp);
						gp->invertSelf();
						parent->invertSelf();
					}
				}
			}
			else {
				bool parentIsLeft = gp->getLeft() == parent;
				bool nodeIsLeft = parent->getLeft() == startNode;
				if (parentIsLeft && nodeIsLeft)
				{
					rightRotate(gp);
					gp->invertSelf();
					parent->invertSelf();
				}
				else if (parentIsLeft && !nodeIsLeft)
				{
					leftRotate(parent);
					rightRotate(gp);
					gp->invertSelf();
					startNode->invertSelf();
				}
				else if (!parentIsLeft && nodeIsLeft)
				{
					rightRotate(parent);
					leftRotate(gp);
					gp->invertSelf();
					startNode->invertSelf();
				}
				else {
					leftRotate(gp);
					gp->invertSelf();
					parent->invertSelf();
				}
			}
		}
		else {
			parent->setColor(Black);
		}
	}
	checkRoot();
}

void RedBlackTree::checkRemoveConditions(RedBlackTreeNode * startNode, bool isLeft)
{
	if (!isLeft) //удал€ем правого потомка
	{
		RedBlackTreeNode* left = startNode->getLeft();
		RedBlackTreeNode* left_left;
		RedBlackTreeNode* left_right;
		RedBlackTreeNode* left_right_left = nullptr;
		RedBlackTreeNode* left_right_right;
		RedBlackTreeColor left_color = Black,
			left_left_color = Black,
			left_right_color = Black,
			left_right_left_color = Black,
			left_right_right_color = Black;
		if (left)
		{
			left_color = left->getColor();
			left_left = left->getLeft();
			left_right = left->getRight();
			if (left_left)
			{
				left_left_color = left_left->getColor();
			}
			if (left_right)
			{
				left_right_color = left_right->getColor();
				left_right_left = left_right->getLeft();
				left_right_right = left_right->getRight();
				if (left_right_left)
					left_right_left_color = left_right_left->getColor();
				if (left_right_right)
					left_right_right_color = left_right_right->getColor();
			}
			
			//case1: start red, start->left black, start->left->childs black
			if ((startNode->getColor() == Red) &&
				(left_color == Black) &&
				(left_left_color == Black) &&
				(left_right_color == Black))
			{
				startNode->setColor(Black);
				left->setColor(Red);
			}
			//case2: start red, start->left black, start->left->left red
			else if ((startNode->getColor() == Red) &&
				(left_color == Black) &&
				(left_left_color == Red))
			{
				startNode->setColor(Black);
				left->setColor(Red);
				rightRotate(startNode);
			}
			//case2.5: start red, start->left black, start->left->right red
			else if ((startNode->getColor() == Red) &&
				(left_color == Black) &&
				(left_right_color == Red))
			{
				startNode->setColor(Black);
				//left_right->setColor(Black);
				leftRotate(left);
				rightRotate(startNode);
			}
			//case3: start black, start->left red, start->left->right->childs black
			else if ((startNode->getColor() == Black) &&
				(left_color == Red) &&
				(left_right_left_color == Black) &&
				(left_right_right_color == Black))
			{
				left->setColor(Black);
				left_right->setColor(Red);
				rightRotate(startNode);
			}
			//case4: start black, start->left red, start->left->right->left red
			else if ((startNode->getColor() == Black) &&
				(left_color == Red) &&
				(left_right_left_color == Red))
			{
				if (left_right_left)
					left_right_left->setColor(Black);
				leftRotate(left);
				rightRotate(startNode);
			}
			//case5: start black, start->left black, start->left->right red
			else if ((startNode->getColor() == Black) &&
				(left_color == Black) &&
				(left_right_color == Red))
			{
				left_right->setColor(Black);
				leftRotate(left);
				rightRotate(startNode);
			}
			//case6: start black, start->left black, start->left->left red
			else if ((startNode->getColor() == Black) &&
				(left_color == Black) &&
				(left_left_color == Red))
			{
				left_left->setColor(Black);
				rightRotate(startNode);
			}
			//case7: all black
			else {
				left->setColor(Red);
				if (startNode->getParent())
					checkRemoveConditions(startNode->getParent(),
						(startNode->getParent()->getRight() == startNode));
			}
		}
		else
		{
			//do nothing
		}
	}
	else { //удал€ем левого потомка
		RedBlackTreeNode* right = startNode->getRight();
		RedBlackTreeNode* right_right;
		RedBlackTreeNode* right_left;
		RedBlackTreeNode* right_left_right = nullptr;
		RedBlackTreeNode* right_left_left;
		RedBlackTreeColor right_color = Black,
			right_right_color = Black,
			right_left_color = Black,
			right_left_right_color = Black,
			right_left_left_color = Black;
		if (right)
		{
			right_color = right->getColor();
			right_right = right->getRight();
			right_left = right->getLeft();
			if (right_right)
			{
				right_right_color = right_right->getColor();
			}
			if (right_left)
			{
				right_left_color = right_left->getColor();
				right_left_right = right_left->getRight();
				right_left_left = right_left->getLeft();
				if (right_left_right)
					right_left_right_color = right_left_right->getColor();
				if (right_left_left)
					right_left_left_color = right_left_left->getColor();
			}

			//case1: start red, start->right black, start->right->childs black
			if ((startNode->getColor() == Red) &&
				(right_color == Black) &&
				(right_right_color == Black) &&
				(right_left_color == Black))
			{
				startNode->setColor(Black);
				right->setColor(Red);
			}
			//case2: start red, start->right black, start->right->right red
			else if ((startNode->getColor() == Red) &&
				(right_color == Black) &&
				(right_right_color == Red))
			{
				startNode->setColor(Black);
				right->setColor(Red);
				leftRotate(startNode);
			}
			//case2.5: start red, start->right black, start->right->left red
			else if ((startNode->getColor() == Red) &&
				(right_color == Black) &&
				(right_left_color == Red))
			{
				startNode->setColor(Black);
				//right_left->setColor(Black);
				rightRotate(right);
				leftRotate(startNode);
			}
			//case3: start black, start->right red, start->right->left->childs black
			else if ((startNode->getColor() == Black) &&
				(right_color == Red) &&
				(right_left_right_color == Black) &&
				(right_left_left_color == Black))
			{
				right->setColor(Black);
				right_left->setColor(Red);
				leftRotate(startNode);
			}
			//case4: start black, start->right red, start->right->left->right red
			else if ((startNode->getColor() == Black) &&
				(right_color == Red) &&
				(right_left_right_color == Red))
			{
				if (right_left_right)
					right_left_right->setColor(Black);
				rightRotate(right);
				leftRotate(startNode);
			}
			//case5: start black, start->right black, start->right->left red
			else if ((startNode->getColor() == Black) &&
				(right_color == Black) &&
				(right_left_color == Red))
			{
				right_left->setColor(Black);
				rightRotate(right);
				leftRotate(startNode);
			}
			//case6: start black, start->right black, start->right->right red
			else if ((startNode->getColor() == Black) &&
				(right_color == Black) &&
				(right_right_color == Red))
			{
				right_right->setColor(Black);
				leftRotate(startNode);
			}
			//case7: all black
			else {
				right->setColor(Red);
				if (startNode->getParent())
					checkRemoveConditions(startNode->getParent(),
						(startNode->getParent()->getRight() == startNode));
			}
		}
		else
		{
			//do nothing
		}
	}
}

void RedBlackTree::checkRoot()
{
	if (this->root->getColor() == RedBlackTreeColor::Red)
		this->root->invertSelf();
}
