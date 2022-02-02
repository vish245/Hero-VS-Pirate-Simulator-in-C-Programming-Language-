#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2
#define FIGHTER_DIES     50
#define CONTINUE_FIGHT   24
#define PIRATE_DIES     -1

#define MAX_STR         64

typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  id;        // REMOVE THIS ONCE DONE CODING
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one scenario of one run
  FighterType  *hero;
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;

// Forward References
int randm(int);		// Pseudo-random number generator function
void *threadFunc(void *arg);
void *scenario(void *arg);
void initDeque(DequeType *deque);
void addFighter(DequeType *deque, FighterType *fighter);
void removeFromBack(DequeType *deque, FighterType **fighter);
void removeFromFront(DequeType *deque, FighterType **fighter);
void deepCopy(DequeType *deque, DequeType *emptyDeque);
void initFighter(int  st, int  arm, int  h, FighterType **fighter);
void createPirates(DequeType *pirates);
void initRunSpecs(DequeType *p, FighterType *tort, FighterType *hare, StatsType *stats, RunSpecsType **run);
void initFight( FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *dqMutex, FightSpecsType **specs);
void initStats(StatsType *stats);
int heroHitsPirate(FighterType *hero, FighterType *pirate);
int pirateHitsHero(FighterType *hero, FighterType *pirate);
void cleanDeque(DequeType *deque);


#endif
