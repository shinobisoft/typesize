# typesize

typesize is a utility application, intended for use by programmers, to
determine the byte sizes of various common data types. typesize
currently supports the bool, char, double, float, int, long,
long long, short, and void* data types.

Input type names can be quoted, tho not required. With the exception
of the \'long long\' data type. It MUST be quoted as it contains a
space character and command-line options are split on spaces...
