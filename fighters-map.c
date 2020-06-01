#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "fighters-map.h"

/***************************************************
*   function name: create_table                    *
*   function parameters: int size                  *
*   function description: create table for map     *
****************************************************/
struct table *create_table(int size)
{
    struct table *t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}

/***************************************************
*   function name: hash_code                       *
*   function parameters: struct table *t,int key   *
*   function description: generate hash code       *
****************************************************/
int hash_code(struct table *t,int key)
{
    if(key < 0)
        return -(key%t->size);
    return key%t->size;
}

/***************************************************
*   function name: insert                          *
*   function parameters: struct table *t,int key,  *
*                        char *name, char health   *
*   function description: insert node to map       *
****************************************************/
void insert(struct table *t,int key,char *name, char health)
{
    int pos = hash_code(t,key);
    struct node *list = t->list[pos];
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *temp = list;
    while(temp)
    {
        if(temp->key == key)
        {
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

/***************************************************
*   function name: lookup                          *
*   function parameters: struct table *t,int key   *
*   function description: find node into map       *
****************************************************/
struct node *lookup(struct table *t,int key)
{
    int pos = hash_code(t,key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while(temp)
    {
        if(temp->key==key)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/***************************************************
*   function name: delete                          *
*   function parameters: struct table *t,int key   *
*   function description: find and delete node     *
****************************************************/
int delete(struct table *t,int key)
{
    int pos = hash_code(t,key);
    struct node *list = t->list[pos];
    struct node **temp = &list;
    struct node *to_free;
    while(*temp)
    {
        to_free = *temp;
        if(to_free->key==key)
        {
            *temp = to_free->next;

            free(to_free);

            return 1;
        }
        temp = &((*temp)->next);
    }
    return 0;

}

/***************************************************
*   function name: read_fighters_from_file         *
*   function parameters: char *file_name           *
*   function description: read nodes from file     *
****************************************************/
int read_fighters_from_file(char *file_name)
{
    printf("in readFightersFromFile1\n");
    int key = 0;
    char *name = NULL;
    char health = 0;
    int fd = open(file_name, O_RDONLY);
    printf("in readFightersFromFile\n");
    if(fd < 0)
        return -1;
    while(read(fd, &key, sizeof(int)) > 0)
    {
        if(!(read(fd, name, sizeof(char) * 50) > 0))
            return -1;
        if(!(read(fd, &health, sizeof(char)) > 0))
            return -1;
        key=0;
        memset(name, ' ', sizeof(char) * 50);
        health=0;
    }
}
