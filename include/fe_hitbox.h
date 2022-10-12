#ifndef FE_HITBOX_H
#define FE_HITBOX_H

#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_fixed_rect.h"

namespace fe {
    class Hitbox : public bn::fixed_rect {
    private:
        bn::fixed _offsetY;
        bn::fixed _offsetX;
    public:
        Hitbox();
        Hitbox(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height);
        void mover(bn::fixed_point pos);
    };
}

#endif