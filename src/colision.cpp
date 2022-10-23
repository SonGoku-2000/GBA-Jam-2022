#include "colision.hpp"
#include "hitbox.hpp"
#include "bn_log.h"

namespace fe {
    bool check_collisions_bb(Hitbox boxA, Hitbox boxB, bool debug){
        if (debug) {
            BN_LOG(boxA.x(), " ", boxA.y(), " ", boxB.x(), " ", boxB.y());
        }
        bool result = boxA.intersects(boxB);
        return result;
    }

}