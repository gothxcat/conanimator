# Project globals
codesrc = ./src
libdir = ./lib

# zsh_comp_destdir = /usr/share/zsh/site-functions
# zsh_comp_script = completions/conanimator.zsh

# Program initialisation, entrypoint, libraries and all sources
bin_PROGRAMS = conanimator
conanimator_SOURCES = $(codesrc)/main.cpp $(codesrc)/* $(libdir)/*

# Compiler flags such as for libraries and includes
AM_CXXFLAGS = -lncurses -pthread \
-I$(codesrc)/include \
-I$(libdir)/argparse/include -I$(libdir)/cjson

# install-data-local:
#     @if test -d $(zsh_comp_destdir); then \
#         cp $(zsh_comp_script) $(zsh_comp_destdir)/_conanimator