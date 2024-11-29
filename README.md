# dimensional_embedded
A rewrite of the "dimensional_graphics" project in C/C++

# Desktop Setup
To test this on a desktop enviroment, use [`MiniFB`](https://github.com/emoon/minifb). Just run 
```
make setup
``` 
to install it.

Then use
```
make build
```
To build with MiniFB

# Embedded Setup
To run this on an ESP32 (or any Arduino device really, but I haven't tested) make an Arduino project. Then copy the contents of the `renderer` directory into the project (Arduino is unable to find C++ files if they are in a sub directory). You can do this with
```
make setup-arduino
```

Look at `main.ino` for how to set it up with a TFT.
