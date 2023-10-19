#ifndef __node_h__
#define __node_h__
#include <iostream>
#include <string>
using namespace std;

string operator * (string left, int right)
{
    string temp = "";
    for (int i = 0; i < right; i++)
        temp += left;
    return temp;
}

class Node {
    const int L = 3;
    const string ch_minus = "-";
    double value;
    Node* left;
    Node* right;
public:
    Node (double value) {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }

    void addLeft(Node* subtree)
    {
        if (!this->left)
            this->left = subtree;
    }

    void addRight(Node* subtree)
    {
        if (!this->right)
            this->right = subtree;
    }

    void rebalance();

    void show(int level = 0) {
        if (this->left) {
            this->left->show(level+1);
        }
        cout << "\n";
        for (int i = 0; i < level; i++)
        {
            cout << (ch_minus * L) << "|";
        }
        cout << "> " << this->value;
        cout << "\n";
        if (this->right) {
            this->right->show(level+1);
        }
    }

    ~Node () {
        if (this->left)
            delete left;
        if (this->right)
            delete right;
    }
};

#endif // __node_h__
