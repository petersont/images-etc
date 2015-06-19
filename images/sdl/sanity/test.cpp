#include <stdio.h>

int main(int argc, char** args)
{
	int i=0;
	for(i; i<argc; i++)
	{
		char* s = args[i];
		
		for(int j=0; s[j]; j++)
		{
			char c = s[j];
			
			putchar(c);
		}
		
		putchar('\n');
	}
	
	return 0;
}

