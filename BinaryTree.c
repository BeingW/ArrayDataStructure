//BinaryTree.c    333 lines
#include "BinaryTree.h"
#include <stdlib.h>
#include <memory.h>

void BinaryTree_Create(BinaryTree *binaryTree) {

	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

/*
�Լ� ��Ī : Insert
��    �� : ��带 �����Ѵ�.
��    �� : Ű
��    �� : ��� ��ũ
*/
BinaryNode* BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode *parent = NULL;
	BinaryNode *node;

	node = binaryTree->root;
	while (node != NULL) {
		parent = node;
		if (compare(node + 1, key) > 0) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	memcpy(node + 1, key, size);
	node->left = NULL;
	node->right = NULL;

	if (parent != NULL) {
		if (compare(parent + 1, key) < 0) {
			parent->right = node;
		}
		else
		{
			parent->left = node;
		}
	}
	else {
		binaryTree->root = node;
	}
	binaryTree->length++;
	if (compare(binaryTree->root + 1, key) < 0) {
		binaryTree->balance++;
	}
	else if (compare(binaryTree->root + 1, key) > 0) {
		binaryTree->balance--;
	}
	return node;
}

/*
�Լ� ��Ī : BinaryTree_Delete
��    �� : ��带 �����.
��    �� : Ű
��    �� : ��� ��ũ (=NULL)
*/
BinaryNode* BinaryTree_Delete(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)) {
	BinaryNode *index;
	BinaryNode *ancester = NULL;
	BinaryNode *parent = NULL;
	BinaryNode *child = NULL;
	BinaryNode *decendant = NULL;
	Long flag = 0;

	index = binaryTree->root;
	while (compare(index + 1, key) != 0) {
		ancester = index;
		if (compare(index + 1, key) < 0) {
			index = index->right;
		}
		else {
			index = index->left;
		}
	}
	if (index->right != NULL) {
		child = index->right;
		while (child->left != NULL) {
			parent = child;
			child = child->left;
		}
		decendant = child->right;
	}
	else if (index->left != NULL) {
		child = index->left;
		while (child->right != NULL) {
			parent = child;
			child = child->right;
		}
		decendant = child->left;
	}
	if (parent != NULL) {
		if (index->right != NULL) {
			parent->left = decendant;
			child->left = index->left;
			child->right = index->right;
		}
		else if (index->left != NULL) {
			parent->right = decendant;
			child->left = index->left;
			child->right = index->right;
		}
	}
	if (binaryTree->root != index) {
		if (compare((binaryTree->root) + 1, index + 1) < 0) {
			flag = -1;
		}
		else if (compare(binaryTree->root + 1, index + 1) > 0) {
			flag = 1;
		}
	}
	else {
		if (index->right != NULL) {
			flag = -1;
		}
		else if (index->left != NULL) {
			flag = 1;
		}
	}

	if (compare((binaryTree->root) + 1, index + 1) < 0) {
		ancester->right = child;
	}
	else if (compare((binaryTree->root) + 1, index + 1) > 0) {
		ancester->left = child;
	}
	else {
		binaryTree->root = child;
	}

	if (index != NULL) {
		free(index);
		index = NULL;
	}
	binaryTree->length--;
	if (flag == 1) {
		binaryTree->balance++;
	}
	else if (flag == -1) {
		binaryTree->balance--;
	}
	return index;
}

/*
�Լ� ��Ī : Search
��    �� : ��带 ã�´�.
��    �� : Ű
��    �� : ��� ��ũ
*/
BinaryNode* Search(BinaryTree *binaryTree, void *key, int(*compare)(void*, void*)) {
	BinaryNode *index;

	index = binaryTree->root;
	while (index != NULL && compare(index + 1, key) != 0) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}

	return index;
}

/*
�Լ� ��Ī : MakeBalance
��    �� : Ʈ���� �뷱���� �����.
��    �� : ����
��    �� : ����
*/
void MakeBalance(BinaryTree *binaryTree, size_t size) {
	void(*keys);
	Long count;

	MakeKeys(binaryTree, &keys, &count, size);
	DeleteAllItems(binaryTree);
	MakeTree(binaryTree, keys, count, size);

	if (keys != NULL) {
		free(keys);
	}
}

