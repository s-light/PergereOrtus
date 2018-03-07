<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
# ortogere ideas & concepts



# touch(less) input
buildin / hidden in the top outer edge is a copper surface that acts as electrode.
it is split in 4 parts and managed with an [FDC1004](https://github.com/s-light/TI_FDC1004_Breakout) or similar

this allows for 'hand waving gestures'

# top input rim
## self build encoder
on underside of rim is a black/white pattern printed.  
(check that printing is really black for IR!!)
then read with two reflective ir sensor.
classical encoder gray-code pattern thing...
- [Overview: Optical Sensors - Reflective](https://www.vishay.com/optical-sensors/reflective-outputisnot-16/)
- [VCNT2020 2,5x2mm SMD package](https://www.vishay.com/optical-sensors/list/product-84285/)



# POV

the idea is that the compass needle can rotate slow in both directions to *set* / *point* a direction of choice.

but also can spin up to about 1800rpm (= 30rps) and have LEDs to create a classic POV display.

on every half of the needle are 12 LEDs (APA102-2020 or Nichia NSSM124D with TLC5971 or something similar)
so we have a 12-Pixel high circle-screen.

## Update rate calculations

| name                                    | value   |
| :-------------------------------------- | :------ |
| pixel pitch                             | 3mm     |
| needle diameter                         | 80mm    |
| outer pixel circumference               | 251mm   |
| outer pixel circumference virtual count | 84      |
| pixel updates per revolution            | 84      |
| updates per second (framerate = fps)    | 30      |
| pixel updates per second  (pixel-rate)  | 2520    |

| calculation step   | APA102                | TLC5971           |
| :----------------- | :-------------------- | :---------------- |
| bytes per update   | 102 (4 + 24*4 + 2)    | 168 (28 * 6)      |
| bits per update    | 816 (102*8)           | 1344              |
| bits per second    | 2056320 (816 * 2520)  | 3386880           |
| Kbit per second    | 2056                  | 3387              |
| Mbit per second    | 2,0                   | 3,4               |
| bit time           | 486 ns (= 0,48us)     | 295 ns (= 0,29us) |



## links
- [Baupläne rotierendes Display (inductive transfer for power and data )](https://www.mikrocontroller.net/topic/80808#675198)
- [Royer Converter](https://www.mikrocontroller.net/articles/Royer_Converter)
- [slip-rings with ball-bearings](http://web.archive.org/web/20101005013331/http://maybevideodoes.de/howto/slipring.html)
    - [images](http://web.archive.org/web/20101010045648/http://www.maybevideodoes.de:80/howto/newSlipring/index.html)

## infrared data transmission

- [Photo Detectors - Phototransistor Output](https://www.vishay.com/photo-detectors/phototrans-out/)
- [Photo Detectors - Photodiode Output](https://www.vishay.com/photo-detectors/photodie-out/)
- [Photo Detectors - Surface Mount Devices](https://www.vishay.com/photo-detectors/surface-mount-devices/)

[Optical Sensors - Transmissive](https://www.vishay.com/optical-sensors/transmissive-sensors/)
