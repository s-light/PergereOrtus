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

### use coils

- [technology overview (TI)](https://www.wirelesspowerconsortium.com/technology/why-not-a-wire-the-case-for-wireless-power.html)
- [more background info: Wireless Electricity Transmission](https://www.wirelesspowerconsortium.com/technology/how-it-works.html)

- [POV Display With Wireless Power!](http://www.instructables.com/id/POV-Display-With-Wireless-Power/)
- [Arduino Wireless Power POV Display](http://www.instructables.com/id/Arduino-Wireless-Power-POV-Display/)
- [rotating air transformer](http://www.oocities.org/tjacodesign/propclock/propclock.html)
- [PCB-Winding - Version 4 (August 2014)](http://electronixandmore.com/projects/propclock/index.html)
- [3D POV Display with 10W wireless power](http://www.instructables.com/id/PropHelix-3D-POV-Display/)
    - [wireless module](https://www.banggood.com/12V-Wireless-Charger-Module-5V-Power-Supply-Charging-Coil-Transmitter-Receiver-For-Phone-p-1122411.html?rmmds=myorder)

#### Phone wireless charging technology
- receiver
    - [bq51013b	WPC 1.1 Compatible Fully Integrated Wireless Power Receiver IC (20VQFN)](http://www.ti.com/product/bq51013b)
    - [bq51050b	Qi (WPC) Compliant Highly Integrated Secondary-Side Direct Lithium Ion Charger (20VQFN)](http://www.ti.com/product/bq51050b)
- transmitter
    - [bq500212a	(NRND) Qi Compliant 5V Wireless Power Transmitter Manager](www.ti.com/product/bq500212a)
    - [5W WPC (Qi) Compliant Wireless Power Transmitter for 5V Applications Reference Design (bq500212A)](http://www.ti.com/tool/tida-00259)
    - [Small 5W Wireless Power Transmitter Reference Design (bq500511 & bq50002)](http://www.ti.com/tool/tida-00623)

- würth electronic
    - [WE-WPCC Wireless Power Transfer Transmitter Spule](http://katalog.we-online.de/de/pbs/WE-WPCC-TRANSMITTER?sid=e05308da79)
    - [high power designs industrial](http://www.we-online.de/web/de/electronic_components/produkte_pb/application_notes/anp032.php)
    - [reference design / kits](http://www.we-online.de/web/de/electronic_components/produkte_pb/demoboards/wireless_power/referencedesigns/referencedesigns.php)


- [Qi-Universalempfänger: Micro-USB “unten”](http://inbay.systems/de/qi-handyzubehoer/)
- [Inbay® Universal Lüftungshalter mit induktiver Ladefunktion](http://inbay.systems/de/inbay-universal-lueftungshalter-2/)
- [acv ist Spezialist für Wireless Charging](https://www.acvgmbh.de/produkte/induktive-lademoeglichkeiten/)

- [modules uway-qi](http://www.uway-qi.com/e/Products/qi_modules/index.html)
    - [Qi RX Receiver Module Model NO: UNIQT-0108 (15W)](http://www.uway-qi.com/e/Products/qi_modules/p32.html)
    - [(SEMICO) Qi 5W Wireless Charging TX Module A11/5V (WPC 1.2.1 certified) (Round Type) Model NO: UNIQT-0004 (1W)](http://www.uway-qi.com/e/Products/qi_modules/p39.html)
    - [Qi 15W Medium power wireless charging TX module Model NO: UNIQT-0014 (15W)](http://www.uway-qi.com/e/Products/qi_modules/p31.html)
    - [Fast-Charge Qi 10W Wireless Charging TX Module Model NO: SAMQT-0011 (10W)](http://www.uway-qi.com/e/Products/qi_modules/p33.html)
    - [(SEMICO) Qi 5W Wireless Charging TX Module A11/5V (WPC 1.2.0 certified) (Square Type) (5W)](http://www.uway-qi.com/e/Products/qi_modules/p40.html)

- [Wireless Power Receiver - Futura Group Srl - 7100-FT1236M (9,9€)](https://store.open-electronics.org/FT1236M?search=ft123)
- [Wireless Power Trasmitter FT1235M - Futura Group Srl- 7100-FT1235M (19,70€)](https://store.open-electronics.org/FT1235M)

## motor

### DC geared
eventually this could work?! [26:1 Sub-Micro Planetengetriebemotor 6Dx16L mm @ 6V: 2500 rpm](https://www.exp-tech.de/motoren/dc-getriebemotoren/7078/26-1-sub-micro-planetengetriebemotor-6dx16l-mm?c=1198)


### Brushless DC motor (BLDC)
- [faulhaber Brushless Flat DC-Micromotors Series 1509...B; Diameter 15 mm, Length 8.8 mm](https://www.faulhaber.com/en/products/series/1509b/)
- [slotless brushless DC minimotor 16BHS 2A E .01 (D16 x L33)](http://www.portescap.de/Produkte/b%C3%BCrstenloser-DC-Motor/16bhs-2-wire-Nutenloser-b%C3%BCrstenloser-DC-Minimotor)
- [21BF nuvoDisc 21BF 3C K .02 (D21 x L11)](http://www.portescap.de/Produkte/B%C3%BCrstenlose%20DC-Motoren-DC-Motor/21BFnuvoDisc)
- [EC 45 flat Ø42.8 mm, brushless, 12 Watt, with Hall sensors (~70€)](https://www.maxonmotor.com/maxon/view/product/motor/ecmotor/ecflat/ecflat45/200188)
- extract motor from Harddisk

### links
- [Closed Loop Speed Control of Miniature Brushless DC Motors (PDF)](http://www.joace.org/uploadfile/2014/1008/20141008114946575.pdf)
- [YouTube slow running BLDC](https://www.youtube.com/watch?v=hLeS3XZbM8A&lc=Ugiec3EFy34h4ngCoAEC)
- [Start your BLDC journey with motor startup (Part III): Initial position detection (IPD)](https://e2e.ti.com/blogs_/b/motordrivecontrol/archive/2015/02/19/start-your-bldc-journey-with-motor-startup-part-iii-initial-position-detection-ipd)
- [TI InstaSPIN™ Motor Control Solutions - Zero & Slow Speed](http://www.ti.com/ww/en/mcu/instaspin/instaspin-zero-and-slow-speed.shtml)

### motordriver
- [Brushless Motor Controller Shield for Arduino](https://hackaday.com/2014/10/08/brushless-motor-controller-shield-for-arduino/)
    - [BLDC_ros_controller](https://github.com/Neuromancer2701/BLDC_ros_controller)
- [OpenBLDC - BLDC shield for arduino and stand alone controller](https://hackaday.io/project/1490-openbldc)
- [Brushless DC (BLDC) Motor Driver](https://www.tindie.com/products/manton/brushless-dc-bldc-motor-driver/)
- [Spinning BLDC(Gimbal) motors at super slooooooow speeds with Arduino and L6234](http://www.berryjam.eu/2015/04/driving-bldc-gimbals-at-super-slow-speeds-with-arduino/)
- [Driving A Brushless DC Motor Sloooooooowly](https://hackaday.com/2015/04/20/driving-a-brushless-dc-motor-sloooooooowly/)
- [Cd-Rom 3 phase sensored BLDC Motor Arduino Controller](https://elecnote.blogspot.de/2014/11/cd-rom-3-phase-sensored-bldc-motor.html)
- [Makeatronics BLDC Motor Control (May 4, 2014)](https://makeatronics.blogspot.de/2014/05/bldc-motor-control.html)
- [Adding Position Control To An Open Source Brushless Motor Driver](https://hackaday.com/2016/02/04/adding-position-control-to-an-open-source-brushless-motor-driver/)
- VSEC
    original designed by Benjamin Vedders  
    uses an ST 32bit chip with chibios
    - [OSHW version 4.10](https://github.com/vedderb/bldc-hardware)
    - [original blog post with descriptions (2016-01-22)](http://vedder.se/2015/01/vesc-open-source-esc/)
    - [VESC – Writing Custom Applications (2016-01-22)](http://vedder.se/2015/08/vesc-writing-custom-applications/)
    - [old forum](http://vedder.se/forums/index.php)
    - [new project website](https://vesc-project.com/)
        - [official VESC SIX schematics](https://vesc-project.com/sites/default/files/Benjamin%20Posts/VESC_6.pdf)
    - mini4  is VSEC6 compatible (by Anton Chromjak *antonchromjak*)
        - [old forum](http://vedder.se/forums/viewtopic.php?f=9&t=1513&start=40)
        - [new forum](https://vesc-project.com/node/246)
        - [github](https://github.com/antonchromjak/MINI4)
    - position control
        - absolute encoder sensor
            [AS5047D-ATSM 14bit 360° magnetic 7,6€](https://www.mouser.de/ProductDetail/ams/AS5047D-ATSM?qs=sGAEpiMZZMu5vlrqIFXt5Ue7EW8vOwUDtxpQ9na6EV0PpB5Gp9ffFw%3d%3d)
        - forum info:
            - how to setup position control:  
                [by Eric](https://vesc-project.com/comment/680#comment-680)
                > Position is not supported with hall, must have an encoder for that.
                >  If you have an encoder, in the Foc-general tab set sensor mode to ABI
                >  and then use the encoder detect function in the FOC-Encoder tab.
                >  The you must tune the position PID controller.
            - [Minimum speed](https://vesc-project.com/node/212)
            - [my question](https://vesc-project.com/node/321)






### ToDo:
- find usable / working BLDC open and free code that can control BLDC motors
in slow and fast and slow in both directions
- find driver & controller uC for this (preferred arduino compatible)
- find suitable small motor
