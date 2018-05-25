# POV simpletest
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->

simple test to get a first *feeling* about something POV related ;-)

![Test Setup design front view](POV_testsetup__frontview.png)
![Test Setup design top view](POV_testsetup__topview.png)

---
# Contents
{:.no_toc}

* Will be replaced with the ToC, excluding the "Contents" header
{:toc}
---

## HW

- Arduino Micro for Motor Speed Controller
- Pololu A-Star as POV Controller
- LEDBoard_4x4_16bit for output

## Software

### SW_motordriver_wTacho
based on [Leonardo_wLCD_protobase](https://github.com/s-light/Leonardo_wLCD_protobase)

added IRLZ34N N-Channel Logic Level Power Mosfet and HP-Shotky Diode for driving the Motor.

will add some sort of Feedback to measure actual speed.

### SW_simple_pov_TLC5971
TODO  :-)

shoud be able to generate some very simple test-patterns for POV.
