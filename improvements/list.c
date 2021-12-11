#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct ListItem {
    int index;

    char blob[2000];
    char * name;
    char * type;
    char * content;
    char * id;
    struct ListItem * next;
    struct ListItem * previous;
} ListItem;

ListItem * createItem() {
    ListItem * item = malloc(sizeof(ListItem));
    return item;
}

ListItem * getLastItem(ListItem * item){
    if(item->next == NULL)
        return item;
    return getLastItem(item->next);
}
ListItem * getFirstItem(ListItem * item){
      if(item->previous == NULL)
        return item;
    return getLastItem(item->previous);
}

void walk(ListItem * list){
    printf("%d\n",list->index);

    char obj[sizeof(list) + 1];
    memcpy(obj, &list, sizeof(list));

    printf("%s %d\n", obj, strlen(obj));
    if(list->next)
        walk(list->next);
}

void addItem(ListItem * parent, ListItem * item){
    ListItem * last = getLastItem(parent);
    last->next = item;
    item->index = last->index + 1;
    item->previous = last;
    //next->next = item;
}


char * createBlob(long size){
    char * blob = malloc(size);
    for(long i = 0; i < size; i++){
        blob[i] = 'Q';
    }
    blob[size] = 0;
    return blob;
}

int main() {
    char * blob = createBlob(1024*1024);

    char * name = "AAAAA";
    ListItem * head = createItem();

    for(int i = 0; i < 1024; i++)
    {
    ListItem * item = createItem();
        item->name = createBlob(1024*1024);
    
    addItem(head, item);
    }
    ListItem * item2 = createItem();
    
    addItem(head, item2);
    walk(head);

    printf("Readyyy: ");   
    char c = getc(stdin);

    return 0;
}