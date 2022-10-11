#ifndef JUGADOR_HPP
#define JUGADOR_HPP

//Butano
#include "bn_compare.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_affine_bg_ptr.h"

class Jugador {
    private:
        bn::sprite_ptr _sprite;// = bn::sprite_items::pirata1.create_sprite(0, 0);
        bn::fixed _dx;
        bn::fixed _dy;  
        bn::fixed_point _pos;

        bool _jumping = false;
        bool _falling = false;
        bool _running = false;
        bool _listening = false;
        bool _grounded = false;
        bool _sliding = false;
        bool _wall_running = false;
        bool _wall_jumped = false;
        bool _already_running = false;
        bool _attacking = false;
    public:
        Jugador();
        void moverIzquierda();
        void moverDerecha();
        void moverArriba();
        void moverAbajo();
        void caer();
        void update_position();
        void jump();
        void ataque();
        
        void comprobarAtaque();
        //void collide_with_objects(bn::affine_bg_ptr map, fe::Level level);
        //void set_listening(bool is_listening);
        //void set_can_wallrun(bool can_wallrun);
        //void apply_animation_state();
        //void actualzarPosicion(bn::affine_bg_ptr map, fe::Level level);
};

#endif


