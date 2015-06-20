
#include "golf.h"
#include <stdio.h>
#include <stdlib.h>

void Jump::display() const {
	printf( "%d %d %d\n", a,b,c );
}

void Board::initFromFile(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if( !fp )
	{
		printf( "file %s didn't open\n", filename );
		return;
	}
	
	int a,b,c;
	
	while(fscanf(fp, "%d %d %d", &a, &b, &c)!=EOF)
	{
		jumps.insert(Jump(a,b,c));
		jumps.insert(Jump(c,b,a));
	}
	
	fclose(fp);
	
	int max=0;
	for(set<Jump>::iterator itr = jumps.begin(); itr!=jumps.end(); itr++)
	{
		if(itr->a > max) max = itr->a;
		if(itr->b > max) max = itr->b;
		if(itr->c > max) max = itr->c;
	}
	
	for(int i=0; i<=max; i++)
		pieces.push_back(false);
}


void Board::display() const
{
	int size = pieces.size();
	int inthisrow=1;
	int r=0;
	
	for(int i=0; i<size; i++)
	{
		if(r==0)
		{
			for(int j=0; j<20-inthisrow; j++)
				printf( " " );
		}
		printf( "%c ", pieces[i]?'*':'_' );
		r++;
		if(r==inthisrow)
		{
			printf( "\n" );
			r = 0;
			inthisrow++;
		}
	}
	
	printf( "\n" );
}


void Board::fillAllButOne(int which)
{
	int size = pieces.size();	
	for(int i=0; i<size; i++)
		pieces[i] = (i!=which);
}


vector<Jump> Board::possibleJumps()
{
	vector<Jump> R;
	
	for(set<Jump>::iterator itr = jumps.begin(); itr!=jumps.end(); itr++)
	{
		if(isPossible(*itr))
			R.push_back(*itr);
	}
	
	return R;
}


bool Board::isPossible(const Jump& J)
{
	return (pieces[J.a] && pieces[J.b] && !pieces[J.c]);
}


bool Board::perform(const Jump& J)
{
	pieces[J.a] = false;
	pieces[J.b] = false;
	pieces[J.c] = true;
}

bool Board::reverse(const Jump& J)
{
	pieces[J.a] = true;
	pieces[J.b] = true;
	pieces[J.c] = false;
}

bool Board::isSolved() const
{
	int count=0;
	int size=pieces.size();
	for(int i=0; i<size; i++)
		count+=pieces[i];
	return count==1;
}

void Board::recurse(vector<Jump> L)
{	
	vector<Jump> V = possibleJumps();
	
	if(isSolved())
	{
		printf( "L:\n" );
		for(vector<Jump>::iterator itr=L.begin(); itr!=L.end(); itr++)
			itr->display();
		
		display();
	}
	
	for(vector<Jump>::iterator itr=V.begin(); itr!=V.end(); itr++)
	{		
		perform(*itr);
		vector<Jump> newL = L;
		newL.push_back(*itr);
		recurse(newL);
		reverse(*itr);
	}
}






