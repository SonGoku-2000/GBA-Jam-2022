#ifndef PIRATA_MALO_HPP
#define PIRATA_MALO_HPP

#include "enemigo.hpp"
#include "bn_camera_ptr.h"

class PirataMalo: public Enemigo{
    public:
        PirataMalo(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, int hp);
};

#endif