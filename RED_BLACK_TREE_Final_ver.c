/****************************************************/
/*                알고리즘 15조                      */
/*                Red Black Tree 구현               */
/*                조원 : 김지우,남주연,이길형         */
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

// 레드블랙트리에서 노드의 색깔 속성
typedef enum colorType {
	red = 0,
	black = 1
}nodeColor;

// 노드 키값
typedef int nodeKey;

// 트리노드의 구조 (색, 값, 좌우 노드, 부모노드)
typedef struct TreeNode {
	nodeColor color;
	nodeKey key;
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* parent;
}TreeNode;

// 트리구조 (루트노드와 닐노드)
typedef struct Tree {
	TreeNode* nil;
	TreeNode* root;
}Tree;

//이진 탐색 트리 (값, 좌우노드)
typedef struct BSNode {
	int key;
	struct BSNode *left, *right;
}BSNode;

int inputMenu(void);									// 메뉴를 입력받음
void inputData(int* userData);							// 키값을 받음
void inorder(TreeNode* root, TreeNode*nil);				// 중위
void preorder(TreeNode* root, TreeNode* nil);			// 전위
void postorder(TreeNode* root, TreeNode* nil);			// 후위
void insert_node(Tree* T, nodeKey key);					// 노드 입력
TreeNode* new_node(nodeKey item, TreeNode* parent);		// 노드 생성
TreeNode* delete_node(Tree *T, TreeNode* z);			// 노드 삭제
TreeNode* min_value_node(TreeNode* node, Tree* T);		// 가장 작은 키값 검색
TreeNode* search(Tree* T, nodeKey key);					// 특정 키값 검색
int emptyCheck(Tree* T);								// 트리가 비어있는지 체크
int getLevelCount(TreeNode* node, Tree* T);				// 트리 레벨 카운트
void printLevel(TreeNode* node, int level, Tree* T);	// 레벨 출력
void printElements(Tree* T);							// 레벨마다 노드 출력
void write(int pp, int offset, TreeNode* root, char* side, int level, Tree* T);// 트리 출력
void displayTree(Tree* T);								// 트리 표현
void checkDoubleRed(Tree* T, nodeKey key);				// 더블레드 체크 후 교정
Tree* createTree();										// 트리 생성
void right_rotate(Tree* T, TreeNode* x);				// 우측 회전연산
void left_rotate(Tree* T, TreeNode* x);					// 좌측 회전연산
TreeNode *successor(Tree *T, TreeNode *x);				// 본인 다음으로 큰 노드를 찾아서 반환
void fix_up_node(Tree* T, TreeNode* x);					// 삭제연산후 더블블랙 교정

