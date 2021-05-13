#include "../headers/header.h"

void create(queue* q){
    q->first = q->last = malloc(sizeof(item));
    q->size = 0;
}

bool empty(queue* q){
    return q->first == q->last;
}

int size(queue* q){
    return q->size;
}

bool push(queue* q, const double value){
    if (!(q->last->next = malloc(sizeof(item)))){
        return false;
    }
    q->last->value = value;
    q->last = q->last->next;
    q->size++;
    return true;
}

double pop(queue* q){
    item *tmp = q->first;
    double value = tmp->value;
    q->first = q->first->next;
    q->size--;
    free(tmp);
    return value;
}

void destroy(queue* q){
    q->last->next = NULL;
    item* tmp = q->first;
    q->first = q->first->next;
    free(tmp);
    if (q->first){
        destroy(q);
    }
    q->last = NULL;
    q->size = 0;
}

