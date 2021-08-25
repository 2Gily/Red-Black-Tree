/****************************************************/
/*                �˰��� 15��                      */
/*                Red Black Tree ����               */
/*                ���� : ������,���ֿ�,�̱���         */
/****************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX_SIZE 10000
#define MYFLUSH { while(getchar()!='\n'); }
#define TRUE 1
#define FALSE 0

// �����Ʈ������ ����� ���� �Ӽ�
typedef enum colorType {
	red = 0,
	black = 1
}nodeColor;

// ��� Ű��
typedef int nodeKey;

// Ʈ������� ���� (��, ��, �¿� ���, �θ���)
typedef struct TreeNode {
	nodeColor color;
	nodeKey key;
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* parent;
}TreeNode;

// Ʈ������ (��Ʈ���� �ҳ��)
typedef struct Tree {
	TreeNode* nil;
	TreeNode* root;
}Tree;

//���� Ž�� Ʈ�� (��, �¿���)
typedef struct BSNode {
	int key;
	struct BSNode *left, *right;
}BSNode;

int inputMenu(void);									// �޴��� �Է¹���
void inputData(int* userData);							// Ű���� ����
void inorder(TreeNode* root, TreeNode*nil);				// ����
void preorder(TreeNode* root, TreeNode* nil);			// ����
void postorder(TreeNode* root, TreeNode* nil);			// ����
void insert_node(Tree* T, nodeKey key);					// ��� �Է�
TreeNode* new_node(nodeKey item, TreeNode* parent);		// ��� ����
TreeNode* delete_node(Tree *T, TreeNode* z);			// ��� ����
TreeNode* min_value_node(TreeNode* node, Tree* T);		// ���� ���� Ű�� �˻�
TreeNode* search(Tree* T, nodeKey key);					// Ư�� Ű�� �˻�
int emptyCheck(Tree* T);								// Ʈ���� ����ִ��� üũ
int getLevelCount(TreeNode* node, Tree* T);				// Ʈ�� ���� ī��Ʈ
void printLevel(TreeNode* node, int level, Tree* T);	// ���� ���
void printElements(Tree* T);							// �������� ��� ���
void write(int pp, int offset, TreeNode* root, char* side, int level, Tree* T);// Ʈ�� ���
void displayTree(Tree* T);								// Ʈ�� ǥ��
void checkDoubleRed(Tree* T, nodeKey key);				// ������ üũ �� ����
Tree* createTree();										// Ʈ�� ����
void right_rotate(Tree* T, TreeNode* x);				// ���� ȸ������
void left_rotate(Tree* T, TreeNode* x);					// ���� ȸ������
TreeNode *successor(Tree *T, TreeNode *x);				// ���� �������� ū ��带 ã�Ƽ� ��ȯ
void fix_up_node(Tree* T, TreeNode* x);					// ���������� ����� ����

/*********************************************************************************************/
/*                             ���� Ž�� Ʈ�� ���                                            */
/*********************************************************************************************/
void BS_inorder(BSNode *root);
void BS_preorder(BSNode *root);
void BS_postorder(BSNode *root);
BSNode *BS_insert_node(BSNode *node, int key);
BSNode *BS_new_node(int item);
BSNode *BS_delete_node(BSNode *root, int key);
BSNode *BS_min_value_node(BSNode *node);
BSNode *BS_search(BSNode  *node, int key);
int BS_emptyCheck(BSNode *root);
int BS_getLevelCount(BSNode *node);
void BS_printLevel(BSNode *node, int level);
void BS_printElements(BSNode *node);
void BS_write(int pp, int offset, BSNode *root, char* side, int level);
void BS_displayTree(BSNode *root);
/*********************************************************************************************/
/*                             ���� Ž�� Ʈ�� ���                                            */
/*********************************************************************************************/

int** A;
int** B;
int** C;

