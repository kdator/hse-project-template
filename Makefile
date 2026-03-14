init-third-party:
	git submodule update --init --recursive

build-image-processor:
	cmake -B build .
	cmake --build build

build-tests:
	cmake -B build -DWITH_TESTS=ON .
	cmake --build build
