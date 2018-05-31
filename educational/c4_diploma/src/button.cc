
#include "button.h"


const sf::Color Button::BASIC_COLOR = sf::Color::Cyan;
const float Button::DEFAULT_HEIGHT = 20.0;
const sf::Color Button::PRESSED_COLOR = sf::Color::Yellow;

Button::Button() :
_action(util::ActionType::None),
_box(),
_text()
{
  // change texture;

  _Init();
}

Button::Button(sf::Text& text) :
_action(util::ActionType::None),
_box(),
_text(text)
{
  _Init();
}

Button::Button(sf::Text& text, util::ActionType action) :
_action(action),
_box(),
_text(text)
{
  _Init();
}

util::ActionType Button::HandleClick(int x, int y) {
  auto rect = _box.getLocalBounds();
  auto pos = this->getPosition();

  rect.left += pos.x;
  rect.top += pos.y;

  bool hit = rect.contains(static_cast<float>(x), static_cast<float>(y));
  if (hit) {
    _box.setFillColor(PRESSED_COLOR);
    return _action;
  }
  else {
    return util::ActionType::None;
  }
}

void Button::SetAction(util::ActionType action) {
  _action = action;
}

void Button::SetPosition(float x, float y) {
  this->setPosition(x, y);
}

void Button::SetPosition(const sf::Vector2f& pos) {
  this->setPosition(pos);
}


void Button::SetString(const std::string& string) {
  _text.setString(string);
  _AdjustBox();
  _AdjustText();
}

void Button::SetText(const sf::Text& text) {
  _text = text;
  _AdjustBox();
  _AdjustText();
}

void Button::Unclick() {
  _box.setFillColor(BASIC_COLOR);
}

//
// Private methods
//

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(_box, states);
  target.draw(_text, states);
}

void Button::_AdjustBox() {
  auto text_bounds = _text.getLocalBounds();
  _box.setSize(sf::Vector2f(text_bounds.width + util::GAP * 2, DEFAULT_HEIGHT));
}

void Button::_AdjustText() {
  sf::FloatRect bounds = _box.getLocalBounds();
  util::CenterOrigin(_text);
  _text.setPosition(bounds.width / 2.0, bounds.height / 2.0);
}

void Button::_Init() {
  _box.setFillColor(BASIC_COLOR);

  _AdjustText();
  _AdjustBox();
}
