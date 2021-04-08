package String_search;

public class minHeap {
	HeapNode heap[];
	int node_num;
	
	minHeap(int len)
	{ //initiator for make MinHeap
		heap = new HeapNode[len+1];
		for(int i = 0 ; i < len + 1 ; i++)
		{
			heap[i] = new HeapNode();
			heap[i].tree_node = new TreeNode();
		}
		node_num = 0;
	}
	public void Insert(HeapNode node) //insert function
	{
		int cur_index;
		cur_index = ++node_num;
		
		while( (cur_index != 1) && (node.key < heap[cur_index/2].key)) //skip when the tree is null and finding 
		{
			heap[cur_index] = heap[cur_index/2];
			cur_index /= 2;
		}
		heap[cur_index] = node;
	}
	public HeapNode Remove() //removing function
	{
		if(node_num < 0)
			return null; //if MinHeap is empty
		int parent = 1, child = 2; //initiate for moving
		HeapNode remove_data, temp;

		remove_data = heap[1]; // index 1 is the least key
		temp = heap[node_num--]; //the last node is going to move for new location.
		
		while(child <= node_num) //until in the heap
		{
			if( (child < node_num) && (heap[child].key > heap[child+1].key) ) //find bigger root's child node
				child++; //move to side node 
			if(temp.key <= heap[child].key)
				break; //find the location
			heap[parent] = heap[child]; //else move child's data to parent
			parent = child; 
			child *= 2; //move child and parent to next level on heap
		}
		heap[parent] = temp; // insert the last node to the location 
		return remove_data; //return the least data on heap
	}
}
