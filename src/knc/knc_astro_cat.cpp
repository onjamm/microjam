#include "knc/knc_astro_cat.h"
#include "mj/mj_game_list.h"

namespace {
    constexpr bn::string_view code_credits[] = { "knc" };
    constexpr bn::string_view graphics_credits[] = { "knc" };
    constexpr bn::string_view sfx_credits[] = { "" };
    constexpr bn::string_view music_credits[] = { "" };
}

namespace knc {

    bn::fixed knc_astro_cat::_recommended_speed(mj::difficulty_level difficulty) {
        if (difficulty == mj::difficulty_level::EASY){
            return 2;
        } else if (difficulty == mj::difficulty_level::NORMAL) {
            return 2.5;
        }
        return 3;
    }

    // helper for intial speed
    bn::fixed knc_astro_cat::_initial_speed(int completed_games, const mj::game_data& data) {
    return _recommended_speed(recommended_difficulty_level(completed_games, data));
}
    knc_astro_cat::knc_astro_cat(int completed_games, const mj::game_data& data)
        : mj::game("knc"),
        _background(),
        _cat(bn::fixed_point(0,40), 2),
        _difficulty(recommended_difficulty_level(completed_games, data)),
        _enemy1_direction(true),
        _enemy1_delay(180),
        _hit(false)
    {
        bn::fixed speed = _recommended_speed(_difficulty);

        if(_difficulty == mj::difficulty_level::NORMAL || _difficulty == mj::difficulty_level::HARD) {
            _planet4 = planet(bn::fixed_point(30, -440), speed);
            _star1 = shooting_star(bn::fixed_point(-120, -30), speed);
            _star2 = shooting_star(bn::fixed_point(-120, 18), speed);
        }

        if(_difficulty == mj::difficulty_level::HARD) {
            _star3 = shooting_star(bn::fixed_point(-120, 0), speed);
            // enemy stays at (1000,1000) until delay expires
        }
    }

    bn::string<16> knc_astro_cat::title() const { return "Dodge Them Fire!"; }
    int knc_astro_cat::total_frames() const { return 60 * 5; }

    mj::game_result knc_astro_cat::play(const mj::game_data& data)
    {
        bn::fixed speed = _recommended_speed(_difficulty);
        _background.update();
        _cat.update();

        _planet1.update();
        if(_planet1.off_screen()) {
            _planet1 = planet(bn::fixed_point(bn::fixed(data.random.get_int(200)) - 100, -80), speed);
        }
        _planet2.update();
        if(_planet2.off_screen()) {
            _planet2 = planet(bn::fixed_point(bn::fixed(data.random.get_int(200)) - 100, -80), speed);
        }
        _planet3.update();
        if(_planet3.off_screen()) {
            _planet3 = planet(bn::fixed_point(bn::fixed(data.random.get_int(200)) - 100, -80), speed);
        }

        // update planet4 — normal + hard only
        if (_difficulty == mj::difficulty_level::NORMAL || _difficulty == mj::difficulty_level::HARD) 
    {
        _planet4.update();
        if(_planet4.off_screen()) {
            _planet4 = planet(bn::fixed_point(bn::fixed(data.random.get_int(200)) - 100, -80), speed);
        }

        _star1.update();
        if(_star1.off_screen()) {
            _star1 = shooting_star(bn::fixed_point(-120, bn::fixed(data.random.get_int(140)) - 70), speed);
        }
        _star2.update();
        if(_star2.off_screen()) {
            _star2 = shooting_star(bn::fixed_point(-120, bn::fixed(data.random.get_int(140)) - 70), speed);
        }
    }
        // hard mode only star + enemy
        if(_difficulty == mj::difficulty_level::HARD) 
    {
        _star3.update();
        if(_star3.off_screen()) {
            _star3 = shooting_star(bn::fixed_point(-120, bn::fixed(data.random.get_int(140)) - 70), speed);
        }

        // count down delay, then activate enemy
        if(_enemy1_delay > 0) {
            _enemy1_delay--;
            if(_enemy1_delay == 0) {
                bn::fixed y = bn::fixed(data.random.get_int(100)) - 50;
                _enemy1 = enemy(bn::fixed_point(-120, y), speed, 1);
            }
        } else {
            _enemy1.update();
            if(_enemy1.off_screen()) {
                _enemy1_direction = !_enemy1_direction;
                int dir = _enemy1_direction ? 1 : -1;
                bn::fixed spawn_x = _enemy1_direction ? bn::fixed(-120) : bn::fixed(120);
                bn::fixed y = bn::fixed(data.random.get_int(100)) - 50;
                _enemy1 = enemy(bn::fixed_point(spawn_x, y), speed, dir);
            }
        }
    }
        // if planet hit cat, end game 
        // if star hit cat, end game

        // easy
        if (_planet1.collides_with(_cat.position(),             cat::COLLISION_RADIUS) ||
        _planet2.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        _planet3.collides_with(_cat.position(), cat::COLLISION_RADIUS)) {
            _hit = true;
        }

        // normal + hard
        if (_difficulty == mj::difficulty_level::NORMAL || _difficulty == mj::difficulty_level::HARD) {
        if (
        _planet4.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        _star1.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        _star2.collides_with(_cat.position(), cat::COLLISION_RADIUS)) {
            _hit = true;
        }
    }
    // hard only
    if (_difficulty == mj::difficulty_level::HARD) {
        if (_star3.collides_with(_cat.position(), cat::COLLISION_RADIUS) ||
        (_enemy1_delay == 0 && _enemy1.collides_with(_cat.position(), cat::COLLISION_RADIUS)))  {
                _hit = true;
    }
}
    // end game if cat got hit
        return mj::game_result(_hit, false);
    }

    // if cat never got hit - Win 
    bool knc_astro_cat::victory() const { return !_hit; }
    void knc_astro_cat::fade_in(const mj::game_data&) {}
    void knc_astro_cat::fade_out(const mj::game_data&) {}

} // namespace knc

MJ_GAME_LIST_ADD(knc::knc_astro_cat)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
