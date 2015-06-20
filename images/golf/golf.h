
#ifndef _GOLF_
#define _GOLF_

#include <vector>
#include <set>

using namespace std;

class Jump {
public:
	int a,b,c;
	
	Jump(){}
	Jump(int ina, int inb, int inc) {a = ina; b = inb; c = inc;}
	
	bool operator<(const Jump& J) const {
		return (a<J.a) || (a==J.a && b<J.b) || (a==J.a && b==J.b && c<J.c);
	}
	
	void display() const;
};

class Board {
	public:
	Board(){}
	~Board(){}

	set<Jump> jumps;
	vector<bool> pieces;
	
	void initFromFile(const char* filename);
	void display() const;
	void fillAllButOne(int which);
	vector<Jump> possibleJumps();
	bool isPossible(const Jump& J);
	bool perform(const Jump& J);
	bool reverse(const Jump& J);
	bool isSolved() const;
	void recurse(vector<Jump> L);
};

#endif