#include "enemigo.hpp"

#include "fe_enemy_type.h"
#include "hitbox.hpp"
#include "colision.hpp"
#include "fe_extras.h"

#include "variables_globales.hpp"
#include "level.hpp"

#include "bn_optional.h"
#include "bn_math.h"
#include "bn_log.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_affine_bg_map_ptr.h"
#include "bn_sprite_items_pirata2.h"


[[nodiscard]] int Enemigo::_get_map_cell(bn::fixed x, bn::fixed y, bn::affine_bg_ptr& map, bn::span<const bn::affine_bg_map_cell> cells)
{
    int map_size = map.dimensions().width();
    int cell = fe::modulo((y.safe_division(8).right_shift_integer() * map_size / 8 + x / 8), map_size * 8).integer();
    return cells.at(cell);
}

[[nodiscard]] bool Enemigo::_contains_cell(int tile, bn::vector<int, 32> tiles)
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

[[nodiscard]] bool Enemigo::_check_collisions_map(bn::fixed_point pos, fe::Hitbox hitbox, direcciones direccion, bn::affine_bg_ptr& map, fe::Level level, bn::span<const bn::affine_bg_map_cell> cells) {

    bn::fixed l = hitbox.left();
    bn::fixed r = hitbox.right();
    bn::fixed u = hitbox.top();
    bn::fixed d = hitbox.bottom();

    bn::vector<int, 32> tiles;
    if (direccion == down) {
        tiles = level.floor_tiles();
    }
    else if (direccion == left || direccion == right) {
        tiles = level.wall_tiles();
    }
    else if (direccion == up) {
        tiles = level.ceil_tiles();
    }
    //BN_LOG(hitbox.x(), " ", hitbox.y(), " ", get_map_cell(l, u, map, cells), " ");
    //BN_LOG("c",l, " ", d, " ", get_map_cell(l, u, map, cells), " ");

    if (_contains_cell(_get_map_cell(l, u, map, cells), tiles) ||
        _contains_cell(_get_map_cell(l, d, map, cells), tiles) ||
        _contains_cell(_get_map_cell(r, u, map, cells), tiles) ||
        _contains_cell(_get_map_cell(l, d, map, cells), tiles)) {
        return true;
    }
    else {
        return false;
    }
}

constexpr const bn::fixed gravity = 0.2;
constexpr const bn::fixed acc = 0.1;
constexpr const bn::fixed max_dy = 6;
constexpr const bn::fixed friction = 0.85;
/*
Enemigo::Enemigo(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, ENEMY_TYPE type, int hp) :
    _pos(x, y), _camera(camera), _type(type), _hp(hp), _map(map), _level(Level(map))
{
    _map_cells = map.map().cells_ref().value();
    _dir = 1;

    if (_type == ENEMY_TYPE::BAT)
    {
        _sprite = bn::sprite_items::bat_sprite.create_sprite(_pos.x(), _pos.y());
        _sprite.value().set_camera(_camera);
        _sprite.value().set_bg_priority(1);
        _action = bn::create_sprite_animate_action_forever(
            _sprite.value(), 4, bn::sprite_items::bat_sprite.tiles_item(), 0, 1, 0, 1);
    }
    else if (_type == ENEMY_TYPE::SLIME) {
        _sprite = bn::sprite_items::slime_sprite.create_sprite(_pos.x(), _pos.y());
        _sprite.value().set_camera(_camera);
        _sprite.value().set_bg_priority(1);
        _action = bn::create_sprite_animate_action_forever(
            _sprite.value(), 20, bn::sprite_items::slime_sprite.tiles_item(), 0, 1, 0, 1);
    }
}
*/
Enemigo::Enemigo(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, int hp) :
    _pos(x, y), _camera(camera), _hp(hp), _map(map), _level(fe::Level(map)) {
    _map_cells = map.map().cells_ref().value();
    _dir = left;
}

int Enemigo::hp() {
    return _hp;
}

bool Enemigo::is_hit(fe::Hitbox attack)
{
    //return check_collisions_bb(attack, _pos.x(), _pos.y(), 16, 16);
    return check_collisions_bb(attack, fe::Hitbox( _pos.x(), _pos.y(), 16, 16));
}

bn::fixed_point Enemigo::pos() {
    return _pos;
}

