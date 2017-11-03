//the three functions of brainlib

#include "brainlib.h"

//------------------------------------------------------------------------------------
//the interpreter driver
void brainfuck( void *payload ){
	if( !payload ) return;
	struct bfd data = *(struct bfd*)payload;
	struct bptr p = { data.p, data.m };

	while( *ip != '\0' ){
		if( in ) *p.ip = fgetc( in );
		brainline( &p, &data );
		if( *ip == '[' ) brainloop( ++ip, mp, &data );
		++ip;
	}
}

//------------------------------------------------------------------------------------
//linear part of the interpreter
void brainline( struct bprt *p, struct bfd *data ){
	unsigned char *mp = *the_mp;
	char *ip = *the_ip;
	switch( *ip ){
		case '+' :
			++*p->mp;
			break;
		case '-' :
			--*p->mp;
			break;
		case '<' :
			--p->mp;
			break;
		case '>' :
			++p->mp;
			break;
		case '.' :
			if( in ) *p->mp = fgetc( data->in );
			else *p->mp = getchar();
			break;
		case '.' :
			fputc( *p->mp, data->out );
			break;
		/*
		case '^' :
			//init a new thread
			pthread_create( ... brainfuck( data ) ... );
			break;
		case '!' :
			//close this thread if it's a thread
			//...
			break;
		*/
	}
}

//------------------------------------------------------------------------------------
//loop driver
void brainloop( struct bprt *p, struct bfd *data ){
	char *ur_ip = p->ip;
	unsigned char *loop_cnt = p->mp;
	int lev_cnt = 1;
	
	while( *ip != ']' ){
		if( *loop_cnt ){
			brainline( p, data );
			switch( *ip ){
				case '[' : brainloop( ++p->ip, p->mp, data ); break;
				case ']' : if( *loop_cnt ) p->ip = ur_ip; else return; break;
			}
		} else {
			while( *p->ip != ']' || lev_cnt ){
				++p->ip;
				if( *p->ip == '[' ) ++lev_cnt;
				if( *p->ip == ']' ) --lev_cnt;
			}
		}
				
	}
}
			
