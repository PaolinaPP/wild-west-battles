#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/fighters-map.h"
#include "include/pub.h"
#include "include/battle.h"

#define NUM_THREADS   2
#define ALL_PEOPLE    6

int alive_people = ALL_PEOPLE;
int array_of_keys[ALL_PEOPLE];

int main(int argc, char *argv[])
{
    pthread_t fighters_th[NUM_THREADS];
    struct table *t = createTable(alive_people);
    struct node *fighters[NUM_THREADS];
    int fighter_map_key[NUM_THREADS], fighter_array_number[NUM_THREADS], i;

    if (sem_init(&lock, 0, 1) != 0)
    {
        printf("\n Mutex initialization failed\n");
        return 1;
    }

    insertPeople(t);
    
    while(alive_people > 0)
    {
        getFighters(&fighter_map_key[0], &fighter_map_key[1], &fighter_array_number[0], &fighter_array_number[1]);


        for(i = 0; i < NUM_THREADS; i++)
        {
            fighters[i] = lookup(t, fighter_map_key[i]);
            printf("fighter health: %d name: %s\n", fighters[i]->health, fighters[i]->name);
            if(pthread_create(&fighters_th[i], NULL, fighterFunc, (void *)&fighters[i]))
            {
                printf("Error in creating posix thread!");
            }
            
        }

        for(i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(fighters_th[i], NULL);
        }

        for(i = 0; i < NUM_THREADS; i++)
        {
            if(fighters[i]->health < 1)
            {
                array_of_keys[fighter_array_number[i]] = -1;
            }
        }

        alive_people--;

        pthread_exit(NULL);
    }
    //pthread_exit(NULL);

    //printf("%d %d\n", fighters[0], fighters[1]);
    //struct node *fighter = lookup(t,5);
    //printf("name:%s health:%d", fighter->name, fighter->health);
    //int retVal = readFightersFromFile("pub-list.txt");

    sem_destroy(&lock);
    return 0;
}

void insertPeople(struct table *t)
{
    int i;

    for(i = 0; i < ALL_PEOPLE; i++){
        array_of_keys[i] = i+1;
    }

    insert(t,1,"mike alian", 100);
    insert(t,2,"poli hello", 100);
    insert(t,3,"vanio picha", 100);
    insert(t,4,"miro slav", 100);
    insert(t,5,"miro yo", 100);
    insert(t,6,"miro yvgfrvto", 100);
    
}

void getFighters(int *fighter1, int *fighter2, int *fighter1_array_number, int *fighter2_array_number)
{
    int i, key1 = 0, key2 = 0;

    do{
        key1 = (rand() % ((alive_people - 1) + 1));
        key2 = (rand() % ((alive_people - 1) + 1));
    }while(key1 == key2);

    if(alive_people == ALL_PEOPLE)
    {
        *fighter1 = array_of_keys[key1];
        *fighter2 = array_of_keys[key2];
        *fighter1_array_number = key1;
        *fighter2_array_number = key2;
    }
    else 
    {
        for(i = 0; i < ALL_PEOPLE; i++)
        {
            if(key1 < 0 && key2 < 0)
            {
                break;
            }
            if(key1 == 0)
            {
                *fighter1 = array_of_keys[i];
                *fighter1_array_number = i;
            }
            if(key2 == 0)
            {
                *fighter2 = array_of_keys[i];
                *fighter2_array_number = i;
            }
            if(array_of_keys[i] != -1)
            {
                key1--;
                key2--;
            }
        }
    }
}
