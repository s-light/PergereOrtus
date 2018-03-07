<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
# POV

the idea is that the compass needle can rotate slow in both directions to *set* / *point* a direction of choice.

but also can spin up to about 1800rpm (= 30rps) and have LEDs to create a classic POV display.

on every half of the needle are 12 LEDs (APA102-2020 or Nichia NSSM124D with TLC5971 or something similar)
so we have a 12-Pixel high circle-screen.

## Update rate calculations

| name                                       | value   |
| :----------------------------------------- | :------ |
| pixel pitch                                | 3mm     |
| needle diameter                            | 80mm    |
| outer pixel circumference                  | 251mm   |
| outer pixel circumference virtual count    | 84      |
| pixel updates per revolution               | 84      |
| updates per second = revolution per second | 30      |
| revolution per minute (RPM)                | 1800    |
| pixel updates per second  (pixel-rate)     | 2520    |

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
- [slip-ring car alternator (to big)](https://www.lima-shop.de/en/product_info.php/info/p297_Slip-ring-univ--d-14-90mm-for-Valeo-Alternator.html)
- [slip-ring small but only 250rpm](http://www.slipring.com/miniature-slip-rings.html)
- [slip-ring small but only 250rpm](http://www.slipring.com/miniature-slip-rings.html)
- [exp / sparkfun - slip-ring 22mm 12x2A <250rpm](https://www.exp-tech.de/motoren/schleifring/8494/slip-ring-12-wire-2a)
- [exp / Adafruit - slip-ring 12mm 6x2A <250rpm](https://www.exp-tech.de/module/sonstige/5583/miniature-slip-ring-12mm-diameter-6-wires-max-240v-at-2a)
- [SRS022-12 - slip-ring 12x2A <3000rpm](http://slipring.com.cn/product_detaile.php?id=116)
- [LTN Servotechnik GmbH - schleifring](https://www.ltn-servotechnik.com/de/produkte/schleifringe/signaluebertragung/)
- [element14 community: DiY Slip Rings: 5 Go-To Guides That Detail How To Make A Slip Ring](https://www.element14.com/community/groups/power-management/blog/2016/09/12/diy-slip-rings-5-go-to-guides-that-detail-how-to-make-a-slip-ring)

## infrared data transmission

- [Photo Detectors - Phototransistor Output](https://www.vishay.com/photo-detectors/phototrans-out/)
- [Photo Detectors - Photodiode Output](https://www.vishay.com/photo-detectors/photodie-out/)
- [Photo Detectors - Surface Mount Devices](https://www.vishay.com/photo-detectors/surface-mount-devices/)

[Optical Sensors - Transmissive](https://www.vishay.com/optical-sensors/transmissive-sensors/)
