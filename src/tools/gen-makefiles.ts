#!/usr/bin/env bun
import fs from 'fs';
import os from 'os';
import path from 'path';
import { RunConfig, generate, main } from '@freik/arduino2proj/lib/main';

type HostConfig = { outputSuffix: string; platformPath: string[] };

const hostConfig: Map<string, HostConfig> = new Map([
  [
    'win32',
    {
      outputSuffix: 'win',
      // Updated for the Arduino IDE install location:
      platformPath: [os.homedir(), 'AppData', 'Local', 'Arduino15', 'packages'],
    },
  ],
  [
    'darwin',
    {
      outputSuffix: 'mac',
      platformPath: [os.homedir(), 'Library', 'Arduino15', 'packages'],
    },
  ],
  [
    'linux',
    {
      outputSuffix: 'lin',
      platformPath: [os.homedir(), 'Apps', 'arduino-1.8.19'],
    },
  ],
]);

type PlatformLocation = {
  makefile?: string;
  target: string;
  mcu: string;
  version: string;
};

const platforms: PlatformLocation[] = [
  { makefile: 'af_nrf52', target: 'adafruit', mcu: 'nrf52', version: '1.6.1' },
  { target: 'teensy', mcu: 'avr', version: '1.59.0' },
  { target: 'rp2040', mcu: 'rp2040', version: '3.9.3' },
];

const srcDir = path.resolve(path.dirname(process.argv[1]), '..');
for (const { makefile, target, mcu, version } of platforms) {
  const key = os.platform();
  if (!hostConfig.has(key)) {
    console.error(
      `Please configure this script (${process.argv[1]}) for the ${key} platform.`,
    );
    process.exit(-1);
  }

  const { outputSuffix, platformPath } = hostConfig.get(key) as HostConfig;
  const plat = path.join(...platformPath, target, 'hardware', mcu, version);
  if (!fs.existsSync(plat)) {
    console.error(
      `${plat} doesn't exist: Make sure you've got stuff configured properly`,
    );
    process.exit(-2);
  }
  process.chdir(srcDir);
  const runConfig: RunConfig = {
    outputFile: `tools/${makefile || target}.${outputSuffix}`,
    configFile: `tools/${target}-make-config.json`,
    root: plat,
    libs: [
      'libs/SdFat',
      'libs/GFX',
      'libs/ST77XX',
      'libs/BusIO',
      'libs/T4_PXP',
      'libs/GFX_Buffer',
      'libs/AsyncDMA',
      'libs/8875',
    ],
  };
  // console.log('Running with these args:');
  // console.log(args);
  generate(runConfig)
    .then(() => {
      console.log('Generated', target);
    })
    .catch((err) => {
      console.error('Error from target generation', target, ':');
      console.error(err);
    });
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
    'libs/SSD1306',
  );
}
*/
