
#include "golf.h"

int main(int argc, char** args)
{
	Board B;
	B.initFromFile("board5");
	B.fillAllButOne(4);
	
	B.recurse(vector<Jump>());
	
	return 0;
}

