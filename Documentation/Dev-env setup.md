# Fluffy dev-env setup

Instruction based on Ubuntu 22.04 LTS environment.
Compiler version GCC 11.4.0
Ubuntu LLVM version 14.0.0
gcovr 5.0

## obd-lib

Packages required:

`sudo apt-get install git cmake clang clang-format clang-tidy gcc-10 build-essential googletest libgtest-dev libgmock-dev qtbase5-dev libqt5bluetooth5 qtconnectivity5-dev`

## obd-scanner

Packages required:
`sudo apt-get install libqt5charts5-dev`

## CMake flags

Project can be configured through CMake flags found in `/Source/CMakeLists.txt`.
Following options compile options be changed there:

- Warnings
- Warnings as errors
- ClangTidy
- ClangFormat
- LLVM Sanitizers
- gcovr coverage

ClangFormat is recommended. It can be triggered by running `run_clang_format` build target.  
For running the ClangTidy run the selected `*_clangtidy` build target.
