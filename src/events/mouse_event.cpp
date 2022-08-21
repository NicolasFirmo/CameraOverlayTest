#include "mouse_event.h"

std::string MouseButtonEvent::toString() const {
	return fmt::format("MouseButtonEvent{{button:{}, action:{}, mods:{}{}{}}}",
					   button == MouseButton::left	 ? "left" :
					   button == MouseButton::right	 ? "right" :
					   button == MouseButton::middle ? "middle" :
													   "unknown",
					   action == MouseAction::pressed ? "pressed" : "released",
					   mods == MouseMods::none								? "none" :
					   mods & MouseMods::shift && mods & MouseMods::ctrlAlt ? "shift+" :
					   mods & MouseMods::shift								? "shift" :
																			  "",
					   mods & MouseMods::ctrl && mods & MouseMods::alt ? "ctrl+" :
					   mods & MouseMods::ctrl						   ? "ctrl" :
																		 "",
					   mods & MouseMods::alt ? "alt" : "");
};

std::string MouseMoveEvent::toString() const {
	return fmt::format("MouseMoveEvent{{x:{}, y:{}}}", pos.x, pos.y);
};