//a couple of function for the interpreter
//soon to be extended as multithreaded brainfuck

#ifndef BRAINLIB__H
#define BRAINLIB__H

#include <stdio.h>

struct bfd{
	FILE *in;
	FILE *out;
	char *p;
	unsigned char *m;
	unsigned p_len;
	unsigned m_len;
};

struct bptr{
	char *ip;
	unsigned char *mp;
};

void brainfuck( void *payload );
void brainline( struct bptr *p, struct bfd *data );
void brainloop( struct bptr *p, struct bfd *data );

#endif
