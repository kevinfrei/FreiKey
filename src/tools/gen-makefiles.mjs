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
process.chdir('src');
if (process.argv.length < 3 || process.argv.includes('teensy')) {
  main(
    '--out',
    'tools/teensy.' + outputSuffix,
    '--config',
    'tools/teensy-make-config.json',
    plat,
    'libs/SdFat',
    'libs/GFX',
    'libs/ST77XX',
    'libs/BusIO',
    'libs/T4_PXP',
    'libs/GFX_Buffer',
    'libs/AsyncDMA',
    'libs/8875',
  );
}
if ((false && process.argv.length < 3) || process.argv.includes('nrf52')) {
  main(
    '--out',
    'tools/af_nrf52.' + outputSuffix,
    '--config',
    'tools/adafruit-make-config.json',
    'libs/nRF52_Adafruit',
    'libs/BusIO',
    'libs/GFX',
    'libs/NeoPixel',
    'libs/SSD1306',
  );
}
