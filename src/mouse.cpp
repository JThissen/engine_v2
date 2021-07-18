#include "mouse.hpp"

namespace engine {
	std::unordered_map<Mouse::MouseCode, std::string> Mouse::map = {
		{ Mouse::MouseCode::Button0			, "Button0" },
		{ Mouse::MouseCode::Button1			, "Button1" },
		{ Mouse::MouseCode::Button2			, "Button2" },
		{ Mouse::MouseCode::Button3			, "Button3" },
		{ Mouse::MouseCode::Button4			, "Button4" },
		{ Mouse::MouseCode::Button5			, "Button5" },
		{ Mouse::MouseCode::Button6			, "Button6" },
		{ Mouse::MouseCode::Button7     , "Button7" },
		{ Mouse::MouseCode::ButtonLast  , "ButtonLast" },
		{ Mouse::MouseCode::ButtonLeft  , "Button0" },
		{ Mouse::MouseCode::ButtonRight , "ButtonRight" },
		{ Mouse::MouseCode::ButtonMiddle, "ButtonMiddle" }
	};
}
