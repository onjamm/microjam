#include <bn_keypad.h>

#include "aaa_planetoid.h"
#include "mj/mj_game_list.h"
#include "mj/mj_game_data.h"
#include "bn_display.h"

namespace
{
    constexpr bn::string_view code_credits[] = {"KJ, Adam Kurfurst"};
    constexpr bn::string_view graphics_credits[] = {"KJ, Adam Kurfurst"};
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(aaa::aaa_planetoids) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace aaa
{

    aaa_planetoids::aaa_planetoids([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("aaa"),
                                                                                                                       _player(bn::fixed_point(0, 0))
    {

        for (int i = 0; i < _enemies.max_size(); i++)
        {
            bn::fixed_point pos(data.random.get_int(-200, 200), data.random.get_int(-120, 120)); // added extra so some enemies spawn off-screen
            bn::fixed speed = data.random.get_fixed(.2, .4);                                // nice slow moving enemies

            _enemies.push_back(aaa_enemy({pos}, speed));
        }
    }

    bn::string<16> aaa_planetoids::title() const
    {
        return "Shoot asteroids!";
    }

    int aaa_planetoids::total_frames() const
    {
        return 480;
    }

    mj::game_result aaa_planetoids::play([[maybe_unused]] const mj::game_data &data)
    {
        _player.update();

        if (bn::keypad::a_pressed())
        {
            if (_bullets.size() != _bullets.max_size()) // this makes it so that only the max amount of bullets can be on screen at a time, i tried to resize rthe bullets vector but could not so i did this bandaid fix
            {
                _bullets.push_back(aaa_Bullet(bn::fixed_point(0, 0), 5, _player.getAngle()));
            }
        }

        for (aaa_enemy &enemy : _enemies)
        {
            enemy.update();
        }

        for (int i = _bullets.size() - 1; i >= 0; --i)
        {
            _bullets[i].update();

            bn::fixed bX = _bullets[i].BulletPos().x();
            bn::fixed bY = _bullets[i].BulletPos().y();

            if (bX > bn::display::width() / 2 || bY > bn::display::height() / 2 || bX < -bn::display::width() / 2 || bY < -bn::display::height() / 2)
            {
                _bullets.erase(_bullets.begin() + i);
            }
        }
        return mj::game_result();
    }

    bool aaa_planetoids::victory() const
    {
        return false;
    }

    void aaa_planetoids::fade_in([[maybe_unused]] const mj::game_data &data)
    {
    }

    void aaa_planetoids::fade_out([[maybe_unused]] const mj::game_data &data)
    {
    }
}