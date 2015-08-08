#pragma  once

namespace KLab {
	class CharHelper {
		CharHelper() {}
		~CharHelper() {}

	public:
		static bool isDigit(char c) {
			return c >= '0' && c <= '9';
		}

		static bool isLetter(char c) {
			return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
		}
	};
}