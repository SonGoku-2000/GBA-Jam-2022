#include "fe_hitbox.h"

#include "bn_fixed_rect.h"

namespace fe {
    Hitbox::Hitbox(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height) :
        bn::fixed_rect(x, y, width, height), _offsetX(x), _offsetY(y) {
    }
    void Hitbox::mover(bn::fixed_point pos){
        set_x( pos.x() + _offsetX );
        set_y( pos.y() + _offsetY );
    }
}