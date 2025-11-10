# Digispark joystick to mouse

Using an dual-axis joystick as a mouse on a digispark USB.


## Components

- Arduino dual-axis joystick
- TINY85 Digispark board


## Wiring

- GND -> GND
- 5V -> 5VA
- SW (button) -> P0
- VRx -> P2
- VRy -> P5


## Warning

Pin P5 (the last one, physically counted as number 6, ADC0) may be configured as a reset pin.
You can fix that by following [that procedure](https://thetoivonen.blogspot.com/2015/12/fixing-pin-p5-or-6-on-digispark-clones.html).

## References

- [Digispark attiny85 mouse/joystick (diy mouse)](https://www.youtube.com/watch?v=djrLpPRj5b8)