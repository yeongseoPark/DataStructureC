#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include <limits.h>

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

/* 중위순회 */
void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d -> ", root->data);
		inorder(root->right);
	}

}

/* 전위순회 */
void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("%d -> ", root->data);
		preorder(root->left);
		preorder(root->right);
	}

}

/* 후위순회 */
void postorder(TreeNode* root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d -> ", root->data);
	}

}

/* 스택으로 중위순회 */
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

// 수식 트리 계산 
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
		printf("%d %c %d 를 계산합니다\n", op1, root->data, op2);
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

// 디렉토리 용량 계산 
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
	else // 이 부분이 없으면 root 가 NULL일때 random value가 리턴됨
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

bool is_balanced(TreeNode* root)
{
	if (root == NULL) return true;
	int left = get_height(root->left);
	int right = get_height(root->right);

	return (left - right <= 1 && left - right >= -1) && is_balanced(root->left) && is_balanced(root->right);
}

int sum_BinaryTree(TreeNode* root)
{
	if (root == NULL) return 0;

	int sum = root->data;

	return sum + sum_BinaryTree(root->left) + sum_BinaryTree(root->right);
}

void print_smaller(TreeNode* root, int val)
{
	if (root == NULL) return;

	if (root->data < val) printf("%d보다 작은 노드 : %d\n", val, root->data);

	print_smaller(root->left, val);
	print_smaller(root->right, val);
}

int return_onechild(TreeNode* root)
{	
	if (root == NULL) return 0;

	if ((root->left && !root->right) || (root->right && !root->left)) {
		return  1 + return_onechild(root->left) + return_onechild(root->right);
	}
	else {
		return 0 + return_onechild(root->left) + return_onechild(root->right);
	}
}


int find_max(TreeNode* root)
{
	if (root == NULL) return INT_MIN;
	if (root->left == NULL && root->right == NULL) return root->data;


	return max(find_max(root->left), find_max(root->right));
}

int find_min(TreeNode* root)
{
	if (root == NULL) return INT_MAX;
	if (root->left == NULL && root->right == NULL) return root->data;


	return min(find_min(root->left), find_min(root->right));
}

int main(void)
{
	printf("중위 = ");
	inorder_iter(root);
	printf("\n");

	
	printf("%d\n", find_max(root));
	printf("%d\n", find_min(root));


	return 0;
}