bool Enemigo::_recibirDano(int dano) {
    if (_invulnerable) {
        return false;
    }

    _hp -= dano;
    _invulnerable = true;
    if (_hp <= 0) {

        animacionMuerte();
        _dead = true;
        return true;
    }
    return false;
}

void Enemigo::animacionMuerte(){

}

bool Enemigo::damage_from_left(int damage) {
    _dy -= 0.5;
    _dx -= 1;
    _grounded = false;
    return _recibirDano(damage);
}

bool Enemigo::damage_from_right(int damage) {
    _dy -= 0.5;
    _dx += 1;
    _grounded = false;
    return _recibirDano(damage);
}

void Enemigo::set_visible(bool visiblity) {
    _sprite.value().set_visible(visiblity);
}


void Enemigo::update_position(){
    BN_LOG("update_position() Funcion no implementada en enemigo.cpp");
}

void Enemigo::update_position(bn::affine_bg_ptr map, fe::Level level){
    BN_LOG("update_position( map, level ) Funcion no implementada en enemigo.cpp");
}


/*

bool Enemy::_will_fall_or_hit_wall()
{

    if (_dx < 0) { // left
        if (!_check_collisions_map(Hitbox(-2, 4, 2, 4), directions::down, _map, _level, _map_cells)) {
            return true;
        }
        if (_check_collisions_map(Hitbox(0, 0, 8, 4), directions::right, _map, _level, _map_cells)) {
            return true;
        }
    }
    else { //right
        if (!_check_collisions_map(Hitbox(2, 4, 2, 4), directions::down, _map, _level, _map_cells)) {
            return true;
        }
        if (_check_collisions_map(Hitbox(0, 0, 8, 4), directions::right, _map, _level, _map_cells)) {
            return true;
        }
    }
    return false;
}

void Enemy::update() {
    //dead check
    if (_action.value().done()) {
        _sprite.value().set_visible(false);
    }

    if (_invulnerable) {
        ++_inv_timer;
        if (_inv_timer > 20) {
            _inv_timer = 0;
            _invulnerable = false;
        }
    }

    if (_direction_timer > 200) {
        // do nothing
    }
    else {
        ++_direction_timer;
    }

    //apply gravity
    if (_type != ENEMY_TYPE::BAT)
    {
        _dy += gravity;
    }


    if (_type == ENEMY_TYPE::BAT) {
        if (_pos.x() < 200) {
            _dir = 1;
            _sprite.value().set_horizontal_flip(false);
        }
        else if (_pos.x() > 400) {
            _dir = -1;
            _sprite.value().set_horizontal_flip(true);
        }
        _pos.set_x(_pos.x() + _dir);
    }
    else if (_type == ENEMY_TYPE::SLIME)
    {
        if (!_invulnerable && _grounded && _direction_timer > 60) {
            if (_will_fall_or_hit_wall()) {
                _dx = 0;
                _dir = -_dir;
                _direction_timer = 0;
                _sprite.value().set_horizontal_flip(!_sprite.value().horizontal_flip());
            }
        }
        if ((_action.value().current_index() == 1 || _action.value().current_index() == 3) && !_invulnerable && _grounded) {
            _dx += _dir * acc;
        }
        _dx = _dx * friction;

        if (_dy > 0) {
            if (_check_collisions_map(Hitbox(0, 4, 4, 0), directions::down, _map, _level, _map_cells)) {
                _dy = 0;
                // BN_LOG(bn::to_string<32>(_pos.x())+" " + bn::to_string<32>(_pos.y()));
                _pos.set_y(_pos.y() - modulo(_pos.y() - 8, 16));
                _grounded = true;
            }
            else {
                _grounded = false;
            }
        }

        if (bn::abs(_dx) > 0) {
            if (_check_collisions_map(Hitbox(0, 0, 2, 4), directions::left, _map, _level, _map_cells) ||
                _check_collisions_map(Hitbox(0, 0, 2, 4), directions::left, _map, _level, _map_cells)) {
                _dx = -_dx;
                _direction_timer = 0;
            }
        }

        //max
        if (_dy > max_dy) {
            _dy = max_dy;
        }

        _pos.set_x(_pos.x() + _dx);
        _pos.set_y(_pos.y() + _dy);

    }

    _sprite.value().set_position(_pos);
    if (!_action.value().done()) {
        _action.value().update();
    }
}
*/