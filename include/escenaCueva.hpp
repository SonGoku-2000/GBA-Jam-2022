#ifndef ESCENACUEVA_HPP
#define ESCENACUEVA_HPP

#include "bn_fixed_point.h"

#include "escenas.hpp"
#include "jugador.hpp"


namespace p {
    class Cueva {
        public:
            Escenas execute(Jugador player, bn::fixed_point spawn);
    };
}

#endif