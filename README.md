# fluffy-dashboard

OBD2 scanner library in C++ & Qt5 for Linux

## Table of contents

- [fluffy-dashboard](#fluffy-dashboard)
  - [Table of contents](#table-of-contents)
  - [General info](#general-info)
  - [Status](#status)
  - [Features](#features)
  - [Build with](#build-with)
  - [Contact](#contact)

## General info

This project is a rewrite of my engineering thesis of car diagnostic platform.
It consist of OBD2 library designed to be used with  bluetooth and usb ELM327 scanners support.  
There are also planned 2 apps making use of said library.  
**Scanner app** which will have basic OBD2 scanner functionalities with GUI made with touch controls in mind.  
**Dashboard app** allowing for user configurable interface showing live vehicle parameters.

## Status

Project is: *in progress*

## Features

List of planned features:

- Reading current and freeze frame vehicle parameters
- Reading stored, pending and permanent DTCs
- Clearing stored DTCs
- Reading vehicle information (VIN etc)
- Support for obd2 services 1, 2, 3, 4, 5, 7, 9, A
- Recording and viewing vehicle parameters
- Localization for multiple languages

## Build with

- C++17 (20 ready)
- ClangTidy, ClangFormat
- CMake
- GTest, GMock
- Qt 5
- Linux based serial communication (termios.h)

## Contact

Email:  <mateusz.siedlecki@protonmail.com>
