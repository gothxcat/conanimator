# Project globals
codesrc = ./src
libdir = ./lib
completiondir = ./completions

if USEZSH
USEZSH = 1
endif

zsh_comp_script = $(completiondir)/conanimator.zsh
zsh_comp_dir = /usr/share/zsh/site-functions
zsh_comp_dest = $(zsh_comp_dir)/_conanimator
zsh_reload = $(completiondir)/reload.zsh

# Program initialisation, entrypoint, libraries and all sources
bin_PROGRAMS = conanimator
conanimator_SOURCES = $(codesrc)/main.cpp $(codesrc)/* $(libdir)/*

# Compiler flags such as for libraries and includes
AM_CXXFLAGS = -lncurses -pthread \
-I$(codesrc)/include \
-I$(libdir)/argparse/include -I$(libdir)/cjson

# Rule extensions
#   https://www.gnu.org/software/automake/manual/html_node/Extending.html
install-data-hook:
	mkdir -p $(zsh_comp_dir) && \
	cp $(zsh_comp_script) $(zsh_comp_dest) && \
	if [ -z "$(USEZSH)" ]; then \
		zsh $(zsh_reload); \
	fi

uninstall-hook:
	rm -f $(zsh_comp_dest)