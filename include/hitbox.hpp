#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "bn_compare.h"
#include "bn_fixed.h"
#include "bn_fixed_point.h"
#include "bn_fixed_rect.h"

namespace fe {

    class Hitbox : public bn::fixed_rect {
        
        private:
            /*
            bn::fixed_point _pos;
            bn::fixed _width;
            bn::fixed _height;
            */

        public:
            Hitbox();
            Hitbox(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height);
            /*
            bn::fixed x();
            bn::fixed y();
            bn::fixed width();
            bn::fixed height();
            bn::fixed_point pos();

            void set_x(bn::fixed x);
            void set_y(bn::fixed y);
            void set_width(bn::fixed width);
            void set_height(bn::fixed height);
            */
    };
}

#endif