#include<stdio.h>
#include<stdlib.h>

//BST 노드의 구성
struct node {
	int data;
	struct node* left;
	struct node* right;
};

//BST의 핵심 root
struct node* root = 0;


struct node* createNode(int n)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	newNode->data = n;
	newNode->left = 0;
	newNode->right = 0;

	return newNode;
}


void addNode(int n)
{
	struct node* newNode = createNode(n);

	if (root == 0)
	{
		root = newNode;
		return;
	}
	struct node* cur = root;
	while (1)
	{
		if (cur->data > n)
		{
			if (cur->left == 0)
			{
				cur->left = newNode;
				return;
			}
			cur = cur->left;
		}
		else
		{
			if (cur->right == 0)
			{
				cur->right = newNode;
				return;
			}
			cur = cur->right;
		}
	}
}

//n의 값이 들어 있는 노드가 BST에 있는지 확인
// 있으면 1반환 , 없으면 0반환 
int searchNode(int n)
{
	struct node* cur = root;
	
	while (1)
	{
		if (cur == 0)
		{
			return 0;
		}

		if (cur->data > n)
		{
			if (cur->data == n)
			{
				return 1;
			}
			cur = cur->left;
		}
		else
		{
			if (cur->data == n)
			{
				return 1;
			}
			cur = cur->right;
		}

	}
}

//모든 노드를 다 돌고 오는 traversal 함수
void inorderTraversal(struct node* traversal)
{
	if (traversal == 0)
	{
		return;
	}
	inorderTraversal(traversal->left);
	printf("%d\n", traversal->data);
	inorderTraversal(traversal->right);

}


struct node *findLeast(struct node *node)
{
	struct node *cur = node;
	while (cur->left != 0)
	{
		cur = cur->left;
	}
	return cur;
}


//n이 들어있는 노드를 삭제해주는 함수
void deleteNode(struct node * node, int key)
{
	
		if (node == 0)
		{
			return 0;
		}
		if (key == node->data)
		{
			// found match
			if (node->left == 0 && node->right == 0)
			{
				free(node);
				return 0;
			}
			else if (node->left == 0)
			{
				struct node *ret = node->right;
				free(node);
				return ret;
			}
			else if (node->right == 0)
			{
				struct node *ret = node->left;
				free(node);
				return ret;
			}
			else
			{
				struct node *toReplace = findLeast(node->right);
				node->data = toReplace->data;
				node->right = deleteNode(node->right, toReplace->data);
				return node;
			}
		}
		else if (key < node->data)
		{
			node->left = deleteNode(node->left, key);
			return node;
		}
		else
		{
			node->right = deleteNode(node->right, key);
			return node;
		}
	
}


int main(void)
{
	addNode(3);
	addNode(1);
	addNode(5);
	addNode(6);

	inorderTraversal(root);
	
	deleteNode(root, 5);

	inorderTraversal(root);

	return 0;
}