/*
�Լ� ��Ī : MakeKeys
��    �� : ����� Ű�� Ű�鿡 ���´�.
��    �� : ����
��    �� : Ű��, ����
*/
void MakeKeys(BinaryTree *binaryTree, void *(*keys), Long *count, size_t size) {
	Long position = 0;
	*count = 0;

	*keys = calloc(binaryTree->length, size);
	Node_MakeKeys(binaryTree->root, *keys, count, &position, size);
}

/*
�Լ� ��Ī : Node_MakeKeys
��   �� : �ݺ��ϸ� ����� Ű�� Ű�鿡 ���´�.
��   �� : ����
��   �� : Ű��, ����*/
void Node_MakeKeys(BinaryNode* binaryNode, void(*keys), Long *count, Long *position, size_t size) {

	if (binaryNode != NULL) {
		Node_MakeKeys(binaryNode->left, keys, count, position, size);
		memcpy(((char*)keys) + ((*position)*size), binaryNode + 1, size);

		(*position)++;
		(*count)++;

		Node_MakeKeys(binaryNode->right, keys, count, position, size);
	}
}

/*
�Լ� ��Ī : DeleteAllItems
��    �� : Ʈ���� ��� ��带 �����.
��    �� : ����
��    �� : ����
*/
void DeleteAllItems(BinaryTree *binaryTree) {

	Node_DeleteAllItems(binaryTree->root);

	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

/*
�Լ� ��Ī : Node_DeleteAllItems
��    �� : �ݺ��ϸ� ��� ��带 �����.
��    �� : ����
��    �� : ����
*/
void Node_DeleteAllItems(BinaryNode *node) {

	if (node != NULL) {
		Node_DeleteAllItems(node->left);
		Node_DeleteAllItems(node->right);
		free(node);
	}
}

/*
�Լ� ��Ī : MakeTree
��    �� : Ʈ���� �����.
��    �� : Ű��, ����
��    �� : ��� ��ũ
*/
BinaryNode* MakeTree(BinaryTree *binaryTree, void(*keys), Long count, size_t size) {
	Long middle;

	binaryTree->root = Node_MakeTree(keys, 0, count - 1, size);
	binaryTree->length = count;
	middle = (count) / 2;
	binaryTree->balance = (0 - middle) + (count - 1 - middle);

	return binaryTree->root;
}

/*
�Լ� ��Ī : Node_MakeTree
��    �� : �ݺ��ϸ� Ʈ���� ��带 �����.
��    �� : Ű��, �ο�, ����
��    �� : ��� ��ũ
*/
BinaryNode* Node_MakeTree(void(*keys), Long low, Long high, size_t size) {
	BinaryNode *node = NULL;
	Long middle;

	if (low <= high) {
		middle = (low + high) / 2;
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		memcpy(node + 1, ((char*)keys) + (middle*size), size);
		node->left = Node_MakeTree(keys, low, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, high, size);
	}

	return node;
}

/*
�Լ� ��Ī : BinaryTree_Destroy
��    �� : Ʈ���� �����.
��    �� : ����
��    �� : ����
*/
void BinaryTree_Destroy(BinaryTree *binaryTree) {

	Node_Destroy(binaryTree->root);

	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

/*
�Լ� ��Ī : Node_Destroy
��    �� : �ݺ��ϸ� Ʈ���� ��带 �����.
��    �� : ����
��    �� : ����
*/
void Node_Destroy(BinaryNode *binaryNode) {

	if (binaryNode != NULL) {
		Node_Destroy(binaryNode->left);
		Node_Destroy(binaryNode->right);
		free(binaryNode);
	}
}

/*
�Լ� ��Ī : GetAt
��    �� : ��� ��ũ�� Ű�� ����Ѵ�.
��    �� : ��� ��ũ
��    �� : Ű
*/
void GetAt(BinaryTree *binaryTree, BinaryNode *index, void *key, size_t size) {

	memcpy(key, index + 1, size);
}