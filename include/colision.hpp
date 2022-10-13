#ifndef COLISION_HPP
#define COLISION_HPP


#include "fe_extras.h"

#include "hitbox.hpp"


namespace fe {

    [[nodiscard]] bool check_collisions_bb(Hitbox boxA, Hitbox boxB) {
        bool result = boxA.x() - boxA.width() / 2 < boxB.x() + boxB.width() / 2 &&
            boxA.x() + boxA.width() / 2 > boxB.x() - boxB.width() / 2 &&
            boxA.y() - boxA.height() / 2 < boxB.y() + boxB.height() / 2 &&
            boxA.y() + boxA.height() / 2 > boxB.y() - boxB.height() / 2;
        return result;
    }

    [[nodiscard]] bool check_collisions_bb(Hitbox boxA, bn::fixed x, bn::fixed y, bn::fixed w, bn::fixed h) {
        bool result = boxA.x() - boxA.width() / 2 < x + w / 2 &&
            boxA.x() + boxA.width() / 2 > x - w / 2 &&
            boxA.y() - boxA.height() / 2 < y + h / 2 &&
            boxA.y() + boxA.height() / 2 > y - h / 2;
        return result;
    }
}



#endif