package abc;

public class cost_class {
	int cost[][]; //������ index������ �ּ� ����� ����
	char edit[][]; //������ ��� ������ �ߴ��� ����, �Ŀ� �ּ� ����� ������ �� ��� ��
	int insert , delete , change; //����, ����, ��ü �ϴµ� ��� ���
	int x_len, y_len; //�� ���ڿ��� ����
	StringBuilder way = new StringBuilder(); //������ ���ڿ� ��ȯ ����� ����
	
	cost_class(int x, int y)
	{
		x_len = x;
		y_len = y;
		cost = new int[y_len+1][x_len+1]; //�� ���ڿ��� ÷�ڵ� ��Ÿ���� ����, ��ĭ �� �� ����
		edit = new char[y_len+1][x_len+1];

		insert = 0 ; delete = 0 ; change = 0;
	}
	void cost_init() //cost�� ���ϱ� ��, cost�� edit �迭 �ʱ�ȭ
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
	
	void make_cost(char[] x, char[] y) //cost �迭�� ���� ä�� ����
	{
		for(int i = 1 ; i < x_len + 1 ; i++)
		{
			for(int j = 1 ; j < y_len + 1 ; j++)
			{
				if(x[i-1] == y[j-1]) //���� �� ���ڿ����� ������ index�� ���ڰ� ���ٸ�, ��ü ����� 0�̹Ƿ�, ��ü�ϴ� ����� ����
				{
					cost[j][i] = cost[j-1][i-1];
					edit[j][i] = 'c';
				}
				else
				{
					cost[j][i] = Math.min( Math.min(cost[j-1][i-1]+change, cost[j-1][i] + insert) , cost[j][i-1] + delete); //������ ������ ���� ���� ���� ã����
					
					if(cost[j][i] == cost[j-1][i-1] + change)
						edit[j][i] = 'c'; // ��ü�� �켱������ ��
					else if(cost[j][i] == cost[j-1][i] + insert)
						edit[j][i] = 'i';
					else if(cost[j][i] == cost[j][i-1] + delete)
						edit[j][i] = 'd';
					else
						edit[j][i] = '?'; //���� Ž��
				}
			}
		}
	}
	
	void show_cost() //cost�� edit�� ���� ���
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
	void find_minst_way(int i, int j) //������ ���ڿ� ��ȯ ����� ������ ���� ���� , ��ȯ ȣ�� ����� ����
	{
		if( (i == 0) && (j == 0) ) //ó���� �����ϸ� ����
		{
			System.out.println("�������� ���� ������ : " + way.reverse());
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
		int x_index = 0 , y_index = 0; //������ ���ڿ��� index�� ����ų ����
		String temp = way.toString();
		char[] minst_way = temp.toCharArray(); //�ռ� ���� ��Ʈ�� ã������ Ȱ��
		int len = minst_way.length; // ����� ������ �ؾ��ϴ��� ����
		
		System.out.print("�Էµ� ���ڿ� : ");
		for(int i = 0 ; i < x.length ; i++)
			System.out.print(x[i]);
		System.out.println();
		System.out.print("���� �Ϸ� ���ڿ� : ");
		for(int i = 0 ; i < y.length ; i++)
			System.out.print(y[i]);
		System.out.println(); //�⺻ setting�� ���
		
		for(int i = 0 ; i < len ; i++)
		{
			if(minst_way[i] == 'c')
			{
				if(x[x_index] != y[y_index])
					x[x_index] = y[y_index];
				x_index++; 
				y_index++; //���� ������ index�� ����Ű�� ���ڵ��� ��ü��Ŵ,
						   //��ü ����� �� ���ڿ����� ��� index�� ��ĭ�� �̵��ϰ� ��
				System.out.print(i+1 + " ��°  ���� (c) : ");
				for(int j = 0 ; j < x.length ; j++)
				{
					if(x[j] != '\0')
						System.out.print(x[j]);
				}
				System.out.println();
			}
			else if(minst_way[i] == 'i')
			{
				char[] t = new char[x.length+1];//���̸� +1�� ���ο� �迭�� ���� t
												//y_index = (y���ڿ����� ���Ե� ���ڸ� ����Ŵ)
				for(int j = 0 ; j < x_index ; j++)//���Ե� ��ġ ������ ������ ���ڿ��� �Ű���, y_index ��ŭ ��ȭ �� ���� �ǹ�
					t[j] = x[j];
				t[x_index] = y[y_index]; //�ش� ��ġ�� ����
				for(int j = x_index; j < x.length; j++)//�ش� ��ġ ���Ŀ� ���� ���ڿ��� ����
					t[j + 1] = x[j];//�տ� ���ο� �� ĭ�� �������Ƿ� +1�ؼ� �Ű���
				x = t;
				x_index++;//x���ڿ��� ���̰� 1 ���������Ƿ�, ������ x_index�� ���� �����ֱ� ���� ����
				y_index++;//y_index�� ����(����)
				System.out.print(i+1 + " ��°  ���� (i) : ");
				for(int j = 0 ; j < x.length ; j++)
				{
					if(x[j] != '\0')
						System.out.print(x[j]);
				}
				System.out.println();
			}
			else if(minst_way[i] == 'd')
			{
				x[x_index] = '\0'; //������ ���ڸ� null���ڷ� ǥ�� ��, �������� �ѹ��� ���� -> index�� �����ϰ� ����ϱ� ���ؼ�
				x_index++; //�ش� index�� ���̻� ��� x
				System.out.print(i+1 + " ��°  ���� (d) : ");
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
				return null; //���� ó��
			}
		}
		StringBuilder result = new StringBuilder(); //��� ���ڿ��� String ������ ����
		for(int i = 0 ; i < x.length ; i++)
		{
			if(x[i] != '\0') //null���ڴ� ������ ���ڵ��̹Ƿ�, �̵��� �����Ͽ� ����
				result.append(x[i]);
		}
		return result.toString(); //��� ���ڿ��� return
	}
	
}
