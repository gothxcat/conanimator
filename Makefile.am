codesrc = ./src
libdir = ./lib

bin_PROGRAMS = conanimator
conanimator_SOURCES = $(codesrc)/main.cpp $(codesrc)/* $(libdir)/*

AM_CXXFLAGS = -lncurses -pthread \
-I$(codesrc)/include \
-I$(libdir)/argparse/include -I$(libdir)/cjson
