#compdef conanimator

_conanimator() {
    anims=(frames string)

    _anims() {
        _values 'built-in animation' $anims
    }

    _arguments \
        {-h,--help}'[shows help message and exits]' \
        {-v,--version}'[prints version information and exits]' \
        {-r,--run}'[run a built-in animation]:built-in animation:_anims' \
        {-f,--file}'[run an animation from a JSON file]:filename:_files'
}

_conanimator