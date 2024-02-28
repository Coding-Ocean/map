#include <stdio.h>
#include <stdlib.h>

// ノード構造体
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// 木の高さ取得
int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// 最大値取得
int max(int a, int b) {
    return a > b ? a : b;
}

// 右回転
Node* rightRotate(Node* node) {
    Node* left = node->left;
    node->left = left->right;
    left->right = node;

    // 高さ更新
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    left->height = max(getHeight(left->left), getHeight(left->right)) + 1;

    return left;
}

// 左回転
Node* leftRotate(Node* node) {
    Node* right = node->right;
    node->right = right->left;
    right->left = node;

    // 高さ更新
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    right->height = max(getHeight(right->left), getHeight(right->right)) + 1;

    return right;
}

// バランス調整
Node* rebalance(Node* node) {
    int balance = getHeight(node->left) - getHeight(node->right);

    // 左側が重い
    if (balance > 1) {
        // 左の子の左側が重い
        if (getHeight(node->left->left) >= getHeight(node->left->right)) {
            return rightRotate(node);
        }
        else {
            // 左の子の右側が重い
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    else if (balance < -1) {
        // 右側が重い
        if (getHeight(node->right->right) >= getHeight(node->right->left)) {
            return leftRotate(node);
        }
        else {
            // 右側の子の左側が重い
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// 挿入
Node* insert(Node* node, int key) {
    if (node == NULL) {
        // 新規ノード作成
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }
    else if (key < node->key) {
        // 左部分木に挿入
        node->left = insert(node->left, key);
    }
    else {
        // 右部分木に挿入
        node->right = insert(node->right, key);
    }

    // 高さ更新
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // バランス調整
    return rebalance(node);
}

// 検索
Node* find(Node* node, int key) {
    if (node == NULL) {
        return NULL;
    }
    else if (key < node->key) {
        // 左部分木で検索
        return find(node->left, key);
    }
    else if (key > node->key) {
        // 右部分木で検索
        return find(node->right, key);
    }
    else {
        // 発見
        return node;
    }
}

// 削除
Node* erace(Node* node, int key) {
    if (node == NULL) {
        return NULL;
    }
    else if (key < node->key) {
        // 左部分木で削除
        node->left = erace(node->left, key);
    }
    else if (key > node->key) {
        // 右部分木で削除
        node->right = erace(node->right, key);
    }
    else {
        // 削除対象ノード

        // 子ノードが1つ以下の場合
        if (node->left == NULL || node->right == NULL) {
            Node* tmp = node->left != NULL ? node->left : node->right;
            free(node);
            return tmp;
        }
        else {
            // 子ノードが2つ存在する場合
            // 後継ノードを見つける
            Node* successor = node->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }

            // 削除対象ノードと後継ノードの値を入れ替え
            int tmpKey = node->key;
            node->key = successor->key;
            successor->key = tmpKey;

            // 後継ノードを削除
            node->right = erace(node->right, successor->key);
        }
    }

    // 高さ更新
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // バランス調整
    return rebalance(node);
}

// 全てのノードを解放
void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// 中間順巡回
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

    // 挿入
    root = insert(root, 5);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 3);

    // 中間順巡回
    printInorder(root);
    printf("\n");

    // 検索
    Node* foundNode = find(root, 3);
    if (foundNode != NULL) {
        printf("Found: %d\n", foundNode->key);
    }
    else {
        printf("Not found: 3\n");
    }

    // 削除
    printf("Delete: 3\n");
    root = erace(root, 3);

    // 中間順巡回
    printInorder(root);
    printf("\n");

    // 全てのノードを解放
    freeTree(root);

    system("pause>0");
}

/*
C言語で平衡2分木の実装
平衡2分木は、二分探索木のバランスを常に保つように改良されたデータ構造です。
挿入や削除などの操作をしても、木の高さが常にO(logN)に保たれるため、
高速な検索・挿入・削除が可能です。

このプログラムは、平衡2分木の基本的な操作である挿入、検索、削除を実装しています。
また、木の高さを更新する関数やバランス調整を行う関数なども実装しています。

改良点
このプログラムは基本的な操作のみを実装しています。
必要に応じて、他の操作も追加することができます。
メモリ管理は簡易的な方法で行っています。
より安全なメモリ管理を行うためには、適切な方法でメモリを確保・解放する必要があります。

応用
平衡2分木は、高速な検索・挿入・削除が必要とされる様々な場面で利用することができます。
例えば、以下のような用途に利用できます。
  辞書
  データベースインデックス
  キャッシュ
  ゲームAI
*/