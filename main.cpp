#include<iostream>
#include<set>
using namespace std;

int main() {
	//整数を記憶する平衡2分木
	set<int> tree;
	//データ構築
	tree.emplace(5);
	tree.emplace(3);
	tree.emplace(2);
	tree.emplace(1);
	tree.emplace(4);
	//全表示
	for (const auto& num : tree)
		cout << num << " ";
	cout << endl;
	//探索
	int num = 2;
	cout << num << "は";
	auto it = tree.find(num);
	if (it != tree.end())
		cout << "あった";
	else
		cout << "なかった";
	cout << endl;

	system("pause>0");
}