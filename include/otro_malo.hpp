#ifndef OTRO_MALO_HPP
#define OTRO_MALO_HPP

#include "enemigo.hpp"
#include "bn_camera_ptr.h"

class PirataMalo2 : public Enemigo {
public:
    PirataMalo2(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, int hp);
    void update_position() override;
};

#endif