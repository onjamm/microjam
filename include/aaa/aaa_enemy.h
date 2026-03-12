#ifndef AAA_ENEMY_H
#define AAA_ENEMY_H

#include <bn_sprite_ptr.h>
namespace aaa
{
    class aaa_enemy
    {
    public:
        aaa_enemy(bn::fixed_point starting_position, bn::fixed speed);

        void update();

    private:
        // The sprite to display the player
        bn::sprite_ptr _sprite;
        // The pixels/frame the player moves in each dimension
        bn::fixed _speed;
    };
}
#endif