int main(void)
{
	int userData;
	int i;
	Tree* T = createTree();
	TreeNode *target_delete;
	TreeNode *deleted_node;
	BSNode *bst_root = NULL;

	clock_t startRB , finishRB ;
	clock_t startBS , finishBS ;
	double resultRB , resultBS ;
	int random_num[MAX_SIZE];
	srand(time(NULL));

	printf("���α׷� ����\n\n");

	while ("Tree")
	{
		startRB = 0.0, finishRB = 0.0;
		startBS = 0.0, finishBS = 0.0;
		resultRB = 0.0, resultBS = 0.0;

		switch (inputMenu())
		{
		case 1:
			printf("**************************************\n");
			printf("   << ���� >>\n");

			inputData(&userData);

			if (T->root != T->nil && search(T, userData) != NULL)			// RBƮ�� üũ
			{
				printf(" ���Խ���[RedBlack]\n");
				printf(" �ߺ��� Ű���� �����մϴ�.[RedBlack]\n");
				printf("**************************************\n");
				break;
			}
			if (BS_search(bst_root, userData) != NULL && bst_root != NULL)	// ����Ž��Ʈ�� üũ
			{
				printf(" ���Խ���[BinarySearch]\n");
				printf(" �ߺ��� Ű���� �����մϴ�.[BinarySearch]\n");
				printf("**************************************\n");
				break;
			}

			startRB = clock();
			insert_node(T, userData);		// �����Ʈ�� ��� ���� �� ���� ����
			checkDoubleRed(T, userData);	// �� �� ���� ���带 üũ�Ͽ� ����
			finishRB = clock();
			printf(" ���ԿϷ�[RedBlack]\n");

			startBS = clock();
			bst_root = BS_insert_node(bst_root, userData); // ����Ž��Ʈ�� ��� ���� �� ���� ����
			finishBS = clock();
			printf(" ���ԿϷ�[BinarySearch]\n");

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree ���� ���� : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree ���� ���� : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;
		case 2:
			printf("**************************************\n");
			printf("   << ���� >>\n");

			if (emptyCheck(T) == TRUE) break;			// RBƮ�� üũ
			if (BS_emptyCheck(bst_root) == TRUE) break; // ����Ž��Ʈ�� üũ
			else
			{
				inputData(&userData);
				target_delete = search(T, userData);	// ������ ��带 ã��

				if (target_delete != NULL)
				{
					startRB = clock();
					deleted_node = delete_node(T, target_delete);	// ��� ���� �� ����
					finishRB = clock();
					printf(" ���� ����[RedBlack]\n");
					free(deleted_node);

					if (BS_search(bst_root, userData) != NULL)		// ����Ž��Ʈ�� ����
					{
						startBS = clock();
						bst_root = BS_delete_node(bst_root, userData);
						finishBS = clock();
						printf(" ���� ����[BinarySearch]\n");

						resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
						resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
						printf(" \n\n Red-Black Tree ���� ���� : %.20lf\n", resultRB);
						printf(" \n Binary Search Tree ���� ���� : %.20lf\n\n", resultBS);

						printf("**************************************\n");
						break;
					}
					else if (BS_search(bst_root, userData) == NULL)
					{
						printf(" ���� ����[BinarySearch]\n");
						printf("**************************************\n");
						break;
					}
					break;
				}
				else if (target_delete == NULL)
				{
					printf(" ���� ����[RedBlack]\n");
					printf("**************************************\n");
					break;
				}
			}

		case 3:
			printf("***********************\n");
			printf(" ������ȸ[RedBlack]\n");

			if (emptyCheck(T) == TRUE) break;			// RBƮ�� üũ
			if (BS_emptyCheck(bst_root) == TRUE) break; // ����Ʈ��Ž�� üũ

			printf("[RedBlack] >> ");
			startRB = clock();
			inorder(T->root, T->nil);
			finishRB = clock();
			printf("\n");

			printf("[BinarySearch] >> ");
			startBS = clock();
			BS_inorder(bst_root);
			finishBS = clock();

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree ���� ��ȸ : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree ���� ��ȸ : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;

		case 4:
			printf("***********************\n");
			printf(" ������ȸ\n");

			if (emptyCheck(T) == TRUE) break;
			if (BS_emptyCheck(bst_root) == TRUE) break;

			printf("[RedBlack] >> ");
			startRB = clock();
			preorder(T->root, T->nil);
			finishRB = clock();
			printf("\n");

			printf("[BinarySearch] >> ");
			startBS = clock();
			BS_preorder(bst_root);
			finishBS = clock();

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree ���� ��ȸ : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree ���� ��ȸ : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;

		case 5:
			printf("***********************\n");
			printf(" ������ȸ\n");

			if (emptyCheck(T) == TRUE) break;
			if (BS_emptyCheck(bst_root) == TRUE) break;

			printf("[RedBlack] >> ");
			startRB = clock();
			postorder(T->root, T->nil);
			finishRB = clock();
			printf("\n");

			printf("[BinarySearch] >> ");
			startBS = clock();
			BS_postorder(bst_root);
			finishBS = clock();

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree ���� ��ȸ : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree ���� ��ȸ : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;


		case 6:
			printf("***********************\n");
			printf(" ������ȸ\n");

			if (emptyCheck(T) == TRUE) break;
			if (BS_emptyCheck(bst_root) == TRUE) break;

			printf("[RedBlack] >> ");
			startRB = clock();
			printElements(T);
			finishRB = clock();
			printf("\n");

			printf("[BinarySearch] >> ");
			startBS = clock();
			BS_printElements(bst_root);
			finishBS = clock();

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree ���� ��ȸ : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree ���� ��ȸ : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;

		case 7:
			printf("***********************\n");
			printf("   << Ž�� >>\n");

			if (emptyCheck(T) == TRUE) break;
			if (BS_emptyCheck(bst_root) == TRUE) break;

			inputData(&userData);

			startRB = clock();
			if (search(T, userData) != NULL)							// RBƮ�� Ž��
				printf("Ű��: [%d]�� �ֽ��ϴ�.[RedBlack]\n", userData);
			else printf("Ű��: [%d]�� �����ϴ�.[RedBlack]\n", userData);
			finishRB = clock();

			startBS = clock();
			if (BS_search(bst_root, userData) != NULL)					// ����Ž��Ʈ�� Ž��
				printf("Ű��: [%d]�� �ֽ��ϴ�.[BinarySearch]\n", userData);
			else printf("Ű��: [%d]�� �����ϴ�.[BinarySearch]\n", userData);
			finishBS = clock();

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree Ž�� : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree Ž�� : %.20lf\n\n", resultBS);


			printf("**************************************\n");
			break;

		case 8:
			printf("\n**************************************");
			printf("\n[RedBlack] Ʈ�� ���\n");
			printf("**************************************\n");
			displayTree(T);
			printf("**************************************\n");
			printf("[BinarySearch] Ʈ�� ���\n");
			printf("**************************************\n");
			BS_displayTree(bst_root);
			break;

		case 9:
			printf("**************************************\n");
			printf("   << �־��� ��� : ����(N = %d) >>\n",MAX_SIZE);
			printf("**************************************\n");
			//////////////////////////////////////////////////////////////////////////////////////

			for (i = 0; i < MAX_SIZE; i++)
			{
				random_num[i] = i+1;
				//random_num[i] = (rand() % MAX_SIZE) + 1;
				//printf("random_num[i] : %d\n", random_num[i]);
			}

			startRB = clock();
			for (i = 0; i < MAX_SIZE; i++)
			{
				if (T->root != T->nil && search(T, random_num[i]) != NULL) break;
				insert_node(T, random_num[i]);
				checkDoubleRed(T, random_num[i]);
			}
			finishRB = clock();

			startBS = clock();
			for (i = 0; i < MAX_SIZE; i++)
			{
				if (BS_search(bst_root, random_num[i]) != NULL && bst_root != NULL) break;
				bst_root = BS_insert_node(bst_root, random_num[i]);
			}
			finishBS = clock();

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n Red-Black Tree ���� ���� : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree ���� ���� : %.20lf\n", resultBS);

			break;

		case 0:
			printf("**************************************\n");
			printf("   << ���� >>\n");
			printf("**************************************\n");
			exit(0);

		default:
			printf("**************************************\n");
			printf(" �߸� �Է��Ͽ����ϴ�.\n");
			printf("**************************************\n");
			MYFLUSH;
			break;
		}
	}

}

