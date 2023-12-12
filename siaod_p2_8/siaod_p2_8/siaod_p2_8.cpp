#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>

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

	void convert_to_table(vector<char>& chars, vector<string>& codes)
	{
		vector<char> chs;
		vector<string> cds;
		queue<node*> queue1; //узлы
		queue<string> queue2; //коды
		queue1.push(root);
		queue2.push("");
		while (queue1.size() > 0)
		{
			//для очередного узла добавляем в очередь его потомков
			node* cur = queue1.front();
			string cur_path = queue2.front();
			queue1.pop();
			queue2.pop();
			if (cur->getLeft())
			{
				queue1.push(cur->getLeft());
				queue2.push(cur_path + "0");
			}
				
			if (cur->getRight())
			{
				queue1.push(cur->getRight());
				queue2.push(cur_path + "1");
			}

			//добавляем символ, если текущий узел - лист
			if ((cur->getLeft() == nullptr) && (cur->getRight() == nullptr))
			{
				chs.push_back(cur->value[0]);
				cds.push_back(cur_path);
			}
		}
		chars = vector<char>(chs);
		codes = vector<string>(cds);
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
	fstream input_file("input.txt", ios::in);
	string input = "";
	while (!input_file.eof())
	{
		string temp = "";
		getline(input_file, temp);
		input += temp;
	}
	haffman_tree tree = haffman_tree();
	tree.construct(input);
	tree.show();
	vector<char> chars;
	vector<string> codes;
	tree.convert_to_table(chars, codes);
	string output = "";
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < chars.size(); j++)
		{
			if (input[i] == chars[j])
			{
				output += codes[j];
				break;
			}
		}
	}
	vector<unsigned char> output_chars;
	for (int i = output.size() - 8; i >= 0; i -= 8) //упаковка 8 бит в 1-байтовое число
	{
		string temp = "";
		for (int j = 0; j < 8; j++)
		{
			temp += output[i + j];
		}
		output_chars.push_back(unsigned char(strtol(temp.c_str(), nullptr, 2)));
	}
	fstream output_file("archived.txt", ios::out | ios::binary);
	for (int i = output_chars.size() - 1; i >= 0; i--)
	{
		output_file.write((char*) &(output_chars[i]), sizeof(unsigned char));
	}
	output_file.close();
	return 0;
}