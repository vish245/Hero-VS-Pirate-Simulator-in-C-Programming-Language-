#include "defs.h"

/*
  Function:  initFight
  Purpose:   initialize the fight.
       in:   hero, pirates, dir, dqMutex -> correspond to hero, pirates, dir, dqMutex.
      out:   specs that stores all specification information.
   return:   void
*/

void initFight( FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *dqMutex, FightSpecsType **specs) {
    (*specs) = malloc(sizeof(FightSpecsType));

    (*specs)->hero = hero;
    (*specs)->pirates = pirates;
    (*specs)->dir = dir;
    (*specs)->dqMutex = dqMutex;
}

/*
  Function:  initStats
  Purpose:   initialize the fight statistics.
       in:   stats structure that contains statistic information.
   return:   void
*/

void initStats(StatsType *stats) {
    stats->numFailure = 0;
    stats->numPartSuccess = 0;
    stats->numSuccess = 0;
}

/*
  Function:  heroHitsPirate
  Purpose:   Simulate hero fighting with the pirate.
       in:   hero that fights with the pirate.
       in:   pirate that fights with the hero.
   return:   int to show if hero dies while fighting the pirate.
*/

int heroHitsPirate(FighterType *hero, FighterType *pirate) {
    int damage = (hero->strength - pirate->armour);

    pirate->health -= damage;
    if (pirate->health <= 0) {
        pirate->health = 0;
        if (hero->health <= 17)
          hero->health += 3;
        return PIRATE_DIES;
    }
    return CONTINUE_FIGHT;
}

/*
  Function:  heroHitsPirate
  Purpose:   Simulate pirate fighting with the hero.
       in:   hero that fights with the pirate.
       in:   pirate that fights with the hero.
   return:   int to show if pirate dies while fighting the hero.
*/

int pirateHitsHero(FighterType *hero, FighterType *pirate) {
    int increaseStrength = randm((pirate->strength) - 1);
    //pirate->strength += increaseStrength;
    int damage = (pirate->strength + increaseStrength - hero->armour);
    hero->health -= damage;
    if (hero->health <= 0) {
        return FIGHTER_DIES;
    }

    return CONTINUE_FIGHT;
}
