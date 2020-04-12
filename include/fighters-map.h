#ifndef FIGHTERS_MAP_H_
#define FIGHTERS_MAP_H_

struct node{
    int key;
    char * name;
    char health;
    struct node *next;
};

struct table{
    int size;
    struct node **list;
};

struct table *createTable(int size);
int hashCode(struct table *t,int key);
void insert(struct table *t,int key,char * name, char health);
struct node *lookup(struct table *t,int key);

#endif /* FIGHTERS_MAP_H_ */