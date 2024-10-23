# Project Requirements

## Overview

This software is being tasked with communication with a car through external OBD2 scanner (e.g. ELM327 based) and allows for reading vehicle data, DTC, test results and clearing DTC. Software consist of two client apps: traditional obd scanner app, and a dashboard.

## Project Scope

Project consists of two apps using common library on Linux based systems.  
**Dashboard client** should be focused on presenting the current data (SIDs 01, 09) to the user, along with options for user customization of its interface.  
**Scanner app** will allow for wider use of OBD2 system and will allow for saving, and reading gathered data.  
Communication between obd scanner and a library will be based on RFCOMM Bluetooth protocol or wired standard (USB, serial).
Application should support multiple languages.

## User needs

Software should allow to easily present available obd data and present it to a user allowing for saving gathered data in a form of logs and graphs. Also allowing to read and clear DTCs.

### Potential users

* Car enthusiasts (on-board computer dashboard app)
* Car power users
* Car mechanics

### Features

* Reading and clearing DTC
* VIN verification
* Reading current vehicle parameters
* Reading freeze frame parameters
* Reading vehicle information

### Scope of OBD2 services

* 01 Show current data
* 02 Show freeze frame data
* 03 Show stored Diagnostic Trouble Codes
* 04 Clear Diagnostic Trouble Codes and stored values
* 05 Test results, oxygen sensor monitoring
* 06 *Not supported*
* 07 Show pending Diagnostic Trouble Codes
* 08 *Not supported*
* 09 Request vehicle information
* 0A Permanent Diagnostic Trouble Codes.

Detailed information about PIDs supported within these services will be specified later.

### Features Out

OBD services:

* 06 Test results, other component/system monitoring
* 08 Control operation of on-board component/system

are not supported due to:

* lack of information available to implement support for these services
* narrowing scope of project
* to avoid users misuse of service 08, which can potentially damage on-board components.
