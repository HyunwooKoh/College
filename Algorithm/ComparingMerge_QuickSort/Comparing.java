package report;
public class report2 {

	public static void main(String[] args)
	{
		int[] size = {1000,5000,10000,20000,50000,100000}; //n�� ������ �����ϴ� �迭 ���� �� �ʱ�ȭ
		int[] arr; //qiuck sort�� �� ������ �迭
		int[] arr2; //merge sort�� �� ������ �迭
		int count = 0; //�ݺ��� Ƚ���� count
		long Sum_timeQ = 0, Sum_timeM = 0; //quick sort�� merge sort�� �ɸ� �ð��� ����
		long[] avgQ = new long[6]; //Quick sort���� �� �ڷ��� �� ���� ��� �ð��� ������ �迭
		long[] avgM = new long[6]; //Merge Sort���� �� �ڷ��� �� ���� ��� �ð��� ������ �迭
		
		for(int i = 0; i < 6; i++) //���س��� �ڷ��� ���� 6����
		{
			arr = new int[size[i]+2]; //Quick Sort�� ���� �迭 �ʱ�ȭ
			arr2 = new int[size[i]+2]; //Merge Sort�� ���� �迭 �ʱ�ȭ
			count = 0; Sum_timeQ = 0; Sum_timeM = 0; //�� �������� �ʱ�ȭ
			while(count < 10)
			{
				for(int j = 1 ; j <= size[i] ; j++) //������ �� ����
				{
					arr[j] = (int)(java.lang.Math.random()*999);
					arr2[j] = arr[j]; //Quick Sort�� Merge Sort��  ���� �迭�� ���� ������, �� ��Ȯ�� �� ����
				}
				QuickSortClass1 qs = new QuickSortClass1(arr,size[i]);
				long start1 = System.currentTimeMillis(); //���� ��������
				arr = qs.QuickSortCall(); //����
				long end1 = System.currentTimeMillis(); //���� �� ����
				Sum_timeQ += (end1 - start1); //�� ���� �� �ð� ���
				
				MergeSortClass ms = new MergeSortClass(arr2,size[i]);
				long start2 = System.currentTimeMillis(); //���� ���� ����
				arr2 = ms.MergeSortCall(); //����
				long end2 = System.currentTimeMillis(); //���� �� ����
				Sum_timeM += (end2 - start2); //�պ� ���� �� �ð� ���
				count++; //�ѹ� ���� �Ϸ� �����Ƿ� count +1
				}
			avgQ[i] = Sum_timeQ / 10; //�� 10���� data set���� ���� �����Ƿ�, 10���� ���� ��� ���ϱ�
			avgM[i] = Sum_timeM / 10; 
		}
		System.out.println("n\t1000\t5000\t10000\t20000\t50000\t100000");
		System.out.println("Quick sort:");
		for(int k = 0 ; k < 6 ; k++)
			System.out.print(avgQ[k] + "\t"); //Quick Sort���� �� �ڷ��� �������� ��� �ð� ���
		System.out.print("\n");
		
		System.out.println("merge sort:");
		for(int k = 0 ; k < 6 ; k++) //Merge Sort���� �� �ڷ��� �������� ��� �ð� ���
			System.out.print(avgM[k] + "\t");
		System.out.print("\n");
	}
}
