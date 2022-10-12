#ifndef JUGADOR_HPP
#define JUGADOR_HPP

//Butano
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_affine_bg_ptr.h"
#include "bn_span.h"
#include "bn_affine_bg_map_cell.h"

#include "level.hpp"
#include "hitbox.hpp"
#include "fe_enemy.h"

class Jugador {
    private:
        bn::sprite_ptr _sprite;
        bn::fixed _dx;
        bn::fixed _dy;  
        bn::fixed_point _pos;
        bn::camera_ptr _camera;

        bool _jumping = false;
        bool _falling = false;
        bool _running = false;
        bool _grounded = false;
        bool _sliding = false;
        bool _already_running = false;
        bool _attacking = false;
        bn::span<const bn::affine_bg_map_cell> _map_cells;
        bn::affine_bg_ptr _map;
        bn::vector<fe::Enemy, 32>* _enemies;

        fe::Hitbox _hitbox_fall = fe::Hitbox(0, 4, 4, 0);
        fe::Hitbox _hitbox_left = fe::Hitbox(-2, 0, 2, 4);
        fe::Hitbox _hitbox_right = fe::Hitbox(2, 0, 2, 4);
        fe::Hitbox _hitbox_jump = fe::Hitbox(0, 2, 4, 2);
        /*bn::sprite_animate_action<10> _action = bn::create_sprite_animate_action_forever(
            _sprite, 6, bn::sprite_items::cat_sprite.tiles_item(), 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
        */
        void _update_camera(int lerp);

    public:
        Jugador();
        void moverIzquierda();
        void moverDerecha();
        void moverArriba();
        void moverAbajo();
        //void caer();
        void update_position(bn::affine_bg_ptr map, fe::Level level);
        void update_position();
        void jump();
        void ataque();
        
        void comprobarAtaque();
        //void collide_with_objects(bn::affine_bg_ptr map, fe::Level level);
        //void set_listening(bool is_listening);
        //void set_can_wallrun(bool can_wallrun);
        //void apply_animation_state();
        //void actualzarPosicion(bn::affine_bg_ptr map, fe::Level level);

        void spawn(bn::fixed_point pos, bn::camera_ptr camera, bn::affine_bg_ptr map, bn::vector<fe::Enemy, 32>& enemies);
        void spawn(bn::fixed_point pos, bn::camera_ptr camera, bn::affine_bg_ptr map);
        void reset();
};

#endif


