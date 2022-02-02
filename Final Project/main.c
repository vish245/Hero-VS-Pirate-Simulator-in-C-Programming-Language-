#include "defs.h"

sem_t mutex;
int main(int argc, char *argv[])
{
  StatsType stats[NUM_SCENARIOS];
  DequeType *pirates[NUM_SCENARIOS];
  void *returnValue = (malloc(sizeof(int*)));

  for (int i = 0; i<NUM_SCENARIOS; ++i) {
    initStats(&stats[i]);
    (pirates[i]) = malloc(sizeof(DequeType));
  }

  FighterType *hairs[NUM_SCENARIOS];
  FighterType *tortoises[NUM_SCENARIOS];
  pthread_t v[NUM_SCENARIOS];
   // DOUBTFUL

  RunSpecsType *specs[NUM_SCENARIOS];


  for (int i = 0; i<NUM_RUNS; ++i) {
    //printf("                    Num of run: %d\n",i);
    createPirates(pirates[0]);
    deepCopy(pirates[0],pirates[1]);
    deepCopy(pirates[0],pirates[2]);
    for (int j = 0; j<NUM_SCENARIOS; j++) {
      //printf("                        Num of scenario: %d\n", j);
      if(j==0) {
        initFighter(TORT_STRENGTH + SWORD_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tortoises[j]);
        initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hairs[j]);
        initRunSpecs(pirates[0], tortoises[j], hairs[j], &stats[j], &specs[j]);
        pthread_create(&v[j], NULL, scenario, specs[j]);
        pthread_join(v[j],returnValue);
        int *value = (int*)returnValue;
        //printf("This is the value of the fight %d\n", *value);

        if (*value == SUCCESS) {
          stats[j].numSuccess+=1;
        }
        else if (*value == PART_SUCCESS) {
          stats[j].numPartSuccess+=1;
        }
        else if (*value == FAILURE) {
          stats[j].numFailure+=1;
        }

      }else if(j==1) {
        initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tortoises[j]);
        initFighter(HARE_STRENGTH + SWORD_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hairs[j]);
        initRunSpecs(pirates[1], tortoises[j], hairs[j], &stats[j], &specs[j]);
        pthread_create(&v[j], NULL, scenario, specs[j]);
        pthread_join(v[j], returnValue);
        int *value = (int*)returnValue;
        //printf("This is the value of the fight %d\n", *value);

        if (*value == SUCCESS) {
          stats[j].numSuccess+=1;
        }
        else if (*value == PART_SUCCESS) {
          stats[j].numPartSuccess+=1;
        }
        else if (*value == FAILURE) {
          stats[j].numFailure+=1;
        }

      }else if(j==2) {
        initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tortoises[j]);
        initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hairs[j]);
        initRunSpecs(pirates[2], tortoises[j], hairs[j], &stats[j], &specs[j]);
        pthread_create(&v[j], NULL, scenario, specs[j]);
        pthread_join(v[j],returnValue);
        int *value = (int*)returnValue;
        //printf("This is the value of the fight %d\n", *value);

        if (*value == SUCCESS) {
          stats[j].numSuccess+=1;
        }
        else if (*value == PART_SUCCESS) {
          stats[j].numPartSuccess+=1;
        }
        else if (*value == FAILURE) {
          stats[j].numFailure+=1;
        }
      }
      free(hairs[j]);
      free(tortoises[j]);
      free(specs[j]);
    }
    cleanDeque(pirates[0]);
    cleanDeque(pirates[1]);
    cleanDeque(pirates[2]);
  }
  printf("+-----------------------------------------------------+\n");
  printf("| Hero with Sword | %s success | %s partial | %s failure |\n", "%", "%", "%");
  printf("+-----------------------------------------------------+\n");
  printf("|    Tortoise     |     %d    |     %d    |     %d    |\n", stats[0].numSuccess, stats[0].numPartSuccess, stats[0].numFailure);
  printf("+-----------------------------------------------------+\n");
  printf("|    Hare         |     %d    |     %d    |     %d    |\n", stats[1].numSuccess, stats[1].numPartSuccess, stats[1].numFailure);
  printf("+-----------------------------------------------------+\n");
  printf("|    None         |     %d    |     %d    |     %d    |\n", stats[2].numSuccess, stats[2].numPartSuccess, stats[2].numFailure);
  printf("+-----------------------------------------------------+\n");
  printf("Total runs: %d\n", NUM_RUNS);

  free(pirates[0]);
  free(pirates[1]);
  free(pirates[2]);
  free(returnValue);
  return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number,
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1)
*/