int inputMenu(void)
{
	int menu_number;

	printf("--------------------------------------\n");
	printf(" 1. ����\n");
	printf(" 2. ����\n");
	printf(" 3. ������ȸ\n");
	printf(" 4. ������ȸ\n");
	printf(" 5. ������ȸ\n");
	printf(" 6. ������ȸ\n");
	printf(" 7. Ž��\n");
	printf(" 8. Ʈ�� ���\n");
	printf(" 9. ���� ����(1~%d)\n",MAX_SIZE);
	printf(" 0. ����\n");
	printf("--------------------------------------\n");
	printf(" �޴� �Է� : ");
	int a = scanf("%d", &menu_number);
	printf("--------------------------------------\n");

	return menu_number;
}
void inputData(int* userData)
{
	printf("\n");
	printf(" key �� �Է�\n >> ");
	int a = scanf("%d", userData);
	printf("\n");
}
// ���� ��ȸ
void inorder(TreeNode* root, TreeNode* nil)
{
	char color;

	if (root != nil)
	{
		inorder(root->left, nil);   // ���ʼ���Ʈ�� ��ȸ

		if (root->color == 0) color = 'R';
		else if (root->color == 1) color = 'B';
		else color = ' ';

		printf("[%d][%c] ", root->key, color);    // ��� �湮
		inorder(root->right, nil);   // �����ʼ���Ʈ�� ��ȸ
	}
}
// ���� ��ȸ
void preorder(TreeNode* root, TreeNode* nil)
{
	char color;

	if (root != nil)
	{
		if (root->color == 0) color = 'R';
		else if (root->color == 1) color = 'B';
		else color = ' ';

		printf("[%d][%c] ", root->key, color);    // ��� �湮
		preorder(root->left, nil);   // ���ʼ���Ʈ�� ��ȸ
		preorder(root->right, nil);   // �����ʼ���Ʈ�� ��ȸ
	}
}
// ���� ��ȸ
void postorder(TreeNode* root, TreeNode* nil)
{
	char color;

	if (root != nil)
	{
		postorder(root->left, nil);   // ���� ���� Ʈ�� ��ȸ
		postorder(root->right, nil);   // ������ ���� Ʈ�� ��ȸ

		if (root->color == 0) color = 'R';
		else if (root->color == 1) color = 'B';
		else color = ' ';

		printf("[%d][%c] ", root->key, color);    // ��� �湮
	}
}

