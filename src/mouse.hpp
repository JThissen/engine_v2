#ifndef MOUSE_CODES_H
#define MOUSE_CODES_H

#include "headers.hpp"

namespace engine {
	class Mouse {
		public:
		enum class MouseCode {
			Button0      = 0,
			Button1      = 1,
			Button2      = 2,
			Button3      = 3,
			Button4      = 4,
			Button5      = 5,
			Button6      = 6,
			Button7      = 7,
			ButtonLast   = Button7,
			ButtonLeft   = Button0,
			ButtonRight  = Button1,
			ButtonMiddle = Button2
  	};

		static std::unordered_map<MouseCode, std::string> map;
	};
}

#endif
