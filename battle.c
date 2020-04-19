#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/battle.h"
#include "include/fighters-map.h"

/*0->NO dead fighter; 1->dead fighter*/
char dead_fighter = 0;

void *fighterFunc(void *args)
{
    struct node *fighter = (struct node*)malloc(sizeof(struct node));
    fighter = (struct node *)args;
    char full_health = 0;
    int damage;

    printf("fighter %d\n", fighter->key);
    printf("dead_fighter = %d\n", dead_fighter);

    if (fighter->health == 100)
        full_health = 1;

    while(dead_fighter != 1)
    {
        if(dead_fighter == 1)
            pthread_exit(NULL);

        sem_wait(&lock);

        if(full_health == 1)
        {
            damage = (rand() % 20 + 1);
            full_health = 0;
        }
        else
        {
            damage = (rand() % 100 + 1);
        }

        fighter->health -= damage;
        if(fighter->health < 1)
        {
            dead_fighter = 1;
            pthread_exit(NULL);
        }


        sem_post(&lock);
        sleep(1);    
    }

} 