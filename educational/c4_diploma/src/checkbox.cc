
#include "checkbox.h"

CheckBox::CheckBox(const std::string& name) :
Button(),
_is_checked(false),
_name(name) {}

util::ActionType CheckBox::HandleClick(int x, int y) {
	return util::ActionType::None;
}

void CheckBox::SetString(const std::string& string) {}

void CheckBox::SetText(const sf::Text& text) {}

void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {}