void insert_node(Tree* T, nodeKey key)	// ����� ��� ���� �� ���� ����
{
	TreeNode* node = T->root;
	TreeNode* nil = T->nil;
	// Ʈ���� ��Ʈ�� nil�̸� ��Ʈ�� ���� ����� �ִ´�.
	if (node == nil)
	{
		T->root = new_node(key, NULL);
		T->root->left = T->nil;
		T->root->right = T->nil;
		T->root->parent = T->nil;
		return;
	}
	// �׷��� ������ ��ȯ������ Ʈ���� ��������.
	TreeNode* newnode = new_node(key, node);
	newnode->left = nil;
	newnode->right = nil;
	while (node != nil) {
		newnode->parent = node;
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
	}
	if (newnode->parent->key < key)
		newnode->parent->right = newnode;
	else
		newnode->parent->left = newnode;
}

TreeNode* delete_node(Tree *T, TreeNode* z)
{
	TreeNode* x = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* y = (TreeNode*)malloc(sizeof(TreeNode));

	if (z->left == T->nil || z->right == T->nil) // ������ ��� z�� ����, ������ �ڽ��� NULL�� �ƴ϶�� ��, �ڽ��� ���ٸ�
	{
		y = z; // y�� z�� �����ϰ�
	}
	else y = successor(T, z); // �ڽ��� �ִٸ�, z�� Successor�� ã�Ƽ� y�� �����Ѵ�. BST���� Successorã�� ������ ����

	if (y->left != T->nil) // ���� ������ ��ġ�� y�� �ڽ��� �ϳ��̰ų� ����.
	{					   // Successor�� �ڽĳ�尡 �� ���� �� ����. y�� ���� �ڽ��� null�� �ƴ϶��
		x = y->left; // y�� ���� �ڽ��� x��
	}
	else x = y->right; // �׷��� �ʴٸ�, y�� ������ �ڽ��� x�� �����Ѵ�.

	x->parent = y->parent; // �״��� y�� �θ� x�� �θ�� �����Ѵ�.

	if (y->parent == T->nil) // ����, y�� �θ� NULL�̶��
	{
		T->root = x; // x�� Ʈ���� root�� �����Ѵ�.
	}
	else if (y == y->parent->left) // y�� �θ��尡 NULL�� �ƴϰ�, y�� y�� �θ��� ���� �ڽĳ����
	{
		y->parent->left = x; // ����� x�� y�� �θ��� ���� �ڽĳ��� �����Ѵ�.
	}
	else y->parent->right = x; // y�� y�� �θ��� ������ �ڽĳ����, ����� x�� �θ����� ������ �ڽ����� �����Ѵ�. ��������� ������ ��带 �����ϴ� �۾��̴�.

	if (y != z) //�����Ϸ��� ��� ��� Successor�� ������ ��� y�� z�� �ٸ���. ���� Successor y����� �����͸� ī�����ִ� �۾��� �ʿ��ϴ�.
	{
		z->key = y->key; // ��������� ������ Binary Search Tree�� ������ ������� ����Ǵ� ���� �����̴�.
						 // ������ ��� y�� red ��� ���ٸ�, Red Black Tree�� ��Ģ�� ���� ���� �ʴ´�.
	}

	if (y->color == black)
	{
		fix_up_node(T, x);// RB - Delete - FixUP(T,x) �Լ� �κ�
	}

	return y;
}

