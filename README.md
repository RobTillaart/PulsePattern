# PulsePattern

Arduino Library to generate repeating pulse patterns **AVR ONLY**

# Description

This is an **experimental** library to generate pulse patterns by means of an Arduino UNO.
As the library uses **AVR hardware timers** it is definitely **NOT** working for ESP
or other non-AVR processors.

The library uses timer1 for the timing of the pulses.
Therefor the class is implemented with a static instance called PPO.
Still by calling init() one can change all parameters of the process.
One should note that calling init() forces the timer to stop.

The timer code is based upon the website of Nick Gammon which
holds quite a lot of good solid material (Thanks Nick!).
https://gammon.com.au/forum/bbshowpost.php?bbtopic_id=123

Use with care.

### Interface

- **PulsePattern()** constructor
- **init(pin, \*ar, size, level, prescaler)** initializer of the Timer1
* pin that outputs the pattern
* array of durations
* size of the array
* starting level HIGH/LOW
* prescaler, one of the 5 defines from .h file
- **stop()** stop the pattern generator
- **start()** start the pattern generator
- **cont()** continue the pattern generator from the last stopped place (approx).
- **isRunning()** status indicator
- **worker()** must be public otherwise the ISR cannot call it.
There is some bad understood __vector_11() error when worker() is private.

# Operation

See example
