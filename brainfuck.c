//a simple brainfuck interpreter

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "brainlib.h"

#define DEFAULT_P_LEN 4096
#define DEFAULT_M_LEN 65536


int main( int argc, char **argv ){
	struct bfd data = {
		stdin,
		stdout,
		calloc( DEFAULT_P_LEN+1, 1 ),
		calloc( DEFAULT_M_LEN, 1 ),
		DEFAULT_P_LEN,
		DEFAULT_M_LEN
	};

	unsigned p_len = DEFAULT_P_LEN;
	char *program = calloc( p_len+1, 1 );
	
	unsigned m_len = DEFAULT_M_LEN;
	unsigned char *mem = calloc( m_len, 1 );
	
	struct option opts[] = {
		{ "program", required_argument, NULL, 'p' },
		{ "file", required_argument, NULL, 'f' },
		{ "mem", required_argument, NULL, 'm' },
		{ "output", required_argument, NULL, 'o' },
		{ NULL, 0, NULL, 0 }
	};
	
	char iota=0; int idx;
	while( (iota = getopt_long( argc, argv, "p:f:m:o:", opts, &idx )) != -1 ){
		switch( iota ){
			case 'p' :
				data.p_len = strlen( optarg );
				data.p = realloc( data.p, data.p_len+1 );
				strncpy( data.p, optarg, data.p_len );
				break;
			case 'f' :
				data.in = fopen( optarg, "r" );
				if( !data.in ) exit( 1 );
				break;
			case 'm' :
				data.m_len = atoi( optarg );
				data.m = calloc( data.m_len, 1 );
				break;
			case 'o' :
				data.out = fopen( optarg, "w" );
				if( !data.out ) exit( 2 );
				break;
		}
	}
	
	brainfuck( &data );
	fputc( '\n', data.out );
    
	return 0;
}
			
