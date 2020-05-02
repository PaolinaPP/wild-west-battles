#ifndef BATTLE_H_
#define BATTLE_H_

#include "fighters-map.h"

sem_t lock;

void *fighter_func(void *args);
int is_fighter_health_full(struct node **fighter);

#endif /* BATTLE_H_ */