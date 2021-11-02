#include <stddef.h>
#include "list.h"

/* Process { int id; int burst; int priority; int waittime; Process* next; }; */

//add a new Process to the beginning of a list
Process* push(Process* head, Process* newNode) {
  newNode->next = head;
  return newNode;
}

//splits a Process* list in two for merge sorting
void split(Process* head, Process** front, Process** back) {
	Process* travel = head->next;
	Process* slow = head;
	*front = head;

	//travel moves twice for every 1 move slow makes
	//and stops when travel reaches the end so slow is mid-1
	while(travel != NULL) {
		travel = travel->next;
		if (travel != NULL) {
			travel = travel->next;
			slow = slow->next;
		}
	}
	//assign back to the mid element in the list and NULL terminate the front half
	*back = slow->next;
	slow->next = NULL;
}

//recursively move the largest first element of 2 lists to a new one
Process* merge(Process* front, Process* back) {
	if(front == NULL)
			return back;
	else if (back == NULL)
			return front;

	Process* merged;
	//elements with the same count are added in order of first appearance
	//since new elements are added to the front, favor the one in back
	if(front->id < back->id) {
		merged = front;
		merged->next = merge(front->next, back);
	} else {
		merged = back;
		merged->next = merge(front, back->next);
	}
	return merged;
}

//recusrively splits and sorts a Process* list using merge sort
//uses double pointers so that the list pointer can be overwritten
void sort(Process** list) {
	Process*	head = *list;
	Process* front, *back;

	if (head == NULL || head->next == NULL)
		return;

	split(head, &front, &back);
	sort(&front);
	sort(&back);
	//recursively merge the list
	*list = merge(front, back);
}
