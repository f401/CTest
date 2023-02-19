#ifndef __DDZ_CARD_ATTRIBUTE_HPP__

#define __DDZ_CARD_ATTRIBUTE_HPP__

#include <stdint.h>

#include "defines.hpp"

namespace ddz {

namespace CardAttributes {
enum class Color { Red = 0, Black = 1 };
} // namespace CardAttributes

class CardAttribute {
public:
  DDZ_INLINE CardAttributes::Color get_color() const { return color; }
  DDZ_INLINE explicit CardAttribute(CardAttributes::Color color, uint8_t id)
      : color(color), id(id) {}

  DDZ_INLINE bool operator==(const CardAttribute &src) const {
    return src.color == color && src.id == id;
  }

private:
  CardAttributes::Color color;
  uint8_t id;
};

namespace CardAttributes {
const CardAttribute FangKuai(Color::Black, 1);
const CardAttribute MeiHua(Color::Red, 2);
const CardAttribute HongTao(Color::Red, 3);
const CardAttribute HeiTao(Color::Black, 4);
const CardAttribute KING1(Color::Black, 5);
const CardAttribute KING2(Color::Red, 6);
} // namespace CardAttributes

} // namespace ddz

#endif /* end of include guard: __DDZ_CARD_ATTRIBUTE_HPP__ */
