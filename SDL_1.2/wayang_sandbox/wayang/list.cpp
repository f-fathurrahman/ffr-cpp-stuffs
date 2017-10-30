#include <stdlib.h>
#include "list.h"

void iInit(Item* i) {
    i->prev = NULL;
    i->next = NULL;
    i->count = 1;
    i->type = 0;
}

void lInit(List *l) {
    l->first = NULL;
    l->last = NULL;
}

void lAddFirst(List *l, Item *item) {
    item->prev = NULL;
    item->next = l->first;
    if (l->first == NULL) {
        l->last = l->first = item;
    }
    else {
        item->next = l->first;
        l->first->prev = item;
        l->first = item;
    }
}

void lAddLast(List *l, Item *item) {
    item->next = NULL;
    item->prev = l->last;
    if (l->last == NULL) {
        l->last = l->first = item;
    }
    else {
        item->prev = l->last;
        l->last->next = item;
        l->last = item;
    }
}

void lAddAfter(List *l, Item *item, Item *prev) {
    if (prev == l->last) {
        lAddLast(l, item);
    }
    else {
        item->prev = prev;
        item->next = prev->next;
        prev->next->prev = item;
        prev->next = item;
    }
}

void lAddBefore(List *l, Item* item, Item *next) {
    if (next == l->first) {
        lAddFirst(l, item);
        return;
    }
    else {
        item->next = next;
        item->prev = next->prev;
        next->prev->next = item;
        next->prev = item;
    }
}

Item* lCutFirst(List *l) {
    Item* i;
    if (l->first == NULL) return NULL;
    i=l->first;
    l->first = i->next;
    if (l->first == NULL) {
        l->last = NULL;
    }
}

Item* lCutLast(List *l) {
    Item* i;
    if (l->first == NULL) return NULL;
    i=l->first;
    l->first = i->next;
    if (l->first == NULL) {
        l->last = NULL;
    }
}

Item* lCut(List *l, Item *item) {
    if (item == l->first) return lCutFirst(l);
    if (item == l->last) return lCutLast(l);
    item->next->prev = item->prev;
    item->prev->next = item->next;
    item->prev = item->next = NULL;
    return item;
}

bool lMoveLast(List *l, Item *i) {
    // if the last, do nothing
    if (l->last == i) return false;
    // if the first
    if (l->first == i) {
        l->first = i->next;
        i->prev = NULL;
    }
    else {
        // in the middle
        i->prev->next = i->next;
        i->next->prev = i->prev;
    }
    // set as the last one
    i->next = NULL;
    i->prev = l->last;
    l->last->next = i;
    l->last = i;
    return true;
}

bool lMoveFirst(List *l, Item *w) {
    // if the first do nothing
    if (w->prev == NULL)
        return false;
    // if the last
    if (w->next == NULL) {
        l->last = w->prev;
        l->last->next = NULL;
    }
    else {
        // in the middle
        w->prev->next = w->next;
        w->next->prev = w->prev;
    }
    // set as the last one
    w->prev = NULL;
    w->next = l->first;
    l->first->prev = w;
    l->first = w;
    return true;
}


bool lMoveNext(List *l, Item *w) {
    Item* w1;
    w1 = w->next;
    if (w1 != NULL) {
        w1->prev = w->prev;
        w->next = w1->next;
        w1->next = w;
        w->prev = w1;
        if (w->next == NULL) {
            l->last = w;
        }
        return true;
    }
    return false;
}

bool lMovePrev(List *l, Item *w) {
    Item* w1;
    w1 = w->prev;
    if (w1 != NULL) {
        w1->next = w->next;
        w->prev = w1->prev;
        w1->prev = w;
        w->next = w1;
        if (w->prev == NULL) {
            l->first = w;
        }
        return true;
    }
    return false;
}



