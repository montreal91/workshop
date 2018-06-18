
#include "utility.h"

namespace util {

void CenterOrigin(sf::Text& text) {
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(
    std::floor(bounds.left + bounds.width / 2.0),
    std::floor(bounds.top + bounds.height / 2.0)
  );
}

sf::Text CreateEmptyLabel(const sf::Color& text_color, const sf::Font& font) {
  auto label = sf::Text();
  label.setFont(font);
  label.setString("");
  label.setColor(text_color);
  label.setCharacterSize(FONT_SIZE);
  return label;
}

b2Vec2 GetNormalizedVector(const b2Vec2& vec) {
  float norma = GetVectorNorm(vec);
  if (norma <= EPSILON) {
    return b2Vec2(vec.x, vec.y);
  }

  b2Vec2 res = b2Vec2(vec.x / norma, vec.y / norma);
  return res;
}

float GetVectorNorm(const b2Vec2& vec) {
  return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

} // namespace util
