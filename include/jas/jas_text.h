#ifndef JAS_TEXT_H
#define JAS_TEXT_H

#include <bn_sprite_text_generator.h>
#include <bn_vector.h>
#include <bn_sprite_ptr.h>

#include "common_variable_8x16_sprite_font.h"

namespace jas {

      /**
     * The text on-screen displaying instructions to the player.
     */
    class text
    {
      public: 
        /* Text constructor */
        text();

      private:
        // Construct text generator
         bn::sprite_text_generator text_generator{common::variable_8x16_sprite_font};

         bn::vector<bn::sprite_ptr, 32> text_sprites;

        // Define text
         const bn::string_view instructions = "Press B for thrusters!";

         static constexpr bn::fixed_point TEXT_POSITION = {-100, -70};
    };
}

#endif