# flour

Moving square block in terminal thing.

## Building

### Prerequisites

* c17 compiler
* meson
* ncursesw
* zlib

Installing the prerequisites on Debian unstable:

    # apt install gcc meson libncurses-dev zlib1g-dev

To build, run the following:

    $ meson setup build
    $ meson compile -C build

The build output should be in `build/flour` as an executable file.

## License

GPL-3.0-or-later
