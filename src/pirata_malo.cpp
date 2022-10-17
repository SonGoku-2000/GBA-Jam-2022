#include "pirata_malo.hpp"
#include "bn_affine_bg_map_ptr.h"
#include "enemigo.hpp"
#include "bn_sprite_items_pirata2.h"

PirataMalo::PirataMalo(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, int hp) :
    Enemigo(x, y, camera, map, hp) {
    _sprite = bn::sprite_items::pirata2.create_sprite(_pos.x(), _pos.y());
    _sprite.value().set_camera(_camera);
    _sprite.value().set_bg_priority(1);
    /*_action = bn::create_sprite_animate_action_forever(
        _sprite.value(), 4, bn::sprite_items::bat_sprite.tiles_item(), 0, 1, 0, 1);*/
}

