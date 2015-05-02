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
static bool reportErrors;

void
fatal (const gcstring& message)
{
    fprintf (stderr, "fatal error: %s\n", message.c_str ());
    exit (2);
}

void verror (const char* loc, const char* format, va_list ap)
{
    if (reportErrors) {
        fprintf (stderr, "%s: ", loc);
        vfprintf (stderr, format, ap);
        fprintf (stderr, "\n");
    }
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
    if (node->errorReported ()) 
        errCount += 1;
    else {
        if (reportErrors)
            node->recordError ();
        va_list ap;
        va_start (ap, format);
        verror (node->loc (), format, ap);
        va_end (ap);
    }
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

int
setNumErrors (int num)
{
    int count0 = errCount;
    errCount = num;
    return count0;
}

bool
setErrorReporting (bool on)
{
    bool reportErrors0 = reportErrors;
    reportErrors = on;
    return reportErrors0;
}

static void
Usage ()
{
    fprintf (stderr, "\
Usage: apyc2 [ -o OUTFILE ] PRELUDE.py PRELUDE-AST PROG.py PROG-AST\n\
    Do semantic analysis on PRELUDE-AST (AST file from the standard\n\
    prelude) and PROG-AST (AST from the user's source program),\n\
    producing output in OUTFILE (default standard output).  The file\n\
    names PRELUDE.py and PROG.py are used for error messages.\n");
    exit (1);
}

static void
printTree (AST_Ptr tree, const gcstring& output)
{
    if (freopen (output.c_str (), "w", stdout) == NULL) {
	errorNoFile ("Could not open %s", output.c_str ());
	return;	
    }
    tree->print (cout, 0);
}

static void
phase2 (const gcstring& preludeSrc, const gcstring& preludeASTFile,
        const gcstring& progSrc, const gcstring& progASTFile,
        const gcstring& outASTFile)
{
    AST_Ptr preludeTree = readAst (preludeASTFile, preludeSrc);
    AST_Ptr tree = readAst (progASTFile, progSrc);

    tree = post1 (tree, preludeTree);

    tree = tree->doOuterSemantics ();

    tree = tree->replaceBindings ();
    replaceDeclBindings ();
    DeclSet usedDecls;
    tree->findUsedDecls (usedDecls);
    usedDecls.insert (mainModule);

    if (numErrors () == 0) {
        printTree (tree, outASTFile);
        outputDecls (cout, usedDecls);
    }
}
 
int
main (int argc, char* argv[])
{
    int i;
    char* outfile;
    outfile = NULL;
    setErrorReporting (true);
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
    if (i + 4 != argc)
	Usage ();
    errCount = 0;
    gcstring preludeSrc = argv[i];
    gcstring preludeASTFile = argv[i+1];
    gcstring progSrc = argv[i+2];
    gcstring progASTFile = argv[i+3];

    gcstring astOutFile;
    if (outfile == NULL) {
        astOutFile = progSrc;
        size_t k = astOutFile.rfind('.');
        if (k != string::npos) {
            astOutFile.erase(k);
        }
        astOutFile += ".dast";
    } else {
        astOutFile = outfile;
    }

    phase2(preludeSrc, preludeASTFile, progSrc, progASTFile, astOutFile);

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
    d->print(cerr, DeclSet());
}
    
