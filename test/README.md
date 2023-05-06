# Winch Light Tests

These tests are designed to run using [EpoxyDuino](https://github.com/bxparks/EpoxyDuino).
They are also dependent on the [AUnit](https://github.com/bxparks/AUnit) library.

Both these libraries need to be installed in the `Ardunio/libraries/` directory. See the respective documentation for details.

You will need to export the `ARDUINO_LIBRARIES` environment variable to point to the `Arduino/libraries/` directory. For example, on MacOS: ~/Documents/Arduino/libraries

To run a test cd into the individual test folder, e.g. buttons, and run:

```
$ make clean
$ make
$ make run
```
