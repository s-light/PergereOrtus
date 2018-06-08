# Test Table Calc
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->
<!--lint disable code-block-style-->


| name                                       | value           | formula                                                     | value |
| :----------------------------------------- | --------------: | ----------------------------------------------------------: | ----: |
| updates_per_second = revolution_per_second | 30              |                                                             | <input type="number" class="unit rpm"  value="30" step="1" min="0" max="120"/> |
| rpm (revolution per minute)                | 1800            | revolution_per_second * 60                                  | <span class="value"></span> |
| pixel_pitch                                | 3mm             |                                                             | <input type="number" class="unit millimeter"  value="3" step="0.1" min="0" max="20" /> |
| needle_diameter                            | 130mm           |                                                             | <input type="number" class="unit millimeter"  value="130" step="1" min="0" max="500" /> |
| needle_active_radius                       | 60mm            | (needle_diameter - 10mm) / 2                                | <span class="unit millimeter"></span> |
| pixel_count_one_side                       | 20              | needle_active_radius / pixel_pitch                          | <span class=""></span> |
| pixel_count_total                          | 40              | pixel_count_one_side * 2                                    | <input type="number" class=""  value="40" step="1" min="0" max="1000" /> |
| pixel_circumference                        | 408mm           | π * needle_diameter                                         | <span class="unit millimeter"></span> |
| pixel_circumference_virtual_count          | 136             | pixel_circumference / pixel_pitch                           | <input type="number" class=""  value="136" step="1" min="0" max="1440" /> |
| pixel_updates_per_second                   | 4080            | revolution_per_second * pixel_updates_per_revolution        | <span class=""></span> |
| pixel_updates_per_revolution               | 136             | = pixel_circumference_virtual_count                         | <span class=""></span> |
| pixel_updates_per_minute                   | 244800          | revolution_per_minute * pixel_updates_per_revolution        | <span class=""></span> |
| duration_per_revolution                    | 33ms            | 1000ms / updates_per_second                                 | <span class="unit milliseconds"></span> |
| duration_per_pixel                         | 242us           | duration_per_revolution / pixel_circumference_virtual_count | <span class="unit microseconds"></span> |
| pixel_pwm_rate_for_8bit       256          | 945ns   1,06MHz | duration_per_pixel /   256                                  | <span class="unit nanoseconds"></span> <span class="unit megahertz"></span> |
| pixel_pwm_rate_for_10bit     1024          | 236ns   4,24MHz | duration_per_pixel /  1024                                  | <span class="unit nanoseconds"></span> <span class="unit megahertz"></span> |
| pixel_pwm_rate_for_12bit     4096          |  59ns  16,95MHz | duration_per_pixel /  4096                                  | <span class="unit nanoseconds"></span> <span class="unit megahertz"></span> |
| pixel_pwm_rate_for_16bit    65535          | 3,7ns 270,27MHz | duration_per_pixel / 65535                                  | <span class="unit nanoseconds"></span> <span class="unit megahertz"></span> |

<button type="button" name="bt_update" id="bt_update">update</button>

<script src="{{ '/assets/js/table_calc_example.js?v=' | append: site.github.build_revision | relative_url }}" charset="utf-8"></script>
<script type="text/javascript">


</script>



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
