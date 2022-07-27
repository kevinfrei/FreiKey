// For each file named "compile_commands.json" under the src/out/* directory
const path = require('path');
const fsp = require('fs').promises;

const rootLoc = path.join('src', 'out');
// File all the compile_commands.json files underneath src/out
async function findFiles() {
  const files = await fsp.readdir(rootLoc);
  const ccfiles = [];
  for (let subdir of files) {
    const allFiles = await fsp.readdir(path.join(rootLoc, subdir));
    if (allFiles.some((fn) => fn === 'compile_commands.json')) {
      ccfiles.push(path.join(rootLoc, subdir, 'compile_commands.json'));
    }
  }
  return ccfiles;
}

async function fixFile(filename) {
  const text = await fsp.readFile(filename);
  const contents = JSON.parse(text);
  const fixed = contents
    .filter((v) => v.directory !== undefined)
    .map((vn) => {
      if (vn.directory === '.') {
        vn.directory = 'src';
      }
      return vn;
    });
  const jsonCC = JSON.stringify(fixed, null, ' ');
  await fsp.writeFile(filename, jsonCC);
}

async function doit() {
  const files = await findFiles();
  await Promise.all(files.map(fixFile));
}

doit().catch(console.error);
