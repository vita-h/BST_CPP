// BinarySearchTree.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct BstNode
{
	int data;
	BstNode* left;
	BstNode* right;
};

struct Node {
	char data;
	Node *left;
	Node *right;
};

bool IsSubtreeGreater(BstNode *root, int value);
bool IsSubtreeLesser(BstNode *root, int value);

BstNode* GetNewNode(int data) 
{
	BstNode* newNode = new BstNode();
	(*newNode).data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

BstNode* Insert(BstNode* root, int data) 
{
	if (root == NULL) // tree is empty
	{
		root = GetNewNode(data);
	}
	else if (data <= root->data)
	{
		root->left = Insert(root->left, data);
	}
	else
	{
		root->right = Insert(root->right, data);
	}
	return root;
}

bool Search(BstNode* root, int data)
{
	if (root == NULL)
		return false;

	else if (root->data == data)
		return true;

	else if (data <= root->data)
		return Search(root->left, data);

	else
		return Search(root->right, data);
}

int FindMin(BstNode* root)
{
	if (root == NULL)
	{
		cout << "Error: Tree is empty!\n";
		return -1;
	}

	while (root->left != NULL)
	{
		root = root->left;
	}
	return root->data;
}

BstNode* FindMinPtr(BstNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}

	while (root->left != NULL)
	{
		root = root->left;
	}

	return root;
}

int FindMax(BstNode* root) 
{
	if (root == NULL)
	{
		cout << "Error: Tree is empty!\n";
		return -1;
	}
	else if (root->right == NULL)
	{
		return root->data;
	}
	
	return FindMax(root->right);
}

int FindHeight(BstNode* root)
{
	if (root == NULL) 
	{
		return -1;
	}

	return max(FindHeight(root->left), FindHeight(root->right)) + 1;
}

bool isLeaf(BstNode* node)
{
	return (node->left == NULL && node->right == NULL) ? true : false ;
}

void LevelOrder(BstNode *root)
{
	if (root == NULL)
		return;

	queue <BstNode*> Q;
	Q.push(root);
	while (!Q.empty())
	{
		BstNode* current = Q.front();
		cout << current->data << " ";
		if (current->left != NULL) Q.push(current->left);
		if (current->right != NULL) Q.push(current->right);
		Q.pop();
	}
}

void PreOrder(BstNode *root)
{
	cout << root->data << " ";

	if (root->left != NULL)
	{
		PreOrder(root->left);
	}

	if (root->right != NULL)
	{
		PreOrder(root->right);
	}
}

void InOrder(BstNode *root)
{
	if (root->left != NULL)
	{
		InOrder(root->left);
	}
	cout << root->data << " ";
	if (root->right != NULL)
	{
		InOrder(root->right);
	}
}

void PostOrder(BstNode *root)
{
	if (root->left != NULL)
	{
		PostOrder(root->left);
	}
	if (root->right != NULL) 
	{
		PostOrder(root->right);
	}
	cout << root->data << " ";
}

bool IsSubtreeLesser(BstNode *root, int value)
{
	if (root == NULL)
		return true;

	if (root->data <= value && IsSubtreeLesser(root->left, value) && IsSubtreeGreater(root->right, value))
		return true;
	else
		return false;
}

bool IsSubtreeGreater(BstNode *root, int value)
{
	if (root == NULL)
		return true;

	if (root->data > value && IsSubtreeGreater(root->right, value) && IsSubtreeLesser(root->left, value))
		return true;
	else
		return false;
}

bool IsBST(BstNode *root)
{
	if (root == NULL)
		return true;

	if (IsSubtreeGreater(root->right, root->data) && IsSubtreeLesser(root->left, root->data) && IsBST(root->left) && IsBST(root->right))
		return true;
	else
		return false;
}

BstNode* Remove(BstNode* root, int data)
{
	if (root == NULL)
	{
		return root;
	}
	else if (data < root->data)
	{
		root->left = Remove(root->left, data);
	}
	else if (data > root->data)
	{
		root->right = Remove(root->right, data);
	}
	else
	{
		// Case 1 - No children
		if (root->left == NULL && root->right)
		{
			delete root;
			root = NULL;
		}
		// Case 2 - One child
		else if (root->left == NULL) 
		{
			BstNode* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL)
		{
			BstNode* temp = root;
			root = root->left;
			delete temp;
		}
		// Case 3 - Two children
		else
		{
			BstNode* temp = FindMinPtr(root->right);
			root->data = temp->data;
			root->right = Remove(root->right, temp->data);
		}
	}
	return root;
}

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	BstNode* rootPtr;
	rootPtr = NULL;

	rootPtr = Insert(rootPtr, 15);
	rootPtr = Insert(rootPtr, 10); rootPtr = Insert(rootPtr, 11); //rootPtr = Remove(rootPtr, 10);
	rootPtr = Insert(rootPtr, 20);  rootPtr = Insert(rootPtr, 21);
	rootPtr = Insert(rootPtr, 25); rootPtr = Insert(rootPtr, 26);
	rootPtr = Insert(rootPtr, 8); rootPtr = Insert(rootPtr, 9);
	rootPtr = Insert(rootPtr, 12); rootPtr = Insert(rootPtr, 24);
	rootPtr = Insert(rootPtr, 5); 
	

	int number;
	cout << "Enter number to be searched:\n";
	cin >> number;

	std::cout << (Search(rootPtr, number) ? "Found." : "Not found.");

	std::cout << "\n\nMin: " << FindMin(rootPtr);
	std::cout << "\nMax: " << FindMax(rootPtr);
	std::cout << "\nHeight of tree is: " << FindHeight(rootPtr);

	std::cout << "\n\nLevel Order Traversal: \n";
	LevelOrder(rootPtr);

	std::cout << "\n\nPre-order: \n";
	PreOrder(rootPtr);

	std::cout << "\n\nIn-order: \n";
	InOrder(rootPtr);

	std::cout << "\n\nPost-order: \n";
	PostOrder(rootPtr);

	std::cout << "\n\nIs this tree a BST: " << IsBST(rootPtr);

	std::cout << endl << endl;
	return 0;
}