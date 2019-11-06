#include "huffman.h"

Node * getTree(long * counts, int * depth)
{
    /*
	FILE * fptr = fopen(countfile, "r");
	if (!fptr) {
		fprintf(stderr, "unable to open count file in tree_info()");
		*depth += 1; //indicates failure and not an empty list
		return NULL;
	}
	FILE * outptr = fopen(outfile, "w");
	if (!outptr) {
		fprintf(stderr, "unable to open output file in tree_info()");
		//fclose(fptr);
		*depth += 1;
		return NULL;
	}
    */

	//long count;
	Node * head = NULL;
	Node * new = NULL;
	//while (fread(&count, sizeof(long), 1, fptr)) {
	unsigned char ascii = 0;
    do {
		if (counts[ascii]) {
			*depth += 1;
			//ascii = ftell(fptr) / 8 - 1;
			new = createNode(ascii, counts[ascii]);
			if (new == NULL) {
				//malloc fail
				while (head != NULL) {
					Node * temp = head->next;
					free(head);
					head = temp;
				}
                //fclose(outptr);
				return NULL;
			}
			head = ListInsert(head, new);
		}
        ascii++;
	} while (ascii > 0);

	if (head == NULL) {
		//fclose(fptr);
		//fclose(outptr);
		return head; //file is empty -- print that its empy/do anything different?
	} //add a similar one for files with some but not very many bytes

	head = constructTree(head);
	//writeTopology(head, outptr);
	//fclose(fptr);
	//fclose(outptr);

	return head;
}
//-----------------------------------------------------------
Node * constructTree(Node * head)
{
	Node * save = NULL;
	while (head->next != NULL) {
		save = (head->next)->next;
		head = mergeNodes(head, head->next);
		head = ListInsert(save, head);
	}
	return head;
}
//-----------------------------------------------------------
Node * mergeNodes(Node * left, Node * right)
{
	right->next = NULL;
	left->next = NULL;
	Node * combined = createNode('\0', left->count + right->count);
	combined->left = left;
	combined->right = right;
	return combined;
}
//-----------------------------------------------------------
Node * ListInsert(Node * head, Node * new)
{
	if (head == NULL) {
		return new;
	}
	if (new->count > head->count) {
		head->next = ListInsert(head->next, new);
		return head;
	}
	if (new->count == head->count) {
		if (new->figure > head->figure || 
				((new->left != NULL) || 
				 (new->right != NULL))) 
		{
			//if (new->figure > head->figure || !new->figure) {
			//^^binary file may contain '\0' for legitimate use
			head->next = ListInsert(head->next, new);
			return head;
		}
	}
	new->next = head;
	return new;
}
//-----------------------------------------------------------
Node * createNode(unsigned char figure, long count)
{
	Node * node = malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "malloc() fail in createNode()\n");
		return NULL;
	}
	node->next = NULL;
	node->left = NULL;
	node->right = NULL;
	node->figure = figure;
	node->count = count;
	return node;
}
//-----------------------------------------------------------
void printList(Node * head) {
	while (head != NULL) {
		fprintf(stdout, "%c   (%ld)\n", head->figure, head->count);
		head = head->next;
	}
	return;
}
/*
//-----------------------------------------------------------
void writeTopology(Node * head, FILE * outptr) {
	if (head->left != NULL || head->left != NULL) {
	//if (head->left != NULL || head->right != NULL) {      //
		fwrite("0", sizeof(unsigned char), 1, outptr);
		writeTopology(head->left, outptr);
		writeTopology(head->right, outptr);
	} else {
		fwrite("1", sizeof(unsigned char), 1, outptr);
		fwrite(&head->figure, sizeof(unsigned char), 1, outptr);
	}
	return;
}
*/
void clearTree(Node * n)
{
	if (n == NULL) { return; }
	clearTree(n->left);
	clearTree(n->right);
	free(n);
}
