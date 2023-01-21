#!/usr/bin/env node
import main from '@freik/arduino2proj/lib/main.js';

main(
	'--out:src/tools/teensy.win',
  '--config:src/tools/teensy-make-config.json',
  'C:/PROGRA~2/Arduino/hardware/teensy/avr',
  'src/libs/SdFat',
  'src/libs/GFX',
  'src/libs/ST77XX',
  'src/libs/BusIO',
  'src/libs/T4_PXP',
  'src/libs/GFX_Buffer',
  'src/libs/AsyncDMA',
  'src/libs/8875',
);
//  tools\teensy.win
