#include<iostream>
#include<map>
using namespace std;

//pair�^�\���p�A�}�����Z�q�̃I�[�o�[���[�h
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& p) {
	return s << p.first << ":" << p.second;
}

//�ǂ̃R���e�i������őS���\���ł���
template<class C>
void show(const C& data) {
	for (const auto& d : data) {
		cout << d << endl;
	}
	cout << endl;
}

int main() {
	//���t2���؃f�[�^�̓��ꕨ
	map<string, int> price;
	//�f�[�^�\�z
	price["���傤��"] = 100;
	price["��[�߂�"] = 200;
	price["����[�͂�"] = 300;
	price["���т܂�"] = 400;
	show(price);
	//�T��
	string key = "���[�߂�";
	cout << key << ' ';
	auto it = price.find(key);
	if (it != price.end()) {
		cout << it->second << "����";
	}
	else {
		cout << "�Ȃ�";
	}

	system("pause>0");
}