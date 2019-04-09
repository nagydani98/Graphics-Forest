#if !defined(MODELOBJECTS_H)
#define MODELOBJECTS_H

#include <obj/model.h>
#include "scene.h"

typedef struct Deer
{
        Model deermodel;
        double x;
        double y;
        double z;
        double speed;
} Deer;

void drawtest(Deer* deer);

#endif // MODELOBJECTS_H
