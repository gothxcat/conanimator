# conanimator

*Codename "Keith"*

A terminal-based 2D text animator built on C++


## Build
### Dependencies
- GNU toolchain (>=C++11)
- ncurses

### Building
`./configure && make`


## Running

`./conanimator`


## Debug
### Dependencies
- gdb

### Debugging
`make && gdb ./conanimator`


## Post-build Installation / Uninstallation

`sudo make install`

`sudo make uninstall`


## Deployment

- Build source tarball
    - `make dist`


### Feature Roadmap

- ~~Functional GNU build structure and Hello World~~ &#10003;
- ~~Object-oriented ncurses display initialisation and deinitialisation~~ &#10003;
    - ~~Basic input handling~~ &#10003;
- ~~Dynamic string reveal animations~~ &#10003;
- Printing single screen hard-coded text images &#9744;
- Reading and displaying text images from files &#9744;
- Color text support &#9744;
- Multi-frame text graphics displayed in sequence &#9744;
- Optimisation &#9744;
