#include <stdio.h> 
#include <stdlib.h> 
#include "main.h"

char* fmt = "Size of %s: %d\n"; 
////////////////////////////////////////////////////////////////////// 
// Application main entry point 
////////////////////////////////////////////////////////////////////// 
int main( int argc, char** argv ) { 
    if( argc == 1 ) return showUsage();

    if( _cmp( argv[ 1 ], "-h" ) || _cmp( argv[ 1 ], "--help" ) )
        return showUsage();

    if( _cmp( argv[ 1 ], "-l" ) || _cmp( argv[ 1 ], "--list" ) ) {
        return listAll();
    }

    char type[ 16 ] = { 0 };
    _cpy( type, argv[ 1 ], 15 );

    if( is_quoted( type ) )
        unquote( type );

    int id = -1;
    if( ( id = isTypeName( type ) ) == -1 ) {
        printf( "Unrecognized or unsupported data type: %s\n", type );
        return 1;
    }

    printf( fmt, TYPENAMES[ id ].type_name, TYPENAMES[ id ].type_size );
    return 0;
}

////////////////////////////////////////////////////////////////////// 
// Function to print, to stdout, information about this program. 
////////////////////////////////////////////////////////////////////// 
int showUsage( void ) { 
    puts( "//////////////////////////////////////////////////////////////////////" ); 
    puts( "// typesize " ); 
    puts( "// Copyright \u00A9 2018 ShinobiSoft Software" ); 
    puts( "//////////////////////////////////////////////////////////////////////" ); 
    puts( "" ); 
    puts( "USAGE: typesize [typename]" ); 
    puts( " OR: typesize --list" ); 
    puts( "" ); 
    puts( "The following flags are supported: " ); 
    puts( " -h, --help - Prints this screen" ); 
    puts( " -l, --list - Print the sizes of all supported common data types" ); 
    puts( " ( IE; char, int, long, etc... ) See below." ); 
    puts( "" ); 
    puts( "typesize is a utility application, intended for use by programmers, to" ); 
    puts( "determine the byte sizes of various common data types. typesize" ); 
    puts( "currently supports the bool, char, double, float, int, long," ); 
    puts( "long long, short, and void* data types." ); 
    puts( "Input type names can be quoted, tho not required. With the exception" ); 
    puts( "of the 'long long' data type. It MUST be quoted as it contains a " ); 
    puts( "space character and command-line options are split on spaces..." ); 
    puts( "" ); 
    return 0; 
}

////////////////////////////////////////////////////////////////////// 
// Function to determine if a given string represents a supported 
// data type. 
////////////////////////////////////////////////////////////////////// 
int isTypeName( const char* s ) { 
    for( int i = 0; i < NUM_TYPENAMES; i++ ) { 
        if( _cmp( TYPENAMES[ i ].type_name, s ) ) 
            return i; 
    } 
    return -1; 
}

////////////////////////////////////////////////////////////////////// 
// Function to print byte sizes of ALL supported data types. 
////////////////////////////////////////////////////////////////////// 
int listAll( void ) {
    for( int i = 0; i < NUM_TYPENAMES; i++ ) {
        printf( fmt, TYPENAMES[ i ].type_name, TYPENAMES[ i ].type_size );
    }
    return 0;
}

////////////////////////////////////////////////////////////////////// 
// Utility function to determine if a string is quoted or not. This 
// function checks for both single and double quotes. 
////////////////////////////////////////////////////////////////////// 
int is_quoted( const char* s ) { 
    if( s == NULL || *s == '\0' ) 
        return -1;

    int l = _len( s );
    char first = *s;
    char last = s[ l-1 ];

    if( ( first == '\"' || first == '\'' ) && last == first )
        return 1;

    return 0;
}

////////////////////////////////////////////////////////////////////// 
// Utility function to remove starting and ending quotes from a string 
// NOTE: This function modifies the supplied string in place. 
////////////////////////////////////////////////////////////////////// 
void unquote( char* src ) { 
    int l = _len( src ); 
    if( src[ l-1 ] == '\'' || src[ l-1 ] == '\"' ) 
        src[ l-1 ] = '\0';

    for( int i = 0; i < l; i++ )
        src[ i ] = src[ i+1 ];
}

////////////////////////////////////////////////////////////////////// 
// Utility function to compare strings. This function takes case in to 
// account. Meaning, this function is case-sensitive, like strcmp(). 
////////////////////////////////////////////////////////////////////// 
int _cmp( const char* s1, const char* s2 ) { 
    if( s1 == NULL || s2 == NULL ) 
        return 0;

    if( _len( s1 ) != _len( s2 ) )
        return 0;

    int iter = 0;
    while( s1[ iter ] != 0 && s2[ iter ] != 0 ) {
        if( (int)s1[ iter ] != (int)s2[ iter ] )
            break;
        iter++;
    }
    return ( iter == _len( s1 ) );
}

////////////////////////////////////////////////////////////////////// 
// Utility function to copy one string to another. 
////////////////////////////////////////////////////////////////////// 
// Caller is responsible for ensuring that 'dst' array is of 
// sufficient size to handle the copy operation. 
////////////////////////////////////////////////////////////////////// 
/**
• @param dst - Destination buffer
• @param src - Source buffer
• @param dst_size - Maximum number of chars to copy to 'dst'
• @return Returns the number of characters copied on success,
•         -1 if 'src' is NULL, or 0 if no characters copied.
 */
int _cpy( char dst, const char* src, int dst_size ) { 
    if( src == NULL || *src == '\0' ) return -1;

    int sl = _len( src );
    if( sl ) {
        for( int i = 0; i < sl && i < dst_size; i++ ) {
            dst[ i ] = src[ i ];
        }
        dst[ sl ] = '\0';
        return _len( dst );
    }
    return 0;
}

////////////////////////////////////////////////////////////////////// 
// Utility function to determine the length of a string 
////////////////////////////////////////////////////////////////////// 
int _len( const char* s ) { 
    int len = 0; 
    while( s[ len ] ) 
        len++; 
    return len; 
}
