#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a) > (b) ? (a) : (b))


typedef struct avlNode {
    char* data;
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

/* 대소문자 구별 없이 알파벳의 선후만을 따짐, a가 사전상 앞이면 1, b이면 -1, 같으면 0 */
int char_comparison(char* a, char* b)
{
    int i = 0;
    int achar;
    int bchar;
    while (a[i] != '\0' && b[i] != '\0')
    {
        achar = a[i];
        bchar = b[i];
        if (a[i] >= 97) achar = a[i] - 32;
        if (b[i] >= 97) bchar = b[i] - 32;

        if (achar < bchar) {
            return 1;
        } else if (achar > bchar) {
            return -1;
        }

        i++;
    }

    if (a[i] == '\0' && b[i] == '\0') {
        return 0;
    } else if (a[i] != '\0' && b[i] == '\0') {
        return -1;
    } else {
        return 1;
    }
}

avlNode* create_node(char* str)
{
    avlNode *node = (avlNode*)malloc(sizeof(avlNode));
    node->data = str;
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
avlNode* insert(avlNode* node, char* key)
{
    if (node == NULL) {
        return create_node(key);
    }

    if (char_comparison(node->data, key) == 1)
    {
        node->right = insert(node->right, key);
    } 
    else if (char_comparison(node->data, key) == -1) 
    {
        node->left = insert(node->left, key);
    }
    else { // 같은값 추가 불가능
        return node;
    }

    int balance = get_balance(node);

    /* LL */
    if (balance > 1 && char_comparison(key, node->left->data) == 1)
    {
        node = rotate_right(node);
    } 
    else if (balance < -1 && char_comparison(key, node->right->data) == -1)  /* RR */
    {
        node = rotate_left(node);
    }
    else if (balance > 1 && char_comparison(key, node->left->data) == -1) /* LR */
    {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
    }
    else if (balance < -1 && char_comparison(key, node->right->data) == 1) /* RL */
    {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
    }

    return node;
}

void preorder(avlNode* root)
{
    if (root != NULL) {
        printf("%s ->", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}


int main(void)
{
    avlNode* root = NULL;

    root = insert(root, "Dec");
    root = insert(root, "Jan");
    root = insert(root, "Apr");
    root =insert(root, "Mar");
    root = insert(root, "July");
    root = insert(root, "Aug");
    root = insert(root, "AA");
    

    printf("\n");
    preorder(root);
}
