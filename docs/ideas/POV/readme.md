# POV
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
<!--lint disable code-block-style-->

the idea is that the compass needle can rotate slow in both directions to *set* / *point* a direction of choice.

but also can spin up to about 1800rpm (= 30rps) and have LEDs to create a classic POV display.

on every half of the needle are 12..20 LEDs (APA102-2020 or Nichia NSSM124D with TLC5971 or something similar)
so we have a 12..20-Pixel high circle-screen.

![pov concept overview](pov_concept_overview.svg)

some first simple tests are documented at [POV_simpletest](../../POV_simpletest)

---
# Contents
{:.no_toc}

* Will be replaced with the ToC, excluding the "Contents" header
{:toc}
---

## basic calculations

### 130mm Needle, 3mm Pixel Pitch

| name                                       | value     | value                                            | formula                                               |
| :----------------------------------------- | --------: | -----------------------------------------------: | ----------------------------------------------------: |
| updates_per_second = revolution_per_second | 30        | <label class="unit rpm"><input type="number" value="30" step="1" min="0" max="120"/></label> |           |
| rpm (revolution per minute)                | 1800      | <span class="">1800</span>                       | updates_per_second * 60                               |
| pixel_pitch                                | 3mm       | <label class="unit millimeter"><input type="number" value="3" step="0.1" min="0" max="20" /></label> |   |
| needle_diameter                            | 130mm     | <label class="unit millimeter"><input type="number" value="130" step="1" min="0" max="500" /></label> |  |
| needle_active_radius                       | 60mm      | <span class="unit millimeter">60</span>          | (needle_diameter - 10) / 2                            |
| pixel_count_one_side                       | 20        | <span class=""></span>                           | toFixed(needle_active_radius / pixel_pitch; 0)        |
| pixel_count_total                          | 40        | <label class=""><input type="number" value="40" step="1" min="0" max="1000" /></label> | pixel_count_one_side * 2 |
| pixel_circumference                        | 408mm     | <span class="unit millimeter"></span>            | toFixed(π * needle_diameter; 1)                       |
| pixel_circ_vcount                          | 136       | <label class=""><input type="number" value="136" step="1" min="0" max="1440" /></label> | toFixed(pixel_circumference / pixel_pitch) |
| pixel_updates_per_revolution               | 136       | <span class=""></span>                           | pixel_circ_vcount                                     |
| pixel_updates_per_second                   | 4080      | <span class=""></span>                           | updates_per_second * pixel_updates_per_revolution     |
| pixel_updates_per_minute                   | 244800    | <span class=""></span>                           | rpm * pixel_updates_per_revolution                    |
| duration_per_revolution                    | 33ms      | <span class="unit milliseconds"></span>          | toFixed(1000 / updates_per_second; 1)                 |
| duration_per_pixel                         | 242us     | <span class="unit microseconds"></span>          | toFixed((duration_per_revolution / pixel_circ_vcount) * 1000; 0) |
| pixel_pwm_duration_for_8bit                | 945ns     | <span class="unit nanoseconds"></span>           | toFixed((duration_per_pixel * 1000) /   256; 0)       |
| pixel_pwm_rate_for_8bit                    | 1,06MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / pixel_pwm_duration_for_8bit ; 2)       |
| pixel_pwm_duration_for_10bit               | 236ns     | <span class="unit nanoseconds"></span>           | toFixed((duration_per_pixel * 1000) /  1024; 0)       |
| pixel_pwm_rate_for_10bit                   | 4,24MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / pixel_pwm_duration_for_10bit; 2)       |
| pixel_pwm_duration_for_12bit               |  59ns     | <span class="unit nanoseconds"></span>           | toFixed((duration_per_pixel * 1000) /  4096; 0)       |
| pixel_pwm_rate_for_12bit                   | 16,95MHz  | <span class="unit megahertz"></span>             | toFixed(1000 / pixel_pwm_duration_for_12bit; 2)       |
| pixel_pwm_duration_for_16bit               | 3,7ns     | <span class="unit nanoseconds"></span>           | toFixed((duration_per_pixel * 1000) / 65535; 2)       |
| pixel_pwm_rate_for_16bit                   | 270,27MHz | <span class="unit megahertz"></span>             | toFixed(1000 / pixel_pwm_duration_for_16bit; 2)       |

<button type="button" name="bt_update" id="bt_update">update</button>
<script src="{{ '/assets/js/table_calc_example.js?v=' | append: site.github.build_revision | relative_url }}" charset="utf-8"></script>



```
reminder / helper

1 s                  = 1Hz
1 000 ms             = 1Hz
1 000 000 us         = 1Hz
1 000 000 000 ns     = 1Hz
1 000 000 000 000 ps = 1Hz

1s  = 1Hz
1ms = 1kHz
1us = 1MHz
1ns = 1GHz
1ps = 1THz
```


## links
- [Baupläne rotierendes Display (inductive transfer for power and data )](https://www.mikrocontroller.net/topic/80808#675198)
- [POV Poi with Teensy (APA102)](https://forum.pjrc.com/threads/30020-Teensy-APA102-POV-Poi-Pixel-Poi-Build-Tutorial/page11)

## LEDs
- [APA102-2020]()

- [APA-102-2020-P5 STRIP](http://neon-world.com/en/product_detail.php?cid=94&id=230)
- [MicroNova LED Strip, 198 LEDs/meter (60564)](https://solarbotics.com/product/60564/)

## LED-Driver
- APA102 (build into led)
- [TLC5971]()

| t6 part                                         | data rate | pwm rate | channels | resolution | ch current | comment |
| :------------------------------------------- | :-------- | :------- | :------- | :--------- | :--------- | :------ |
| [APA102](https://cpldcpu.wordpress.com/2014/08/27/apa102/) | ~10 - 20MHz | 20kHz | 3 | 8Bit |  18mA      | simple to use - but no real datasheet values |
| [TLC5971](http://www.ti.com/product/TLC5971) | 20MHz     |  ?       | 12       | 16Bit      |  60mA      | internal oscillator, available libs |
| [TLC5947](http://www.ti.com/product/TLC5947) | 15MHz     |  4MHz    | 24       | 12Bit      |  30mA      | internal oscillator |
| [TLC5930](http://www.ti.com/product/TLC5930) | 20MHz     | 10MHz/20MHz | 12       | 10Bit      |  30mA      | internal oscillator |
| [TLC5943](http://www.ti.com/product/TLC5943) | 30MHz     | 33MHz    | 16       | 16Bit      |  50mA      | schnick-schnack-systems is using these. needs external GS clock |


## infrared data transmission
[look at pov_datatransmission.md](pov_datatransmission.md)

## power transmission
[look at pov_powertransmission.md](pov_powertransmission.md)

## motor
[look at pov_motor.md](pov_motor.md)

## 3D
- [more research & brainstorming at POV_3D/](POV_3D/readme.md)
