#ifndef _LIST_H_INCLUDED
#define _LIST_H_INCLUDED

typedef struct Item {
    struct Item *prev, *next;
    int type, count;
} Item;

typedef struct List {
    Item* first;
    Item* last;
} List;

void iInit(Item* i);
static inline Item* iNext(Item* i) {return i->next;}
static inline Item* iPrev(Item* i) {return i->prev;}
static inline int iCount(Item* i) {return i->count;}
static inline int iUse(Item* i) {return ++(i->count);}
static inline int iFree(Item* i) {return --(i->count);}

void lInit(List *l);
void lAddFirst(List *l, Item *item);
void lAddLast(List *l, Item *item);
void lAddAfter(List *l, Item *item, Item *prev);
void lAddBefore(List *l, Item* item, Item *next);

Item* lCut(List *l, Item *item);
Item* lCutFirst(List *l);
Item* lCutLast(List *l);

bool lMoveLast(List *l, Item *w);
bool lMoveFirst(List *l, Item *w);
bool lMoveNext(List *l, Item *w);
bool lMovePrev(List *l, Item *w);

static inline Item* lFirst(List *l) {return l->first;}
static inline Item* lLast(List* l) {return l->last;}

#endif // _LIST_H_INCLUDED

