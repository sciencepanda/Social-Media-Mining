#include <iostream>

class tt {
	public:
		tt() {};
		explicit tt(const tt& t) : id(t.id) {};
		tt& operator = (const tt& t) {
			id = t.id;
			std::cout << "xx" << std::endl;	
		}
		int id;
};
