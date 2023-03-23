// For each file named "compile_commands.json" under the src/out/* directory
// fix the directory location to work from the root of the repo instead of src
// TODO: Maybe just make this also invoke Make, since that would add a lot of
// flexibility to the system

const path = require('path');
const fsp = require('fs').promises;

const rootLoc = path.join('src', 'out');
const ccname = 'compile_commands.jsn';
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
  const text = (await fsp.readFile(filename))
    .toString()
    .split('\n')
    .map((v) => v.trim());
  const contents = [];
  for (let i = 0; i < text.length - 2; i += 3) {
    const obj = {};
    const ln1 = text[i];
    let flag = 0;
    if (ln1.startsWith('dir#')) {
      const dir = ln1.substring(4);
      obj.directory = dir === '.' ? 'src' : dir;
    }
    flag += 1;
    const ln2 = text[i + 1];
    if (ln2.startsWith('fil#')) {
      obj.file = ln2.substring(4);
      flag += 2;
    }
    const ln3 = text[i + 2];
    if (ln3.startsWith('cmd#')) {
      obj.command = ln3.substring(4);
      flag += 4;
    }
    if (flag === 7) {
      contents.push(obj);
    }
  }
  const jsonCC = JSON.stringify(contents, null, ' ');
  await fsp.writeFile(filename.replace('.jsn', '.json'), jsonCC);
}

async function doit() {
  const files = await findFiles();
  await Promise.all(files.map(fixFile));
}

doit().catch(console.error);
