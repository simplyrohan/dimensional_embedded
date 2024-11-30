# dimensional_embedded
A rewrite of the [dimensional_graphics](https://github.com/simplyrohan/dimensional_graphics) project in C/C++ for embedded systems (ESP32 or Arduino)

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

# obj2h
A tool to convert Wavefront OBJ files into headers compatible with this project.

```
python obj2h.py path/to/model.obj
# TODO
(This is mainly a task list for myself)
 - Rename transformations (translation->position, consolidating things into a struct, vertex->vector3, etc)
 - Textures
 - Scene system 