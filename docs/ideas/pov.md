<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
# POV

the idea is that the compass needle can rotate slow in both directions to *set* / *point* a direction of choice.

but also can spin up to about 1800rpm (= 30rps) and have LEDs to create a classic POV display.

on every half of the needle are 12 LEDs (APA102-2020 or Nichia NSSM124D with TLC5971 or something similar)
so we have a 12-Pixel high circle-screen.

## update-rate calculations

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
- [element14 community: DIY Slip Rings: 5 Go-To Guides That Detail How To Make A Slip Ring](https://www.element14.com/community/groups/power-management/blog/2016/09/12/diy-slip-rings-5-go-to-guides-that-detail-how-to-make-a-slip-ring)

## infrared data transmission
idea here is to have a IR led directly pulsing the raw data out and an receiver converting it back to signal..
so this could be transmitted over the rotation contact-less.
challenge here is the bit time - we need some very very fast photo detectors...

- [Photo Detectors - Phototransistor Output](https://www.vishay.com/photo-detectors/phototrans-out/)
- [Photo Detectors - Photodiode Output](https://www.vishay.com/photo-detectors/photodie-out/)
- [Photo Detectors - Surface Mount Devices](https://www.vishay.com/photo-detectors/surface-mount-devices/)

[Optical Sensors - Transmissive](https://www.vishay.com/optical-sensors/transmissive-sensors/)

## power transmission
power transmission should be possible with slip-rings.
as Jürgen pointed out in chat - if you get the diameter of the slide-ring smaller you get lower surface speed -
so less wear...

this is in contrast to the data ir transmission - as i need to get these wires or fibers through the shaft..
but i think i will find a good compromise..

TODO: source for small brushes?!
- use some small motors?!
- [exp-tech DC 130-Size, 6V, 11.5kRPM; 1,7€](https://www.exp-tech.de/motoren/dc-motoren/4858/dc-buerstenmotor-130-size-6v-11.5krpm-800ma-stall?c=1199)
- [exp-tech DC M260, 1V, 6.6kRPM; 2,0€](https://www.exp-tech.de/motoren/dc-motoren/5204/hobby-motor-gear?c=1199)

## motor

eventually this could work?! [26:1 Sub-Micro Planetengetriebemotor 6Dx16L mm @ 6V: 2500 rpm](https://www.exp-tech.de/motoren/dc-getriebemotoren/7078/26-1-sub-micro-planetengetriebemotor-6dx16l-mm?c=1198)
more likely with much better results:

use a Brushless DC motor (BLDC)


links:
- [Closed Loop Speed Control of Miniature Brushless DC Motors (PDF)](http://www.joace.org/uploadfile/2014/1008/20141008114946575.pdf)
- [youtube slow running BLDC](https://www.youtube.com/watch?v=hLeS3XZbM8A&lc=Ugiec3EFy34h4ngCoAEC)
- [Start your BLDC journey with motor startup (Part III): Initial position detection (IPD)](https://e2e.ti.com/blogs_/b/motordrivecontrol/archive/2015/02/19/start-your-bldc-journey-with-motor-startup-part-iii-initial-position-detection-ipd)
- [TI InstaSPIN™ Motor Control Solutions - Zero & Slow Speed](http://www.ti.com/ww/en/mcu/instaspin/instaspin-zero-and-slow-speed.shtml)
- [faulhaber Brushless Flat DC-Micromotors Series 1509...B; Diameter 15 mm, Length 8.8 mm](https://www.faulhaber.com/en/products/series/1509b/)
- [Nutenloser bürstenloser DC Minimotor 16BHS 2A E .01 (D16 x L33)](http://www.portescap.de/Produkte/b%C3%BCrstenloser-DC-Motor/16bhs-2-wire-Nutenloser-b%C3%BCrstenloser-DC-Minimotor)
- [21BF nuvoDisc 21BF 3C K .02 (D21 x L11)](http://www.portescap.de/Produkte/B%C3%BCrstenlose%20DC-Motoren-DC-Motor/21BFnuvoDisc)

motordriver
- [Brushless Motor Controller Shield for Arduino](https://hackaday.com/2014/10/08/brushless-motor-controller-shield-for-arduino/)
    - [](https://github.com/Neuromancer2701/BLDC_ros_controller)
- [OpenBLDC - BLDC shield for arduino and stand alone controller](https://hackaday.io/project/1490-openbldc)
- [Brushless DC (BLDC) Motor Driver](https://www.tindie.com/products/manton/brushless-dc-bldc-motor-driver/)
- [Spining BLDC(Gimbal) motors at super slooooooow speeds with Arduino and L6234](http://www.berryjam.eu/2015/04/driving-bldc-gimbals-at-super-slow-speeds-with-arduino/)
- [Driving A Brushless DC Motor Sloooooooowly](https://hackaday.com/2015/04/20/driving-a-brushless-dc-motor-sloooooooowly/)
- [Cd-Rom 3 phase Sensored BLDC Motor Arduino Controller ](https://elecnote.blogspot.de/2014/11/cd-rom-3-phase-sensored-bldc-motor.html)
- [Makeatronics BLDC Motor Control (May 4, 2014)](https://makeatronics.blogspot.de/2014/05/bldc-motor-control.html)
- [Adding Position Control To An Open Source Brushless Motor Driver](https://hackaday.com/2016/02/04/adding-position-control-to-an-open-source-brushless-motor-driver/)


ToDo:
- find usable / working BLDC open and free code that can control BLDC motors
in slow and fast and slow in both directions
- find driver & controller uC for this (preferred arduino compatible)
- find suitable small motor
    - [EC 45 flat Ø42.8 mm, brushless, 12 Watt, with Hall sensors (~70€)](https://www.maxonmotor.com/maxon/view/product/motor/ecmotor/ecflat/ecflat45/200188)
