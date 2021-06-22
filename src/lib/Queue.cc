#include "lib/Queue.h"

void Queue::enqueue (Chain* item)
{
	item->next = 0; 
	*tail = item;    
	tail = &(item->next); 
}


Chain* Queue::dequeue ()
{
	Chain* item;

	item = head;   
	if (item) {
		head = item->next; 
		if (!head)           
			tail = &head;      
		else              
			item->next = 0;  
	}
	return item;
}


void Queue::remove (Chain* item)
{
	Chain* curr;

	if (head) {
		curr = head; 
		if (item == curr)
			dequeue ();    
		else {
			while (curr->next && item != curr->next) 
				curr = curr->next;  

			if (curr->next) {
				curr->next = item->next; 
				item->next = 0;      

				if (!curr->next)     
					tail = &(curr->next); 
			}
		}
	}
}

