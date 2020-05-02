#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/battle.h"
#include "include/fighters-map.h"

/*0->NO dead fighter; 1->dead fighter*/
char dead_fighter = 0;

/***************************************************
*   function name: fighter_func                    *
*   function parameters: void *args                *
*   function description: realize fight using      *
*        random damage                             *
****************************************************/
void *fighter_func(void *args)
{
    struct node *fighter = (struct node *)args;
    int damage;

    printf("fighter key %d\n", fighter->key);
    printf("fighter name %s\n", fighter->name);
    printf("dead_fighter = %d\n", dead_fighter);

    while(dead_fighter != 1) //loop while there is no dead fighter
    {
        sem_wait(&lock); //wait for free semaphore

        if(is_fighter_health_full(&fighter)) //check is fighter health 100
        {
            printf("fighter health is full");
            damage = (rand() % 20 + 1); //if true then damage can be between 1 and 20
        }
        else
        {
            damage = (rand() % 100 + 1); //if false then damage can be between 1 and 100
        }
        printf("health %d \n", fighter-> health);
        printf("damage %d\n", damage);
        fighter->health -= damage;
        if(fighter->health < 1) //check is fighter health less than 1
        {
            dead_fighter = 1; //set there is death fighter
            pthread_exit(NULL);
        }


        sem_post(&lock); //unlock semaphore
        sleep(1);    
    }
    pthread_exit(NULL);

}

/***************************************************
*   function name: is_fighter_health_full          *
*   function parameters: struct node **fighter     *
*   function description: check is fighter health  *
*        full (100)                                *
****************************************************/
int is_fighter_health_full(struct node **fighter)
{
    if ((*fighter)->health == 100)
    {
        return 1;
    }

    return 0;
}