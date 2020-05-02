#ifndef FIGHTERS_MAP_H_
#define FIGHTERS_MAP_H_

struct node{
    int key;
    char *name;
    char health;
    struct node *next;
};

struct table{
    int size;
    struct node **list;
};

struct table *create_table(int size);
int hash_code(struct table *t,int key);
void insert(struct table *t,int key,char *name, char health);
struct node *lookup(struct table *t,int key);
int read_fighters_from_file(char *file_name);
int delete(struct table *t,int key);

#endif /* FIGHTERS_MAP_H_ */