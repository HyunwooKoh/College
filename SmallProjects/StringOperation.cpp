// made for practice string operation. Hyunwoo, KOH, DKU software Engineering, trghyunwoo@naver.com
// Here, we need 3 argument without exe file name, option, file name, patter(if option == 1)

#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

void menu();
int main(int argc, char* argv[])
{
	//argc : 아규멘트(인자)의 개수, 이번 프로젝트에서는 총 4개의 인자가 들어오므로, argc = 4
	//들어오는 인자 : 프로그램 실행파일 이름, 텍스트 파일 이름, 옵션(1 ~ 5), pattern
	if (argc > 4 || argc < 3)
	{
		printf("Usage : we need 3 argument without exe file name, option, file name, patter(if option == 1)\n");
		return -1;
	}
	menu();
	char text[256]; //한 줄의 최대길이를 256자로 한정
	int size = 0, count = 0;


	FILE *fp;
	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("0\n");
		return -1;
	}

	if (argv[2][0] == '1') //패턴 개수를 count하는 부분
	{
		clock_t start = clock();
		int pt_count = 0, txt_index = 0, pt_index = 0;;
		while (fgets(text, 256, fp))
		{
			txt_index = 0;
			pt_index = 0;
			while (text[txt_index])
			{
				if (text[txt_index] == argv[3][pt_index])
				{
					txt_index++;
					pt_index++;
					if (!argv[3][pt_index]) //패턴을 찾은 경우
					{
						pt_count++; //패턴 count 증가
						pt_index = 0;
					}
				}
				else 
				{
					if (pt_index) //패턴 찾다가 실패시 실행(한번이라도 pt_index가 증가했을 경우 실행)
					{
						txt_index = txt_index - pt_index + 1; //텍스트 파일의 참조 위치를 시작 위치 패턴을 찾기 시작한 위치 다음으로 이동
						pt_index = 0;
					}
					else //그냥 다른 경우
						txt_index++;
				}
			}
		}
		printf("텍스트에 패턴이 %d개 있습니다\n", pt_count);
		clock_t end = clock();
		printf("수행 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	}
	else if (argv[2][0] == '2') //토큰(단어) 개수 count하는 부분
	{
		clock_t start = clock();
		char *p;
		int token_count = 0;
		while (fgets(text, 256, fp))
		{
			p = text;
			while (*p)
			{
				while (*p != ' ' && *p)
					p++; //띄어쓰기 혹은 마지막 글자 일때 까지 이동

				if (*p)
				{
					p++; //마지막 문자가 아니면 다음으로 이동
					token_count++; //토큰 개수 증가
				}
				else
					token_count++; //마지막 문자이면 참조 위치 이동시키지 않고, 토큰 개수 증가
			}
		}
		printf("텍스트에 토큰이 %d개 있습니다\n", token_count);
		clock_t end = clock();
		printf("수행 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	}
	else if (argv[2][0] == '3') //문자 개수를 count, strlen을 사용하지 않고 구현
	{
		clock_t start = clock();
		char *p;
		int char_count = 0;
		while (fgets(text, 256, fp))
		{
			p = text;
			while (*p)
			{
				char_count++; //널문자 이전 까지 문자의 개수 증가
				p++;
			}
		}
		printf("텍스트에 문자가 %d개 있습니다\n", char_count);
		clock_t end = clock();
		printf("수행 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	}
	else if (argv[2][0] == '4') //단어의 평균 길이를 계산하는 부분
	{
		clock_t start = clock();
		char *p;
		int total_len = 0, token_count = 0;
		float avg_token_len = 0.0;
		while (fgets(text, 256, fp))
		{
			p = text;
			while (*p)
			{
				while (*p != ' ' && *p)
				{
					p++;
					total_len++; //모든 토큰의 길이의 합을 저장
				}
				if (*p)
				{
					p++;
					token_count++; //토큰 개수의 증가
				}
				else
					token_count++;
			}
		}
		avg_token_len = (float)total_len / token_count;
		printf("텍스트에 있는 단어 길이의 총 합은 %d 이며, 단어의 개수는 %d개 입니다.\n", total_len, token_count);
		printf("텍스트에 있는 단어의 평균 길이는 %lf입니다\n", avg_token_len);
		clock_t end = clock();
		printf("수행 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	}
	else if (argv[2][0] == '5') //단어 길이의 표준 편차를 구함
	{
		clock_t start = clock();
		char *p;
		int arr[30] = { 0, }; //단어의 최대 길이가 30이라고 가정 및 모두 0으로 초기화, 여기서 index가 단어의 길이를 나타낼 것이고, 단어의 개수는 arr[index]에 저장 될거임
		int token_count = 0, token_len = 0, sum = 0, i;
		float ex = 0.0, ex2 = 0.0;
		double c = 0.0;
		while (fgets(text, 256, fp))
		{
			p = text;
			while (*p)
			{
				token_len = 0; //각 토큰 마다 길이를 0으로 초기화
				while (*p != ' ' && *p)
				{
					p++;
					token_len++; // 한 토큰 내에서 길이 증가
				}
				token_count++; //토큰 개수 증가
				arr[token_len]++; //해당 길이의 토큰 개수를 증가
				if (*p) p++;
			}
		}
		//E(x)구하기
		for (i = 0; i < 20; i++)
			sum += arr[i] * i;
		ex = (float)sum / token_count;

		// E(x^2)구하기
		for (i = 0; i < 30; i++)
			sum += arr[i] * i * i;
		ex2 = (float)sum / token_count;
		c = sqrt(ex2 - ex * ex); // c가 표준푠차

		printf("단어의 길이별 개수 :\n ");
		//단어의 길이 출력
		for (i = 0; i < 30; i++)
			printf("%d\t", i);
		printf("\n");
		//단어의 길이별 개수 출력
		for (i = 0; i < 30; i++)
			printf("%d\t", arr[i]);
		printf("\n");

		printf("총 단어의 길이에 대한 표준편차는 %lf입니다.\n", c);
		clock_t end = clock();
		printf("수행 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	}

	fclose(fp);
	return 0;
}
void menu()
{
	printf("option : \n");
	printf("1 : 패턴개수 구하기\t2: 단어의 개수 구하기\t3:문자의 개수 구하기\n");
	printf("4 : 단어의 평균 길이 구하기\t5: 단어의 길이에 대한 표준편차 구하기\n");
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