void fix_up_node(Tree *T, TreeNode* x)
{
	TreeNode* w = (TreeNode*)malloc(sizeof(TreeNode));

	while (x != T->root && x->color == black) // ���� x�� ��Ʈ����̰ų�, x�� �������� While���� ���������� x�� BLACK���� ������ְ� �����ϸ� �ȴ�.
	{
		if (x == x->parent->left)			 // While�� �ȿ����� ũ�� �ѷ� ���������� �ȴ�. ���� x�� x�� �θ����� ���� �ڽ��̶�� Case 1, 2, 3, 4�� �ش��ϸ�
		{									//  �θ����� ������ �ڽ��̶�� Case 5, 6, 7, 8�� �ش��Ѵ�.
			w = x->parent->right;

			if (w->color == red)			// ���� ����� w��尡 RED�� ��찡 Case 1�� �ش��Ѵ�.
			{
				w->color = black;			// Case1�� ��� w��带 BLACK���� �����
				x->parent->color = red;		//  x�� �θ��� ��带 RED�� ���� ����
				left_rotate(T, x->parent);	// x�� �θ��� �������� LEFT-ROTATE�Ѵ�
				w = x->parent->right;		// ���ο� w��  x�� �θ����� right�� �ǹǷ� ���� �����Ѵ�
			}								// ���ο� w���� BLACK �̹Ƿ�(x�� �θ��尡 RED�� �����) �ٽ� While������ ������ ��, Case2, 3, 4�� ���� �ȴ�.

			if (w->left->color == black && w->right->color == black) // Case 2, 3, 4�� �����ϰ� �ȴ�. w�� ����, ������ �ڽĳ�尡 �Ѵ� BLACK�� ��� Case2�� �ش��Ѵ�.
			{														 // w�� x�� ���� black�� �ϳ��� ��� �θ� ��忡�� �����Ѵ�.
				w->color = red;										 // �׷��� �ϱ� ���ؼ� w�� RED��尡 �ǰ�
				x = x->parent;										 // x�� �θ��带 x�� ����� �ش�.
			}													     // x�� �θ��尡 RED���ٸ� �ٽ� While���� ���� �ʰ� x�� RED�� ���� �ڿ� �����ϸ� �ǰ�
																	 // x�� �θ��尡 BLACK�̾��ٸ� x�� x�� �θ���� ���� double-black ��尡 �� x�� �ٽ� �ݺ��ؼ� ó�����ָ� �ȴ�.

			else if (w->right->color == black) // w�� ������ �ڽ��� BLACK�̰�, ���� �ڽ��� RED�� ��� Case 3�� �ش��Ѵ�.
			{
				w->left->color = black;        // RIGHT-ROTATE�� ����� �� ����� ���� ��ȯ�ϰ�
				w->color = red;				   // (w�� RED��, w�� ���� �ڽĳ�带 BLACK���� �ٲٰ�)
				right_rotate(T, w);			   // w�� �������� RIGHT-ROTATE �Ѵ�.
				w = x->parent->right;		   // �̷��� �Ǹ� w�� x�� �θ����� ���ο� ������ �ڽĳ�尡 �ǰ�, �װ��� ���� RED�̴�. �׸��� Case 4�� �ٷ� �Ѿ� ����.
			}
			else
			{
				w->color = x->parent->color;	// LEFT-ROTATE�� ����� �� ����� ���� ��ȯ�Ѵ�. w�� ���� x�� �θ����� ������ �ٲٰ�
				x->parent->color = black;		// x�� �θ��带 BLACK���� �ٲ۴�.
				w->right->color = black;		// w�� ������ �ڽ��� ���� BLACK���� �ٲ۴�.
				left_rotate(T, x->parent);		// �� ���� p[x]�� �������� LEFT-ROTATE�� �����Ѵ�.
				x = T->root;					// x��� ������ ������ root[T]�� �����Ͽ� Case 4�� ������ while���� ����ǵ��� �Ѵ�.
			}									// ���� Ʈ������ ��ȭ�� ����. Ʈ���� ��Ʈ�� ���Ѱ��� �ƴϴ�.
		}
		else // Case 5, 6, 7, 8�� ��Ī������ ó���Ѵ�. x�� x�� �θ����� ������ �ڽ��� ����̴�.
		{
			w = x->parent->left;

			if (w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				right_rotate(T, x->parent);
				w = x->parent->left;
			}

			if (w->right->color == black && w->left->color == black)
			{
				w->color = red;
				x = x->parent;
			}
			else if (w->left->color == black)
			{
				w->right->color = black;
				w->color = red;
				left_rotate(T, w);
				w = x->parent->left;
			}
			else {
				w->color = x->parent->color;
				x->parent->color = black;
				w->left->color = black;
				right_rotate(T, x->parent);
				x = T->root;
			}
		}

	}
	x->color = black; // Ʈ���� ��Ʈ�� ���� BLACK���� �����ϴ� ���� ���� �ص� ������ ���� �ʴ´�.
}

