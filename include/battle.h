#ifndef BATTLE_H_
#define BATTLE_H_

#include <semaphore.h>

sem_t lock;

void *fighterFunc(void *args);

#endif /* BATTLE_H_ */