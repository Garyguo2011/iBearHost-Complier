# Top-level Makefile for Project 1.
# 
# Targets:
#   make [ default ]        Compiles sources in src directory
#   make check              Compiles sources and runs tests.  The parameter
#                            APYC indicates which compiler to run.
#   make clean              Removes unnecessary files, including those that
#                            are reproducible.
#   make depend	            Compute makefile dependencies and store
#                            in .depend.  Use this whenever you add a new
#                            source file or change an #include line.
#   make really-clean       Same as 'clean', also removes the file .depend.
#

ARCH := $(shell uname -m)
OS := $(shell uname)

ifndef LIBHOME
ifdef MASTERDIR
   LIBHOME := $(MASTERDIR)/pkg/$(ARCH)/horn2
else
   LIBHOME := $(HOME)/pkg/$(ARCH)/horn2
endif
endif

HORN = $(LIBHOME)/bin/horn

APYC = $(shell echo `pwd`/../apyc3)

CXXFLAGS = -g -Wall

INCLUDES = -I$(LIBHOME)/include

OTHER_LIBS =

LOADLIBS = -L$(LIBHOME)/lib -lgc $(OTHER_LIBS)

CXXFLAGS = -g -Wall -std=c++0x $(INCLUDES)

# List of normal C++ sources.  Add any new ones here
SRCS = apyc3.cc dast.cc decls.cc exprs.cc modules.cc \
       stmts.cc tokens.cc types.cc

# C++ top-level (i.e., as opposed to #included) sources that are generated
# by other rules in this Makefile.
GENERATED_SRCS = dast-parser.cc

# List of all C++ object files
OBJS = $(SRCS:.cc=.o) $(GENERATED_SRCS:.cc=.o)

# List of all C++ sources generated by tools
OTHER_SRCS = $(GENERATED_SRCS) \
	     dast-lexer.l dast-lexer.cc dast-lexer.hh \
             dast-parser.y dast-parser.hh

.PHONY: default compile check check1 check2 clean really-clean depend

default: compile

compile: ../apyc3

$(OTHER_SRCS): parser-sentinel
	@true

# The parser-sentinel file is a device that is used to group all the files
# generated by horn into one dependency.  Each time we generate these files, 
# we update the modify date on parser-sentinel.  The generated files in turn
# depend on parser-sentinel, and it depends on apyc.hn. So, whenever apyc.hn
# is changed, any compilation that depends on a generated file will cause 
# horn to rebuild the generated files (OTHER_SRCS).
parser-sentinel: dast.hn
	$(HORN) $<
	touch parser-sentinel

../apyc3: $(OBJS) 
	$(CXX) -g -o $@ $(OBJS) $(LOADLIBS)

check: 
	$(MAKE) -C .. APYC=$(APYC) check

clean:
	$(RM) *~ *.o *.pyc *.*ast  *.tab.c *.output 
	$(RM) $(OTHER_SRCS) parser-sentinel

really-clean: clean
	$(RM) .depend

# Dependencies

.depend:
	touch .depend
	$(MAKE) depend

depend: $(OTHER_SRCS)
	$(RM) .depend
	$(CXX) -MM -std=c++0x $(INCLUDES) $(OBJS:.o=.cc) > .depend \
             || { $(RM) .depend; false; }

-include .depend
