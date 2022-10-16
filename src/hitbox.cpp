#include "hitbox.hpp"

#include "bn_fixed_rect.h"
#include "bn_log.h"

namespace fe {
    Hitbox::Hitbox(bn::fixed x, bn::fixed y, bn::fixed width, bn::fixed height) :
        bn::fixed_rect(x, y, width, height) {
        _offsetX = x * 2;
        _offsetY = y * 2;
        //BN_LOG(_offsetX);
        //BN_LOG(_offsetY);
    }
    void Hitbox::setOffsetY(bn::fixed y) {
        _offsetY = y;
    }
    void Hitbox::setOffsetX(bn::fixed x) {
        _offsetX = x;
    }
    void Hitbox::mover(bn::fixed_point pos) {
        set_x((_offsetX + pos.x()) / 2);
        set_y((_offsetY + pos.y()) / 2);
    }
}

/*
bn::fixed_point Hitbox::pos() {
    return _pos;
}

bn::fixed Hitbox::x() {
    return _pos.x();
}

bn::fixed Hitbox::y() {
    return _pos.y();
}

bn::fixed Hitbox::width() {
    return _width;
}

bn::fixed Hitbox::height() {
    return _height;
}

void Hitbox::set_x(bn::fixed x) {
    _pos.set_x(x);
}

void Hitbox::set_y(bn::fixed y) {
    _pos.set_y(y);
}

void Hitbox::set_width(bn::fixed width) {
    _width = width;
}

void Hitbox::set_height(bn::fixed height) {
    _height = height;
}

*/