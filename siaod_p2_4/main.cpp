#include <iostream>
#include "node.h"

using namespace std;

int main()
{
    Node* n1 = new Node(15.3);
    Node* n2 = new Node(29.8);
    Node* n3 = new Node(40.2);
    Node* n4 = new Node(3.14);
    Node* n5 = new Node(-14.4);
    Node* n6 = new Node(10.7);
    Node* n7 = new Node(25.6);
    n1->addLeft(n2);
    n2->addLeft(n3);
    n3->addRight(n4);
    n3->addLeft(n5);
    n1->addRight(n6);
    n6->addLeft(n7);
    n1->show();
    return 0;
}
