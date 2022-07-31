#include "newModule.h"
#include <iostream>

class FakeDisplay;
class FakeCalculator;
class FakeLineEditor;

class FakeDisplay : public Registerable {
 public:
  FakeDisplay() : Registerable(ModuleId::Display, {}) {
    Constructed();
  }
  virtual void RegisterDependency(Registerable* r) {
    // Never should be reached...
    std::cerr << "FAIL!" << std::endl;
  }
};

class FakeLineEditor : public Registerable {
  FakeDisplay* disp;

 public:
  FakeLineEditor()
    : disp(nullptr), Registerable(ModuleId::LineEditor, {ModuleId::Display}) {
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
};

class FakeCalculator : public Registerable {
  FakeLineEditor* edit;
  FakeDisplay* disp;

 public:
  FakeCalculator()
    : edit(nullptr),
      disp(nullptr),
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
};

FakeLineEditor lineEditor;
FakeDisplay fakeDisplay;
FakeCalculator FakeCalculator;
