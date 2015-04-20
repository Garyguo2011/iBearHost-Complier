/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* apyc2.cc: Driver for compiler phase 2 of apyc. */

/* Authors:  P. N. Hilfinger */


#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdarg>
#include "apyc.h"

using namespace std;

bool GCINIT::initialized = false;
static GCINIT _gcdummy;

static int errCount;

void
fatal (const gcstring& message)
{
    fprintf (stderr, "fatal error: %s\n", message.c_str ());
    exit (2);
}

void verror (const char* loc, const char* format, va_list ap)
{
    fprintf (stderr, "%s: ", loc);
    vfprintf (stderr, format, ap);
    fprintf (stderr, "\n");
    errCount += 1;
}

void
error (const char* loc, const char* format, ...)
{
    va_list ap;
    va_start (ap, format);
    verror (loc, format, ap);
    va_end (ap);
}

void
error (AST_Ptr node, const char* format, ...)
{
    va_list ap;
    va_start (ap, format);
    verror (node->loc (), format, ap);
    va_end (ap);
}

void
errorNoFile (const char* format, ...) 
{
    va_list ap;
    va_start (ap, format);
    vfprintf (stderr, format, ap);
    va_end (ap);
    fprintf (stderr, "\n");
    errCount += 1;
}

int
numErrors ()
{
    return errCount;
}

static void
Usage ()
{
    fprintf (stderr, "\
Usage: apyc3 [ -o OUTFILE.cc ] PROG.py PROG-DAST\n\
    Do code generation on PROG-DAST (Decorated AST from the user's\n\
    source program), producing C++ output in OUTFILE (default standard\n\
    output). The file name PROG.py is used for error messages.\n");
    exit (1);
}

static void
phase3 (const gcstring& progSrc, const gcstring& progDastFile,
        const gcstring& ccOutFile)
{
    AST_Ptr tree = readDast (progDastFile, progSrc);

    if (ccOutFile.size () > 0 &&
        freopen (ccOutFile.c_str (), "w", stdout) == NULL) {
        perror (ccOutFile.c_str ());
	errorNoFile ("Could not output file.");
	return;
    }

    tree->codeGen ();
}
 
int
main (int argc, char* argv[])
{
    int i;
    char* outfile;
    outfile = NULL;
    for (i = 1; i < argc; i += 1) {
	string opt = argv[i];
	if (opt == "-o" && i < argc-1) {
	    outfile = argv[i+1];
	    i += 1;
	} else if (opt.size () == 0 || opt[0] == '-') {
	    Usage();
	} else {
	    break;
        }
    }
    if (i + 2 != argc)
	Usage ();
    errCount = 0;
    gcstring progSrc = argv[i];
    gcstring progDastFile = argv[i+1];

    gcstring ccOutFile;
    if (outfile == NULL) {
        gcstring ccOutFile = progSrc;
        size_t k = ccOutFile.rfind('.');
        if (k != string::npos) {
            ccOutFile.erase(k);
        }
        ccOutFile += ".cc";
    } else {
        ccOutFile = outfile;
    }

    phase3(progSrc, progDastFile, ccOutFile);

    exit (numErrors () == 0 ? 0 : 1);
}

/* Debugging routines.  These are never called in the skeleton.  They
 * are intended to be called from GDB, as in 
 *     (gdb) call DB(aTree)
 */

void
DB(const AST_Ptr& x)
{
    AST::dump(x, cerr);
    cerr << endl;
}

void
DB(const Type_Ptr& x)
{
    AST::dump(x, cerr);
    cerr << endl;
}

void
DB(AST* x)
{
    AST::dump(x, cerr);
    cerr << endl;
}

void
DB(Type* x)
{
    if (x == NULL)
        cerr << "(null)";
    else
        x->print (cerr, 0);
    cerr << endl;
}

void
DB(Decl* d)
{
    d->print(cerr);
}
    
