# POV LEDs and LED-Driver
<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->

idea here is to have a IR led directly pulsing the raw data out and an receiver converting it back to signal..
so this could be transmitted over the rotation contact-less.
challenge here is the bit time - we need some very very fast photo detectors...

![pov concept overview](pov_concept_overview.svg)

---
# Contents
{:.no_toc}

* Will be replaced with the ToC, excluding the "Contents" header
{:toc}
---

# LEDs
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
- [arduino TLC5940 lib](https://github.com/artcfox/tlc5940)
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


### driver-update-rates

| calculation step   | APA102                | TLC5971             | formula               |
| :----------------- | :-------------------- | :------------------ | --------------------: |
| bytes_per_update   | 166 (4 + 40*4 + 2)    | 280 (28 * (40 / 4)) |                       |
| bits_per_update    | 1328                  | 2240                | bytes_per_update * 8  |
| bits_per_second    | 5418240               | 9139200             | bits_per_update * pixel_updates_per_second |
| kbit_per_second    | 5418                  | 9139                |                       |
| Mbit_per_second    | 5,41                  | 9,14                |                       |
| bit_time_max       | 184ns (= 0,184us)     | 109 ns (= 0,109us)  | `1s / (5,41*10^6) ==` |

```
1 second == 1.000 ms == 1.000.000 us == 1.000.000.000 ns

10 bit pro second == 1s/10         per bit == 100ms per bit
10kbit pro second == 1s/10k        per bit == 100us per bit
10Mbit pro second == 1s/10M        per bit == 0,0000001s == 100 ns  
10Mbit pro second == 1s/10.000.000 per bit == 0,0000001s == 100 ns  
```
