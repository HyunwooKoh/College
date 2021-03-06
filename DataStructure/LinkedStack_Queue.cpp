#include "pch.h"
#include <iostream>
using namespace std;
//Linked list basic frame: Always check whether it is blank or not!

class LinkedStack; //Stack class Forward declaration
class LinkedQueue; //Queue class Forward declaration
class ChainNode { 
	friend LinkedQueue; //Assigned as friend class to access data and * link variables in LinkedQueue class
	friend LinkedStack; //Assigned as friend class to access data and * link variables in LinkedStack class
private:
	int data;
	ChainNode *link; //Pointer variable to point to the next Node
public:
	ChainNode(int element = 0, ChainNode *next = 0)
	{
		data = element;
		link = next;
	}
};

class LinkedStack { 
private:
	ChainNode *top; // Pointer to the most recently inserted Node
					// Stack Class is LIFO type.
public:
	LinkedStack() { top = 0; }
	~LinkedStack() {}
	void Push(int &istvalue); 
	int* Pop(int &retvalue); 
	void print(); 
};

class LinkedQueue {
private:
	ChainNode *front, *rear; // Pointer to the most recently deleted Node
							 // Pointer to the most recently inserted Node
public:
	LinkedQueue() { front = rear = 0; }
	~LinkedQueue() {} 
	void Push(int &istvalue);
	int* Pop(int &retvalue);
	void print();
};
void LinkedStack::Push(int &istvalue)
{
	top = new ChainNode(istvalue, top);
	// The existing top node is inserted in the form indicated by the new top node 
	// by entering the node pointed to by the top into the link of the newly entered node.
}
int* LinkedStack::Pop(int &retvalue)
{
	if (top == 0) {
		cout << "Stack is empty";
		return 0;
	}

	ChainNode* delNode = top; // Declaration of temporary node containing information of the node to be deleted
	retvalue = top->data; // Stores the data value of the node to be deleted in the variable received as an argument
	top = top->link; // Change the top node to the node pointed to by the existing top node
	delete delNode;
	return &retvalue;
}
void LinkedStack::print()
{
	if (top == 0) cout << "Stack is empty!\n";
	ChainNode *prtNode = top; // If you move the top when printing, the links will be cut in the process of printing.
							  // Declare temporary Node to replace top and assign the same value as top
	while (prtNode)
	{
		cout << prtNode->data << "  "; 
		prtNode = prtNode->link;
	}
	cout << "\n";
	return;
}
void LinkedQueue::Push(int &istvalue)
{
	if (front == 0) front = rear = new ChainNode(istvalue, 0); // Before inserting, it is an empty queue check by front == rear == 0
															   // After checking, if empty queue, set front == rear == new
	else 
		rear = rear->link = new ChainNode(istvalue, 0); // The link at the current rear points to the new node, and the rear is replaced with the node the link at the current rear points to.
}
int* LinkedQueue::Pop(int &retvalue)
{
	if (front == 0) { // Before deletion occurs, check if it is an empty queue check by front == rear == 0
		cout << "queue is empty!\n";
		return 0;
	}
	ChainNode *delNode = front; // Create a temporary node to temporarily store the node to be deleted
	retvalue = front->data; // Store the data value of the node to be deleted in the variable received as an argument
	front = front->link; 
	delete delNode; 
	return &retvalue; // 저장한 변수의 주소 반환
}
void LinkedQueue::print()
{
	if (front == 0) cout << "queue is empty!\n"; 
	ChainNode *prtNode = front; // Declare a node to replace the link when the front pointer is moved when the output is executed.

	while (prtNode) // ptrNod == !NULL 일때 까지 반복
	{
		cout << prtNode->data << "  "; // ptrNode가 가르키는 Node의 data 출력
		prtNode = prtNode->link; // 출력 후 , ptrNode를 현재 가르키던 Node가 가르키는 Node로 이동
	}
	cout << "\n";
	return;
}

void menu(); // Declare a function to output the items to be selected in the process of executing the program

int main(void)
{
	int num = 0, instvalue = 0, retvalue = 0; // num : Variable to store which run was selected
											  // instvalue : Variable to store the value to be input when executing input
											  // retvalue : Variable to receive the value when the function returns the deleted value when executing delete
	LinkedStack myStack;
	LinkedQueue myqueue;
	menu();
	while (1) { // Condition = 1-> infinite loop because the program must continue to run
		cin >> num;
		if (!num) break; //If you enter 0, the program ends

		switch (num)
		{
		case 1:// Insert into LinkedStack class
			cout << "Insert Value :";
			cin >> instvalue; // Input value to insert
			myStack.Push(instvalue);
			break;
		case 2: // Insert into LinkedQueue class
			cout << "Insert Value :";
			cin >> instvalue; // Input value to insert
			myqueue.Push(instvalue);
			break;
		case 3: // Removed from LinkedStack class
			myStack.Pop(retvalue);
			cout << "deleted  Value : " << retvalue << "\n"; //Print deleted values
			break;
		case 4: // Removed from LinkedQueue class
			myqueue.Pop(retvalue);
			cout << "deleted  Value : " << retvalue << "\n"; // Print deleted values
		case 5: // Print contents of LinkedStack class
			cout << "my Stack : ";
			myStack.print();
			break;
		case 6: // Print contents of LinkedQueue class
			cout << "My Queue : ";
			myqueue.print();
			break;
		}
	}
	cout << "End the program.\n"; // If 0 is entered during menu selection, the while statement is exited and output.
	return 0;
}

void menu()
{
	cout << "----------메뉴----------\n";
	cout << "1.Insert into stack \ t2.Insert into queue \ n3.Delete from stack \ t4.Delete from queue \ n5.View stack contents \ t6.View queue contents";
	cout << "\n(Ends the program when input 0 )\n";
	return;
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
