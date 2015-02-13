/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Interfaces for apyc. */

#ifndef _APYC_H_
#define _APYC_H_

#include <cstdio>
#include <string>
#include "ast.h"

/** A dummy class whose sole purpose is to provide a constructor that
 *  initializes the garbage collector (required for Darwin).  Put a
 *  definition of a dummy GCINIT at the beginning of each source
 *  file. */
class GCINIT {
public:
    GCINIT() {
        if (!initialized) 
            GC_init();
        initialized = true;
    }
private:
    static bool initialized;
};

/** Print an error message in standard Unix format:
 *      <filename>:<linenum>: <message>
 *  where <filename> and <linenum> denote the file and line number
 *  containing source location LOC, and <message> is composed from
 *  FORMAT and the trailing arguments as
 *  for the printf family. */
extern void error (const char* loc, const char* format, ...);
/** Print an error message (without file or line number indications)
 *  composed from FORMAT and the trailing arguments as for the printf
 *  family. */
extern void error_no_file (const char* format, ...);

/* Defined by Horn framework. */
extern gcstring yyprinted_location (const char* loc);

extern void parse (FILE*, const gcstring&);

extern bool debugParser;

#endif

