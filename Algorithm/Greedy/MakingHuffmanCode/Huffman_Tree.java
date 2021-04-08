package String_search;

public class Huffman_Tree {

	public TreeNode Make_Huffman_Tree() throws Exception
	{
		minHeap heap = new minHeap(27);
		HeapNode n1,n2,n3;
		
		counter count = new counter();
		count.file_count();
		count.count_print();
		

		
		for(int i = 0 ; i < count.size ; i++)
		{
			TreeNode node = new TreeNode();
			node.symbol = count.alphabet[i];
			n1 = new HeapNode();
			n1.key = node.weight = count.count[i];
			n1.tree_node = node;
			heap.Insert(n1);
		} //make min_heap for make huffman_tree
		
		for(int i = 1 ; i < count.size ; i++)
			//if there is n node in MinHeap, it has to do n-1 term
		{
			n1 = new HeapNode();
			n2 = new HeapNode(heap.Remove());
			n3 = new HeapNode(heap.Remove());
			//put two most small key from MinHeap and tie them. by n1 node
			TreeNode x = new TreeNode(n2.tree_node, n3.tree_node);
			n1.key = x.weight = n2.key + n3.key;
			n1.tree_node = x;
			heap.Insert(n1); //and again put them to MinHeap
		}
		n1 = new HeapNode(heap.Remove());
		return n1.tree_node; //this is the root node for tree and it contains huffman tree
	}
	public void Print_Huffman_Tree(TreeNode root, String str)
	{
		if(root == null) { //if tree is empty
			return;
		}
		else if( root.leftchild ==null && root.rightchild == null) {
			System.out.println(root.symbol + ": " + str); 
			//if this node is leaf, print its symbol and it's string
		}
		else
		{
			String Huffman_code = str; //initiator
			Huffman_code +="0"; //add 0 for going to left child
			Print_Huffman_Tree(root.leftchild, Huffman_code); //go to left child
			Huffman_code = str; //initiate again
			Huffman_code += "1"; //add 1 for going to right child
			Print_Huffman_Tree(root.rightchild, Huffman_code); //go to right child
		}
	}
}
