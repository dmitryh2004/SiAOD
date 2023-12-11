#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct node {
	string value = "";
	int count = 1;
	node* left = nullptr;
	node* right = nullptr;

	node(string ch)
	{
		this->value = ch;
	}

	~node() {
		if (this->left) delete left;
		if (this->right) delete right;
	}

	void setLeft(node* left) {
		this->left = left;
	}

	void setRight(node* right) {
		this->right = right;
	}

	void setCount(int count) {
		this->count = count;
	}

	node* getLeft() {
		return this->left;
	}

	node* getRight() {
		return this->right;
	}

	int getCount() {
		return this->count;
	}

	void show(string path)
	{
		if ((this->left == nullptr) && (this->right == nullptr))
		{
			for (int i = 0; i < path.size(); i++)
			{
				cout << "\t";
			}
			cout << " < " << this->value << " (count: " << this->count << ") > " << path << "\n";
		}
		else
		{
			if (this->right)
				this->right->show(path + "1");
			for (int i = 0; i < path.size(); i++)
			{
				cout << "\t";
			}
			cout << "| (count: " << this->count << ")" << endl;
			if (this->left)
				this->left->show(path + "0");
		}
	}
};

class haffman_tree {
	node* root;
public:
	haffman_tree() {
		this->root = nullptr;
	}

	void show() {
		this->root->show("");
	}

	void construct(string input) {
		vector<node*> chs;
		vector<int> cnts;
		for (int i = 0; i < input.size(); i++)
		{
			bool modified = false;
			for (int j = 0; j < chs.size(); j++)
			{
				if (chs[j]->value[0] == input[i])
				{
					modified = true;
					chs[j]->setCount(++cnts[j]);
					break;
				}
			}
			if (!modified)
			{
				string v = string(1, input[i]);
				chs.push_back(new node(v));
				cnts.push_back(1);
			}
		}

		while (chs.size() > 1)
		{
			for (int i = 0; i < chs.size(); i++)
			{
				for (int j = 0; j < chs.size(); j++)
				{
					if (cnts[i] < cnts[j])
					{
						swap(cnts[i], cnts[j]);
						swap(chs[i], chs[j]);
					}
				}
			}
			node* ch1 = chs[0];
			node* ch2 = chs[1];
			node* ch3 = new node(ch1->value + ch2->value);
			ch3->setLeft(ch1);
			ch3->setRight(ch2);
			ch3->setCount(ch1->getCount() + ch2->getCount());
			chs.push_back(ch3);
			cnts.push_back(cnts[0] + cnts[1]);

			vector<node*> temp;
			vector<int> temp2;
			for (int i = 2; i < chs.size(); i++)
			{
				temp.push_back(chs[i]);
				temp2.push_back(cnts[i]);
			}
			chs = temp;
			cnts = temp2;
		}

		this->root = chs[0];
	}

	~haffman_tree() {
		delete root;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	string input = "Прибавь к ослиной голове еще одну, получишь две. Но сколько б ни было ослов, они и двух не свяжут слов.";
	haffman_tree tree = haffman_tree();
	tree.construct(input);
	tree.show();
	return 0;
}