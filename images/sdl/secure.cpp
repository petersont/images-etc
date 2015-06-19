
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

int main(int argc, char** args)
{
	SSL_load_error_strings();
	ERR_load_BIO_strings();
	OpenSSL_add_all_algorithms();
	
	
	BIO * bio;
	
	bio = BIO_new_connect((char*)"127.0.0.1:2011");
	if(bio == NULL)
	{
		/* Handle the failure */
		printf( "bio creation failed\n" );
	}
	
	if(BIO_do_connect(bio) <= 0)
	{
		/* Handle failed connection */
		printf( "bio connection failed\n" );
	}
	

#if 0
	int x = BIO_read(bio, buffer, len);
	if(x == 0)
	{
		/* Handle closed connection */
	}
	else if(x < 0)
	{
	   if(! BIO_should_retry(bio))
		{
			/* Handle failed read here */
		}
	
		/* Do something to handle the retry */
	}
#endif

	int length = 256;
	char* buffer = (char*)malloc(length*sizeof(char));
	sprintf(buffer, "Test String\n");
	
	if(BIO_write(bio, buffer, length) <= 0)
	{
		if(! BIO_should_retry(bio))
		{
			/* Handle failed write here */
		}
	
		/* Do something to handle the retry */
	}
	
	free(buffer);
	
	
	/* To reuse the connection, use this line */
	BIO_reset(bio);
	
	
	/* To free it from memory, use this line */
	BIO_free_all(bio);
	
	return 0;
}

