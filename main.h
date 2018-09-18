#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef bool
    #include <stdbool.h>
#endif // bool


typedef struct TYPEDATA {
    char* type_name;
    int   type_size;
} TYPEDATA;

#define NUM_TYPENAMES 9
TYPEDATA TYPENAMES[ NUM_TYPENAMES ] = {
    { "bool",       sizeof( bool ) },
    { "char",       sizeof( char ) },
    { "double",     sizeof( double ) },
    { "float",      sizeof( float ) },
    { "int",        sizeof( int ) },
    { "long",       sizeof( long ) },
    { "long long",  sizeof( long long ) },
    { "short",      sizeof( short ) },
    { "void*",      sizeof( void* ) },
};

int isTypeName( const char* s );
int listAll( void );
int showUsage( void );

int is_quoted( const char* s );
void unquote( char* src );

/* Local string functions. Usually faster than stdlib functions */
// This also prevents me from having to #include <string.h> too!
int _cmp( const char* s1, const char* s2 );
int _cpy( char* dst, const char* src, int dst_size );
int _len( const char* s );

#endif // _MAIN_H_
