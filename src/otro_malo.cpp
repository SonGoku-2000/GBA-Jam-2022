#include "otro_malo.hpp"
#include "bn_affine_bg_map_ptr.h"
#include "enemigo.hpp"
#include "bn_sprite_items_pirata2.h"
#include "fe_extras.h"
#include "hitbox.hpp"
#include "variables_globales.hpp"

constexpr const bn::fixed gravity = 0.2;
constexpr const bn::fixed wall_run_speed = 0.25;
constexpr const bn::fixed jump_power = 4;
constexpr const bn::fixed acc = 0.4;
constexpr const bn::fixed max_dy = 6;
constexpr const bn::fixed friction = 0.85;


PirataMalo2::PirataMalo2(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, int hp) :
    Enemigo(x, y, camera, map, hp) {
    _sprite = bn::sprite_items::pirata2.create_sprite(_pos.x(), _pos.y());
    _sprite.value().set_camera(_camera);
    _sprite.value().set_bg_priority(1);
    /*_action = bn::create_sprite_animate_action_forever(
        _sprite.value(), 4, bn::sprite_items::pirata2.tiles_item(), 0, 1, 0, 1);*/
}

void PirataMalo2::update_position() {
    //apply gravity
    _dy += gravity;


    _pos.set_x(_pos.x() + _dx);
    _pos.set_y(_pos.y() + _dy);

    _sprite.value().set_position(_pos);


    if (_dy > 0) {
        fe::Hitbox hbCaida = fe::Hitbox(0, 8, 8, 0);
        hbCaida.mover(_pos);
        if (_check_collisions_map(hbCaida, direcciones::down, _map, _level, _map_cells)) {
            _dy = 0;
            // BN_LOG(bn::to_string<32>(_pos.x())+" " + bn::to_string<32>(_pos.y()));
            _pos.set_y(_pos.y() - fe::modulo(_pos.y(), 8));
            _grounded = true;
        }
        else {
            _grounded = false;
        }
    }

}
