#include <stdio.h>
#include <stdlib.h>

// �m�[�h�\����
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// �؂̍����擾
int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// �ő�l�擾
int max(int a, int b) {
    return a > b ? a : b;
}

// �E��]
Node* rightRotate(Node* node) {
    Node* left = node->left;
    node->left = left->right;
    left->right = node;

    // �����X�V
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    left->height = max(getHeight(left->left), getHeight(left->right)) + 1;

    return left;
}

// ����]
Node* leftRotate(Node* node) {
    Node* right = node->right;
    node->right = right->left;
    right->left = node;

    // �����X�V
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    right->height = max(getHeight(right->left), getHeight(right->right)) + 1;

    return right;
}

// �o�����X����
Node* rebalance(Node* node) {
    int balance = getHeight(node->left) - getHeight(node->right);

    // �������d��
    if (balance > 1) {
        // ���̎q�̍������d��
        if (getHeight(node->left->left) >= getHeight(node->left->right)) {
            return rightRotate(node);
        }
        else {
            // ���̎q�̉E�����d��
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    else if (balance < -1) {
        // �E�����d��
        if (getHeight(node->right->right) >= getHeight(node->right->left)) {
            return leftRotate(node);
        }
        else {
            // �E���̎q�̍������d��
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// �}��
Node* insert(Node* node, int key) {
    if (node == NULL) {
        // �V�K�m�[�h�쐬
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }
    else if (key < node->key) {
        // �������؂ɑ}��
        node->left = insert(node->left, key);
    }
    else {
        // �E�����؂ɑ}��
        node->right = insert(node->right, key);
    }

    // �����X�V
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // �o�����X����
    return rebalance(node);
}

// ����
Node* find(Node* node, int key) {
    if (node == NULL) {
        return NULL;
    }
    else if (key < node->key) {
        // �������؂Ō���
        return find(node->left, key);
    }
    else if (key > node->key) {
        // �E�����؂Ō���
        return find(node->right, key);
    }
    else {
        // ����
        return node;
    }
}

// �폜
Node* erace(Node* node, int key) {
    if (node == NULL) {
        return NULL;
    }
    else if (key < node->key) {
        // �������؂ō폜
        node->left = erace(node->left, key);
    }
    else if (key > node->key) {
        // �E�����؂ō폜
        node->right = erace(node->right, key);
    }
    else {
        // �폜�Ώۃm�[�h

        // �q�m�[�h��1�ȉ��̏ꍇ
        if (node->left == NULL || node->right == NULL) {
            Node* tmp = node->left != NULL ? node->left : node->right;
            free(node);
            return tmp;
        }
        else {
            // �q�m�[�h��2���݂���ꍇ
            // ��p�m�[�h��������
            Node* successor = node->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }

            // �폜�Ώۃm�[�h�ƌ�p�m�[�h�̒l�����ւ�
            int tmpKey = node->key;
            node->key = successor->key;
            successor->key = tmpKey;

            // ��p�m�[�h���폜
            node->right = erace(node->right, successor->key);
        }
    }

    // �����X�V
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // �o�����X����
    return rebalance(node);
}

// �S�Ẵm�[�h�����
void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// ���ԏ�����
void printInorder(Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%d ", node->key);
    printInorder(node->right);
}

int main() {
    Node* root = NULL;

    // �}��
    root = insert(root, 5);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 3);

    // ���ԏ�����
    printInorder(root);
    printf("\n");

    // ����
    Node* foundNode = find(root, 3);
    if (foundNode != NULL) {
        printf("Found: %d\n", foundNode->key);
    }
    else {
        printf("Not found: 3\n");
    }

    // �폜
    printf("Delete: 3\n");
    root = erace(root, 3);

    // ���ԏ�����
    printInorder(root);
    printf("\n");

    // �S�Ẵm�[�h�����
    freeTree(root);

    system("pause>0");
}

/*
C����ŕ��t2���؂̎���
���t2���؂́A�񕪒T���؂̃o�����X����ɕۂ悤�ɉ��ǂ��ꂽ�f�[�^�\���ł��B
�}����폜�Ȃǂ̑�������Ă��A�؂̍��������O(logN)�ɕۂ���邽�߁A
�����Ȍ����E�}���E�폜���\�ł��B

���̃v���O�����́A���t2���؂̊�{�I�ȑ���ł���}���A�����A�폜���������Ă��܂��B
�܂��A�؂̍������X�V����֐���o�����X�������s���֐��Ȃǂ��������Ă��܂��B

���Ǔ_
���̃v���O�����͊�{�I�ȑ���݂̂��������Ă��܂��B
�K�v�ɉ����āA���̑�����ǉ����邱�Ƃ��ł��܂��B
�������Ǘ��͊ȈՓI�ȕ��@�ōs���Ă��܂��B
�����S�ȃ������Ǘ����s�����߂ɂ́A�K�؂ȕ��@�Ń��������m�ہE�������K�v������܂��B

���p
���t2���؂́A�����Ȍ����E�}���E�폜���K�v�Ƃ����l�X�ȏ�ʂŗ��p���邱�Ƃ��ł��܂��B
�Ⴆ�΁A�ȉ��̂悤�ȗp�r�ɗ��p�ł��܂��B
  ����
  �f�[�^�x�[�X�C���f�b�N�X
  �L���b�V��
  �Q�[��AI
*/