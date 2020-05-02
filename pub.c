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
    struct table *t = create_table(alive_people);
    struct node *fighters[NUM_THREADS];
    int fighter_map_key[NUM_THREADS], fighter_array_number[NUM_THREADS], i;

    initialize_mutex(); //initialize mutex to use it later

    insert_people(t); //insert people to map
    
    while(alive_people > 1) //loop running while there are stile alive people
    {
        get_fighters(&fighter_map_key[0], &fighter_map_key[1], &fighter_array_number[0], &fighter_array_number[1]); //calling function to get 2 RANDOM fighters

        for(i = 0; i < NUM_THREADS; i++)
        {
            fighters[i] = lookup(t, fighter_map_key[i]); //getting fighters nodes of map
            printf("fighter health: %d name: %s key: %d\n", fighters[i]->health, fighters[i]->name, fighters[i]->key);
            if(pthread_create(&fighters_th[i], NULL, fighter_func, (void *) fighters[i])) //creating fighter thread
            {
                printf("Error in creating posix thread!");
            }
        }

        for(i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(fighters_th[i], NULL); //join threads
        }

        for(i = 0; i < NUM_THREADS; i++)
        {
            if(fighters[i]->health < 1) //if the fighter has no more health
            {   
                printf("Dead fighter %s\n", fighters[i]->name);
                array_of_keys[fighter_array_number[i]] = -1; //set -1 value to array_of_keys to mark the fighter has no more health
                if(!delete(t, fighters[i]->key)) //check is fighter deleted of map
                {
                    printf("fighter not deleted!\n");
                }
            }
            else 
            {
                printf("WINNER: %s, HEALTH: %d\n", fighters[i]->name, fighters[i]->health);
            }
        }

        alive_people--;
    }

    
    pthread_exit(NULL);

    //printf("%d %d\n", fighters[0], fighters[1]);
    //struct node *fighter = lookup(t,5);
    //printf("name:%s health:%d", fighter->name, fighter->health);
    //int retVal = readFightersFromFile("pub-list.txt");

    sem_destroy(&lock);
    return 0;
}

void insert_people(struct table *t)
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

/***************************************************
*   function name: initialize_mutex                *
*   function parameters: no parameters             *
*   function description: initialize mutex to use  *
*       it later in therads                        *
****************************************************/
void initialize_mutex()
{
    if (sem_init(&lock, 0, 1) != 0)
    {
        printf("\n Mutex initialization failed\n");
    }
}

/***************************************************
*   function name: get_fighters                    *
*   function parameters: int *fighter1             *
*                        int *fighter2             *
*                        int *fighter1_array_number*
*                        int *fighter2_array_number*
*   function description: get random 2 random      *
*        numbers which are 2 alive fighters        *
****************************************************/
void get_fighters(int *fighter1, int *fighter2, int *fighter1_array_number, int *fighter2_array_number)
{
    int i, key1 = 0, key2 = 0;

    do{
        key1 = (rand() % ((alive_people - 1) + 1));
        key2 = (rand() % ((alive_people - 1) + 1));
    }while(key1 == key2); //loop while both keys are not different numbers between 1 and alive_people

    if(alive_people == ALL_PEOPLE) //if all fighters ara alive
    {
        //all people in array are alive, so we can take the same numbers
        *fighter1 = array_of_keys[key1];
        *fighter2 = array_of_keys[key2];
        *fighter1_array_number = key1;
        *fighter2_array_number = key2;
    }
    else //if not all fighters are alive
    {
        for(i = 0; i < ALL_PEOPLE; i++) //loop over the array
        {
            if(key1 < 0 && key2 < 0) //check if both keys are less than 0
            {
                break;
            }
            if(key1 == 0) //if the first key is 0, this means  that the persent on this position is the first figter
            {
                *fighter1 = array_of_keys[i];
                *fighter1_array_number = i;
            }
            if(key2 == 0) //if the second key is 0, this means  that the persent on this position is the second figter
            {
                *fighter2 = array_of_keys[i];
                *fighter2_array_number = i;
            }
            if(array_of_keys[i] != -1) //every time we find alive (different of -1) fighter we decrease key1 and key2
            {
                key1--;
                key2--;
            }
        }
    }
}
