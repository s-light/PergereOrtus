# Test Table Calc
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
<!--lint disable code-block-style-->


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
