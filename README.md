# conanimator
A terminal-based 2D text animator built on C++

## Project Initialisation
`git submodule init && git submodule update`

## Build
### Dependencies
- GNU toolchain (>=C++17)
- ncurses

### Building
`./configure && make`


## Running
- `./conanimator -h`
    - Display usage
- `./conanimator -r frames`
    - Run the example animation

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


## Development and Contribution
- See `STRUCTURE` for an outline of the project
- Code begins at `src/main.cpp`


### Feature Roadmap
- ~~Functional GNU build structure and Hello World~~ &#10003;
- ~~Object-oriented ncurses display initialisation and deinitialisation~~ &#10003;
    - ~~Basic input handling~~ &#10003;
- ~~Dynamic string reveal animations~~ &#10003;
- ~~Multi-frame text animations displayed in sequence~~ &#10003;
- ~~Universal framerate~~ &#10003;
- ~~Reading and displaying text images from files~~  &#10003;
- Scan user config directory for available animations &#9744;
- Text to JSON animation formatter &#9744;
- Color text support &#9744;
- Optimisation &#9744;
