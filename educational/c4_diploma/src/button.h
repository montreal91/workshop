
#pragma once


#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "utility.h"

class Button :
public sf::Drawable,
public sf::Transformable,
private sf::NonCopyable
{
public:
  typedef std::function<void()> Callback;

  explicit Button();
  explicit Button(sf::Text& text);
  explicit Button(sf::Text& text, util::ActionType action);

  virtual util::ActionType HandleClick(int x, int y);

  virtual void SetAction(util::ActionType action);

  virtual void SetPosition(float x, float y);

  virtual void SetPosition(const sf::Vector2f& pos);

  virtual void SetString(const std::string& string);

  virtual void SetText(const sf::Text& text);

  virtual void Unclick();

private:
  static const sf::Color  BASIC_COLOR;
  static const float      DEFAULT_HEIGHT;
  static const sf::Color  PRESSED_COLOR;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void _AdjustBox();
  void _AdjustText();
  void _Init();

  util::ActionType    _action;
  sf::RectangleShape  _box;
  sf::Text            _text;
};
