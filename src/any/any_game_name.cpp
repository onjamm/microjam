#include "any_game_name.h"
#include "bn_sprite_items_astronaut.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "mj/mj_game_list.h"

namespace {
    constexpr bn::string_view code_credits[] = { "Anthony Margullis, Yousif Sultan" };
    constexpr bn::string_view graphics_credits[] = { "Kenney Game Assets" };
    constexpr bn::string_view sfx_credits[] = {""};
    constexpr bn::string_view music_credits[] = {""};
}

MJ_GAME_LIST_ADD(any::any_game_name)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace any {

any_game_name::any_game_name([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
    mj::game("any")
    {
        _astronaut_sprite = bn::sprite_items::astronaut.create_sprite(0, -20);
        _player.emplace(*_astronaut_sprite);
    }



bn::string<16> any_game_name::title() const {
    return "Astronaut";
}

int any_game_name::total_frames() const {
    return 600;
}

mj::game_result any_game_name::play([[maybe_unused]] const mj::game_data& data){
    // _player.update();
    if (_player) {
        _player->update(bn::span<const platform>(_platforms, 3));

        if (_player->y() > 70) {
            _has_lost = true;
        }
    }

    return mj::game_result(victory(), false);

}

bool any_game_name::victory() const {
    return _player && _player->y() < -40;
}

void any_game_name::fade_in([[maybe_unused]]const mj::game_data& data)
{
}

void any_game_name::fade_out([[maybe_unused]] const mj::game_data& data)
{    
}

}