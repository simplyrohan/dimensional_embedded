setup:
	@echo "\033[32m[START] Installing MiniFB\033[0m"
	git clone "https://github.com/emoon/minifb" && echo "\033[32m[DONE] Cloned MiniFB\033[0m" && cd minifb && mkdir build && cd build && echo "\033[32m[START] Building MiniFB\033[0m" && cmake .. -DUSE_METAL_API=ON && make -j8
	@echo "\033[32m[DONE] Installed MiniFB\033[0m"
	@echo "\033[32m[DONE] Finished![0m"