# Airbag 
This repository has the files used in Make: Inventions Episode 3 | Airbags.

## At Your Own Risk
The goal of this project was to get from zero to a working prototype as quickly as possible. It was not to produce beautiful code or circuits. 

If used as intended this project also detonates explosive charges on command  — or when a sensor tells it to, which can be somewhat random. **Use of this project is at your own risk.** And at the risk of anyone near you.

## Project Notes
The circuit and code make a thing crudely similar to that of an airbag system.  It sends a voltage through a wire when an accelerometer goes above a set value. In the final project that wire includes and igniter made from 1cm of 40 gauge nichrome wire. When the circuit it powered by a trio of 9V batteries, that wire will reach melting temperature in about 0.025 second. If you remove the accelerometer you can trigger the igniter with a manual button. From a safe distance.

### Features
**Status lights** make it easy to see what's going on at a safe distance.

- Green light: Powered up.
- Orange light: The charge is armed.
- Red light: The igniter has been triggered. The igniter will not trigger more than once from the accelerometer. (Though you can trigger it more times if you connect a manual trigger.)
	
**Arming switch.** With the switch in the off position the igniter is physically disconnected from the rest of the circuit and safe from accidental ignition. (Well, safe from accidentally being ignited from this circuit anyway. Your'e on your own for the rest.)

**Manual trigger**. Optionally connect a manual trigger for testing.

**G-Force reporting**. Press and hold the "report" button for 1 second and the three status lights will report the maximum G-force reading since it was turned on/reset. Green blinks the hundreds, Orange blinks the tens, Red blinks the singles. All lights blinking 3 times quickly = zero. (Example: Orange, Orange Orange, Green = 31)

## Parts List:
This circuit is quick and dirty and I'm not an electrical engineer. Don't assume any of the parts or values are the most appropriate.

- Arduino Uno/Mini
- ADXL193 single axis 250g accelerometer on a Sparkfun breakout board.
- Red LED 10mm diffused 
- Orange LED 10mm diffused 
- Green LED 10mm diffused 
- DPST Toggle switch.
- Tactile switch.
- N channel MOSFET FQP30N06L (60V 30A)
- (4) 10K Ω 1/4 watt resistors
- (3) 220Ω 1/4 watt resistors
- 5v regulator KA78M05 + heatsink (A common 7805 will work if you don't use too much current.)
- (2) 100µF 25V electrolytic capacitor.
- 0.1µF ceramic capacitor.
- (3) two-connector screw terminals
- Various bits of wire, perfobard, etc, etc.

You might want to add a power switch. I just disconnected the batteries.

## License
All text — not including source code — and the schematic are licensed under the [Creative Commons Attribution 3.0 Unported License.](http://creativecommons.org/licenses/by/3.0/deed.en_US). 

Under this license you can:

- Share — to copy, distribute and transmit the work
- Remix — to adapt the work
- make commercial use of the work

All source code is licensed under the [MIT license](http://opensource.org/licenses/MIT).

	The MIT License (MIT)
	
	Copyright (c) 2013 Steve Hoefer
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE. 