// ConsoleApplication123.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdbool.h>
using namespace std;
class Stack { //path를 보여줄 때 사용할 stack class	
private:
	int top;
	int *stack;
	int capacity;
public:
	Stack() { top = -1; capacity = 4; stack = new int[capacity]; };
	int* pop(int &x); //출력함수
	void push(const int &x); //입력함수
};
int* Stack::pop(int &x)
{
	if (top == -1) return 0;
	x = stack[top--];
	return &x;
}
void Stack::push(const int &x)
{
	if (top == capacity - 1) //stack의 용량이 꽉 찼을 때,
	{
		int *temp;
		capacity *= 2;
		temp = new int[capacity];
		for (int i = 0; i < capacity; i++)
			temp[i] = stack[i];
		delete stack;
		stack = temp;
	}
	stack[++top] = x;
	return;
}

class GRAPH
{
private:
	int **length; //간선의 크기를 저장할 2차원 배열
	int *dist; //거리를 저장할 1차원 배열
	bool *s; //이미 들린 정점인지를 기록할 1차원 배열
	int *path; //path를 저장할 1차원 배열
	int num; //정점의 개수
public:
	GRAPH(const int vertices, const int edge); //생성자
	~GRAPH(); //소멸자
	void showgraph(); //graph를 보여주는 함수
	void showshortest_dist(const int v); //최단 거리를 보여주는 함수
	void showShortest_Path(const int v); //최단 경로를 보여주는 함수
	void ShortestPath(const int v); //최단 거리,경로를 구하는 함수
	int choose(const int v); //현재 상태에서 가장 가까운 정점을 찾아오는 함수
};
GRAPH::GRAPH(const int vertices, const int edge)
{
	num = vertices;
	length = new int*[num]; //동적할당
	dist = new int[num]; //동적할당
	s = new bool[num]; //동적할당
	path = new int[num]; //동적할당

	for (int i = 0; i < num; i++)
		length[i] = new int[num]; //2차원 배열의 동적 할당
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++) //2차원 배열의 초기화
		{
			if (i == j) length[i][j] = 0;
			else length[i][j] = 9999;
		}
	}
	for (int i = 0; i < edge; i++)
	{
		int u, v, weight;
		cout << i + 1 << "번째 간선 및 가중치 입력 : ";
		cin >> u >> v >> weight;
		length[u][v] = length[v][u] = weight;
	}
}
GRAPH::~GRAPH()
{
	for (int i = 0; i < num; i++)
	{
		delete[] length[i]; //2차원 배열의 삭제
	}
	delete[] length;
	delete[] dist; //나머지 1차원 배열의 삭제
	delete[] s;
	delete path;
}
int GRAPH::choose(const int v) 
{
	int min_index;
	int min = 9999;
	for (int i = 0; i < num; i++)
	{
		if (dist[i] < min && s[i] == false) //그 경로의 값이, 현재 최소값 보다 작으면,
		{
			min = dist[i]; //최소값을 업데이트 하고
			min_index = i; //그 index를 저장
		}
	}
	return min_index; //최소값의 index를 리턴
}
void GRAPH::ShortestPath(const int v)
{
	for (int i = 0; i < num; i++)
	{
		s[i] = false; //초기화
		dist[i] = length[v][i]; //거리 초기값 입력
		path[i] = v; // path초기화
	}
	s[v] = true; //시작점이므로 이미 지나감
	dist[v] = 0; // 시작점과의 거리는 자신이므로 0

	for (int i = 0; i < num - 2; i++)
	{
		int u = choose(num); //u에 가장 가까운 정점의 index를 저장
		s[u] = true; //방문하였으므로 true로 변환
		for (int w = 0; w < num; w++) //방문하지 않으점들의 값을 업데이트 하기
		{
			if (!s[w]) //방문하지 않았으면,
			{
				if (dist[u] + length[u][w] < dist[w]) { //기존의 거리값 보다 새로운 점을 들렸다가 가는 거리값이 작으면
					dist[w] = dist[u] + length[u][w]; //그 새로운 점을 들렸다가 가는 값으로 업데이트
					path[w] = u; //그 점을 들렸다가 가야하므로 path도 업데이트
				}
			}
			if (dist[w] == 9999) //만약 최소값이 무한대(9999로 임의의 값)이면
				path[w] = 9999; //path도 없다고 표시하기 위하여 9999입력
		}
	}
	return;
}
void GRAPH::showgraph() //그래프에 저장되어 있는 가중치들및 정점을 출력
{
	cout << "인접행렬 : \n  \t";
	for (int i = 0; i < num; i++)
		cout << i << "\t";
	cout << "\n";
	for (int i = 0; i < num; i++)
	{
		cout << i << ":\t";
		for (int j = 0; j < num; j++)
		{
			if (length[i][j] == 9999) cout << "∞\t";
			else
				cout << length[i][j] << "\t";
		}
		cout << "\n";
	}
	return;
}
void GRAPH::showshortest_dist(const int v) //각 정점의 shortestpath의 dist결과를 출력
{
	cout << "정점 " << v << "로 부터 모든 점에 대한 최소 비용\n";
	for (int i = 0; i < num; i++) {
		if (dist[i] == 9999) cout << i << ": ∞\t";
		else
			cout << i << ": " << dist[i] << "\t";
	}
	cout << "\n";
}

void GRAPH::showShortest_Path(const int v) //각 정점의 shortestpath의 dist값을 찾기까지, 지나간 길을 출력
{
	Stack myst;
	int temp;
	for (int i = 0; i < num; i++)
	{
		temp = i;
		if (v == i) continue; //자기 자신의 경로는 생략
		else if (path[temp] == 9999) //거리가 무한대, 즉, 연결되지 않았을 경우
		{
			cout << "경로가 존재하지 않습니다.\n";
			continue;
		}
		else //경로가 존재할 경우
		{
			while (1) {
				myst.push(temp); //스택구조를 이용 -> LIFO형식
				temp = path[temp]; //현재 정점의 dist값이 바뀔때, 지나가야 하는 정점을 표시 하기 위해서, path에 입력해 놨던 점을 지나가는데
				if (temp == v) break; //그 정점들을 스택에 push함, 그리고 그 값이 출발점일 경우 중지
			}
			myst.push(v); //출발점을 push
		}
		cout << "===================================\n";
		cout << v << "-" << i << "간 최단경로 : ";
		while (1)
		{
			int val;
			if (myst.pop(val)) cout << val << "-";
			else break;
		}
		cout << "\n";
	}
}
int main(void)
{
	int v, e;
	cout << "정점수와 간선수 입력: ";
	cin >> v >> e;
	GRAPH mygp(v, e);
	mygp.showgraph();
	cout << "시작 정점 입력> ";
	cin >> v;
	mygp.ShortestPath(v);
	mygp.showshortest_dist(v);
	mygp.showShortest_Path(v);
	mygp.~GRAPH();
	return 0;
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
