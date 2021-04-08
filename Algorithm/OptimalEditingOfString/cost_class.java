package abc;

public class cost_class {
	int cost[][]; //각각의 index까지의 최소 비용을 저장
	char edit[][]; //직전에 어떠한 연산을 했는지 저장, 후에 최소 비용을 추적할 때 사용 됨
	int insert , delete , change; //삽입, 삭제, 교체 하는데 드는 비용
	int x_len, y_len; //두 문자열의 길이
	StringBuilder way = new StringBuilder(); //최적의 문자열 변환 방식을 저장
	
	cost_class(int x, int y)
	{
		x_len = x;
		y_len = y;
		cost = new int[y_len+1][x_len+1]; //각 문자열의 첨자도 나타내기 위해, 한칸 씩 더 생성
		edit = new char[y_len+1][x_len+1];

		insert = 0 ; delete = 0 ; change = 0;
	}
	void cost_init() //cost를 구하기 전, cost와 edit 배열 초기화
	{
		cost[0][0] = 0;
		edit[0][0] = ' ';
		for(int j = 1 ; j < x_len+1 ; j++ )
		{
			cost[0][j] = cost[0][j-1] + delete;
			edit[0][j] = 'd';
		}
		for(int j = 1 ; j < y_len +1 ; j++ )
		{
			cost[j][0] = cost[j-1][0] + insert;
			edit[j][0] = 'i';
		}
	}
	
	void make_cost(char[] x, char[] y) //cost 배열에 값을 채워 넣음
	{
		for(int i = 1 ; i < x_len + 1 ; i++)
		{
			for(int j = 1 ; j < y_len + 1 ; j++)
			{
				if(x[i-1] == y[j-1]) //만약 두 문자열에서 동일한 index의 문자가 같다면, 교체 비용이 0이므로, 교체하는 방식을 선택
				{
					cost[j][i] = cost[j-1][i-1];
					edit[j][i] = 'c';
				}
				else
				{
					cost[j][i] = Math.min( Math.min(cost[j-1][i-1]+change, cost[j-1][i] + insert) , cost[j][i-1] + delete); //세가지 연산준 가장 작은 값을 찾아줌
					
					if(cost[j][i] == cost[j-1][i-1] + change)
						edit[j][i] = 'c'; // 교체에 우선순위를 둠
					else if(cost[j][i] == cost[j-1][i] + insert)
						edit[j][i] = 'i';
					else if(cost[j][i] == cost[j][i-1] + delete)
						edit[j][i] = 'd';
					else
						edit[j][i] = '?'; //오류 탐색
				}
			}
		}
	}
	
	void show_cost() //cost와 edit의 내용 출력
	{
		System.out.println("==================== cost ====================");
		System.out.print("\t");
		for(int i = 0 ; i < y_len + 1 ; i++)
			System.out.print( i + "\t");
		System.out.println();
		for(int i = 0 ; i < x_len + 1 ; i ++)
		{
			System.out.print( i + "\t");
			for(int j = 0 ; j < y_len + 1 ; j++ )
			{
				System.out.print(cost[j][i] + "\t");
			}
			System.out.println();	
		}
		System.out.println("==================== edit ====================");
		System.out.print("\t");
		for(int i = 0 ; i < y_len + 1 ; i++)
			System.out.print( i + "\t");
		System.out.println();
		for(int i = 0 ; i < x_len + 1 ; i ++)
		{
			System.out.print( i + "\t");
			for(int j = 0 ; j < y_len + 1 ; j++ )
			{
				System.out.print(edit[j][i] + "\t");
			}
			System.out.println();
		}
	}
	void find_minst_way(int i, int j) //최적의 문자열 변환 방식을 끝에서 부터 따라감 , 순환 호출 방식을 선택
	{
		if( (i == 0) && (j == 0) ) //처음에 도달하면 끝남
		{
			System.out.println("최최적의 편집 순서열 : " + way.reverse());
			return;
		}
		if(edit[i][j] == 'c')
		{
			way.append("c");
			find_minst_way(i-1,j-1);
		}
		else if(edit[i][j] == 'i')
		{
			way.append("i");
			find_minst_way(i-1,j);
		}
		else
		{
			way.append("d");
			find_minst_way(i,j-1);
		}
	}

	String change_string(char[] x, char[] y)
	{	
		int x_index = 0 , y_index = 0; //각각의 문자열의 index를 가르킬 변수
		String temp = way.toString();
		char[] minst_way = temp.toCharArray(); //앞서 최적 루트를 찾은것을 활용
		int len = minst_way.length; // 몇번의 연산을 해야하는지 저장
		
		System.out.print("입력된 문자열 : ");
		for(int i = 0 ; i < x.length ; i++)
			System.out.print(x[i]);
		System.out.println();
		System.out.print("변형 완료 문자열 : ");
		for(int i = 0 ; i < y.length ; i++)
			System.out.print(y[i]);
		System.out.println(); //기본 setting을 출력
		
		for(int i = 0 ; i < len ; i++)
		{
			if(minst_way[i] == 'c')
			{
				if(x[x_index] != y[y_index])
					x[x_index] = y[y_index];
				x_index++; 
				y_index++; //현재 각각의 index가 가르키는 문자들을 교체시킴,
						   //교체 방식은 두 문자열에서 모두 index가 한칸씩 이동하게 됨
				System.out.print(i+1 + " 번째  변경 (c) : ");
				for(int j = 0 ; j < x.length ; j++)
				{
					if(x[j] != '\0')
						System.out.print(x[j]);
				}
				System.out.println();
			}
			else if(minst_way[i] == 'i')
			{
				char[] t = new char[x.length+1];//길이를 +1한 새로운 배열을 선언 t
												//y_index = (y문자열에서 삽입될 문자를 가르킴)
				for(int j = 0 ; j < x_index ; j++)//삽입될 위치 이전의 기존의 문자열을 옮겨줌, y_index 많큼 변화 된 것을 의미
					t[j] = x[j];
				t[x_index] = y[y_index]; //해당 위치에 삽입
				for(int j = x_index; j < x.length; j++)//해당 위치 이후에 기존 문자열을 삽입
					t[j + 1] = x[j];//앞에 새로운 한 칸이 생겼으므로 +1해서 옮겨줌
				x = t;
				x_index++;//x문자열의 길이가 1 증가했으므로, 기존의 x_index와 값을 맞춰주기 위해 증가
				y_index++;//y_index를 증가(삽입)
				System.out.print(i+1 + " 번째  변경 (i) : ");
				for(int j = 0 ; j < x.length ; j++)
				{
					if(x[j] != '\0')
						System.out.print(x[j]);
				}
				System.out.println();
			}
			else if(minst_way[i] == 'd')
			{
				x[x_index] = '\0'; //삭제된 문자를 null문자로 표현 후, 마지막에 한번에 삭제 -> index를 유용하게 사용하기 위해서
				x_index++; //해당 index는 더이상 사용 x
				System.out.print(i+1 + " 번째  변경 (d) : ");
				for(int j = 0 ; j < x.length ; j++)
				{
					if(x[j] != '\0')
						System.out.print(x[j]);
				}
				System.out.println();			
			}
			else
			{
				System.out.println("Error!");
				return null; //에러 처리
			}
		}
		StringBuilder result = new StringBuilder(); //결과 문자열을 String 변수로 저장
		for(int i = 0 ; i < x.length ; i++)
		{
			if(x[i] != '\0') //null문자는 삭제된 문자들이므로, 이들은 제외하여 저장
				result.append(x[i]);
		}
		return result.toString(); //결과 문자열을 return
	}
	
}
