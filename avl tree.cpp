// import library
#include<stdio.h>
#include<stdlib.h>

// definisi struct node
struct Node {
    int key; //nilai yang disimpan dalam node
    struct Node* left; //pointer ke anak kiri
    struct Node* right;//ponter ke anak kanan
    int height; //menyimpan tinggi dari node ini (penting untuk menghitung balance).
};

//Fungsi Membuat Node Baru
struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // node baru selalu punya height 1
    return node;
}

//Fungsi Menghitung Tinggi Node
int height(struct Node* node) {
    if (node == NULL) return 0; //jika node kosong maka tinggi dianggap 0
    return node->height; //jika node tidak kosong
}

//Fungsi Menghitung Balance Factor
int getBalance(struct Node* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right); //Balance factor = tinggi anak kiri - tinggi anak kanan.
} //Nilainya harus antara -1 hingga +1 untuk AVL Tree yang seimbang.

//Fungsi Rotasi Kanan (Right Rotate)
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left; //Node y berat di kiri.
    struct Node* T2 = x->right; //x adalah anak kiri dari y.

    // Rotasi
    x->right = y; //Rotasi: x naik ke atas, y jadi anak kanannya x.
    y->left = T2; 

    // Update height
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    //Update tinggi semua node yang terlibat.
    return x;
}

//Fungsi Rotasi Kiri (Left Rotate)
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right; //Node x berat di kanan.
    struct Node* T2 = y->left; //y adalah anak kanan dari x.

    // Rotasi
    y->left = x; //Rotasi: y naik ke atas, x jadi anak kirinya y.
    x->right = T2;

    // Update height
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    //Update height semua node yang terlibat.
    return y;
}

//Fungsi Insert AVL
struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Tidak boleh ada key duplikat

    // Update tinggi node ini
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Hitung balance factor
    int balance = getBalance(node);

    // Jika tidak seimbang, lakukan rotasi yang sesuai:

    // Kasus Kiri-Kiri
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Kasus Kanan-Kanan
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Kasus Kiri-Kanan
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Kasus Kanan-Kiri
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//Traversal Preorder
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Program Utama (main)
int main() {
    struct Node* root = NULL;

    // Insert data
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Cetak tree preorder
    printf("Preorder traversal AVL Tree:\n");
    preOrder(root);

    return 0;
}

/*Masukkan data seperti biasa (mirip BST).

Update tinggi node.

Hitung balance factor.

Kalau balance factor abnormal ? lakukan rotasi.

Pohon tetap seimbang!*/


