# A SAT-based Mastermind solver

This repository features an implementation of [a SAT-based Mastermind solver](https://bohlender.pro/blog/playing-hard-mastermind-games-with-a-sat-based-ai/).

In contrast to the implementation from the blog post this one is tailored to be used in the backend of a website, so it
- uses C/C++ to enable transpilation to [WASM](https://webassembly.org/), and
- uses [kissat](https://github.com/arminbiere/kissat) instead of [Z3](https://github.com/Z3Prover/z3) to obtain a reasonably small binary (<300KB).

The [API](mastermind-solver-cpp/src/api.h) is minimal.
For example usage from C++ or JavaScript see [`api_test.cpp`](mastermind-solver-cpp/test/api_test.cpp) or [`api_test.mjs`](mastermind-solver-js/api_test.mjs) respectively.

## Build

### C/C++ library
If you're just here for the C/C++ library, i.e. you don't need WASM, run the following in the project root to build the non-WASM library in a dedicated `build` directory:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target mastermind
ctest
```

### WASM library
Building the NPM package works pretty much the same but relies on [Emscripten](https://emscripten.org/)'s `emcmake`.
So you have to either install Emscripten and run
```
mkdir build
cd build
emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target mastermind_npm
ctest
```
or simply run the following if you have [Docker](https://www.docker.com/) installed
```
docker run --rm \
  -v $(pwd):/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk:3.1.71 \
  bash -c "mkdir build && cd build && emcmake cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build . --target mastermind_npm && ctest"
```
