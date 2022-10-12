#include "jugador.hpp"

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_map_ptr.h"
#include "bn_string.h"
#include "bn_keypad.h"
#include "bn_math.h"
#include "bn_size.h"
#include "bn_optional.h"
#include "bn_span.h"
#include "bn_log.h"

#include "bn_sprite_items_pirata1.h"
#include "bn_affine_bg_items_mapa.h"

constexpr const bn::fixed gravity = 0.2;
constexpr const bn::fixed wall_run_speed = 0.25;
constexpr const bn::fixed jump_power = 4;
constexpr const bn::fixed acc = 0.4;
constexpr const bn::fixed max_dy = 6;
constexpr const bn::fixed friction = 0.85;

Jugador::Jugador() :
    _sprite(bn::sprite_items::pirata1.create_sprite(0, 0)),
    _camera(bn::camera_ptr::create(0, 0)) ,
    _map(bn::affine_bg_items::mapa.create_bg(0, 0)) {
    _map.set_visible(false);
    _pos.set_x(0);
    _pos.set_y(0);
}

void Jugador::moverDerecha() {
    _sprite.set_horizontal_flip(false);
    _dx += acc;
    _running = true;
    _sliding = false;
}

void Jugador::moverIzquierda() {
    _sprite.set_horizontal_flip(true);
    _dx -= acc;
    _running = true;
    _sliding = false;
}

void Jugador::_update_camera(int lerp) {
    // update camera
    if (_pos.x() < 122 + 30) {
        _camera.set_x(_camera.x() + (122 - _camera.x()) / lerp);
    }
    else if (_pos.x() > 922 - 30) {
        _camera.set_x(_camera.x() + (922 - 20 - _camera.x()) / lerp);
    }
    else
    {
        if (_sprite.horizontal_flip()) {
            _camera.set_x(_camera.x() + (_pos.x() - 30 - _camera.x() + _dx * 8) / lerp);
        }
        else {
            _camera.set_x(_camera.x() + (_pos.x() + 30 - _camera.x() + _dx * 8) / lerp);
        }
    }

    if (_pos.y() < 942) {
        _camera.set_y(_camera.y() + (_pos.y() - 10 - _camera.y()) / lerp);
    }
    else {
        _camera.set_y(_camera.y() + (942 - _camera.y()) / lerp);
    }
}

void Jugador::update_position(bn::affine_bg_ptr map, fe::Level level) {
    //_update_camera(10);

    // apply friction
    _dx = _dx * friction;

    //apply gravity
    _dy += gravity;

    // take input
    if (bn::keypad::left_held()) {
        moverIzquierda();
    }
    else if (bn::keypad::right_held()) {
        moverDerecha();
    }
    else if (_running) //slide to a stop
    {
        if (!_falling & !_jumping) {
            _sliding = true;
            _running = false;
        }
    }
    else if (_sliding) //stop sliding
    {
        if (bn::abs(_dx) < 0.1 || _running) {
            _sliding = false;
        }
    }
    /*
    if (bn::keypad::up_held()) {
        if (_dy > 0 && bn::abs(_dx) > 1 && !_wall_jumped && _can_wallrun) {
            _wall_running = true;
            _dy = _dy / 2;
        }

    }
    else {
        _wall_running = false;
    }*/
    /*
        if (_listening) {
            _text_bg1.set_position(_camera.x() + 64 + 8, _camera.y() + 40 + 24);
            _text_bg2.set_position(_camera.x() - 64 + 8, _camera.y() + 40 + 24);
        }*/

        // jump
        /*if (bn::keypad::a_pressed()) {
            jump();
        }*/
        /*
            // attack
            if (bn::keypad::b_pressed()) {
                attack();
            }*/

            //check_attack();

            // collide
         //   collide_with_objects(map, level);

            // update position
    _pos.set_x(_pos.x() + _dx);
    _pos.set_y(_pos.y() + _dy);

    // lock player position to map limits x
    if (_pos.x() > 1016) {
        _pos.set_x(1016);
    }
    else if (_pos.x() < 4) {
        _pos.set_x(4);
    }

    // update sprite position
    _sprite.set_x(_pos.x());
    _sprite.set_y(_pos.y());

}


void Jugador::update_position() {
    _update_camera(10);

    // apply friction
    _dx = _dx * friction;

    //apply gravity
    //////////_dy += gravity;

    // take input
    if (bn::keypad::left_held()) {
        moverIzquierda();
    }
    else if (bn::keypad::right_held()) {
        moverDerecha();
    }
    else if (_running) //slide to a stop
    {
        if (!_falling & !_jumping) {
            _sliding = true;
            _running = false;
        }
    }
    else if (_sliding) //stop sliding
    {
        if (bn::abs(_dx) < 0.1 || _running) {
            _sliding = false;
        }
    }
    /*
    if (bn::keypad::up_held()) {
        if (_dy > 0 && bn::abs(_dx) > 1 && !_wall_jumped && _can_wallrun) {
            _wall_running = true;
            _dy = _dy / 2;
        }

    }
    else {
        _wall_running = false;
    }*/
    /*
        if (_listening) {
            _text_bg1.set_position(_camera.x() + 64 + 8, _camera.y() + 40 + 24);
            _text_bg2.set_position(_camera.x() - 64 + 8, _camera.y() + 40 + 24);
        }*/

        // jump
        /*if (bn::keypad::a_pressed()) {
            jump();
        }*/
        /*
            // attack
            if (bn::keypad::b_pressed()) {
                attack();
            }*/

            //check_attack();

            // collide
         //   collide_with_objects(map, level);

            // update position
    _pos.set_x(_pos.x() + _dx);
    _pos.set_y(_pos.y() + _dy);

    // lock player position to map limits x
    if (_pos.x() > 1016) {
        _pos.set_x(1016);
    }
    else if (_pos.x() < 4) {
        _pos.set_x(4);
    }

    // update sprite position
    _sprite.set_x(_pos.x());
    _sprite.set_y(_pos.y());

}

void Jugador::spawn(bn::fixed_point pos, bn::camera_ptr camera, bn::affine_bg_ptr map, bn::vector<fe::Enemy, 32>& enemies) {
    _pos = pos;
    _camera = camera;
    _map = map;
    _map_cells = map.map().cells_ref().value();
    _enemies = &enemies;
    _map.set_visible(true);

    reset();
}
void Jugador::spawn(bn::fixed_point pos, bn::camera_ptr camera, bn::affine_bg_ptr map) {
    _pos = pos;
    _camera = camera;
    _map = map;
    _map_cells = map.map().cells_ref().value();
    _map.set_visible(true);

    reset();
}


void Jugador::reset() {
    _sprite.set_camera(_camera);
    _sprite.set_bg_priority(0);
    _sprite.put_above();
    //_text_bg1.set_camera(_camera);
    //_text_bg2.set_camera(_camera);
    _update_camera(1);
    _dy = 0;
    _dy = 0;
    _jumping = false;
    _falling = false;
    _running = false;
    //_listening = false;
    _grounded = false;
    _sliding = false;
    //_wall_running = false;
    //_wall_jumped = false;
    _already_running = false;
    _attacking = false;

    //_can_wallrun = false;
}

