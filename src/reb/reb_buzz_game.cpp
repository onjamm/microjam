#include "reb_buzz_game.h"

#include "bn_keypad.h"
#include <bn_rect.h>
#include <bn_size.h>
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "mj/mj_game_list.h"

namespace
{
    constexpr bn::string_view code_credits[] = { "Rebecca Riffle" };
    constexpr bn::string_view graphics_credits[] = { "" };
    constexpr bn::string_view sfx_credits[] = {""};
}

MJ_GAME_LIST_ADD(reb::reb_buzz_game)
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
// MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace reb
{
    reb_buzz_game::reb_buzz_game([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data& data) :
        mj::game("reb")
    {
       _beeAnimation = bn::create_sprite_animate_action_forever(_playerSprite, 6, bn::sprite_items::reb_buzz.tiles_item(), 0, 1);
    }

    void reb_buzz_game::fade_in([[maybe_unused]] const mj::game_data& data)
    {
        _flowerSprite.set_position(-100, 0);
        _playerSprite.set_position(0, 0);
    }

    /**
     * Creates a rectangle centered at a sprite's location with a given size.
     * sprite the sprite to center the box around
     * box_size the dimensions of the bounding box
     */
    bn::rect create_bounding_box(bn::sprite_ptr sprite) {
        return bn::rect(sprite.x().round_integer(),
                        sprite.y().round_integer(),
                        4,
                        4);
    }

    mj::game_result reb_buzz_game::play([[maybe_unused]] const mj::game_data& data)
    {
        _beeAnimation->update();
        _victory = false;

        bn::fixed player_speed = 2;
        if(bn::keypad::left_held()) {
            _playerSprite.set_x(_playerSprite.x() - player_speed);
        }
        if(bn::keypad::right_held()) {
            _playerSprite.set_x(_playerSprite.x() + player_speed);
        }
        if(bn::keypad::up_held()) {
            _playerSprite.set_y(_playerSprite.y() - player_speed);
        }
        if(bn::keypad::down_held()) {
            _playerSprite.set_y(_playerSprite.y() + player_speed);
        }

        bn::rect bee_bounding_box = create_bounding_box(_playerSprite);
        bn::rect flower_bounding_box = create_bounding_box(_flowerSprite);

        if (bee_bounding_box.intersects(flower_bounding_box))
        {
            _victory = true;
        }

        mj::game_result result(victory(), false);

        return result;
    }

    bool reb_buzz_game::victory() const
    {
        return _victory;
    }

    void reb_buzz_game::fade_out([[maybe_unused]] const mj::game_data& data)
    {
    }

}