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
		Scanner scanner = new Scanner(System.in); //�Է��� ���� scanner����
		
		
		System.out.println("ù ��° ���ڿ�(����� ���ڿ�)�� ���̴�? : ");
		x_len = scanner.nextInt(); //�迭�� ũ�⸦ �Է¹��� �� ����
		scanner.nextLine(); //�Է� bufferó��
		System.out.println("ù ��° ���ڿ�(����� ���ڿ�)�� �Է��Ͻÿ� : ");
		x_s = scanner.nextLine(); //���ڿ��� �Է� ����
		x = x_s.toCharArray(); //�Է¹��� ���ڿ��� char�� �迭�� ��ȯ
		if(x_len != x.length)
		{
			System.out.println("�Է��Ͻ� ���ڿ��� �־��� ���ڿ��� ���̰� �ٸ��ϴ�.");
			return;
		} //����ó��
		//��� x�� ���̿� y�� ���̴� �Է¹޾Ƶ� ���� ������, �䱸���� �̹Ƿ� �Է¹���

		System.out.println("�� ��° ���ڿ�(�������� �� ���ڿ�)�� ���̴�? : ");
		y_len = scanner.nextInt();
		scanner.nextLine();
		System.out.println("�� ��° ���ڿ�(�������� �� ���ڿ�)�� �Է��Ͻÿ� : ");
		y_s = scanner.nextLine();
		y = y_s.toCharArray();
		if(y_len != y.length)
		{
			System.out.println("�Է��Ͻ� ���ڿ��� �־��� ���ڿ��� ���̰� �ٸ��ϴ�.");
			return;
		} //���� x�� ������ ����
		
		//������ ������ ���� �Է¹���
		cost_class cost = new cost_class(x_len, y_len);
		System.out.println("����(insert), ����(delete), ��ü(change)�� ����� �Է��Ͻÿ�. : ");
		cost.insert = scanner.nextInt();
		cost.delete = scanner.nextInt();
		cost.change = scanner.nextInt();
		
		cost.cost_init(); //cost�� edit �ʱ�ȭ 
		cost.make_cost(x,y); //cost�� ä�� ����
		cost.show_cost(); //cost�� edit ���
		cost.find_minst_way(y.length,x.length); //�ִ� ��� ���
		String R = (String) cost.change_string(x, y); //���ڿ� ��ȯ ����
		System.out.println("���ڿ� ��ȯ ��� : " + R ); //���� ��� ���
		
	}
}