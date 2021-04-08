package String_search;
import java.io.FileReader;
public class counter {
	int i, size;
	char alphabet[] = new char[27];
	int count[] = new int[27];
	
	counter() /* this is CREATER */
	{
		for(i = 0 ; i < 26; i++)
			alphabet[i] = (char)(i+97);
		alphabet[i] = ' '; 
		//alphabet[0] = a ~ alphabet[25] = z , alphabet[26] = ' '
		for(i = 0 ; i < 27 ; i++)
			count[i] = 0;
		size = alphabet.length;
	} 
	public void file_count() throws Exception
	{
		String path = "C:/test/Test1.txt";
		FileReader f = new FileReader(path);
		
		i = 0;
		while( (i = f.read()) != -1 ) //takes a letter from the file.
		{
			char ch = (char)i;
			
			if(ch >= 97 && ch <= 122)
				count[i-97]++; //increase the key for the letter 
			else if(ch == 32) //for space increase
				count[26]++;
			else
				continue; // if the letter is not a~z and ' '
		}
		f.close();
		for(i = 0 ; i < size ; i++)
			System.out.printf(" %3c ",alphabet[i]);
		System.out.println();
		
		for(i = 0 ; i < size ; i++)
			System.out.printf(" %3d ",count[i]);
		System.out.println();
		System.out.println();
		System.out.println();
		
		int remove_size = 0; // find the letter which isn't used in the text.
		for (int j = 0 ; j < count.length - remove_size; j++)
		{
			if(count[j] == 0)
			{
				for(int k = j ; k < count.length -1 ; k++)
				{
					count[k] = count[k+1];
					alphabet[k] = alphabet[k+1];
				} //move to front
				j--; //start again from the deleted index
				remove_size++;
			}
		}
		size = size - remove_size; // a new size will reduce the execute time
	}
	public void count_print()
	{
		for(i = 0 ; i < size ; i++)
			System.out.printf(" %3c ",alphabet[i]);
		System.out.println();
		
		for(i = 0 ; i < size ; i++)
			System.out.printf(" %3d ",count[i]);
		System.out.println();
	}
}