/*********************************************************************************************/
/*                             이진 탐색 트리 기능                                            */
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
/*                             이진 탐색 트리 기능                                            */
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

	printf("프로그램 시작\n\n");

	while ("Tree")
	{
		startRB = 0.0, finishRB = 0.0;
		startBS = 0.0, finishBS = 0.0;
		resultRB = 0.0, resultBS = 0.0;

		switch (inputMenu())
		{
		case 1:
			printf("**************************************\n");
			printf("   << 삽입 >>\n");

			inputData(&userData);

			if (T->root != T->nil && search(T, userData) != NULL)			// RB트리 체크
			{
				printf(" 삽입실패[RedBlack]\n");
				printf(" 중복된 키값이 존재합니다.[RedBlack]\n");
				printf("**************************************\n");
				break;
			}
			if (BS_search(bst_root, userData) != NULL && bst_root != NULL)	// 이진탐색트리 체크
			{
				printf(" 삽입실패[BinarySearch]\n");
				printf(" 중복된 키값이 존재합니다.[BinarySearch]\n");
				printf("**************************************\n");
				break;
			}

			startRB = clock();
			insert_node(T, userData);		// 레드블랙트리 노드 생성 및 삽입 연산
			checkDoubleRed(T, userData);	// 그 후 더블 레드를 체크하여 교정
			finishRB = clock();
			printf(" 삽입완료[RedBlack]\n");

			startBS = clock();
			bst_root = BS_insert_node(bst_root, userData); // 이진탐색트리 노드 생성 및 삽입 연산
			finishBS = clock();
			printf(" 삽입완료[BinarySearch]\n");

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree 삽입 연산 : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree 삽입 연산 : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;
		case 2:
			printf("**************************************\n");
			printf("   << 삭제 >>\n");

			if (emptyCheck(T) == TRUE) break;			// RB트리 체크
			if (BS_emptyCheck(bst_root) == TRUE) break; // 이진탐색트리 체크
			else
			{
				inputData(&userData);
				target_delete = search(T, userData);	// 삭제할 노드를 찾음

				if (target_delete != NULL)
				{
					startRB = clock();
					deleted_node = delete_node(T, target_delete);	// 노드 삭제 후 교정
					finishRB = clock();
					printf(" 삭제 성공[RedBlack]\n");
					free(deleted_node);

					if (BS_search(bst_root, userData) != NULL)		// 이진탐색트리 삭제
					{
						startBS = clock();
						bst_root = BS_delete_node(bst_root, userData);
						finishBS = clock();
						printf(" 삭제 성공[BinarySearch]\n");

						resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
						resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
						printf(" \n\n Red-Black Tree 삭제 연산 : %.20lf\n", resultRB);
						printf(" \n Binary Search Tree 삭제 연산 : %.20lf\n\n", resultBS);

						printf("**************************************\n");
						break;
					}
					else if (BS_search(bst_root, userData) == NULL)
					{
						printf(" 삭제 실패[BinarySearch]\n");
						printf("**************************************\n");
						break;
					}
					break;
				}
				else if (target_delete == NULL)
				{
					printf(" 삭제 실패[RedBlack]\n");
					printf("**************************************\n");
					break;
				}
			}

		case 3:
			printf("***********************\n");
			printf(" 중위순회[RedBlack]\n");

			if (emptyCheck(T) == TRUE) break;			// RB트리 체크
			if (BS_emptyCheck(bst_root) == TRUE) break; // 이진트리탐색 체크

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
			printf(" \n\n Red-Black Tree 중위 순회 : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree 중위 순회 : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;

		case 4:
			printf("***********************\n");
			printf(" 전위순회\n");

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
			printf(" \n\n Red-Black Tree 전위 순회 : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree 전위 순회 : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;

		case 5:
			printf("***********************\n");
			printf(" 후위순회\n");

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
			printf(" \n\n Red-Black Tree 후위 순회 : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree 후위 순회 : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;


		case 6:
			printf("***********************\n");
			printf(" 레벨순회\n");

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
			printf(" \n\n Red-Black Tree 레벨 순회 : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree 레벨 순회 : %.20lf\n\n", resultBS);

			printf("**************************************\n");
			break;

		case 7:
			printf("***********************\n");
			printf("   << 탐색 >>\n");

			if (emptyCheck(T) == TRUE) break;
			if (BS_emptyCheck(bst_root) == TRUE) break;

			inputData(&userData);

			startRB = clock();
			if (search(T, userData) != NULL)							// RB트리 탐색
				printf("키값: [%d]은 있습니다.[RedBlack]\n", userData);
			else printf("키값: [%d]은 없습니다.[RedBlack]\n", userData);
			finishRB = clock();

			startBS = clock();
			if (BS_search(bst_root, userData) != NULL)					// 이진탐색트리 탐색
				printf("키값: [%d]은 있습니다.[BinarySearch]\n", userData);
			else printf("키값: [%d]은 없습니다.[BinarySearch]\n", userData);
			finishBS = clock();

			resultRB = (double)(finishRB - startRB) / CLOCKS_PER_SEC;
			resultBS = (double)(finishBS - startBS) / CLOCKS_PER_SEC;
			printf(" \n\n Red-Black Tree 탐색 : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree 탐색 : %.20lf\n\n", resultBS);


			printf("**************************************\n");
			break;

		case 8:
			printf("\n**************************************");
			printf("\n[RedBlack] 트리 출력\n");
			printf("**************************************\n");
			displayTree(T);
			printf("**************************************\n");
			printf("[BinarySearch] 트리 출력\n");
			printf("**************************************\n");
			BS_displayTree(bst_root);
			break;

		case 9:
			printf("**************************************\n");
			printf("   << 최악의 경우 : 삽입(N = %d) >>\n",MAX_SIZE);
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
			printf(" \n Red-Black Tree 삽입 연산 : %.20lf\n", resultRB);
			printf(" \n Binary Search Tree 삽입 연산 : %.20lf\n", resultBS);

			break;

		case 0:
			printf("**************************************\n");
			printf("   << 종료 >>\n");
			printf("**************************************\n");
			exit(0);

		default:
			printf("**************************************\n");
			printf(" 잘못 입력하였습니다.\n");
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
	printf(" 1. 삽입\n");
	printf(" 2. 삭제\n");
	printf(" 3. 중위순회\n");
	printf(" 4. 전위순회\n");
	printf(" 5. 후위순회\n");
	printf(" 6. 레벨순회\n");
	printf(" 7. 탐색\n");
	printf(" 8. 트리 출력\n");
	printf(" 9. 순차 삽입(1~%d)\n",MAX_SIZE);
	printf(" 0. 종료\n");
	printf("--------------------------------------\n");
	printf(" 메뉴 입력 : ");
	int a = scanf("%d", &menu_number);
	printf("--------------------------------------\n");

	return menu_number;
}
void inputData(int* userData)
{
	printf("\n");
	printf(" key 값 입력\n >> ");
	int a = scanf("%d", userData);
	printf("\n");
}
// 중위 순회
void inorder(TreeNode* root, TreeNode* nil)
{
	char color;

	if (root != nil)
	{
		inorder(root->left, nil);   // 왼쪽서브트리 순회

		if (root->color == 0) color = 'R';
		else if (root->color == 1) color = 'B';
		else color = ' ';

		printf("[%d][%c] ", root->key, color);    // 노드 방문
		inorder(root->right, nil);   // 오른쪽서브트리 순회
	}
}
// 전위 순회
void preorder(TreeNode* root, TreeNode* nil)
{
	char color;

	if (root != nil)
	{
		if (root->color == 0) color = 'R';
		else if (root->color == 1) color = 'B';
		else color = ' ';

		printf("[%d][%c] ", root->key, color);    // 노드 방문
		preorder(root->left, nil);   // 왼쪽서브트리 순회
		preorder(root->right, nil);   // 오른쪽서브트리 순회
	}
}
// 후위 순회
void postorder(TreeNode* root, TreeNode* nil)
{
	char color;

	if (root != nil)
	{
		postorder(root->left, nil);   // 왼쪽 서브 트리 순회
		postorder(root->right, nil);   // 오른쪽 서브 트리 순회

		if (root->color == 0) color = 'R';
		else if (root->color == 1) color = 'B';
		else color = ' ';

		printf("[%d][%c] ", root->key, color);    // 노드 방문
	}
}

void insert_node(Tree* T, nodeKey key)	// 평범한 노드 생성 및 삽입 연산
{
	TreeNode* node = T->root;
	TreeNode* nil = T->nil;
	// 트리의 루트가 nil이면 루트를 새로 만들어 넣는다.
	if (node == nil)
	{
		T->root = new_node(key, NULL);
		T->root->left = T->nil;
		T->root->right = T->nil;
		T->root->parent = T->nil;
		return;
	}
	// 그렇지 않으면 순환적으로 트리를 내려간다.
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

	if (z->left == T->nil || z->right == T->nil) // 삭제할 노드 z의 왼쪽, 오른쪽 자식이 NULL이 아니라면 즉, 자식이 없다면
	{
		y = z; // y에 z를 저장하고
	}
	else y = successor(T, z); // 자식이 있다면, z의 Successor를 찾아서 y에 저장한다. BST에서 Successor찾는 과정과 동일

	if (y->left != T->nil) // 위의 과정을 거치면 y는 자식이 하나이거나 없다.
	{					   // Successor는 자식노드가 두 개일 수 없다. y의 왼쪽 자식이 null이 아니라면
		x = y->left; // y의 왼쪽 자식을 x로
	}
	else x = y->right; // 그렇지 않다면, y의 오른쪽 자식을 x로 저장한다.

	x->parent = y->parent; // 그다음 y의 부모를 x의 부모로 설정한다.

	if (y->parent == T->nil) // 만약, y의 부모가 NULL이라면
	{
		T->root = x; // x를 트리의 root로 설정한다.
	}
	else if (y == y->parent->left) // y의 부모노드가 NULL이 아니고, y가 y의 부모의 왼쪽 자식노드라면
	{
		y->parent->left = x; // 저장된 x를 y의 부모의 왼쪽 자식노드로 설정한다.
	}
	else y->parent->right = x; // y가 y의 부모의 오른쪽 자식노드라면, 저장된 x를 부모노드의 오른쪽 자식으로 설정한다. 여기까지가 실제로 노드를 삭제하는 작업이다.

	if (y != z) //삭제하려는 노드 대신 Successor를 삭제한 경우 y와 z가 다르다. 따라서 Successor y노드의 데이터를 카피해주는 작업이 필요하다.
	{
		z->key = y->key; // 여기까지는 기존의 Binary Search Tree와 동일한 방식으로 진행되는 삭제 연산이다.
						 // 삭제한 노드 y가 red 노드 였다면, Red Black Tree의 규칙에 위반 되지 않는다.
	}

	if (y->color == black)
	{
		fix_up_node(T, x);// RB - Delete - FixUP(T,x) 함수 부분
	}

	return y;
}

void fix_up_node(Tree *T, TreeNode* x)
{
	TreeNode* w = (TreeNode*)malloc(sizeof(TreeNode));

	while (x != T->root && x->color == black) // 만약 x가 루트노드이거나, x가 레드노드라면 While문을 빠져나가서 x를 BLACK으로 만들어주고 종료하면 된다.
	{
		if (x == x->parent->left)			 // While문 안에서는 크게 둘로 나뉘어지게 된다. 만약 x가 x의 부모노드의 왼쪽 자식이라면 Case 1, 2, 3, 4에 해당하며
		{									//  부모노드의 오른쪽 자식이라면 Case 5, 6, 7, 8에 해당한다.
			w = x->parent->right;

			if (w->color == red)			// 형제 노드인 w노드가 RED인 경우가 Case 1에 해당한다.
			{
				w->color = black;			// Case1의 경우 w노드를 BLACK으로 만들고
				x->parent->color = red;		//  x의 부모노드 노드를 RED로 만든 다음
				left_rotate(T, x->parent);	// x의 부모노드 기준으로 LEFT-ROTATE한다
				w = x->parent->right;		// 새로운 w는  x의 부모노드의 right가 되므로 새로 저장한다
			}								// 새로운 w노드는 BLACK 이므로(x의 부모노드가 RED로 변경됨) 다시 While문으로 들어왔을 때, Case2, 3, 4로 가게 된다.

			if (w->left->color == black && w->right->color == black) // Case 2, 3, 4를 구분하게 된다. w의 왼쪽, 오른쪽 자식노드가 둘다 BLACK인 경우 Case2에 해당한다.
			{														 // w와 x로 부터 black을 하나씩 뺏어서 부모 노드에게 전달한다.
				w->color = red;										 // 그렇게 하기 위해서 w는 RED노드가 되고
				x = x->parent;										 // x의 부모노드를 x로 만들어 준다.
			}													     // x의 부모노드가 RED였다면 다시 While문을 돌지 않고 x를 RED로 만든 뒤에 종료하면 되고
																	 // x의 부모노드가 BLACK이었다면 x를 x의 부모노드로 놓고 double-black 노드가 된 x를 다시 반복해서 처리해주면 된다.

			else if (w->right->color == black) // w의 오른쪽 자식이 BLACK이고, 왼쪽 자식이 RED인 경우 Case 3에 해당한다.
			{
				w->left->color = black;        // RIGHT-ROTATE의 대상인 두 노드의 색을 교환하고
				w->color = red;				   // (w를 RED로, w의 왼쪽 자식노드를 BLACK으로 바꾸고)
				right_rotate(T, w);			   // w를 기준으로 RIGHT-ROTATE 한다.
				w = x->parent->right;		   // 이렇게 되면 w는 x의 부모노드의 새로운 오른쪽 자식노드가 되고, 그것의 색은 RED이다. 그리고 Case 4로 바로 넘어 간다.
			}
			else
			{
				w->color = x->parent->color;	// LEFT-ROTATE의 대상인 두 노드의 색을 교환한다. w의 색을 x의 부모노드의 색으로 바꾸고
				x->parent->color = black;		// x의 부모노드를 BLACK으로 바꾼다.
				w->right->color = black;		// w의 오른쪽 자식의 색을 BLACK으로 바꾼다.
				left_rotate(T, x->parent);		// 그 다음 p[x]를 기준으로 LEFT-ROTATE를 수행한다.
				x = T->root;					// x라는 포인터 변수를 root[T]로 변경하여 Case 4가 끝나면 while문이 종료되도록 한다.
			}									// 실제 트리에는 변화가 없다. 트리의 루트가 변한것은 아니다.
		}
		else // Case 5, 6, 7, 8을 대칭적으로 처리한다. x가 x의 부모노드의 오른쪽 자식인 경우이다.
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
	x->color = black; // 트리의 루트의 색을 BLACK으로 변경하는 것은 언제 해도 문제가 되지 않는다.
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
	// 맨 왼쪽 단말 노드를 찾으러 내려감
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
		printf(" 루트노드가 없습니다.\n");
		printf("**************************************\n\n");
		return TRUE;
	}
	else return FALSE;
}
int getLevelCount(TreeNode*node, Tree* T) // 노드의 최대 높이를 찾는 함수
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

void printLevel(TreeNode* node, int level, Tree* T) // 레벨순회 방식으로 출력 루트 노트부터 차례대로 출력, 레벨을 이용한다.
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

void printElements(Tree* T) // 레벨 1부터 레벨 n까지 차례대로 printLevel 함수에 대입하여 해당 레벨을 넣어준다.
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
		if (me->parent == me->parent->parent->left)					// 내 부모가 부모의 부모의 왼쪽자식일때
		{
			uncle = me->parent->parent->right;
			if (uncle->color == red)								// 부모의 형제노드가 빨강일때 recoloring실행
			{
				me->parent->color = black;
				uncle->color = black;
				me->parent->parent->color = red;
				me = me->parent->parent;							// recoloring의 결과로 다시 doubleRed가 발생할 경우 해결하기위해 현재위치를 부모의 부모로 옮김
			}
			else if (me == me->parent->right) {						// 내가 부모의 오른쪽 자식일때의 restructuring
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
		else {														// 내 부모가 부모의 부모의 오른쪽자식일때
			uncle = me->parent->parent->left;
			if (uncle->color == red)								// 부모의 형제노드가 빨강일때 recoloring실행
			{
				me->parent->color = black;
				uncle->color = black;
				me->parent->parent->color = red;
				me = me->parent->parent;							// recoloring의 결과로 다시 doubleRed가 발생할 경우 해결하기위해 현재위치를 부모의 부모로 옮김
			}
			else if (me == me->parent->left) {						// 내가 부모의 오른쪽 자식일때의 restructuring
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
/*                             이진 탐색 트리 기능                                            */
/*********************************************************************************************/

// 중위 순회
void BS_inorder(BSNode *root)
{
	if (root)
	{
		BS_inorder(root->left);	// 왼쪽서브트리 순회
		printf("[%d] ", root->key); 	// 노드 방문
		BS_inorder(root->right);	// 오른쪽서브트리 순회
	}
}
// 전위 순회
void BS_preorder(BSNode *root)
{
	if (root)
	{
		printf("[%d] ", root->key); 	// 노드 방문
		BS_preorder(root->left);	// 왼쪽서브트리 순회
		BS_preorder(root->right);	// 오른쪽서브트리 순회
	}
}
// 후위 순회
void BS_postorder(BSNode *root)
{
	if (root)
	{
		BS_postorder(root->left);	// 왼쪽 서브 트리 순회
		BS_postorder(root->right);	// 오른쪽 서브 트리 순회
		printf("[%d] ", root->key); 	// 노드 방문
	}
}

BSNode *BS_insert_node(BSNode *node, int key)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) return BS_new_node(key);
	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (key < node->key)
		node->left = BS_insert_node(node->left, key);
	else if (key > node->key)
		node->right = BS_insert_node(node->right, key);

	// 변경된 루트 포인터를 반환한다. 
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
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->key)
		root->left = BS_delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->key)
		root->right = BS_delete_node(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else {
		// 첫 번째나 두 번째 경우
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
		// 세 번째 경우
		BSNode * temp = BS_min_value_node(root->right);
		// 중외 순회시 후계 노드를 복사한다. 
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = BS_delete_node(root->right, temp->key);
	}
	return root;
}

BSNode *BS_min_value_node(BSNode *node)
{
	BSNode * current = node;
	// 맨 왼쪽 단말 노드를 찾으러 내려감
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
		printf(" 루트노드가 없습니다.\n");
		printf("-----------------\n\n");
		return TRUE;
	}
	else return FALSE;
}
int BS_getLevelCount(BSNode *node) // 노드의 최대 높이를 찾는 함수
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

void BS_printLevel(BSNode *node, int level) // 레벨순회 방식으로 출력 루트 노트부터 차례대로 출력, 레벨을 이용한다.
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

void BS_printElements(BSNode *node) // 레벨 1부터 레벨 n까지 차례대로 printLevel 함수에 대입하여 해당 레벨을 넣어준다.
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
/*                             이진 탐색 트리 기능                                            */
/*********************************************************************************************/