TreeNode* new_node(nodeKey item, TreeNode* parent)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->parent = parent;
	temp->color = red;
	if (parent == NULL)
	{
		temp->color = black;
	}
	return temp;
}

TreeNode* min_value_node(TreeNode* node, Tree* T)
{
	TreeNode* current = node;
	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != T->nil)
		current = current->left;

	return current;
}

TreeNode* search(Tree* T, nodeKey key)
{
	TreeNode *node = T->root;
	node = T->root;
	while (node != T->nil)
	{
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

int emptyCheck(Tree* T)
{
	if (T->root == T->nil)
	{
		printf("**************************************\n");
		printf(" ��Ʈ��尡 �����ϴ�.\n");
		printf("**************************************\n\n");
		return TRUE;
	}
	else return FALSE;
}
int getLevelCount(TreeNode*node, Tree* T) // ����� �ִ� ���̸� ã�� �Լ�
{
	if (node == T->nil)
	{
		return 0;
	}
	int leftMaxLevel = 1 + getLevelCount(node->left, T);
	int rightMaxLevel = 1 + getLevelCount(node->right, T);
	if (leftMaxLevel > rightMaxLevel)
	{
		return leftMaxLevel;
	}
	else
	{
		return rightMaxLevel;
	}
}

void printLevel(TreeNode* node, int level, Tree* T) // ������ȸ ������� ��� ��Ʈ ��Ʈ���� ���ʴ�� ���, ������ �̿��Ѵ�.
{
	char color;

	if (node != T->nil && level == 0)
	{
		if (node->color == 0) color = 'R';
		else if (node->color == 1) color = 'B';
		else color = ' ';

		printf("[%d][%c] ", node->key, color);
	}
	else if (node != T->nil)
	{
		printLevel(node->left, level - 1, T);
		printLevel(node->right, level - 1, T);
	}
}

void printElements(Tree* T) // ���� 1���� ���� n���� ���ʴ�� printLevel �Լ��� �����Ͽ� �ش� ������ �־��ش�.
{
	int i;
	int levelCount = getLevelCount(T->root, T);
	for (i = 0; i < levelCount; i++)
	{
		printLevel(T->root, i, T);
	}
}

void displayTree(Tree* T)
{
	TreeNode* root = T->root;
	int i, j;
	int height = getLevelCount(root, T);
	int nn = (int)pow(2, height + 1) - 1;
	char color;

	A = NULL;
	B = NULL;
	A = (int**)malloc((height + 1 + 1) * sizeof(int*));
	B = (int**)malloc((height + 1 + 1) * sizeof(int*));

	for (int i = 1; i <= height + 1; i++)
	{
		A[i] = (int*)malloc((nn + 1) * sizeof(int));
		B[i] = (int*)malloc((nn + 1) * sizeof(int));
	}

	for (i = 1; i <= height + 1; i++)
	{
		for (j = 1; j <= nn; j++)
		{
			A[i][j] = 0;
			B[i][j] = 0;
		}
	}

	write(nn + 1, (nn + 1) / 2, root, "left", 1, T);

	for (i = 1; i <= height + 1; i++)
	{
		for (j = 1; j <= nn; j++)
		{
			if (B[i][j] == 0) color = 'R';
			else if (B[i][j] == 1) color = 'B';
			else color = ' ';

			if (A[i][j] != 0) printf("%d[%c]", A[i][j], color);
			else printf("   ");
		}
		printf("\n\n\n");
	}
	for (i = height + 1; i >= 1; i--)
	{
		free(A[i]);
		free(B[i]);
	}
	free(A);
	free(B);
	return;
}

void write(int pp, int offset, TreeNode* root, char* side, int level, Tree* T)
{
	if (root == T->nil) return;

	if (strcmp(side, "left") == 0)
	{
		A[level][pp - offset] = root->key;
		B[level][pp - offset] = root->color;
		write(pp - offset, offset / 2, root->left, "left", level + 1, T);
		write(pp - offset, offset / 2, root->right, "right", level + 1, T);
	}
	else
	{
		A[level][pp + offset] = root->key;
		B[level][pp + offset] = root->color;
		write(pp + offset, offset / 2, root->left, "left", level + 1, T);
		write(pp + offset, offset / 2, root->right, "right", level + 1, T);
	}
}

void checkDoubleRed(Tree* T, nodeKey key)
{
	TreeNode* me = search(T, key);
	TreeNode* uncle = (TreeNode*)malloc(sizeof(TreeNode));
	while (me->parent->color == red)
	{
		if (me->parent == me->parent->parent->left)					// �� �θ� �θ��� �θ��� �����ڽ��϶�
		{
			uncle = me->parent->parent->right;
			if (uncle->color == red)								// �θ��� ������尡 �����϶� recoloring����
			{
				me->parent->color = black;
				uncle->color = black;
				me->parent->parent->color = red;
				me = me->parent->parent;							// recoloring�� ����� �ٽ� doubleRed�� �߻��� ��� �ذ��ϱ����� ������ġ�� �θ��� �θ�� �ű�
			}
			else if (me == me->parent->right) {						// ���� �θ��� ������ �ڽ��϶��� restructuring
				me = me->parent;
				left_rotate(T, me);
			}
			else
			{
				me->parent->color = black;
				me->parent->parent->color = red;
				right_rotate(T, me->parent->parent);
			}
		}
		else {														// �� �θ� �θ��� �θ��� �������ڽ��϶�
			uncle = me->parent->parent->left;
			if (uncle->color == red)								// �θ��� ������尡 �����϶� recoloring����
			{
				me->parent->color = black;
				uncle->color = black;
				me->parent->parent->color = red;
				me = me->parent->parent;							// recoloring�� ����� �ٽ� doubleRed�� �߻��� ��� �ذ��ϱ����� ������ġ�� �θ��� �θ�� �ű�
			}
			else if (me == me->parent->left) {						// ���� �θ��� ������ �ڽ��϶��� restructuring
				me = me->parent;
				right_rotate(T, me);
			}
			else
			{
				me->parent->color = black;
				me->parent->parent->color = red;
				left_rotate(T, me->parent->parent);
			}
		}
	}
	T->root->color = black;
}

Tree* createTree() {
	Tree* T = (Tree*)malloc(sizeof(Tree));
	TreeNode* Nil = (TreeNode*)malloc(sizeof(TreeNode));
	Nil->color = black;
	T->root = Nil;
	T->nil = Nil;
	return T;
}

void right_rotate(Tree* T, TreeNode* y) {
	TreeNode* x = (TreeNode*)malloc(sizeof(TreeNode));
	x = y->left;
	y->left = x->right;
	if (x->right != T->nil)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == T->nil)
		T->root = x;
	else if (y == y->parent->right)
		y->parent->right = x;
	else
		y->parent->left = x;
	x->right = y;
	y->parent = x;
}

void left_rotate(Tree* T, TreeNode* x)
{
	TreeNode* y = (TreeNode*)malloc(sizeof(TreeNode));
	y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == T->nil)
		T->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

TreeNode *successor(Tree *T, TreeNode *x)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));

	if (x->right != T->nil) {
		return min_value_node(x->right, T);
	}
	temp = x->parent;
	while (temp != T->nil && x == temp->right) {
		x = temp;
		temp = temp->parent;
	}

	return temp;
}

