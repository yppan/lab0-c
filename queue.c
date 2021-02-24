#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
        return;
    }
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;  // means new element in head
    if (!q) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    size_t s_len = strlen(s) + 1;
    newh->value = (char *) malloc(s_len * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;
    }
    snprintf(newh->value, s_len, "%s", s);
    q->size++;
    newh->next = q->head;
    q->head = newh;
    if (!q->tail) {
        q->tail = newh;
    }
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newt;  // means new element in tail
    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    size_t s_len = strlen(s) + 1;
    newt->value = (char *) malloc(s_len * sizeof(char));
    if (!newt->value) {
        free(newt);
        return false;
    }
    newt->next = NULL;
    snprintf(newt->value, s_len, "%s", s);
    q->size++;
    if (!q->tail) {
        q->tail = newt;
        q->head = newt;
        return true;
    }
    q->tail->next = newt;
    q->tail = newt;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    q->head = q->head->next;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q) {
        return false;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || !q->head || q->size == 1) {
        return;
    }
    list_ele_t *tmp = q->head->next;
    q->tail->next = q->head;
    while (tmp != q->tail) {
        q->head->next = tmp->next;
        tmp->next = q->tail->next;
        q->tail->next = tmp;
        tmp = q->head->next;
    }
    q->tail = q->head;
    q->tail->next = NULL;
    q->head = tmp;
    return;
}

void merge_sort(list_ele_t **head)
{
    if (!(*head) || !((*head)->next)) {
        return;
    }

    list_ele_t *l1 = (*head)->next;  // faster pointer
    list_ele_t *l2 = *head;          // slower pointer

    // split list by moving l1 l2 in different speed
    while (l1 && l1->next) {
        l2 = l2->next;
        l1 = l1->next->next;
    }
    l1 = l2->next;
    l2->next = NULL;
    l2 = *head;

    // Recursively split until each list exist one element
    merge_sort(&l2);  // the left linked list
    merge_sort(&l1);  // the right linked list

    // merge sorted l1 and sorted l2
    // reuse head to record the head of new list
    *head = NULL;
    list_ele_t **tmp = head;

    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) < 0) {  // l1 < l2
            *tmp = l1;
            l1 = l1->next;
        } else {
            *tmp = l2;
            l2 = l2->next;
        }
        tmp = &((*tmp)->next);
    }

    // Either l1 or l2 will left
    *tmp = l1 ? l1 : l2;
}
/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || q->size == 1) {
        return;
    }

    // Merge sort
    merge_sort(&q->head);

    // locate tail pointed to the last element of the list
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}
