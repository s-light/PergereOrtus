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

| name                                       | test      | value                                            | formula                                               |
| :----------------------------------------- | --------: | -----------------------------------------------: | ----------------------------------------------------: |
| updates_per_second = revolution_per_second | 30        | <label class="unit rpm"><input type="number" value="30" step="1" min="0" max="120"/></label> |           |
| rpm (revolution per minute)                | 1800      | <span class="">1800</span>                       | updates_per_second * 60                               |
| pixel_pitch                                | 3mm       | <label class="unit millimeter"><input type="number" value="1.5" step="0.1" min="0" max="20" /></label> | |
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
| duration_per_pixel                         | 0.242ms   | <span class="unit milliseconds"></span>          | toFixed((duration_per_revolution / pixel_circ_vcount); 7) |
| duration_per_pixel_us                      | 242us     | <span class="unit microseconds"></span>          | toFixed(duration_per_pixel * 1000; 0)                 |
| duration_per_pixel_ns                      | 242000ns  | <span class="unit nanoseconds"></span>           | toFixed(duration_per_pixel * 1000000; 0)              |
| pixel_pwm_duration_for_8bit                | 945ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_pixel_ns /   256; 0)             |
| pixel_pwm_rate_for_8bit                    | 1,06MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / pixel_pwm_duration_for_8bit ; 2)       |
| pixel_pwm_duration_for_10bit               | 236ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_pixel_ns /  1024; 0)             |
| pixel_pwm_rate_for_10bit                   | 4,24MHz   | <span class="unit megahertz"></span>             | toFixed(1000 / pixel_pwm_duration_for_10bit; 2)       |
| pixel_pwm_duration_for_12bit               |  59ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_pixel_ns /  4096; 0)             |
| pixel_pwm_rate_for_12bit                   | 16,95MHz  | <span class="unit megahertz"></span>             | toFixed(1000 / pixel_pwm_duration_for_12bit; 2)       |
| pixel_pwm_duration_for_16bit               | 3,7ns     | <span class="unit nanoseconds"></span>           | toFixed(duration_per_pixel_ns / 65535; 2)             |
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
- APA102-2020
    - [APA-102-2020-P5 STRIP](http://neon-world.com/en/product_detail.php?cid=94&id=230)
    - [MicroNova LED Strip, 198 LEDs/meter (60564)](https://solarbotics.com/product/60564/)
    - [Ultra High Density DotStar LED PCB Bar - 128 LEDs (4,17mm Pitch)](https://www.adafruit.com/product/3776)
- [digikey overview](https://www.digikey.de/products/de/optoelectronics/led-indication-discrete/105?k=&pkeyword=&pv206=3108&pv206=3107&pv206=2750&pv206=1408&FV=1c0002%2C94030c%2C1140003%2C3380580%2C3380abe%2C3380bc6%2C3380c23%2C3380c24%2C3380f1c%2C338100d%2C33c0360%2C33c0363%2C1ccc0003%2C1f140000%2Cffe00069%2Cb844b6%2Cb844d5%2Cb845c7&quantity=1&ColumnSort=-206&page=1&stock=1&nstock=1&rohs=1&pageSize=25)

| package    | width | length | height | red     | green   | blue    | white    | manufacture      | part                                                                                                   | digikey                                                                                                     |
| :--------- | :---- | :----- | :----- | ------: | ------: | ------: | -------: | ---------------: | -----------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------- |
| NSSM124D   | 3.3mm | 3.0mm  | 0.75mm |  750mcd | 2200mcd |  500mcd | 2800mcd  | Nichia           | [NSSM124D](http://www.nichia.co.jp/en/product/led_product_data.html?type=%27NSSM124D%27)               | [Lumitronix 0,4€](https://www.leds.de/nichia-nssm124dt-smd-led-rgb-30201.html)                              |
| PLCC-6     | 2.8mm | 2.8mm  | 2.5mm  | 1000mcd | 2250mcd |  460mcd | 2340mcd  | Cree             | [CLY6D-FKC-Cnp1st1E1BB7D3D3](http://www.cree.com/led-components/media/documents/ds-1321-CLY6D-FKC.pdf) | [0,34€](https://www.digikey.de/product-detail/de/cree-inc/CLY6D-FKC-CNP1ST1E1BB7D3D3/CLY6D-FKC-CNP1ST1E1BB7D3D3CT-ND/6138647) |
| 3528(1411) | 3.5mm | 2.8mm  | 0.6mm  |  700mcd | 1200mcd |  400mcd | 1560mcd  | Rohm             | [SMLVN6RGB1U](https://www.rohm.com/datasheet/SMLVN6RGB1U)                                              | [1,13€](https://www.digikey.de/product-detail/de/rohm-semiconductor/SMLVN6RGB1W1/846-1187-1-ND/5053804)     |
| 1816(0706) | 1.8mm | 1.6mm  | 0.5mm  |  400mcd |  550mcd |  180mcd | 1058mcd  | Rohm             | [MSL0402RGB](https://www.rohm.com/datasheet/MSL0402RGBU)                                               | [0,60€](https://www.digikey.de/product-detail/de/rohm-semiconductor/MSL0402RGBU1/MSL0402RGBU1CT-ND/6573090) |
| PLCC-6     | 3.4mm | 2.8mm  | 1.8mm  |  650mcd | 1900mcd |  384mcd | -        | Broadcom Limited | [ASMT-YTB7-0AA02](https://media.digikey.com/pdf/Data%20Sheets/Avago%20PDFs/ASMT-YTB7-0AA02.pdf)        | [1,03€](https://www.digikey.de/product-detail/de/broadcom-limited/ASMT-YTB7-0AA02/516-3132-1-ND/4969472)    |
| PLCC-4     | 3.2mm | 2.8mm  | 1.9mm  |  540mcd | 1600mcd |  350mcd | -        | Broadcom Limited | [ASMB-MTB0-0A3A2](https://docs.broadcom.com/docs/AV02-4186EN)                                          | [0,47€](https://www.digikey.de/product-detail/de/broadcom-limited/ASMB-MTB0-0A3A2/516-3279-1-ND/5695364)    |



## LED-Driver

### information collection
- TI forum
    - [question](https://e2e.ti.com/support/power_management/led_driver/f/192/t/699773)
    - [TLC5951](https://e2e.ti.com/support/power_management/led_driver/f/192/t/702179)
    - [Real-time SPI support with DMA, has it been done, is it feasible?](https://e2e.ti.com/support/embedded/linux/f/354/t/259974)

- [pov with avr TLC5940](https://sites.google.com/site/artcfox/demystifying-the-tlc5940)
- [arduino tlc5940](https://github.com/artcfox/tlc5940)
- [arduino TLC5951 lib](https://github.com/def1/tlc5951)
- [arduino TLC5955 lib](https://github.com/zfphil/TLC5955)
- [arduino TLC5958 lib](https://e2e.ti.com/support/power_management/led_driver/f/192/t/543912)

### comparison

| part                                           | data rate | pwm rate       | channels | resolution | ch current | oscillator    | Package            | comment                      | stars | mouser                                                |
| :--------------------------------------------- | :-------- | :------------- | :------- | :--------- | :--------- | :------------ | :----------------- | :--------------------------- | :---: | :---------------------------------------------------- |
| [APA102](https://cpldcpu.wordpress.com/2014/08/27/apa102/) | ~20MHz | 20kHz | 3        | 8Bit       |  18mA      | internal      | custom             | no real datasheet values     | *     | [0,25€](https://www.mouser.de/_/?Keyword=APA102+2020) |
| [TLC5971](http://www.ti.com/product/TLC5971)   | 20MHz     | 10MHz/20MHz    | 12       | 16Bit      |  60mA      | int. / ext.   | HTSSOP / QFN       | available libs               | **    | [2,70€](https://www.mouser.de/_/?Keyword=TLC5971)     |
| [TLC5930](http://www.ti.com/product/TLC5930)   | 20MHz     | 10MHz/20MHz    | 12       | 10Bit      |  30mA      | int. / ext.   | HTSSOP             |                              | ***   | [5,26€](https://www.mouser.de/_/?Keyword=TLC5930)     |
| [TLC5943](http://www.ti.com/product/TLC5943)   | 30MHz     | 33MHz          | 16       | 16Bit      |  50mA      | ext. GS clock | HTSSOP             | schnick-schnack-systems      | ?     | [2,30€](https://www.mouser.de/_/?Keyword=TLC5943)     |
| [TLC5947](http://www.ti.com/product/TLC5947)   | 15MHz     |  4MHz          | 24       | 12Bit      |  30mA      | internal      | HTSSOP             |                              | -     | [2,87€](https://www.mouser.de/_/?Keyword=TLC5947)     |
| [TLC5949](http://www.ti.com/product/TLC5949)   | 33MHz     | 33MHz          | 16       | 12Bit      |  45mA      | ext. GS clock | HTSSOP             |                              | ?     | [2,23€](https://www.mouser.de/_/?Keyword=TLC5949)     |
| [TLC5951](http://www.ti.com/product/TLC5951)   | 33MHz     | 33MHz          | 24       | 8/10/12Bit |  40mA      | ext. GS clock | HTSSOP             |                              | ***** | [3,56€](https://www.mouser.de/_/?Keyword=TLC5951)     |
| [TLC5955](http://www.ti.com/product/TLC5955)   | 25MHz     | 33MHz          | 48       | 16Bit      |  30mA      | ext. GS clock | HTSSOP-56 / QFN-56 | CC-setting internal          | ?     | [4,59€](https://www.mouser.de/_/?Keyword=TLC5955)     |
| [TLC5957](http://www.ti.com/product/TLC5957)   | 33MHz     | 33MHz          | 48       | 9-16Bit    |  25mA      | ext. GS clock | QFN-56             |                              | ?     | [4,82€](https://www.mouser.de/_/?Keyword=TLC5957)     |
| [TLC5958](http://www.ti.com/product/TLC5958)   | 25MHz     | 33MHz          | 48       | 16Bit      |  25mA      | ext. GS clock | QFN-56             | 32-multiplex / 48k GS-memory | -     | [5,50€](https://www.mouser.de/_/?Keyword=TLC5958)     |
| [TLC59581](http://www.ti.com/product/TLC59581) | 25MHz     | 33MHz          | 48       | 16Bit      |  25mA      | ext. GS clock | QFN-56             | 32-multiplex / 48k GS-memory | -     | [6,31€](https://www.mouser.de/_/?Keyword=TLC59581)     |
| [TLC59582](http://www.ti.com/product/TLC59582) | 25MHz     | 33MHz          | 48       | 16Bit      |  25mA      | ext. GS clock | QFN-56             | 16-multiplex / 48k GS-memory | -     | [5,43€](https://www.mouser.de/_/?Keyword=TLC59582)     |





## infrared data transmission
[look at pov_datatransmission.md](pov_datatransmission.md)

## power transmission
[look at pov_powertransmission.md](pov_powertransmission.md)

## mechanics
[look at pov_mechanics.md](pov_mechanics.md)

## motor
[look at pov_motor.md](pov_motor.md)

## 3D
- [more research & brainstorming at POV_3D/](POV_3D/readme.md)
