#include "pirata_malo.hpp"
#include "bn_affine_bg_map_ptr.h"
#include "enemigo.hpp"
#include "bn_sprite_items_pirata2.h"
#include "fe_extras.h"
#include "hitbox.hpp"
#include "bn_compare.h"
#include "variables_globales.hpp"

/*

[[nodiscard]] int _get_map_cell(bn::fixed x, bn::fixed y, bn::affine_bg_ptr& map, bn::span<const bn::affine_bg_map_cell> cells)
{
    int map_size = map.dimensions().width();
    int cell = fe::modulo((y.safe_division(8).right_shift_integer() * map_size / 8 + x / 8), map_size * 8).integer();
    return cells.at(cell);
}

[[nodiscard]] bool _contains_cell(int tile, bn::vector<int, 32> tiles)
{
    for (int index = 0; index < tiles.size(); ++index)
    {
        if (tiles.at(index) == tile)
        {
            return true;
        }
    }
    return false;
}

[[nodiscard]] bool _check_collisions_map(bn::fixed_point pos, fe::Hitbox hitbox, direcciones direction, bn::affine_bg_ptr& map, fe::Level level, bn::span<const bn::affine_bg_map_cell> cells)
{
    bn::fixed l = pos.x() - hitbox.width() / 2 + hitbox.x();
    bn::fixed r = pos.x() + hitbox.width() / 2 + hitbox.x();
    bn::fixed u = pos.y() - hitbox.height() / 2 + hitbox.y();
    bn::fixed d = pos.y() + hitbox.height() / 2 + hitbox.y();

    bn::vector<int, 32> tiles;
    if (direction == down) {
        tiles = level.floor_tiles();
    }
    else if (direction == left || direction == right) {
        tiles = level.wall_tiles();
    }
    else if (direction == up) {
        tiles = level.ceil_tiles();
    }

    if (_contains_cell(_get_map_cell(l, u, map, cells), tiles) ||
        _contains_cell(_get_map_cell(l, d, map, cells), tiles) ||
        _contains_cell(_get_map_cell(r, u, map, cells), tiles) ||
        _contains_cell(_get_map_cell(l, d, map, cells), tiles)) {
        return true;
    }
    else {
        return false;
    }
}*/

constexpr const bn::fixed gravity = 0.2;
constexpr const bn::fixed wall_run_speed = 0.25;
constexpr const bn::fixed jump_power = 4;
constexpr const bn::fixed acc = 0.4;
constexpr const bn::fixed max_dy = 6;
constexpr const bn::fixed friction = 0.85;


PirataMalo::PirataMalo(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, int hp) :
    Enemigo(x, y, camera, map, hp) {
    _sprite = bn::sprite_items::pirata2.create_sprite(_pos.x(), _pos.y());
    _sprite.value().set_camera(_camera);
    _sprite.value().set_bg_priority(1);
    /*_action = bn::create_sprite_animate_action_forever(
        _sprite.value(), 4, bn::sprite_items::pirata2.tiles_item(), 0, 1, 0, 1);*/
}

void PirataMalo::update_position() {
    //apply gravity
    _dy += gravity;

    _pos.set_x(_pos.x() + _dx);
    _pos.set_y(_pos.y() + _dy);

    _sprite.value().set_position(_pos);

    if (_dy > 0) {
        fe::Hitbox hbCaida = fe::Hitbox(0, 8, 8, 0);
        hbCaida.mover(_pos);
        if (_check_collisions_map(_pos, hbCaida, direcciones::down, _map, _level, _map_cells)) {
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

void PirataMalo::update_position(bn::affine_bg_ptr map, fe::Level level) {
    // apply friction
    //_dx = _dx * friction;
//apply gravity
    _dy += gravity;


    _pos.set_x(_pos.x() + _dx);
    _pos.set_y(_pos.y() + _dy);

    _sprite.value().set_position(_pos);

    if (_dy > 0) {
        if (_check_collisions_map(_pos, fe::Hitbox(0, 8, 8, 0), direcciones::down, _map, _level, _map_cells)) {
            _dy = 0;
            // BN_LOG(bn::to_string<32>(_pos.x())+" " + bn::to_string<32>(_pos.y()));
            _pos.set_y(_pos.y() - fe::modulo(_pos.y(), 8));
            _grounded = true;
        }
        else {
            _grounded = false;
        }
    }

    // take input
    /*d
    if (bn::keypad::left_held()) {
        moverIzquierda();
    }
    else if (bn::keypad::right_held()) {
        moverDerecha();
    }
    else if (_running) { //slide to a stop

        if (!_falling & !_jumping) {
            _sliding = true;
            _running = false;
        }
    }
    else if (_sliding) { //stop sliding

        if (bn::abs(_dx) < 0.1 || _running) {
            _sliding = false;
        }
    }

    if (bn::keypad::a_pressed()) {
        jump();
    }
    */
    /*
     // collide
     collide_with_objects(map, level);

     // update position
     _pos.set_x(_pos.x() + _dx);
     _pos.set_y(_pos.y() + _dy);

     //_hitbox_fall.set_position(_pos);
     actualizarHitboxes(_pos);
     //_hitbox_fall.mover(_pos);

     // lock player position to map limits x
     if (_pos.x() > 1016) {
         _pos.set_x(1016);
         actualizarHitboxes(_pos);
     }
     else if (_pos.x() < 4) {
         _pos.set_x(4);
         actualizarHitboxes(_pos);
     }

     // update sprite position
     _sprite.set_x(_pos.x());
     _sprite.set_y(_pos.y());
     */

}


