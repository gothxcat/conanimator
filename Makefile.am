# Project globals
codesrc = ./src
libdir = ./lib

# Prog initialisation, entrypoint, libraries and all sources
bin_PROGRAMS = conanimator
conanimator_SOURCES = $(codesrc)/main.cpp $(codesrc)/* $(libdir)/*

# Compiler flags such as for libraries and includes
AM_CXXFLAGS = -lncurses -pthread \
-I$(codesrc)/include \
-I$(libdir)/argparse/include -I$(libdir)/cjson
