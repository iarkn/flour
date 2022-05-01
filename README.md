# flour

Moving square block in terminal thing.

## Building

### Prerequisites

- GNU Make
- GCC or any C17 compiler that works
- ncursesw (>= 6.3)
- zlib (>= 1.2.11)

Older versions of ncurses-wide will probably work. For Debian-based
distributions, do the following to install the prerequisites:

    # apt install gcc make pkg-config libncurses-dev zlib1g-dev

Then, get the source code and build the project:

    $ git clone https://github.com/iarkn/flour.git && cd flour
    $ make

The build output is in the `build/` directory. To run the program, execute
`./build/flour`.

## License

GPL-3.0-or-later
