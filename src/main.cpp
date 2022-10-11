#include "bn_compare.h"
#include "bn_core.h"

#include "bn_sprite_items_obstaculo.h"

#include "jugador.hpp"

int main() {
    bn::core::init();
    Jugador jugador = Jugador();
    bn::sprite_ptr _sprite = bn::sprite_items::obstaculo.create_sprite(40, 10);

    while(true) {
        jugador.update_position();
        bn::core::update();
    }
}
