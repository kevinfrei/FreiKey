#include <ctype.h>
#include <iostream>
#include <string>

#include "bitmap.h"
#include "imgencoder.h"

int parseCodec(const std::string& name, cmdLine* ln) {
  if (name.find("rle") == 0) {
    ln->cmpType = image_compression::NQRLE;
  } else if (name.find("prle") == 0) {
    ln->cmpType = image_compression::PAL_NQRLE;
  } else if (name.find("pal") == 0) {
    ln->cmpType = image_compression::PAL_RAW;
  } else if (name.find("raw") == 0) {
    ln->cmpType = image_compression::RAW;
  } else
    return 1;
  return 0;
}

int32_t readPosNumber(const std::string& maybeNum) {
  int32_t res = 0;
  for (char c : maybeNum) {
    if (!isdigit(c)) {
      return -1;
    }
    res = res * 10 + c - '0';
  }
  return res;
}

int parseHeight(const std::string& height, cmdLine* ln) {
  int val = readPosNumber(height);
  if (val < 0) {
    return 1;
  } else {
    ln->height = val;
    return 0;
  }
}

int parseWidth(const std::string& width, cmdLine* ln) {
  int val = readPosNumber(width);
  if (val < 0) {
    return 1;
  } else {
    ln->width = val;
    return 0;
  }
}

int parseImageNum(const std::string& num, cmdLine* ln) {
  int val = readPosNumber(num);
  if (val < 0) {
    return 1;
  } else {
    ln->imageToDecode = val + 1;
    return 0;
  }
}

int usage(const std::string& name) {
  std::cerr
    << "Usage:" << std::endl
    << std::endl
    << name << " <--codec/-c:XXX> <filename>" << std::endl
    << "\tWhere <filename> is (probably) a file produced from " << std::endl
    << "\thttps://lvgl.io/tools/imageconverter in the 565 format" << std::endl
    << "\tand XXX is optionally raw, rle, pal, or prle" << std::endl
    << std::endl
    << "OR" << std::endl
    << name << " --decode/-d:# <filename>" << std::endl
    << "\tSpit out the internal image # into <filename>" << std::endl
    << std::endl
    << "OR" << std::endl
    << name << " <--codec/-c:XXX> --width/-w:# --height/-h:# <filename.raw>"
    << std::endl
    << "\tAssume the filename.raw file is just a bunch of 565 pixels"
    << std::endl
    << ">>> Note: If a codec isn't set, the best compression will be used."
    << std::endl;
  return 1;
}

struct flags {
  std::string name;
  int (*parser)(const std::string&, cmdLine*);
};

const flags parser[] = {
  {.name = std::string("--decode:"), .parser = parseImageNum},
  {.name = std::string("--codec:"), .parser = parseCodec},
  {.name = std::string("--width:"), .parser = parseWidth},
  {.name = std::string("--height:"), .parser = parseHeight},
  {.name = std::string("-d:"), .parser = parseImageNum},
  {.name = std::string("-c:"), .parser = parseCodec},
  {.name = std::string("-w:"), .parser = parseWidth},
  {.name = std::string("-h:"), .parser = parseHeight},
};

int parseArgs(int argc, const char* argv[], cmdLine* ln) {
  // Argument parsing really does suck...
  for (int curArg = 1; curArg < argc; curArg++) {
    std::string arg{argv[curArg]};
    if (arg[0] != '-') {
      if (curArg != argc - 1) {
        return -1;
      }
      ln->filename = arg;
    } else {
      for (auto& flag : parser) {
        if (arg.size() > flag.name.size() &&
            arg.substr(0, flag.name.size()) == flag.name) {
          int res = flag.parser(arg.substr(flag.name.size()), ln);
          if (res != 0)
            return res;
          else
            break;
        }
      }
    }
  }
  return 0;
}

bool validateArgs(cmdLine& ln) {
  if (!!ln.height != !!ln.width) {
    return false;
  }
  if (ln.imageToDecode > builtin_count) {
    return false;
  }
  if (ln.filename.empty()) {
    return false;
  }
  if (ln.imageToDecode && ln.height) {
    return false;
  }
  if (ln.imageToDecode && ln.cmpType != image_compression::FIND_BEST) {
    return false;
  }
  return true;
}
