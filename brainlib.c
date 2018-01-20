//the three functions of brainlib

#include "brainlib.h"

//------------------------------------------------------------------------------------
//the interpreter driver
void brainfuck( void *payload ){
	if( !payload ) return;
	struct bfd data = *(struct bfd*)payload;
	struct bptr p = { data.p, data.m };

	while( *p.ip != '\0' ){
		brainline( &p, &data );
		++p.ip;
	}
}

//------------------------------------------------------------------------------------
//linear part of the interpreter
void brainline( struct bptr *p, struct bfd *data ){
	switch( *p->ip ){
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
		case ',' :
            *p->mp = fgetc( data->in );
			break;
		case '.' :
            fputc( *p->mp, data->out );
			break;
        case '[' :
            ++p->ip;
            brainloop( p, data );
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
void brainloop( struct bptr *p, struct bfd *data ){
	char *ur_ip = p->ip;
	unsigned char *loop_cnt = p->mp;
	
	while( *loop_cnt ){
        if( *p->ip == ']' ) p->ip = ur_ip;
        else brainline( p, data );
	}
}
