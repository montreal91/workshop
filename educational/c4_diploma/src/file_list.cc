
#include "file_list.h"

#include <iostream>


const int       FileList::NEGATIVE = -1;
const sf::Color FileList::TEXT_COLOR = sf::Color::Black;


FileList::FileList(
    const std::vector<std::string>& filenames,
    const sf::Font& font
) :
_current_top(0),
_down_btn(),
_file_buttons(),
_file_names(),
_font(font),
_max_positions(3),
_up_btn(),
_value(NEGATIVE) {
  for (auto i=0; i<filenames.size(); i++) {
    _file_names.push_back(filenames[i]);
  }
  std::sort(_file_names.begin(), _file_names.end());
  _InitButtons();
  // _CutStrings();
}

std::string FileList::GetValue() const {
  if (_value > NEGATIVE) {
    return _file_names[_value];
  }
  else {
    return "";
  }
}

util::ActionType FileList::HandleClick(int x, int y) {
  sf::Vector2f pos(x, y);
  pos -= this->getPosition();
  if (_up_btn.HandleClick(pos.x, pos.y) == util::ActionType::Dummy) {
    if (_CanMoveUp()) {
      _current_top++;
      _MoveButtons();
    }
    return util::ActionType::None;
  }
  if (_down_btn.HandleClick(pos.x, pos.y) == util::ActionType::Dummy) {
    if (_current_top > 0) {
      _current_top--;
      _MoveButtons();
    }
    return util::ActionType::None;
  }
  auto res = _HandleFileButtonClick(pos.x, pos.y);
  if (res == NEGATIVE) {
    return util::ActionType::None;
  }
  if (res >= _current_top && res < _current_top + _max_positions) {
    _value = res;
    return util::ActionType::ReloadFile;
  }
  else {
    return util::ActionType::None;
  }
}

void FileList::SetMaxPositions(size_t p) {
  _max_positions = p;
  // _InitButtons();
}

void FileList::SetWidth(int w) {
  _width = w;
  _down_btn.SetWidth(w);
  _up_btn.SetWidth(w);

  for (auto& btn : _file_buttons) {
    btn->SetWidth(w);
  }
}

void FileList::Unclick() {
  _down_btn.Unclick();
  _up_btn.Unclick();

  for (auto& btn : _file_buttons) {
    btn->Unclick();
  }
}

void FileList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= this->getTransform();
  for (auto i=_current_top; i<_GetLastButtonIndex(); i++) {
    _file_buttons[i]->draw(target, states);
  }
  target.draw(_down_btn, states);
  target.draw(_up_btn, states);
}

void FileList::_CutStrings() {
  const auto char_width = 8;
  auto len = _width / char_width;
  for (auto& btn : _file_buttons) {
    btn->CutString(len);
  }
}

bool FileList::_CanMoveUp() const {
  bool cond1 = _current_top < _file_buttons.size() - _max_positions;
  bool cond2 = _file_buttons.size() > _max_positions;
  return cond1 && cond2;
}

size_t FileList::_GetLastButtonIndex() const {
  auto size = _file_buttons.size();
  if (size < _max_positions) {
    return size;
  }
  else {
    return static_cast<size_t>(_current_top + _max_positions);
  }
}

int FileList::_HandleFileButtonClick(int x, int y) {
  for (auto i=0; i<_file_buttons.size(); i++) {
    if (_file_buttons[i]->HandleClick(x, y) != util::ActionType::None) {
      return i;
    }
  }
  return NEGATIVE;
}

void FileList::_InitButtons() {
  _up_btn.SetAction(util::ActionType::Dummy);
  _up_btn.SetText(util::CreateEmptyLabel(TEXT_COLOR, _font));
  _up_btn.SetString("<Up>");
  const auto step = _down_btn.GetSize().y;
  for (auto i=0; i<_file_names.size(); i++) {
    auto btn = Button::CreateButton(
      _file_names[i],
      _font,
      util::ActionType::ReloadFile
    );

    btn->SetPosition(0, (step + util::GAP) * (i + 1 + _current_top));
    _file_buttons.push_back(std::move(btn));
  }
  _down_btn.SetAction(util::ActionType::Dummy);
  _down_btn.SetText(util::CreateEmptyLabel(TEXT_COLOR, _font));
  _down_btn.SetString("<Down>");

  _down_btn.SetPosition(0, (step + util::GAP) * (_max_positions + 1));
}

void FileList::_MoveButtons() {
  const auto step = _down_btn.GetSize().y;
  for (auto i=0; i<_file_buttons.size(); i++) {
    auto x = 0;
    auto y = (step + util::GAP) * (i - static_cast<int>(_current_top) + 1);
    _file_buttons[i]->SetPosition(x, y);
  }
}
