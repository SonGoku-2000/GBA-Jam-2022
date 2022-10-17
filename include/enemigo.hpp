#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_optional.h"
#include "bn_span.h"
#include "bn_string.h"
#include "bn_string_view.h"
#include "bn_sprite_animate_actions.h"
#include "bn_affine_bg_ptr.h"
#include "bn_span.h"
#include "bn_affine_bg_map_cell.h"

#include "level.hpp"
#include "hitbox.hpp"
#include "variables_globales.hpp"

enum class ENEMY_TYPE
{
    BAT,
    SLIME
};

class Enemigo{
    protected:
        bn::fixed_point _pos;
        bn::fixed _dy = 0;
        bn::fixed _dx = 0;
        bn::camera_ptr _camera;
        ENEMY_TYPE _type;
        direcciones _dir;
        int _hp;
        int _direction_timer = 0;
        bool _invulnerable = false;
        bool _dead = false;
        bool _grounded = false;
        int _inv_timer = 0;
        bool _stunned = false;
        bn::optional<bn::sprite_ptr> _sprite;
        bn::optional<bn::sprite_animate_action<4>> _action;

        bn::span<const bn::affine_bg_map_cell> _map_cells;
        bn::affine_bg_ptr _map;
        fe::Level _level;

        bool _recibirDano(int dano);
        bool _will_fall_or_hit_wall();

    public:
        Enemigo(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, ENEMY_TYPE type, int hp);
        Enemigo(int x, int y, bn::camera_ptr camera, bn::affine_bg_ptr map, int hp);
        void update();
        bn::fixed_point pos();
        bool is_hit(fe::Hitbox attack);
        bool damage_from_left(int damage);
        bool damage_from_right(int damage);
        int hp();
        void animacionMuerte();

};


#endif
/*


*/