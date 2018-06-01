
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "utility.h"


class Button : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
public:
  typedef std::unique_ptr<Button> UPtr;

  explicit Button();
  explicit Button(sf::Text& text);
  explicit Button(sf::Text& text, util::ActionType action);

  virtual sf::Vector2f GetSize() const;

  virtual util::ActionType HandleClick(int x, int y);

  virtual void SetAction(util::ActionType action);

  virtual void SetPosition(float x, float y);

  virtual void SetPosition(const sf::Vector2f& pos);

  virtual void SetSize(const sf::Vector2f& size);

  virtual void SetString(const std::string& string);

  virtual void SetText(const sf::Text& text);

  virtual void SetWidth(int w);

  virtual void Unclick();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
  bool IsHit(int x, int y) const;
  virtual void _AdjustBox();
  virtual void _AdjustText();

private:
  static const sf::Color  BASIC_COLOR;
  static const float      DEFAULT_HEIGHT;
  static const sf::Color  PRESSED_COLOR;


  void _Init();

  util::ActionType    _action;
  sf::RectangleShape  _box;
  sf::Text            _text;
};
