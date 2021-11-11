# fluffy-dashboard
OBD2 scanner in C++ & Qt for Linux
## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Features](#features)
* [Status](#status)

## General info
This program is a *in progress* remake of my engineering thesis of car diagnostic platform.
It is a basic OBD2 scanner designed to be used with ELM327 bluetooth scanners and optimised for touch screen controls. 
## Technologies
Project is created using:
* C++ 
* Google test
* Linux based (<termios.h>)
* Qt 5	
## Features
List of planned features:
* Reading current and freeze frame vehicle parameters
* Reading and clearing DTC
* Reading vehicle information (VIN etc)
* Support for obd2 services 1, 2, 3, 4, 5, 7, 9, A
* Recording and viewing vehicle parameters
* Localization for multiple launguages
* Two client apps with shared core
  * Dashboard
  * Classic obd2 scanner app

`At the moment more details are available on dev branch in documentation folder.`
## Status
Project is: _in progress_
