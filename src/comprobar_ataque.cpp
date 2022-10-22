#include "comprobar_ataque.hpp"
#include "bn_log.h"

void comprobarAtaque(Jugador &jugador, bn::vector<Enemigo*, 32> &enemigos, bool debug = false) {
    fe::Hitbox hitbox = jugador.hitboxAtaque();

    if (jugador.isHorizontalFlip()) {
        hitbox.set_x(hitbox.x() - 8);
    }
    else {
        hitbox.set_x(hitbox.x() + 8);
    }


    for (int i = 0; i < enemigos.size(); i++) {
        if (enemigos.at(i)->is_hit(hitbox)) {
            if (debug) {

                BN_LOG("Enemigo atacado");
            }
            if (jugador.isHorizontalFlip()) {
                enemigos.at(i)->damage_from_left(1);
            }
            else {
                enemigos.at(i)->damage_from_right(1);
            }
        }
    }
}
