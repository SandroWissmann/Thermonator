# Thermonator

## About

The goal of this repo is write a program to control eq3 radiator thermostats from remote.

The reason I came up with this is because the software for the thermostats is rather limited, it only allows modifications from a phone which needs to be close to the thermostat. 

It would be much more nice to be able to connect to a local server, also to manipulate the heating when not in the house. 

Also the software from the manufacturer allows only one profile per weekday. It would be much nicer to be able to have several profiles and be able to easy swap them with a click. 

## Feature goals

I planned to implement this step by step. The key things to implement: 
- [x] Connect to one fixed thermostat
- [ ] Implement all commands for manipulating thermostats and receive statuses (No Gui yet:
  - [x] Read current status.
  - [x] Set mode (auto, manual, vacation).
  - [x] Switch to comfort temperature.
  - [x] Switch to eco temperature.
  - [x] Set target temperature.
  - [x] Enable / disable thermostat.
  - [x] Enable / disable boost.
  - [x] Read / Write profile for a day.
  - [x] Set comfort temperature.
  - [x] Set eco temperature.
  - [x] Set window mode (interval and temperature)
  - [x] Set offset temperature
  - [x] Lock / unlock thermostat
  - [ ] Factory reset
- [ ] Implement basic gui for:
  - [ ] Scan for available thermostats.
  - [ ] Connect to thermostats.
  - [ ] Send commands and receive statuses to thermostats.
- [ ] Make this basic program work on a Raspberry Pi.
- [ ] Implement advanced management for thermostats:
  - [ ] Possibility to save thermostat settings in a persistent file
  - [ ] Define rooms in the gui
  - [ ] Save thermostats with settings per room
  - [ ] Save a heating program for each day of the week.
  - [ ] Save several profiles per day. e.g (work day, vacation day, out of house day)
  - [ ] Add a calendar to manage for each day of the year which profile for heating should be used.
- [ ] If one Raspberry Pi has not enough range it would be cool to have a second smaller Raspberry Pi which works as a node to extend the range to of the bluetooth. 

## Technologies and tools used
* C++20
* Qt 5.15 (Might be ported to Qt 6 during development)
* QML

## Development Environment

* X64 Manjaro (Later will be ported to Raspberry Pi)

## Hardware 
* Eqiva Bluetooth® Smart Heizkörperthermostat, 141771E0. Model N. See [here](https://www.amazon.de/gp/product/B01N39V0I4/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&th=1)