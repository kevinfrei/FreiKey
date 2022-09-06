#include "newModule.h"
#include <iostream>

class FakeDisplay;
class FakeCalculator;
class FakeLineEditor;

class FakeDisplay : public Registerable {
  bool ready;

 public:
  FakeDisplay() : ready(false), Registerable(ModuleId::Display, {}) {
    Constructed();
  }
  virtual void RegisterDependency(Registerable* r) {
    // Never should be reached...
    std::cerr << "FAIL!" << std::endl;
  }
  virtual void AllDependenciesMet() {
    if (ready) {
      std::cerr << "Already ready!" << std::endl;
    } else {
      ready = true;
    }
  }
};

class FakeLineEditor : public Registerable {
  FakeDisplay* disp;
  bool ready;

 public:
  FakeLineEditor()
    : disp(nullptr),
      ready(false),
      Registerable(ModuleId::LineEditor, {ModuleId::Display}) {
    Constructed();
  }
  virtual void RegisterDependency(Registerable* r) {
    if (r->ID() != ModuleId::Display) {
      std::cerr << "Failed in dep registration: " << static_cast<int>(r->ID())
                << std::endl;
    } else if (disp != nullptr) {
      std::cerr << "Looks like the calculator dependency is already registered!"
                << std::endl;
    } else {
      disp = static_cast<FakeDisplay*>(r);
    }
  }
  virtual void AllDependenciesMet() {
    if (disp == nullptr) {
      std::cerr << "Display dependency not met, but claimed to have been."
                << std::endl;
    } else if (ready) {
      std::cerr << "Already dep-met, but triggered again..." << std::endl;
    } else {
      ready = true;
    }
  }
};

class FakeCalculator : public Registerable {
  FakeLineEditor* edit;
  FakeDisplay* disp;
  bool ready;

 public:
  FakeCalculator()
    : edit(nullptr),
      disp(nullptr),
      ready(false),
      Registerable(ModuleId::Calculator,
                   {ModuleId::Display, ModuleId::LineEditor}) {
    Constructed();
  }
  virtual void RegisterDependency(Registerable* r) {
    switch (r->ID()) {
      case ModuleId::Display:
        if (disp != nullptr) {
          std::cerr
            << "Looks like the calculator dependency is already registered!"
            << std::endl;
        } else {
          disp = static_cast<FakeDisplay*>(r);
        }
        break;
      case ModuleId::LineEditor:
        if (edit != nullptr) {
          std::cerr
            << "Looks like the calculator dependency is already registered!"
            << std::endl;
        } else {
          edit = static_cast<FakeLineEditor*>(r);
        }
        break;
      default:
        std::cerr << "Failed in dep registration: " << static_cast<int>(r->ID())
                  << std::endl;
    }
  }
  virtual void AllDependenciesMet() {
    if (disp == nullptr) {
      std::cerr << "Display dependency not met, but claimed to have been."
                << std::endl;
    } else if (ready) {
      std::cerr << "Already dep-met, but triggered again..." << std::endl;
    } else {
      ready = true;
    }
  }
};

FakeLineEditor lineEditor;
FakeDisplay fakeDisplay;
FakeCalculator fakeCalculator;
