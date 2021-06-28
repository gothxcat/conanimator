codesrc = ./src
libdir = ./lib

bin_PROGRAMS = conanimator
conanimator_SOURCES = $(codesrc)/main.cpp

AM_CXXFLAGS = -lncurses -pthread \
-I$(codesrc)/include \
-I$(libdir)/argparse/include -I$(libdir)/cjson
