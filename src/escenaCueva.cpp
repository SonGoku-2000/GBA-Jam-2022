#include "escenaCueva.hpp"

//butano
#include "bn_compare.h"
#include "bn_core.h"
#include "bn_log.h"
#include "bn_keypad.h"
#include "bn_string.h"
#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_affine_bg_ptr.h"
#include "bn_affine_bg_map_ptr.h"
#include "bn_optional.h"
#include "bn_span.h"
#include "bn_affine_bg_map_cell.h"

//fe code
#include "level.hpp"
#include "jugador.hpp"
#include "escenas.hpp"

//assets
#include "bn_affine_bg_items_mapa.h"


namespace p {
    Escenas Cueva::execute(Jugador player, bn::fixed_point spawn_location) {

        bn::camera_ptr camera = bn::camera_ptr::create(spawn_location.x(), spawn_location.y());

        //NPC
       // NPC tortoise = NPC(bn::fixed_point(535, 304), camera, NPC_TYPE::TORTOISE);

        // map
        //bn::regular_bg_ptr map_bg = bn::regular_bg_items::house_bg.create_bg(512, 512);
        bn::affine_bg_ptr map = bn::affine_bg_items::mapa.create_bg(512, 512);
        //map_bg.set_priority(2);
        map.set_priority(1);
        fe::Level level = fe::Level(map);
        map.set_horizontal_scale(2);
        map.set_vertical_scale(2);

        // camera
        map.set_camera(camera);
        //map_bg.set_camera(camera);

        // bn::fixed max_cpu_usage;
        // int counter = 1;
        bn::vector<fe::Enemy, 32> enemies = {};

        // player
        //player.spawn(spawn_location, camera, map, enemies);
        player.spawn(spawn_location, camera, map);
        while (true)
        {

            // max_cpu_usage = bn::max(max_cpu_usage, bn::core::last_cpu_usage());
            // --counter;
            // if(! counter)
            // {
            //     BN_LOG("cpu:" + bn::to_string<32>((max_cpu_usage * 100).right_shift_integer()));
            //     max_cpu_usage = 0;
            //     counter = 60;
            // }


            /*if(tortoise.near_player(player.pos()))
            {
                if(bn::keypad::a_pressed()){
                    player.set_listening(true);
                    tortoise.talk();
                }else if(!tortoise.is_talking()){
                    player.set_listening(false);
                }
            }
            tortoise.update();
*/
//elevator.update_position();
            player.update_position(map, level);
            //player.apply_animation_state();
            // BN_LOG(bn::to_string<32>(player.pos().x())+" " + bn::to_string<32>(player.pos().y()));

            if (bn::keypad::start_pressed()) {
                return Escenas::CUEVA;
            }
            /*
            if(bn::keypad::up_pressed())
            {
                if(player.pos().x() < 720 && player.pos().x() > 700){
                    if(player.pos().y() < 320 && player.pos().y() > 280){
                        return Scene::HOUSE_SKY;
                    }
                }
            }
            */


            bn::core::update();
        }
    }
}