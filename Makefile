setup-desktop:
	@echo "\033[32m[START] Installing MiniFB\033[0m"
	git clone "https://github.com/emoon/minifb" && echo "\033[32m[DONE] Cloned MiniFB\033[0m" && cd minifb && mkdir build && cd build && echo "\033[32m[START] Building MiniFB\033[0m" && cmake .. -DUSE_METAL_API=ON && make -j8
	@echo "\033[32m[DONE] Installed MiniFB\033[0m"
	@echo "\033[32m[DONE] Finished![0m"

build-desktop:
	g++ -std=c++14 main.cpp -Iminifb/include -Lminifb/build -lminifb -framework Cocoa -framework MetalKit -framework Metal -o main

dev-desktop:
	g++ -std=c++14 main.cpp -Iminifb/include -Lminifb/build -lminifb -framework Cocoa -framework MetalKit -framework Metal -o main && ./main

setup-arduino:
	cp -r renderer/ ./

build-arduino:
	@echo "\033[32mUse the either the Arduino IDE or arduino-cli to build and upload the project\033[0m"