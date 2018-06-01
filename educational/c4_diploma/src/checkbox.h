
#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "utility.h"


class CheckBox : public Button {
public:
  CheckBox(const std::string& name);

  util::ActionType HandleClick(int x, int y) override;
  bool IsChecked() const;
  void SetChecked(bool checked);

  // void SetPosition(float x, float y) override;

  // void SetPosition(const sf::Vector2f& pos) override;

  void SetString(const std::string& string) override;

  void SetText(const sf::Text& text) override;
  void ToggleChecked();

private:

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  // sf::RectangleShape
  bool        _is_checked;
  std::string _name;
};
