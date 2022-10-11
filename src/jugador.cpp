#include "jugador.hpp"

#include "bn_compare.h"
#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_math.h"

constexpr const bn::fixed gravity = 0.2;
constexpr const bn::fixed wall_run_speed = 0.25;
constexpr const bn::fixed jump_power = 4;
constexpr const bn::fixed acc = 0.4;
constexpr const bn::fixed max_dy = 6;
constexpr const bn::fixed friction = 0.85;

Jugador::Jugador() {
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


void Jugador::update_position(/*bn::affine_bg_ptr map, fe::Level level*/) {
    //_update_camera(10);

    // apply friction
    _dx = _dx * friction;

    //apply gravity
//    //_dy += gravity;

    // take input
    if (bn::keypad::left_held() && !_listening) {
        moverIzquierda();
    }
    else if (bn::keypad::right_held() && !_listening) {
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
    /*if (_pos.x() > 1016) {
        _pos.set_x(1016);
    }
    else if (_pos.x() < 4) {
        _pos.set_x(4);
    }*/

    // update sprite position
    _sprite.set_x(_pos.x());
    _sprite.set_y(_pos.y());

}