package abc;
import java.util.Scanner;

public class test {

	public static void main(String[] args)
	{
		char[] x = null;
		char[] y = null;
		String x_s, y_s;
		
		int x_len, y_len;
		@SuppressWarnings("resource")
		Scanner scanner = new Scanner(System.in); //입력을 위한 scanner선언
		
		
		System.out.println("첫 번째 문자열(변경될 문자열)의 길이는? : ");
		x_len = scanner.nextInt(); //배열의 크기를 입력받은 후 저장
		scanner.nextLine(); //입력 buffer처리
		System.out.println("첫 번째 문자열(변경될 문자열)을 입력하시오 : ");
		x_s = scanner.nextLine(); //문자열을 입력 받음
		x = x_s.toCharArray(); //입력받은 문자열을 char형 배열로 변환
		if(x_len != x.length)
		{
			System.out.println("입력하신 문자열과 주어진 문자열의 길이가 다릅니다.");
			return;
		} //에러처리
		//사실 x의 길이와 y의 길이는 입력받아도 되지 않지만, 요구사항 이므로 입력받음

		System.out.println("두 번째 문자열(기준으로 할 문자열)의 길이는? : ");
		y_len = scanner.nextInt();
		scanner.nextLine();
		System.out.println("두 번째 문자열(기준으로 할 문자열)을 입력하시오 : ");
		y_s = scanner.nextLine();
		y = y_s.toCharArray();
		if(y_len != y.length)
		{
			System.out.println("입력하신 문자열과 주어진 문자열의 길이가 다릅니다.");
			return;
		} //위의 x와 동일한 과정
		
		//각각의 연산의 값을 입력받음
		cost_class cost = new cost_class(x_len, y_len);
		System.out.println("삽입(insert), 삭제(delete), 교체(change)의 비용을 입력하시오. : ");
		cost.insert = scanner.nextInt();
		cost.delete = scanner.nextInt();
		cost.change = scanner.nextInt();
		
		cost.cost_init(); //cost와 edit 초기화 
		cost.make_cost(x,y); //cost를 채워 넣음
		cost.show_cost(); //cost와 edit 출력
		cost.find_minst_way(y.length,x.length); //최단 방식 출력
		String R = (String) cost.change_string(x, y); //문자열 변환 과정
		System.out.println("문자열 변환 결과 : " + R ); //최종 결과 출력
		
	}
}