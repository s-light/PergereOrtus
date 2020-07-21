# POV
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
<!--lint disable code-block-style-->

the idea is that the compass needle can rotate slow in both directions to *set* / *point* a direction of choice.

but also can spin up to about 1800rpm (= 30rps) and have LEDs to create a classic POV display.

on every half of the needle are 12..20 LEDs (APA102-2020 or Nichia NSSM124D with TLC5971 or something similar)
so we have a 12..20-Pixel high circle-screen.

![pov concept overview](pov_concept_overview.svg)

some first simple tests are documented at [POV_simpletest](https://s-light.github.io/POV_simpletest/docs/)

---
# Contents
{:.no_toc}

* Will be replaced with the ToC, excluding the "Contents" header
{:toc}
---

## basic calculations

### 130mm Needle, 3mm Pixel Pitch

line = virtual pixel line on circumference (from inside to outside of circle)

| name                                       | test      | value                                            | formula                                               |
| :----------------------------------------- | --------: | -----------------------------------------------: | ----------------------------------------------------: |
| updates_per_second = revolution_per_second | 30        | <label class="unit rpm"><input type="number" value="30" step="1" min="0" max="120"/></label> |           |
| rpm (revolution per minute)                | 1800      | <span class="">1800</span>                       | updates_per_second * 60                               |
| pixel_pitch                                | 3mm       | <label class="unit millimeter"><input type="number" value="1.5" step="0.1" min="0" max="20" /></label> | |
| needle_diameter                            | 130mm     | <label class="unit millimeter"><input type="number" value="130" step="1" min="0" max="500" /></label> |  |
| needle_active_radius                       | 60mm      | <span class="unit millimeter">60</span>          | (needle_diameter - 10) / 2                            |
| pixel_per_line_count                       | 20        | <span class=""></span>                           | toFixed(needle_active_radius / pixel_pitch; 0)        |
| pixel_per_line_count_total                 | 40        | <label class=""><input type="number" value="40" step="1" min="0" max="1000" /></label> | pixel_per_line_count * 2 |
| line_circumference                         | 408mm     | <span class="unit millimeter"></span>            | toFixed(π * needle_diameter; 1)                       |
| line_count                                 | 136       | <label class=""><input type="number" value="136" step="1" min="0" max="1440" /></label> | toFixed(line_circumference / pixel_pitch) |
| line_updates_per_revolution                | 136       | <span class=""></span>                           | line_count                                            |
| line_updates_per_second                    | 4080      | <span class=""></span>                           | updates_per_second * line_updates_per_revolution      |
| line_updates_per_minute                    | 244800    | <span class=""></span>                           | rpm * line_updates_per_revolution                     |
| duration_per_revolution                    | 33ms      | <span class="unit milliseconds"></span>          | toFixed(1000 / updates_per_second; 1)                 |
| duration_per_line                          | 0.242ms   | <span class="unit milliseconds"></span>          | toFixed((duration_per_revolution / line_count); 7)    |
| duration_per_line_us                       | 242us     | <span class="unit microseconds"></span>          | toFixed(duration_per_line * 1000; 0)                  |
| duration_per_line_ns                       | 242000ns  | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line * 1000000; 0)               |
| line_pwm_duration_for_8bit                 | 945ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns /   256; 0)              |
| line_pwm_rate_for_8bit                     | 1,06MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_8bit ; 2)        |
| line_pwm_duration_for_9bit                 | 478ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns /   512; 0)              |
| line_pwm_rate_for_9bit                     | 2,09MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_9bit ; 2)        |
| line_pwm_duration_for_10bit                | 236ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns /  1024; 0)              |
| line_pwm_rate_for_10bit                    | 4,24MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_10bit; 2)        |
| line_pwm_duration_for_11bit                | 120ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns /  2048; 0)              |
| line_pwm_rate_for_11bit                    | 8,33MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_11bit; 2)        |
| line_pwm_duration_for_12bit                |  59ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns /  4096; 0)              |
| line_pwm_rate_for_12bit                    | 16,95MHz  | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_12bit; 2)        |
| line_pwm_duration_for_13bit                |  30ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns /  8192; 0)              |
| line_pwm_rate_for_13bit                    | 33,33MHz  | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_13bit; 2)        |
| line_pwm_duration_for_14bit                |  15ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns / 16384; 0)              |
| line_pwm_rate_for_14bit                    | 66,67MHz  | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_14bit; 2)        |
| line_pwm_duration_for_15bit                |   7ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns / 32768; 0)              |
| line_pwm_rate_for_15bit                    | 142,86MHz | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_15bit; 2)        |
| line_pwm_duration_for_16bit                | 3,7ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_line_ns / 65535; 2)              |
| line_pwm_rate_for_16bit                    | 270,27MHz | <span class="unit megahertz"></span>             | toFixed(1000 / line_pwm_duration_for_16bit; 2)        |

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

## LEDs & LED-Driver
[look at pov_leddriver.md](pov_leddriver.md)

## data transmission
[look at pov_datatransmission.md](pov_datatransmission.md)

## power transmission
[look at pov_powertransmission.md](pov_powertransmission.md)

## mechanics
[look at pov_mechanics.md](pov_mechanics.md)

## motor
[look at pov_motor.md](pov_motor.md)

## 3D
- [more research & brainstorming at POV_3D/](POV_3D/readme.md)
