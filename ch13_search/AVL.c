#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct avlNode {
    int data;
    struct avlNode* left;
    struct avlNode* right;
} avlNode;

/* h(∅) = -1, h(single node) = 0, height = Max(Depth) */
int get_height(avlNode* node)
{
    int height = -1;

    if (node != NULL) 
    {
        height = 1 + max(get_height(node->left), get_height(node->right));
    }

    return height;
}

/* 균형값 계산 */
int get_balance(avlNode* node)
{
    if (node == NULL) return 0;
    return get_height(node->left) - get_height(node->right);
}

avlNode* create_node(int key)
{
    avlNode *node = (avlNode*)malloc(sizeof(avlNode));
    node->data = key;
    node->left = node->right = NULL;
    
    return node;
}

avlNode* rotate_right(avlNode* parent)
{
    avlNode* child = parent->left;
    parent->left = child->right;
    child->right = parent;

    return child;
}

avlNode* rotate_left(avlNode* parent)
{
    avlNode* child = parent->right;
    parent->right = child->left;
    child->left = parent;

    return child;
}

/* AVL에 새로운 노드 추가, 새로운 루트 반환 */
avlNode* insert(avlNode* node, int key)
{
    if (node == NULL) {
        return create_node(key);
    }

    if (node->data < key) 
    {
        node->right = insert(node->right, key);
    } 
    else if(node->data > key) 
    {
        node->left = insert(node->left, key);
    }
    else { // 같은값 추가 불가능
        return node;
    }

    int balance = get_balance(node);

    /* LL */
    if (balance > 1 && key < node->left->data) 
    {
        node = rotate_right(node);
    } 
    else if (balance < -1 && key > node->right->data)  /* RR */
    {
        node = rotate_left(node);
    }
    else if (balance > 1 && key > node->left->data) /* LR */
    {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
    }
    else if (balance < -1 && key < node->right->data) /* RL */
    {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
    }

    return node;
}

void preorder(avlNode* root)
{
    if (root != NULL) {
        printf("%2d ->", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(avlNode* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%2d ->", root->data);
        inorder(root->right);
    }
}

int main(void)
{
    avlNode* root = NULL;

    int arr[7] = {4,2,5,1,3,7,6};

    for (int i = 0; i < 7; i++) 
    {
        root = insert(root, arr[i]);
    }

    printf("\n");
    inorder(root);
}
