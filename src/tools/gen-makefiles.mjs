#!/usr/bin/env node
import fs from 'fs';
import os from 'os';
import path from 'path';
import { Type } from '@freik/core-utils';
import main from '@freik/arduino2proj/lib/main.js';

const data = {
  win32: {
    outputSuffix: 'win',
    // Updated for the Arduino IDE install location:
    platformPath: path.join(
      os.homedir(),
      'AppData',
      'Local',
      'Arduino15',
      'packages',
    ),
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

const teensyLoc = ['teensy', 'hardware', 'avr', '1.57.2'];

const key = os.platform();
if (!Type.has(data, key)) {
  console.error(
    `Please configure this script (${process.argv[1]}) for the ${key} platform.`,
  );
  process.exit(-1);
}

const { outputSuffix, platformPath } = data[key];
const plat = path.join(...[platformPath, ...teensyLoc]);
if (!fs.existsSync(plat)) {
  console.error(
    `${plat} doesn't exist: Make sure you've got stuff configured properly`,
  );
  process.exit(-2);
}
process.chdir('src');
if (process.argv.length < 3 || process.argv.includes('teensy')) {
  const args = [
    '-o',
    'tools/teensy.' + outputSuffix,
    '-c',
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
  ];
  console.log('Running with these args:');
  console.log(args);
  main(...args);
}
/*
if (process.argv.length < 3 || process.argv.includes('nrf52')) {
  main(
    '-o', 'tools/af_nrf52.' + outputSuffix,
    '-c','tools/adafruit-make-config.json',
    'libs/nRF52_Adafruit',
    'libs/BusIO',
    'libs/GFX',
    'libs/NeoPixel',
		'libs/SSD1306'
  );
}
*/
