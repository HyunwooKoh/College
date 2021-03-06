#include "pch.h"
#include <iostream>
using namespace std;
class Tree; //전방선언
class TreeNode {
	friend class Tree;
private:
	TreeNode *Leftchild; //왼쪽 자식을 가르키는 node pointer
	int data; //data값
	TreeNode *Rightchild; //오른쪽 자식을 가르키는 node pointer
};
class Tree {
private:
	TreeNode *root;
public:
	Tree() { root = 0; }; //생성자 함수
	bool insert(const int &insvalue); //삽입 함수
	void DeleteNode(const int &delvalue); // 삭제함수
	void inorder(TreeNode *currentNode); //중위순회함수
	void inorder() { inorder(root); }; //중위순회 Driver
	TreeNode *IterSearch(const int &srcvalue);
};
bool Tree::insert(const int &insvalue)
{
	TreeNode *p = root; //움직일 노드를 가르킬 포인터
	TreeNode *q = NULL; //움직이는 포인터의 이전 위치를 기억하는 포인터
	while (p) //이동한 노드가 NULL일때 까지 이동
	{
		q = p;
		if (insvalue == p->data) //이미 존재하는 값이면 실패 출력
		{
			cout << "There is " << insvalue << "in list already\n";
			return false;
		}
		if (insvalue < p->data) p = p->Leftchild; //입력값이 현재 노드의 데이터 값보다 작을경우 왼쪽 노드로 이동
		else p = p->Rightchild; //크면 오른쪽 노드로 이동
	}
	p = new TreeNode(); //NULL인 위치에 새로운 노드 생성
	p->Leftchild = p->Rightchild = 0; //새로운 노드의 왼쪽,오른쪽 노드 초기값 설정
	p->data = insvalue; //새로운 노드의 데이터에 입력값 저장
	if (!root) root = p; //만약 빈 트리일경우, 새로운 노드를 root로 설정
	else if (insvalue < q->data) q->Leftchild = p; //새로운 노드의 값이 윗 노드보다 값이 작으면 왼쪽 자식노드로 설정
	else q->Rightchild = p; //크면 오른쪽 자식 노드로 설정
	return true; //성공
}
void Tree::DeleteNode(const int&delvalue)
{
	TreeNode *temp = root;
	TreeNode *temp_par = NULL;
	TreeNode *p = NULL;
	TreeNode *q = NULL;
	if (!IterSearch(delvalue)) //삭제할 값이 존재하는지 찾아보고 없을때
	{
		cout << "Not Exist Value\n";
		return;
	}
	while (temp->data != delvalue) //삭제할 데이타 값을 갖는 노드 찾기
	{
		temp_par = temp; //삭제할 노드의 윗노드를 저장
		if (delvalue > temp->data) temp = temp->Rightchild; //삭제할 값이 현재 노드의 데이터 값보다 크면 오른쪽으로,
		else temp = temp->Leftchild; //작으면 왼쪽으로 이동
	}
	if (!(temp->Leftchild) && !(temp->Rightchild)) //삭제하고자 하는 Node가 단말 Node인 경우
	{
		if (temp == root) //삭제할 노드가 단말이면서, root인 경우
		{
			root = NULL;
			delete temp;
			return;
		}
		else if (temp_par->Rightchild == temp) //root가 아닌데, 윗노드의 오른쪽 노드일 경우
			temp_par->Rightchild = NULL; //윗노드의 오른쪽 노드를 NULL로 설정
		else temp_par->Leftchild = NULL; //왼쪽일 경우, 윗노드의 왼쪽 노드를 NULL로 설정
		delete temp; //노드 삭제
		return;
	}
	if (!(temp->Leftchild) || !(temp->Rightchild)) //자식이 하나만 있는 비단말 노드
	{
		if (temp == root)//삭제할 노드가 root 노드인 경우
		{
			if (temp->Leftchild) //삭제할 노드의 왼쪽에만 노드가 있는 경우
				root = temp->Leftchild; //root노드를 왼쪽 노드로 설정
			else root = temp->Rightchild; //삭제할 노드의 오른쪽에만 있는경우, root노드를 오른쪽 노드로 설정
			delete temp; //노드 삭제
		}
		else if (temp_par->Leftchild == temp) //root노드가 아니면서, 윗노드의 왼쪽 노드일 경우
		{
			if (!(temp->Leftchild)) temp_par->Leftchild = temp->Rightchild; //삭제할 노드의 왼쪽이 NULL인경우 윗노드의 왼쪽 노드를 삭제할 노드의 오른쪽 노드와 연결
			else temp_par->Leftchild = temp->Leftchild; //삭제할 노드의 오른쪽이 NULL인 경우 윗노드의 왼쪽 노드를 삭제할 노드의 왼쪽 노드와 연결
		}
		else //root노드가 아니면서, 윗노드의 오른쪽 노드일 경우
		{
			if (!(temp->Leftchild)) temp_par->Rightchild = temp->Rightchild; //삭제할 노드의 왼쪽 노드가 NULL인 경우, 윗노드의 오른쪽 노드를 삭제할 노드의 오른쪽 노드와 연결
			else temp_par->Rightchild = temp->Leftchild; //삭제할 노드의 오른쪽이 NULL인 경우 윗노드의 오른쪽 노드를 삭제할 노드의 왼쪽 노드와 연결
		}
		delete temp; //노드 삭제
		return;
	}
	if (temp->Leftchild && temp->Rightchild) //자식이 양쪽에 있는 비단말 노드
	{
		p = temp; //움직일 임시 노드가 삭제할 노드를 가르킴
		p = p->Leftchild; //왼쪽 자식으로 이동(왼쪽 서브트리)
		while (p->Rightchild) //오른쪽이 NULL이기 전까지
		{
			q = p; //왼쪽 서브 트리의 마지막 오른쪽 노드의 윗노드를 q에 저장
			p = p->Rightchild; //p로 계속 오른쪽으로 이동
		}
		if (p->Leftchild) //p에 왼쪽 자식이 있는경우
		{
			if (temp == root) //삭제할 노드가 root인 경우
			{
				root = p; //root를 p로 설정(왼쪽 서브트리에서 가장 큰 노드로 대체)
				p->Rightchild = temp->Rightchild; // 왼쪽 서브트리에서 가장 큰 노드의 오른쪽에 전체 오른쪽 서브트리를 연결 
				delete temp; //노드 삭제
				return;
			}
			if (!q)//q가 NULL일때
			{
				p->Rightchild = temp->Leftchild;
			}
			else
			{
				q->Rightchild = p->Leftchild; //q의 오른쪽 자식노드에 오른쪽자식노드인 p의 왼쪽자식을 연결(항상 작음)
				p->Leftchild = temp->Leftchild; //왼쪽 서브트이의 가장 큰 노드인 p에 삭제할 노드의 왼쪽 서브트리를 연결
				p->Rightchild = temp->Rightchild; //p의 오른쪽에 오른쪽 서브트리를 연결
			}
		}
		else //p의 왼쪽에 자식이 없는 경우
		{
			if (!q) //q가 NULL일 경우
			{
				p->Rightchild = temp->Rightchild;
			}
			else
			{
				p->Leftchild = temp->Leftchild; // 왼쪽 서브트리의 가장 큰 노드인 p의 왼쪽에 삭제할 노드의 왼쪽 서브트리를 연결
				p->Rightchild = temp->Rightchild;// 오른쪽에 오른쪽 서브트리를 연결
				q->Rightchild = NULL; //p의 윗 노드의 오른쪽 자식 노드를 NULL로 설정
			}
		}
		if (temp_par->Leftchild == temp) //삭제할 노드가 윗 노드의 왼쪽 자식일 경우
			temp_par->Leftchild = p;
		else //오른쪽 자식일 경우
			temp_par->Rightchild = p;
		return;
	}
}
void Tree::inorder(TreeNode *currentNode) //중위순회
{
	if (currentNode)
	{
		inorder(currentNode->Leftchild);
		cout << currentNode->data;
		inorder(currentNode->Rightchild);
	}
}
TreeNode* Tree::IterSearch(const int &srcvalue)
{
	for (TreeNode *temp = root; temp; )
	{
		if (srcvalue == temp->data) return temp;
		if (srcvalue < temp->data) temp = temp->Leftchild; //탐색할때 현재 노드의 데이터 값보다 찾는 값이 작으면 왼쪽으로
		else temp = temp->Rightchild; //크면 오른쪽으로 포인터 노드를 이동
	}
	return 0;
}
void menu() //메뉴함수
{
	cout << "메뉴를 선택하세요.\n";
	cout << "===============메뉴====================\n";
	cout << "1.삽입\t2.삭제\t3.탐색\t4.중위우선순회.\n(종료는 -1)\n";
	return;
}
int main(void)
{
	int select;
	int value = 0;
	Tree mytree;
	menu();
	while (1)
	{
		cin >> select;
		if (select == -1) {
			cout << "program quit\n";
			return 0;
		}
		switch (select)
		{
		case 1:
			cout << "Insert value: ";
			cin >> value;
			mytree.insert(value);
			break;

		case 2:
			cout << "Delete Value: ";
			cin >> value;
			mytree.DeleteNode(value);
			break;
		case 3:
			cout << "Searching value: ";
			cin >> value;
			if (mytree.IterSearch(value))
				cout << "Exist\n";
			else
				cout << "Not Exist\n\n";
			break;
		case 4:
			mytree.inorder();
			cout << endl;
			break;
		}
	}
	return 0;
}
