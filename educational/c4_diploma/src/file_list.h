
#pragma once


#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "button.h"


class FileList :
    public sf::Drawable,
    public sf::Transformable,
    public sf::NonCopyable
{
public:
  typedef std::unique_ptr<FileList> UPtr;

  explicit FileList(const std::vector<std::string>& files, const sf::Font& font);

  virtual std::string GetValue() const;
  virtual util::ActionType HandleClick(int x, int y);
  virtual void SetMaxPositions(size_t p);
  virtual void SetWidth(int w);
  virtual void Unclick();

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
  static const sf::Color  BASIC_COLOR;
  static const float      DEFAULT_HEIGHT;
  static const sf::Color  DISABLED_COLOR;
  static const int        NEGATIVE;
  static const sf::Color  PRESSED_COLOR;
  static const sf::Color  TEXT_COLOR;

  bool _CanMoveUp() const;
  void _CutStrings();
  size_t _GetLastButtonIndex() const;
  int _HandleFileButtonClick(int x, int y);
  void _InitButtons();
  void _MoveButtons();


  size_t _current_top;
  Button _down_btn;
  std::vector<Button::UPtr> _file_buttons;
  std::vector<std::string> _file_names;
  sf::Font _font;
  size_t _max_positions;
  Button _up_btn;
  int _value;
  float _width;
};
