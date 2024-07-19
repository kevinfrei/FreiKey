#!/usr/bin/env bun
import fs from 'fs';
import os from 'os';
import path from 'path';
import {
  Config,
  RunConfig,
  generate,
  main,
} from '@freik/arduino2proj/lib/main';

type HostConfig = { outputSuffix: string; platformPath: string[] };

// These are the MCU's I've run on:
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

// This is the base config for all platforms.
// Basically, I want to run on C++17, not C++11 or 14...
const config: Partial<Config> = {
  transforms: [
    {
      defmatch: '_FLAGS_CPP',
      text: '-std=gnu++14',
      replace: '-std=gnu++17',
    },
    {
      defmatch: '_FLAGS_CPP',
      text: '-std=gnu++11',
      replace: '-std=gnu++17',
    },
    {
      defmatch: '_CPP_FLAGS',
      text: '-std=gnu++11',
      replace: '-std=gnu++17',
    },
  ],
  // TODO: There's something odd going on with this.
  // It shows up in AF, but not Teensy
  filters: [{ defmatch: 'CPP_SYS_SRCS', remove: 'BLEMidi.cpp' }],
};

type PlatformLocation = {
  // Output name of the makefile to include
  makefile?: string;
  // Path from the arduino platform stuff
  target: string;
  // MCU from the arduino platform stuff
  mcu: string;
  // Version of the arduino platform
  version: string;
  // The config for the platform
  config: Partial<Config>;
};

const platforms: PlatformLocation[] = [
  {
    makefile: 'af_nrf52',
    target: 'adafruit',
    mcu: 'nrf52',
    version: '1.6.1',
    config,
  },
  { target: 'teensy', mcu: 'avr', version: '1.59.0', config },
  // This one's not working yet (Issue with Arduino2Proj)
  // { target: 'rp2040', mcu: 'rp2040', version: '3.9.3', config },
];

const srcDir = path.resolve(path.dirname(process.argv[1]), '..');
for (const { makefile, target, mcu, version, config } of platforms) {
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
    config,
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
