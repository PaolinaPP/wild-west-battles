#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>

#include "fighters-map.h"
#include "pub.h"

int peopleInPubBook = 50;

int main(int argc, char *argv[]) {
    printf("in main\n");
    int fighter1, fighter2;
    struct table *t = createTable(5);
    printf("before insertPeolple\n");
    insertPeople(t);
    printf("before getFighters\n");
    getFighters(&fighter1, &fighter2);
    printf("%d %d\n", fighter1, fighter2);
    //struct node *fighter = lookup(t,5);
    //printf("name:%s health:%d", fighter->name, fighter->health);
    //int retVal = readFightersFromFile("pub-list.txt");

    return 0;
}

void insertPeople(struct table *t){
    printf("in insertPeople\n");
    insert(t,1,"mike alian", 100);
    insert(t,2,"poli hello", 100);
    insert(t,3,"vanio picha", 100);
    insert(t,4,"miro slav", 100);
    insert(t,5,"miro yo", 100);
}

void getFighters(int *fighter1, int *fighter2){
    printf("in getFighters\n");
    do{
        *fighter1 = (rand() % peopleInPubBook + 1);
        *fighter2 = (rand() % peopleInPubBook + 1);
    }while(*fighter2 == *fighter1);
}