# POV motor
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->

## DC geared
eventually this could work?! [26:1 Sub-Micro Planetengetriebemotor 6Dx16L mm @ 6V: 2500 rpm](https://www.exp-tech.de/motoren/dc-getriebemotoren/7078/26-1-sub-micro-planetengetriebemotor-6dx16l-mm?c=1198)


## Brushless DC motor (BLDC)
- [faulhaber Brushless Flat DC-Micromotors Series 1509...B; Diameter 15 mm, Length 8.8 mm](https://www.faulhaber.com/en/products/series/1509b/)
- [slotless brushless DC minimotor 16BHS 2A E .01 (D16 x L33)](http://www.portescap.de/Produkte/b%C3%BCrstenloser-DC-Motor/16bhs-2-wire-Nutenloser-b%C3%BCrstenloser-DC-Minimotor)
- [21BF nuvoDisc 21BF 3C K .02 (D21 x L11)](http://www.portescap.de/Produkte/B%C3%BCrstenlose%20DC-Motoren-DC-Motor/21BFnuvoDisc)
- [EC 45 flat Ø42.8 mm, brushless, 12 Watt, with Hall sensors (~70€)](https://www.maxonmotor.com/maxon/view/product/motor/ecmotor/ecflat/ecflat45/200188)
- extract motor from Harddisk
- [24V 4000RPM 0.0625Nm 26W 1.8A 42x42x40mm Brushless DC Motor](https://www.omc-stepperonline.com/24v-4000rpm-00625nm-26w-18a-42x42x40mm-brushless-dc-motor-42bls40-24-01.html?search=4000rpm)
- [B4240-12 HighSpeed 4000rpm](https://www.transmotec.com/product/b4240-12/)

### with hollow shaft
- [ST4118M1804-L —  Stepper Motor with Hollow Shaft - NEMA 17 (42mm)](https://en.nanotec.com/products/1271-st4118m1804-l/)
- [NEMA 17 42mm High Speed Brushless DC Motor](http://gemsmotor.com/nema-17-square-brushless-dc-motor)
- [import Kundenspezifische Hohlwellen Motoren](http://www.lionpower.ch/import-motoren/hohlwellen-motor/index.html)

## links
- [Closed Loop Speed Control of Miniature Brushless DC Motors (PDF)](http://www.joace.org/uploadfile/2014/1008/20141008114946575.pdf)
- [YouTube slow running BLDC](https://www.youtube.com/watch?v=hLeS3XZbM8A&lc=Ugiec3EFy34h4ngCoAEC)
- [Start your BLDC journey with motor startup (Part III): Initial position detection (IPD)](https://e2e.ti.com/blogs_/b/motordrivecontrol/archive/2015/02/19/start-your-bldc-journey-with-motor-startup-part-iii-initial-position-detection-ipd)
- [TI InstaSPIN™ Motor Control Solutions - Zero & Slow Speed](http://www.ti.com/ww/en/mcu/instaspin/instaspin-zero-and-slow-speed.shtml)

## motordriver
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
- [odrive](https://discourse.odriverobotics.com/)





## ToDo:
- find usable / working BLDC open and free code that can control BLDC motors in position control and slow and fast and slow in both directions
- find driver & controller uC for this (preferred arduino compatible)
- find suitable small motor
