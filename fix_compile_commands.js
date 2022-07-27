// For each file named "compile_commands.json" under the src/out/* directory
// fix the directory location to work from the root of the repo instead of src
// TODO: Maybe just make this also invoke Make, since that would add a lot of
// flexibility to the system

const path = require('path');
const fsp = require('fs').promises;

const rootLoc = path.join('src', 'out');
const ccname = 'compile_commands.json';
// File all the compile_commands.json files underneath src/out
async function findFiles() {
  const files = await fsp.readdir(rootLoc);
  const ccfiles = [];
  for (let subdir of files) {
    const fullDir = path.join(rootLoc, subdir);
    const allFiles = await fsp.readdir(fullDir);
    if (allFiles.some((fn) => fn === ccname)) {
      ccfiles.push(path.join(fullDir, ccname));
    }
  }
  return ccfiles;
}

async function fixFile(filename) {
  const text = await fsp.readFile(filename);
  const contents = JSON.parse(text);
  const fixed = contents
    .filter((v) => v.directory !== undefined)
    .map((vn) => (vn.directory === '.' ? { ...vn, directory: 'src' } : vn));
  const jsonCC = JSON.stringify(fixed, null, ' ');
  await fsp.writeFile(filename, jsonCC);
}

async function doit() {
  const files = await findFiles();
  await Promise.all(files.map(fixFile));
}

doit().catch(console.error);
