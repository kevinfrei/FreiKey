#!/usr/bin/env node
import fs from 'fs';
import os from 'os';
import path from 'path';
import { Type } from '@freik/core-utils';
import main from '@freik/arduino2proj/lib/main.js';

const data = {
  win32: {
    outputSuffix: 'win',
    platformPath: 'C:/PROGRA~2/Arduino',
  },
  darwin: {
    outputSuffix: 'mac',
    platformPath: '/Applications/Teensyduino.app/Contents/Java',
  },
  linux: {
    outputSuffix: 'lin',
    platformPath: path.join(process.env.HOME || '', 'Apps/arduino-1.8.19'),
  },
};

const key = os.platform();
if (!Type.has(data, key)) {
  console.error(
    `Please configure this script (${process.argv[1]}) for the ${key} platform.`,
  );
  process.exit(-1);
}

const { outputSuffix, platformPath } = data[key];
const plat = path.join(platformPath, 'hardware', 'teensy', 'avr');
if (!fs.existsSync(plat)) {
  console.error(
    `${plat} doesn't exist: Make sure you've got stuff configured properly`,
  );
  process.exit(-2);
}
if (process.argv.length < 3 || process.argv.includes('teensy')) {
  main(
    '--out:src/tools/teensy.' + outputSuffix,
    '--config:src/tools/teensy-make-config.json',
    plat,
    'src/libs/SdFat',
    'src/libs/GFX',
    'src/libs/ST77XX',
    'src/libs/BusIO',
    'src/libs/T4_PXP',
    'src/libs/GFX_Buffer',
    'src/libs/AsyncDMA',
    'src/libs/8875',
  );
}
if (process.argv.length < 3 || process.argv.includes('nrf52')) {
  main(
    '--out:src/tools/af_nrf52.' + outputSuffix,
    '--config:src/tools/adafruit-make-config.json',
    'src/libs/nRF52_Adafruit',
    'src/libs/BusIO',
    'src/libs/GFX',
    'src/libs/NeoPixel',
		'src/libs/SSD1306'
  );
}
