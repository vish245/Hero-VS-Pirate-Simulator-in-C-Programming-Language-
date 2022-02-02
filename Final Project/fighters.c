#include "defs.h"



/*
  Function:  initFighter
  Purpose:   initialize the fighters.
       in:   st, arm, h -> correspond to strength, armour and health properties of the fighter.
      out:   fighters that has to be initilized and contains all fighter information
   return:   void
*/

void initFighter(int  st, int  arm, int  h, FighterType **fighter) {
    (*fighter) = malloc(sizeof(FighterType));
    static int nextId = 1;

    (*fighter)->id = nextId;
    nextId++;
    (*fighter)->strength = st;
    (*fighter)->armour = arm;
    (*fighter)->health = h;

}


/*
  Function:  createPirates
  Purpose:   initialize a new pirate and add it to the deque.
       in:   deque to store the fighters
   return:   void
*/

void createPirates(DequeType *pirates) {
    initDeque(pirates);
    FighterType *pirate;
    int strength;
    int armour;

    for (int i = 0; i < NUM_PIRATES; ++i) {
        int v = randm(9);

        if (v < 5) {
            if (v == 0) {
                armour = v + 1;
            }
            else {
                armour = v;
            }

            strength= v + 5;
        }
        else if (v >= 5){
            armour = v - 4;
            strength = v;
        }

        initFighter(strength, armour, PIRATE_HEALTH, &pirate);
        addFighter(pirates,pirate);
    }
}

/*
  Function:  initRunSpecs
  Purpose:   initialize the fight specification.
       in:   p, tort, hare, stats -> correspond to pirates, tortoises, hare, statics.
      out:   run that stores all run specification information.
   return:   void
*/

void initRunSpecs(DequeType *p, FighterType *tort, FighterType *hare, StatsType *stats, RunSpecsType **run) {
    (*run) = malloc(sizeof(RunSpecsType));

    (*run)->pirates = p;
    (*run)->tort = tort;
    (*run)->hare = hare;
    (*run)->stats = stats;

}