int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) );

  return (int)(r * max);
}

/*
  Function:  heroHitsPirate
  Purpose:   Create threads
       in:   void type argument to generate a thread.
   return:   void
*/
void *threadFunc(void *arg)
{
  //printf("Inside threadFunc\n");
  FightSpecsType *spec=(FightSpecsType*) arg;
  FighterType *pirate=NULL;
  //StatsType *stats;
  while (spec->pirates->head!= NULL) {
    if (sem_wait(&mutex) < 0) {
      printf("semaphore wait error\n");
      exit(1);
    }
    if(spec->dir==FRONT) {
      removeFromFront(spec->pirates, &pirate);
      //printf("Front: ID:%d  S: %d,  A:%d,  H:%d\n", pirate->id,pirate->strength,pirate->armour,pirate->health);

      while(1){
        if(heroHitsPirate(spec->hero,pirate)==PIRATE_DIES){
          //printf("Pirate Dead\n");
          break;
        }
        if(pirateHitsHero(spec->hero,pirate)==FIGHTER_DIES){
          //printf("Hero Dead\n");
          free(pirate);
          if (sem_post(&mutex) < 0) {
            printf("semaphore post error\n");
            exit(1);
          }
          return(void*)FIGHTER_DIES;
          //break;
        }
      }
      free(pirate);
    }
    else {
      removeFromBack(spec->pirates,&pirate);
      //printf("Back: ID:%d  S: %d,  A:%d,  H:%d\n",pirate->id,pirate->strength,pirate->armour,pirate->health);
      while(1){
        if(heroHitsPirate(spec->hero,pirate)==PIRATE_DIES){
          //printf("Pirate Dead\n");
          break;
        }
        if(pirateHitsHero(spec->hero,pirate)==FIGHTER_DIES){
          free(pirate);
        //  printf("Hero Dead\n");
          if (sem_post(&mutex) < 0) {
            printf("semaphore post error\n");
            exit(1);
          }
          return(void*)FIGHTER_DIES;
          //break;
        }
      }
      free(pirate);
    }

    if (sem_post(&mutex) < 0) {
      printf("semaphore post error\n");
      exit(1);
    }
    usleep(1000);
  }
  return(0);
}


/*
  Function:  heroHitsPirate
  Purpose:   Simulate the scenarios of the fight
       in:   void type argument to generate a thread.
   return:   void
*/

void *scenario(void *arg) {
  RunSpecsType *spec = (RunSpecsType*) arg;
  FightSpecsType *fSpecs1, *fSpecs2;
  void *ret1=(malloc(sizeof(int*))),*ret2=(malloc(sizeof(int*)));
  if (sem_init(&mutex, 0, 1) < 0) {
    printf("semaphore initialization error\n");
    exit(1);
  }
  //printf("Inside scenario func\n");
  initFight(spec->tort, spec->pirates, 0, &mutex, &fSpecs1);
  initFight(spec->hare, spec->pirates, 1, &mutex, &fSpecs2);
  pthread_t fThread1, fThread2;
  pthread_create(&fThread1,NULL,threadFunc,fSpecs1);
  pthread_create(&fThread2,NULL,threadFunc,fSpecs2);
  pthread_join(fThread1,ret1);
  pthread_join(fThread2,ret2);
  int *val1=(int*)ret1;
  int *val2=(int*)ret2;
  //printf("Retvalue 1: %d\n", *val1);
  //printf("Retvalue 2: %d\n", *val2);
  free(fSpecs1);
  free(fSpecs2);
  if (*val1 == 0 && *val2 == 0) {
    free(ret1);
    free(ret2);
    return (void*)SUCCESS;

  }
  else if (*val1 == 50 && *val2 == 50) {
    free(ret1);
    free(ret2);
    return (void*)FAILURE;
  }
  else if (*val1 == 50 || *val2 == 50) {
    free(ret1);
    free(ret2);
    return (void*)PART_SUCCESS;
  }
  free(ret1);
  free(ret2);
  return(0);
}
