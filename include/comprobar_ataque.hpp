#ifndef COMPROBAR_ATAQUE_HPP
#define COMPROBAR_ATAQUE_HPP

#include "enemigo.hpp"
#include "jugador.hpp"
#include "bn_vector.h"


void comprobarAtaque(Jugador &jugador, bn::vector<Enemigo*, 32> &enemigos, bool debug);

#endif