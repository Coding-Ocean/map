#include<iostream>
#include<set>
using namespace std;

int main() {
	//�������L�����镽�t2����
	set<int> tree;
	//�f�[�^�\�z
	tree.emplace(5);
	tree.emplace(3);
	tree.emplace(2);
	tree.emplace(1);
	tree.emplace(4);
	//�S�\��
	for (const auto& num : tree)
		cout << num << " ";
	cout << endl;
	//�T��
	int num = 2;
	cout << num << "��";
	auto it = tree.find(num);
	if (it != tree.end())
		cout << "������";
	else
		cout << "�Ȃ�����";
	cout << endl;

	system("pause>0");
}