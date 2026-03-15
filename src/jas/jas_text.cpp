#include "jas/jas_text.h"

namespace jas {

  /* Text constructor */
  text::text() {
        // Generate the sprites and store them in the vector
        text_generator.generate(TEXT_POSITION, instructions, text_sprites);

  }

}