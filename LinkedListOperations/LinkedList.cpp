#include <iostream>
#include <stdio.h>
#include <conio.h>

struct Node
{
	int data;
	struct Node* next;
};

//Creates a new node with passed data value
struct Node* newNode(int data)
{
	struct Node* newNode = (struct Node*) malloc (sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;

	return newNode;
}

//Builds a linked list 123
struct Node*
	buildOneTwoThree()
{
	struct Node* first = newNode(1);
	struct Node* second = newNode(2);
	struct Node* third = newNode(3);

	first->next = second;
	second->next = third;

	return first;

}

//Prints a linked list with head passed
void PrintLinkedlist(struct Node* head)
{
	if(head == NULL)
	{
		printf("Empty List\n");
		return;
	}
	struct Node* current = head;
	while(current != NULL)
	{
		printf("%d->", current->data);
		current = current->next;
	}
	printf("NULL");

}

// Pushes a given node in the required position
void Push(struct Node** head, int data)
{
	struct Node* temp = newNode(data);
	temp->next = (*head);
	(*head) = temp;
}

//Computes the length of the linked List
int lengthOfLinkedList(struct Node* head)
{
	int count = 0;
	struct Node* current = head;
	while(current != NULL)
	{
		count++;
		current = current->next;
	}

	return count;
}

//Deletes a given list
void
	DeleteList(struct Node** head)
{
	struct Node* current = *head;
	struct Node* temp;

	while(current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}

	*head = NULL;
}

// Returns the data of the first node in the list and deletes it
int Pop(struct Node** head)
{
	int data = 0;
	struct Node* current = *head;
	struct Node* temp = current->next;
	*head = temp;
	
	data = current->data;
	free(current);
	

	return data;
}

//Inserts at the end of the given list
void PushTail(struct Node** head, int data)
{
	struct Node* newnode = newNode(data);
	struct Node* current = NULL;

	if(*head == NULL)
	{
		*head = newnode;
		return;
	}

	current = *head;
	while(current->next != NULL)
	{
		current = current->next;
	}

	current->next = newnode;
}

//Inserts at Nth position into list
void InsertNth(struct Node** head, int index, int data)
{	
	int len = 0;
	if(*head == NULL)
	{
		struct Node* newnode = newNode(data);
		*head = newnode;
		return;
	}
	len = lengthOfLinkedList(*head);
	if(index > (len))
	{
		printf("Index out of bounds\n");
		return;
	}

	struct Node* current = *head;
	struct Node* prev = NULL;
	int k = 0;

	while(k != index)
	{
		prev = current;
		current = current->next;
		k++;
	}

	struct Node* newnode = newNode(data);
	newnode->next = current;
	prev->next = newnode;
}
// Inserts a node into right position in a sorted LinkedList
void InsertSorted(struct Node** head, int key)
{
	struct Node* current = *head;
	struct Node* prev = NULL;

	if(*head == NULL)
	{
		*head = newNode(key);
		return;
	}

	if(current != NULL)
	{
		if(key < current->data)
		{
			Push(head, key);
			return;
		}
	

		while(current->data < key)
		{
			prev = current;
			if(current->next != NULL)
			{
				current = current->next;
			}
			else
			{
				struct Node* lastnode = newNode(key);
				current->next = lastnode;
				return;
			}
		}
	
		struct Node* newnode = newNode(key);
		newnode->next = current;
		prev->next = newnode;
	}
}

//Sorts a linkedList using InsertSorted
void InsertSort(struct Node** head)
{
	struct Node* current = *head;
	struct Node* sortedList = NULL;
	struct Node* temp = NULL;

	while(current != NULL)
	{
		temp = current->next;
		InsertSorted(&sortedList, current->data);
		current = temp;
	}

	*head = sortedList;
}

//Appends a list b to a and makes b empty
void Append(struct Node** a, struct Node** b)
{
	if(*a != NULL)
	{
		struct Node* current = *a;
		while(current->next != NULL)
		{
			current = current->next;
		}

		if(*b != NULL)
		{
			current->next = *b;
			*b = NULL;
		}
	}
}

// Removes duplicates from a linked list
void RemoveDuplicates(struct Node** head)
{
	int* temp = (int*) malloc (sizeof(int)*100);
	memset (temp, 0, sizeof (int) * 100);
	struct Node* current = *head;
	struct Node* prev = NULL;

	while(current != NULL)
	{
		if(temp[current->data] > 0)
		{
			struct Node* next = current->next;
			free(current);
			prev->next = next;
			current = next;
			continue;
			
		}
		else
		{
			temp[current->data]++;
			//printf("\n data and value %d %d\n", current->data, temp[current->data]);
		}

		prev = current;
		if(current->next != NULL)
		current = current->next;
		else
			return;
	}
}

//Splits the LinkedList into two halves and returns them seperately
void FrontBackSplit(struct Node** head, struct Node** front, struct Node** back)
{
	int firstHalf = 0;
	int secondHalf = 0;
	int len = 0;
	if(*head == NULL)
	{
		printf("List is empty\n");
		return;
	}

	len = lengthOfLinkedList(*head);
	//printf("\nLength %d", len);
	if(len%2 == 0)
	{
		firstHalf = len/2;
		secondHalf = len/2;
	}
	else
	{
		firstHalf = len/2 + 1;
		secondHalf = len/2;
	}

	//*front = *head;
	int index = 0;
	struct Node* current = *head;
	while(index != firstHalf && current != NULL)
	{
		InsertNth(front, index, current->data); 
		current = current->next;
		index++;
	}
	int secondIndex = 0;
	while(index != (len) && current != NULL)
	{
		InsertNth(back, secondIndex, current->data);
		current = current->next;
		secondIndex++;
		index++;
	}
		
	//*back = current;
}

//Moves the node frm the second list to first
void MoveNode(struct Node** dest, struct Node** src)
{
	int temp = 0;
	if(*src == NULL)
	{
		printf("Source list is empty\n");
		return;
	}

	temp = Pop(src);
	struct Node* newnode = newNode(temp);
	if(*dest == NULL)
	{
		*dest = newnode;
		return;
	}
	else
	{
		Push(dest, temp);
	}
}


//Alternatively splitting the list into two lists
void AlternateSplit(struct Node** head, struct Node** first, struct Node** second)
{
	if(*head == NULL)
	{
		printf("Source list is empty\n");
		return;
	}
	struct Node* current = *head;
	while(current != NULL)
	{
		MoveNode(first, &current);
		if(current != NULL)
		MoveNode(second, &current);
	}
}

//Given two lists, merge their nodes together to make one list taking nodes alternatively from both lists
void ShuffleMerge(struct Node** first, struct Node** second, struct Node** mergedList)
{
	int index = 0;
	int temp = 0;
	while(*first != NULL || *second != NULL)
	{
		if(*first != NULL)
		{
			temp = Pop(first);
			InsertNth(mergedList, index, temp);
			index++;
		}
		if(*second != NULL)
		{
			temp = Pop(second);
			InsertNth(mergedList, index, temp);
			index++;
		}
	}
}

// Given Two lists in increasing order, merge them to produce a list in increasing order

void SortedMerge(struct Node** result, struct Node** first, struct Node** second)
{
	struct Node* currentFirst = *first;
	struct Node* currentSecond = *second;
	int temp = 0;
	while(currentFirst != NULL && currentSecond != NULL)
	{
		if(currentFirst->data < currentSecond->data)
		{
			temp = Pop(&currentFirst);
			PushTail(result, temp); 
		}
		else
		{
			temp = Pop(&currentSecond);
			PushTail(result, temp);
		}
	}

	while(currentFirst != NULL)
	{
		temp = Pop(&currentFirst);
		PushTail(result, temp);
	}
	
	while(currentSecond != NULL)
	{
		temp = Pop(&currentFirst);
		PushTail(result, temp);
	}
}

//Merge Sort to sort a linkedList
void MergeSort(struct Node** head)
{
	if(*head == NULL || (*head)->next == NULL)
		return;

	struct Node* a = NULL;
	struct Node* b = NULL;
	struct Node* result;

	FrontBackSplit(head, &a, &b);

	MergeSort(&a);
	MergeSort(&b);

	SortedMerge(head, &a, &b);
}

int main()
{
	int len = 0;
	struct Node* head = buildOneTwoThree();
	Push(&head, 13);
	Push(&(head->next), 42);
	PrintLinkedlist(head);

	len = lengthOfLinkedList(head);
	printf("\nlength of linked list is %d\n", len);

	//DeleteList(&head);
	//PrintLinkedlist(head);

	int data = Pop(&head);
	printf("Popped value is %d\n", data);
	PrintLinkedlist(head);

	//InsertNth(&head, 2, 5);
	printf("\n");
	PrintLinkedlist(head);
	printf("\n..........................................................\n");

	// Insert a node into sorted list
	struct Node* sortedList = buildOneTwoThree();
	InsertSorted(&sortedList, 5);
	PrintLinkedlist(sortedList);
	printf("\n");
	InsertSorted(&sortedList, 4);
	PrintLinkedlist(sortedList);
	printf("\n........................................................\n");

	// Sort a given list
	PrintLinkedlist(head);
	printf("\n");
	InsertSort(&head);
	PrintLinkedlist(head);
	printf("\n");

	//Append a list to another list and make the second list empty
	Append(&head, &sortedList);
	PrintLinkedlist(head);
	printf("\n");
	PrintLinkedlist(sortedList);
	printf("\n..........................................................\n");

	//Remove Duplicates from a linked list
	struct Node* duplicateList = NULL;
	Push(&duplicateList, 5);
	Push(&duplicateList, 2);
	Push(&duplicateList, 1);
	Push(&duplicateList, 2);
	Push(&duplicateList, 3);
	Push(&duplicateList, 5);
	Push(&duplicateList, 5);
	Push(&duplicateList, 6);
	RemoveDuplicates(&duplicateList);
	PrintLinkedlist(duplicateList);
	printf("\n"); 

	// Split the likedList into two halves
	struct Node* front = NULL;
	struct Node* back = NULL;
	FrontBackSplit(&duplicateList, &front, &back);
	PrintLinkedlist(front);
	printf("\n");
	PrintLinkedlist(back);
	printf("\n");

	// Move Node from one list to another
	printf("..........................................................\n");
	MoveNode(&front, &back);
	PrintLinkedlist(front);
	printf("\n");
	PrintLinkedlist(back);
	printf("\n");

	// Alternatively splitting the list into two lists with reversed order of nodes
	printf("..........................................................\n");
	struct Node* first = NULL;
	struct Node* second = NULL;
	PrintLinkedlist(head);
	printf("\n");
	AlternateSplit(&head, &first, &second);
	PrintLinkedlist(first);
	printf("\n");
	PrintLinkedlist(second);
	printf("\n");

	//Given two lists, merge their nodes together to make one list taking nodes alternatively from both lists
	printf("..........................................................\n");
	struct Node* mergedList = NULL;
	ShuffleMerge(&first, &second, &mergedList);
	PrintLinkedlist(mergedList);

	printf("\n");
	printf("..........................................................\n");

	first = NULL;
	second = NULL;
/*	Push(&first, 5);
	Push(&second, 4);
	Push(&first, 3);
	Push(&second, 2);
	Push(&first, 1);
*/
	// Given Two lists in increasing order, merge them to produce a list in increasing order
	Push(&first, 8);
	Push(&first, 7);
	Push(&second, 6);
	Push(&first, 4);
	Push(&first, 3);
	Push(&first, 1);
	Push(&second, 5);
	PrintLinkedlist(first);
	printf("\n");
	PrintLinkedlist(second);
	printf("\n");
	SortedMerge(&sortedList, &first, &second);
	PrintLinkedlist(sortedList);

	printf("\n");
	printf("..........................................................\n");
	struct Node* list = NULL;
	//Merge sort to sort a linkedlist
	Push(&list, 8);
	Push(&list, 7);
	Push(&list, 4);
	Push(&list, 6);
	Push(&list, 9);
	Push(&list, 1);
	Push(&list, 5);
	PrintLinkedlist(list);
	MergeSort(&list);
	printf("\n");
	/*PrintLinkedlist(list);*/


	_getch();
	return 0;
}