/*********************************************************************************************/
/*                             ���� Ž�� Ʈ�� ���                                            */
/*********************************************************************************************/

// ���� ��ȸ
void BS_inorder(BSNode *root)
{
	if (root)
	{
		BS_inorder(root->left);	// ���ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root->key); 	// ��� �湮
		BS_inorder(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}
// ���� ��ȸ
void BS_preorder(BSNode *root)
{
	if (root)
	{
		printf("[%d] ", root->key); 	// ��� �湮
		BS_preorder(root->left);	// ���ʼ���Ʈ�� ��ȸ
		BS_preorder(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}
// ���� ��ȸ
void BS_postorder(BSNode *root)
{
	if (root)
	{
		BS_postorder(root->left);	// ���� ���� Ʈ�� ��ȸ
		BS_postorder(root->right);	// ������ ���� Ʈ�� ��ȸ
		printf("[%d] ", root->key); 	// ��� �湮
	}
}

BSNode *BS_insert_node(BSNode *node, int key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return BS_new_node(key);
	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key < node->key)
		node->left = BS_insert_node(node->left, key);
	else if (key > node->key)
		node->right = BS_insert_node(node->right, key);

	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}

BSNode *BS_new_node(int item)
{
	BSNode * temp = (BSNode *)malloc(sizeof(BSNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

BSNode *BS_delete_node(BSNode *root, int key)
{
	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->key)
		root->left = BS_delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->key)
		root->right = BS_delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
		if (root->left == NULL) {
			BSNode * temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			BSNode * temp = root->left;
			free(root);
			return temp;
		}
		// �� ��° ���
		BSNode * temp = BS_min_value_node(root->right);
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = BS_delete_node(root->right, temp->key);
	}
	return root;
}

BSNode *BS_min_value_node(BSNode *node)
{
	BSNode * current = node;
	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}

BSNode *BS_search(BSNode *node, int key)
{
	while (node != NULL) {
		if (key == node->key) return node;
		else if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

int BS_emptyCheck(BSNode *root)
{
	if (root == NULL)
	{
		printf("-----------------\n");
		printf(" ��Ʈ��尡 �����ϴ�.\n");
		printf("-----------------\n\n");
		return TRUE;
	}
	else return FALSE;
}
int BS_getLevelCount(BSNode *node) // ����� �ִ� ���̸� ã�� �Լ�
{
	if (node == NULL)
	{
		return 0;
	}
	int leftMaxLevel = 1 + BS_getLevelCount(node->left);
	int rightMaxLevel = 1 + BS_getLevelCount(node->right);
	if (leftMaxLevel > rightMaxLevel)
	{
		return leftMaxLevel;
	}
	else
	{
		return rightMaxLevel;
	}
}

void BS_printLevel(BSNode *node, int level) // ������ȸ ������� ��� ��Ʈ ��Ʈ���� ���ʴ�� ���, ������ �̿��Ѵ�.
{
	if (node != NULL && level == 0)
	{
		printf("[%d] ", node->key);
	}
	else if (node != NULL)
	{
		BS_printLevel(node->left, level - 1);
		BS_printLevel(node->right, level - 1);
	}
}

void BS_printElements(BSNode *node) // ���� 1���� ���� n���� ���ʴ�� printLevel �Լ��� �����Ͽ� �ش� ������ �־��ش�.
{
	int i;
	int levelCount = BS_getLevelCount(node);
	for (i = 0; i < levelCount; i++)
	{
		BS_printLevel(node, i);
	}
}

void BS_displayTree(BSNode *root)
{
	int i, j;
	int height = BS_getLevelCount(root);
	int nn = (int)pow(2, height + 1) - 1;

	C = NULL;
	C = (int **)malloc((height + 1 + 1) * sizeof(int *));

	for (int i = 1; i <= height + 1; i++)
	{
		C[i] = (int *)malloc((nn + 1) * sizeof(int));
	}

	for (i = 1; i <= height + 1; i++)
	{
		for (j = 1; j <= nn; j++)
		{
			C[i][j] = 0;
		}
	}

	BS_write(nn + 1, (nn + 1) / 2, root, "left", 1);

	for (i = 1; i <= height + 1; i++)
	{
		for (j = 1; j <= nn; j++)
		{
			if (C[i][j] != 0) printf("%d", C[i][j]);
			else printf(" ");
		}
		printf("\n\n\n");
	}
	for (i = height + 1; i >= 1; i--)
	{
		free(C[i]);
	}
	free(C);
	return;
}

void BS_write(int pp, int offset, BSNode *root, char *side, int level)
{
	if (root == NULL) return;

	if (strcmp(side, "left") == 0)
	{
		C[level][pp - offset] = root->key;
		BS_write(pp - offset, offset / 2, root->left, "left", level + 1);
		BS_write(pp - offset, offset / 2, root->right, "right", level + 1);
	}
	else
	{
		C[level][pp + offset] = root->key;
		BS_write(pp + offset, offset / 2, root->left, "left", level + 1);
		BS_write(pp + offset, offset / 2, root->right, "right", level + 1);
	}
}

/*********************************************************************************************/
/*                             ���� Ž�� Ʈ�� ���                                            */
/*********************************************************************************************/