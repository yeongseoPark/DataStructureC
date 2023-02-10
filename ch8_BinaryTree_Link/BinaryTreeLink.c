#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;


TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

/* ������ȸ */
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d -> ", root->data);
		inorder(root->right);
	}

}

/* ������ȸ */
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("%d -> ", root->data);
		preorder(root->left);
		preorder(root->right);
	}

}

/* ������ȸ */
void postorder(TreeNode* root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d -> ", root->data);
	}

}

/* �������� ������ȸ */
#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p)
{
	if (top != SIZE - 1)
		stack[++top] = p;
}

TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top != -1)
		p = stack[top--];
	return p;
}

void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left)
			push(root);

		root = pop();
		if (root == NULL) break;
		printf("%d -> ", root->data);

		root = root->right;
	}
}

// ���� Ʈ�� ��� 
int evaluate(TreeNode* root)
{
	if (root == NULL) {
		return 0;
	}
	if (root->left == NULL && root->right == NULL) {
		return root->data;
	} 
	else {
		int op1 = evaluate(root->left);
		int op2 = evaluate(root->right);
		printf("%d %c %d �� ����մϴ�\n", op1, root->data, op2);
		switch (root->data)
		{
		case '+':
			return op1 + op2;
		case '-':
			return op1 - op2;
		case '*':
			return op1 * op2;
		case '/':
			return op1 / op2;
		
		}

	}

	return 0; 
}

// ���丮 �뷮 ��� 
int calc_dir_size(TreeNode* root)
{
	int left_size, right_size;

	if (root == NULL) return 0;
	left_size = calc_dir_size(root->left);
	right_size = calc_dir_size(root->right);
	return left_size + right_size + root->data;
}

int get_node_count(TreeNode* root)
{

	if (root != NULL)
		return 1 + get_node_count(root->left) + get_node_count(root->right);
	else // �� �κ��� ������ root �� NULL�϶� random value�� ���ϵ�
		return 0;
}

int get_leaf_count(TreeNode* root)
{
	if (root == NULL) {
		return 0;
	}
	else if (root->left == NULL && root->right == NULL) {
		return 1;
	}
	else {
		return get_leaf_count(root->left) + get_leaf_count(root->right);
	}
}

int max_return(int a, int b) {
	return ((a > b) ? a : b);
}

int get_height(TreeNode* root)
{
	if (root == NULL) {
		return 0;
	}
	else {
		return 1 + max_return(get_height(root->left), get_height(root->right));
	}
}

int main(void)
{
	printf("���� = ");
	inorder_iter(root);
	printf("\n");

	printf("%d\n", get_node_count(root));
	printf("%d\n", get_leaf_count(root));
	printf("%d\n", get_height(root));


	return 0;
}