package report;
public class report2 {

	public static void main(String[] args)
	{
		int[] size = {1000,5000,10000,20000,50000,100000}; //n의 개수를 포함하는 배열 선언 및 초기화
		int[] arr; //qiuck sort를 할 정수형 배열
		int[] arr2; //merge sort를 할 정수형 배열
		int count = 0; //반복한 횟수를 count
		long Sum_timeQ = 0, Sum_timeM = 0; //quick sort와 merge sort의 걸린 시간을 합함
		long[] avgQ = new long[6]; //Quick sort에서 각 자료의 수 마다 평균 시간을 저장할 배열
		long[] avgM = new long[6]; //Merge Sort에서 각 자료의 수 마다 평균 시간을 저장할 배열
		
		for(int i = 0; i < 6; i++) //정해놓은 자료의 수가 6가지
		{
			arr = new int[size[i]+2]; //Quick Sort를 위한 배열 초기화
			arr2 = new int[size[i]+2]; //Merge Sort를 위한 배열 초기화
			count = 0; Sum_timeQ = 0; Sum_timeM = 0; //각 변수들의 초기화
			while(count < 10)
			{
				for(int j = 1 ; j <= size[i] ; j++) //데이터 셋 설정
				{
					arr[j] = (int)(java.lang.Math.random()*999);
					arr2[j] = arr[j]; //Quick Sort와 Merge Sort가  같은 배열을 갖고 있을때, 더 정확한 비교 가능
				}
				QuickSortClass1 qs = new QuickSortClass1(arr,size[i]);
				long start1 = System.currentTimeMillis(); //정렬 시작지점
				arr = qs.QuickSortCall(); //정렬
				long end1 = System.currentTimeMillis(); //정렬 끝 지점
				Sum_timeQ += (end1 - start1); //퀵 정렬 후 시간 계산
				
				MergeSortClass ms = new MergeSortClass(arr2,size[i]);
				long start2 = System.currentTimeMillis(); //정렬 시작 지점
				arr2 = ms.MergeSortCall(); //정렬
				long end2 = System.currentTimeMillis(); //정렬 끝 지점
				Sum_timeM += (end2 - start2); //합병 정렬 후 시간 계산
				count++; //한번 수행 완료 했으므로 count +1
				}
			avgQ[i] = Sum_timeQ / 10; //각 10개의 data set으로 실행 했으므로, 10으로 나눈 평균 구하기
			avgM[i] = Sum_timeM / 10; 
		}
		System.out.println("n\t1000\t5000\t10000\t20000\t50000\t100000");
		System.out.println("Quick sort:");
		for(int k = 0 ; k < 6 ; k++)
			System.out.print(avgQ[k] + "\t"); //Quick Sort에서 각 자료의 수에서의 평균 시간 출력
		System.out.print("\n");
		
		System.out.println("merge sort:");
		for(int k = 0 ; k < 6 ; k++) //Merge Sort에서 각 자료의 수에서의 평균 시간 출력
			System.out.print(avgM[k] + "\t");
		System.out.print("\n");
	}
}
