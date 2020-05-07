#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/battle.h"
#include "include/fighters-map.h"

#define FULL_HEALTH_MAX_DAMAGE     20
#define NOT_FULL_HEALTH_MAX_DAMAGE 100
#define FULL_HEALTH                100
#define MIN_HEALTH                 1

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

    while(dead_fighter != 1) //loop while there is no dead fighter
    {
        sem_wait(&lock); //wait for free semaphore

        if(is_fighter_health_full(&fighter)) //check is fighter health 100
        {
            damage = (rand() % FULL_HEALTH_MAX_DAMAGE + 1); //if true then damage can be between 1 and 20
        }
        else
        {
            damage = (rand() % NOT_FULL_HEALTH_MAX_DAMAGE + 1); //if false then damage can be between 1 and 100
        }

        fighter->health -= damage;

        if(fighter->health < MIN_HEALTH) //check is fighter health less than 1
        {
            dead_fighter = 1; //set there is death fighter
            sem_post(&lock);
            pthread_exit(NULL);
        }
        sem_post(&lock); //unlock semaphore 
        sleep(1);
    }
    dead_fighter = 0;
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
    if ((*fighter)->health == FULL_HEALTH)
    {
        return 1;
    }

    return 0;
}