#ifndef FE_HOUSE_SCENE_H
#define FE_HOUSE_SCENE_H

#include "fe_scene.h"
#include "jugador.hpp"
#include "bn_fixed_point.h"

namespace fe
{
    class House
    {       
        public:
            Scene execute(Jugador player, bn::fixed_point spawn);
    };
}

#endif