#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

typedef struct {
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
} element;

typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}

void display(TreeNode* p)
{

	if (p!= NULL)
	{
		display(p->left);
		printf("%s : %s ", p->key.word, p->key.meaning);
		display(p->right);
	}
}

TreeNode* search(TreeNode* root, element key)
{
	TreeNode* p = root;

	while (p != NULL)
	{
		if (compare(key, p->key) == 0) return p;

		else if (compare(key, p->key) < 0)
			p = p->left;
		else if (compare(key, p->key) > 0)
			p = p->right;
	}

	return p;
}

TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element key)
{
	if (node == NULL) return new_node(key);

	if (compare(key, node->key) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key) > 0)
		node->right = insert_node(node->right, key);

	return node;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

TreeNode* delete_node(TreeNode* root, element key)
{
	if (root == NULL) return root;

	if (compare(key, root->key) < 0)
		root->left = delete_node(root->left, key);
	if (compare(key, root->key) > 0)
		root->right = delete_node(root->right, key);

	else {
		if (root->left == NULL) {
			TreeNode* tmp = root->right;
			free(root);
			return tmp;
		}
		else if (root->right == NULL) {
			TreeNode* tmp = root->left;
			free(root);
			return tmp;
		}

		TreeNode* tmp = min_value_node(root->right);

		root->key = tmp->key;
		root->right = delete_node(root->right, tmp->key);
	}

	return root;
}

void help()
{
	printf("\n*** i: 입력, d: 삭제, p: 출력, q: 종료 ***\n");
}

int main(void)
{
	char command;
	element e;
	TreeNode* root = NULL;
	TreeNode* tmp;

	do {
		help();
		command = getchar();
		getchar();
		switch (command) {
			case 'i':
				printf("단어 :");
				fgets(e.word, MAX_WORD_SIZE, stdin);
				printf("의미 :");
				fgets(e.meaning, MAX_MEANING_SIZE, stdin);
				root = insert_node(root, e);
				break;
		
			case 'd':
				printf("단어 :");
				fgets(e.word, MAX_WORD_SIZE, stdin);
				root = delete_node(root, e);
				break;
			case 'p':
				display(root);
				printf("\n");
				break;
			case 's':
				printf("단어");
				fgets(e.word, MAX_WORD_SIZE, stdin);
				tmp = search(root, e);
				if (tmp != NULL)
					printf("의미 :%s\n", e.meaning);
				break;
		}
	} while (command != 'q');
	return 0;
}