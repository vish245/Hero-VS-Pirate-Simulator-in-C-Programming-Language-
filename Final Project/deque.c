#include "defs.h"


/*
  Function:  initDeque
  Purpose:   Initialie the head and tail nodes of the deque.
       in:   deque to be initialized
   return:   void
*/

void initDeque(DequeType *deque) {
  (deque)->head = NULL;
  (deque)->tail = NULL;

}

/*
  Function:  addFighter
  Purpose:   Add a fighter to the back of the deque.
       in:   deque to store the fighters
       in:   fighters to be added to the deque.
   return:   void
*/

void addFighter(DequeType *deque, FighterType *fighter) {
  NodeType *currentNode;
  NodeType *newNode;

  if(deque->head==NULL && deque->tail==NULL){
    newNode=malloc(sizeof(NodeType));
    newNode->data=fighter;
    newNode->next=NULL;
    deque->head=newNode;
    deque->tail=newNode;
  }else{
    currentNode=deque->tail;
    newNode=malloc(sizeof(NodeType));
    newNode->data=fighter;
    newNode->next=NULL;
    currentNode->next=newNode;
    deque->tail=newNode;
  }
}

/*
  Function:  removeFromBack
  Purpose:   Remove the last element from the deque.
       in:   deque to store the fighters
       in:   fighters to be added to the deque.
   return:   void
*/

void removeFromBack(DequeType *deque, FighterType **fighter) {
  NodeType *l=deque->head;
  NodeType *sl=deque->head;
  while(l->next!=NULL){
    sl=l;
    l=l->next;
  }
  if(l==deque->head){
    deque->head=NULL;
    deque->tail=NULL;
  }else{
    sl->next=NULL;
  }
  *fighter=l->data;
  free(l);
}


/*
  Function:  removeFromFront
  Purpose:   Remove the first element from the deque.
       in:   deque to store the fighters
       in:   fighters to be added to the deque.
   return:   void
*/

void removeFromFront(DequeType *deque, FighterType **fighter) {
  NodeType *currentNode = deque->head;
  if (currentNode != NULL) {
    *fighter = currentNode->data;
    //NodeType *temp = currentNode;
    //currentNode = currentNode->next;
    deque->head=currentNode->next;
    free(currentNode);
  }
}



/*
  Function:  deepCopy
  Purpose:   copy the data (all elements) of a deque into another deque.
       in:   deque to store the fighters
      out:   new empty deque that will contain fighters to be added to the deque.
   return:   void
*/

void deepCopy(DequeType *deque, DequeType *emptyDeque) {
    NodeType *current = deque->head;        // used to iterate over the original list
    //emptyDeque->head  = NULL;
    initDeque(emptyDeque);
    NodeType *newList = emptyDeque->head;   // head of the new list
    NodeType *tail =NULL;    // point to the last node in a new list
    FighterType *new;
    //NodeType *newNode;
    while (current != NULL)
    {
        // special case for the first new node
        if (newList == NULL)
        {
            newList= malloc(sizeof(NodeType));
            initFighter(current->data->strength,current->data->armour,current->data->health,&new);
            newList->data=new;
            newList->next = NULL;
            emptyDeque->head=newList;
            emptyDeque->tail=newList;
            tail = newList;
        }
        else {
            tail->next = malloc(sizeof(NodeType));
            tail = tail->next;
            initFighter(current->data->strength,current->data->armour,current->data->health,&new);
            tail->data = new;
            tail->next = NULL;
        }

        current = current->next;
    }
}


/*
  Function:  cleanDeque
  Purpose:   free the deque space stored in the heap.
       in:   deque to store the fighters
   return:   void
*/

void cleanDeque(DequeType *deque) {
    NodeType *curr=deque->head;
    NodeType *next=NULL;
    while(curr!=NULL){
        next=curr->next;
        free(curr->data);
        free(curr);
        curr=next;
    }
}
