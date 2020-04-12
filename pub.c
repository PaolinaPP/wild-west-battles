#include <stdio.h>
//#include <pthread.h>

#include "fighters-map.h"
#include "pub.h"


int main(int argc, char *argv[]) {
    struct table *t = createTable(5);
    insert(t,2,"mike alian", 100);
    insert(t,5,"poli hello", 100);
    struct node *fighter = lookup(t,5);
    printf("name:%s health:%d", fighter->name, fighter->health);

    return 0;
}