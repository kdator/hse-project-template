all: init-boost

init-boost:
	git submodule add https://github.com/boostorg/boost.git external/boost
	git submodule update --init --recursive
