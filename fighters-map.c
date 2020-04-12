#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "fighters-map.h"

struct table *createTable(int size){
    struct table *t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}

int hashCode(struct table *t,int key){
    if(key<0)
        return -(key%t->size);
    return key%t->size;
}

void insert(struct table *t,int key,char *name, char health){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *temp = list;
    while(temp){
        if(temp->key == key){
            temp->name = name;
            temp->health = health;
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->name = name;
    newNode->health = health;
    newNode->next = list;
    t->list[pos] = newNode;
}

struct node *lookup(struct table *t,int key){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while(temp){
        if(temp->key==key){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int readFightersFromFile(char *fileName){
    printf("in readFightersFromFile1\n");
    int key = 0;
    char *name = NULL;
    char health = 0;
    int fd = open(fileName, O_RDONLY);
    printf("in readFightersFromFile\n");
    if(fd < 0)
        return -1;
    while(read(fd, &key, sizeof(int)) > 0){
        if(!(read(fd, name, sizeof(char) * 50) > 0))
            return -1;
        if(!(read(fd, &health, sizeof(char)) > 0))
            return -1;
        key=0;
        memset(name, ' ', sizeof(char) * 50);
        health=0;
    }
}
