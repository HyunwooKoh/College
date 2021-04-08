package String_search;

public class Test {
	public static void main(String[] args) throws Exception
	{
		Huffman_Tree huff = new Huffman_Tree();
		String str = "";
		TreeNode root = new TreeNode();
		root = huff.Make_Huffman_Tree();
		System.out.println("Huffman code : ");
		huff.Print_Huffman_Tree(root, str);
		
		return ;
	}
}
