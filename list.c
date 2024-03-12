// list/list.c
//
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


list_t *list_alloc()
{
  list_t *mylist = (list_t *)malloc(sizeof(list_t));
  mylist->head = NULL;
}

void list_free(list_t *l)
{
  if (!l->head)
  {
    return;
  }

  node_t *current = l->head;
  l->head = NULL;
  while (current != NULL)
  {
    node_t *saved = current;
    current = current->next;
    free(saved);
  }
}


//Function to print the current state of the linkedlist
void list_print(list_t *l)
{
  node_t *current = l->head;
  int count = 1;
  printf("{");

  while (current != NULL)
  {
    if (current != l->head)
    {
      printf("->");
    }
    printf("%d[%d]", current->value, count++);
    current = current->next;
  }
  printf("}\n");
}


//Function that converts the linkedlist to a string
char *listToString(list_t *l)
{
  char *buf = (char *)malloc(sizeof(char) * 1024);
  buf[0] = '\0';
  char tbuf[20];
  node_t *curr = l->head;

  while (curr != NULL)
  {
    sprintf(tbuf, "%d", curr->value);
    strcat(buf, tbuf);
    if (curr->next != NULL)
    {
      strcat(buf, "->");
    }
    curr = curr->next;
    
  }
  strcat(buf, "->NULL");
  return buf;
}


//Function that calculates the length of the linkedlist
int list_length(list_t *l)
 { 
  int length = 0;
    node_t *current = l->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}


void list_add_to_back(list_t *l, elem value) {
    


    if (value <0) {
        fprintf(stderr, "FAILED: Attempt to add Negative Value in Linkedlist\n");

        return;        
    }
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
    
    new_node->value = value;
    new_node->next = NULL; // New node will be the last node, so its next should be NULL

    // If the list is empty, set both head and tail to the new node
    if (l->head == NULL) {
        l->head = new_node;
        l->tail = new_node;
    } else {
        // Otherwise, traverse the list to the last node
        node_t *current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Set the next of the last node to the new node
        current->next = new_node;
        // Update the tail pointer to the new node
        l->tail = new_node;
    }

}

void list_add_to_front(list_t *l, elem value)
{
        if (value <0) {
        fprintf(stderr, "FAILED: Attempt to add negative value in Linkedlist\n");

        return;        
    }
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = l->head;
  l->head = new_node;

}

void list_add_at_index(list_t *l, elem value, int index) 
{
    if (!list_length(l)) {

        return;
    }


    if (index <= 0 || value < 0) {
        fprintf(stderr, "Invalid/Negative index or value\n");

        return;        
    }
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->value = value;

    if (index == 1) {
        // Insert at the beginning of the list
        return list_add_to_front(l,value);
    }
    else 
    {
        // Traverse the list to find the node at the previous index
        node_t *current = l->head;
        int i = 1;
        while (current != NULL && i < index - 1) {
            current = current->next;
            i++;
        }

        if (current == NULL) {
            fprintf(stderr, "Index out of bounds\n");
            free(new_node);
            return; 
            
        }

        // Insert the new node after the node at the previous index
        new_node->next = current->next;
        current->next = new_node;

        // Update the tail pointer if the new node is added at the end
        if (new_node->next == NULL) {
            l->tail = new_node;
        }
    }

    // Increment the length of the list
    l->length++;



}

elem list_remove_from_back(list_t *l) {
  if (l == NULL || l->head == NULL) {
        fprintf(stderr, "Empty list\n");
    }

    elem removed_elem;
    // If there's only one node in the list
    if (l->head->next == NULL) {
        removed_elem = l->head->value;
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
    } else {
        node_t *current = l->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        removed_elem = current->next->value;
        free(current->next);
        current->next = NULL;
        l->tail = current;
    }
    return removed_elem;
}



elem list_remove_from_front(list_t *l) {
      if (l == NULL || l->head == NULL) {
        fprintf(stderr, "Empty list\n");
    }

    node_t *temp = l->head;
    elem removed_value = temp->value;

    l->head = l->head->next;
    free(temp);

    // If the list becomes empty after removal
    if (l->head == NULL) {
        l->tail = NULL;
    }

    return removed_value;
}

elem list_remove_at_index(list_t *l, int index)
{
    if (!list_length(l)) {
        fprintf(stderr, "Linked List is empty!\n");

        return -1;
    }

    if (index <= 0) {
        fprintf(stderr, "Invalid index entered\n");

        return -1;        
    }

    if (index == 1) {

        return list_remove_from_front(l);
    }

    node_t *current = l->head;
    node_t *previous = NULL;
    int i = 1;

    // Traverse the list to find the node at the specified index
    while (current != NULL && i < index) {
        previous = current;
        current = current->next;
        i++;
    }

    if (current == NULL) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }

    // Remove the node at the specified index
    previous->next = current->next;
    elem removed_value = current->value;
    free(current);

    return removed_value;


}

bool list_is_in(list_t *l, elem value) { 

    if (!list_length(l)) {

        return false;
    }

    node_t *current = l->head;
    while (current != NULL) {
        if (current->value == value) {
            return true; // Value found in the list
        }
        current = current->next;
    }

    return false; // Value not found in the list

}

elem list_get_elem_at(list_t *l, int index) {
    if (!list_length(l)) {
        fprintf(stderr, "Linkedlist is empty\n");

        return -1;
    }

    if (index < 1) {
        //fprintf(stderr, "Invalid index supplied\n");

        return -1;
    }

    node_t *current = l->head;

    int i = 1;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }

    return current->value;

 }

int list_get_index_of(list_t *l, elem value) { 
    if (value <0){
        fprintf(stderr, "Negative value supplied\n");
        return -1;


    }

    if (l == NULL || l->head == NULL) {
        return -1; // Empty list
    }
    node_t *current = l->head;
    int index = 1;
    while (current != NULL) {
        if (current->value == value) {
            return index; // Value found, return the index
        }
        current = current->next;
        index++;
    }

    return -1; // Value not found in the list


 }
