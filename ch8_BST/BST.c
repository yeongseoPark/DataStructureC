#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* seach(TreeNode* node, int key)
{
	while (node) {
		if (node->data == key) return node;

		if (node->data < key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	
	return NULL;
}

TreeNode* new_node(int item)
{
	TreeNode* tmp = malloc(sizeof(TreeNode));

	tmp->data = item;
	tmp->left = tmp->right = NULL;

	return tmp;
}

TreeNode* insert_node(TreeNode* node, int key)
{
	if (node == NULL) return new_node(key);

	if (node->data == key) return;
	if (node->data < key) {
		node->right = insert_node(node->right, key);
	}
	else {
		node->left = insert_node(node->left, key);
	}

	return node;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* cur = node;

	while (cur->left != NULL) {
		cur = cur->left;
	}

	return cur;
}

/*
	1. 삭제하려는 노드가 단말노드
	2. 삭제하려는 노드가 서브트리 중 하나만
	3. 삭제하려는 노드가 두개의 서브트리 모두 가지고 있음
*/
TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) return root;

	if (root->data > key) {
		root->left = delete_node(root->left, key);
	}
	else if (root->data < key) 
	{
		root->right = delete_node(root->right, key);
	}
	else {
		// 1, 2의 경우
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}

		// 3의 경우, 우측 서브트리의 가장작은(왼쪽)값으로 교체 
		TreeNode* temp = min_value_node(root->right);

		root->data = temp->data;
		root->right = delete_node(root->right, temp->data);
	}

	return root;
}

void inorder(TreeNode* root)
{
	if (root) {
		inorder(root->left);
		printf("%d ->", root->data);
		inorder(root->right);
	}
}

void ArraytoBST(TreeNode* root)
{
	int arr[] = { 11,3,4,1,56,5,6,2,98,32,23 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		root = insert_node(root, arr[i]);
	}

	inorder(root);
}

void iter_decrement(TreeNode* root)
{
	if (root) {
		iter_decrement(root->right);
		printf("%d ->", root->data);
		iter_decrement(root->left);
	}
}

void increment_one(TreeNode* root)
{
	if (root) {
		increment_one(root->left);
		root->data++;
		increment_one(root->right);
	}
}

void ArraytoBST_decrement(TreeNode* root)
{
	int arr[] = { 11,3,4,1,56,5,6,2,98,32,23 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		root = insert_node(root, arr[i]);
	}

	increment_one(root);
	iter_decrement(root);
}


int main(void)
{
	TreeNode* root = NULL;
	ArraytoBST(root);
	printf("\n");
	ArraytoBST_decrement(root);

	/*TreeNode* tmp = NULL;

	root = insert_node(root, 3);
	root = insert_node(root, 2);
	root = insert_node(root, 1);
	root = insert_node(root, 4);
	root = insert_node(root, 5);
	root = insert_node(root, 6);

	inorder(root);


	printf("\n");

	printf("%d \n", seach(root, 3)->data);

	delete_node(root, 3);

	printf("%d \n", seach(root, 3) ? 1 : 0);*/
}