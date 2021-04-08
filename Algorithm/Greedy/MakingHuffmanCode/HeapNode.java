package String_search;

public class HeapNode {
	TreeNode tree_node;
	int key;
	HeapNode()
	{
		tree_node = null;
		key = 0;
	}
	HeapNode(HeapNode node)
	{
		tree_node = node.tree_node;
		key = node.key;
	}
}
