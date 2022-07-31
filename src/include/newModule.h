#pragma once
#if !defined(_GUARD_MODULE_H)
#define _GUARD_MODULE_H

#include <forward_list>
#include <map>

#include "enumtypes.h"

/*
I want all built modules to be able to register what they depend on,
and then get initialized *after* their dependencies are intialized...
*/

class Registerable {
 private:
  static std::map<ModuleId, Registerable*> completedDepencies;
  static std::multimap<ModuleId, Registerable*> waitingForDependency;
  uint8_t numUnmetDeps;
  const ModuleId name;
  const std::forward_list<ModuleId> dependencies;

  // a recursive demand-based dependency linker, basically?
  void RegistrationComplete() {
    Registerable::completedDepencies.insert(std::make_pair(name, this));
    for (auto deps = Registerable::waitingForDependency.find(name);
         deps != Registerable::waitingForDependency.end() &&
         deps->first == name;
         deps++) {
      deps->second->RegisterDependency(this);
      deps->second->numUnmetDeps--;
      if (deps->second->numUnmetDeps == 0) {
        deps->second->RegistrationComplete();
      }
    }
    Registerable::waitingForDependency.erase(name);
    AllDependenciesMet();
  }

 protected:
  Registerable(ModuleId n, std::initializer_list<ModuleId> i)
    : name(n), dependencies(i) {
    // You need to invoke the 'Constructed' method in the child constructor,
    // otherwise, registration *may* occur before your object is full
    // constructed
  }
  // Demand-based dependency walking, hopefully
  void Constructed() {
    uint8_t unmet = 0;
    for (ModuleId nextDep : dependencies) {
      auto dep = Registerable::completedDepencies.find(nextDep);
      if (dep == Registerable::completedDepencies.end() ||
          dep->first != nextDep) {
        unmet++;
        Registerable::waitingForDependency.insert(
          std::make_pair(nextDep, this));
      } else {
        RegisterDependency(dep->second);
      }
    }
    numUnmetDeps = unmet;
    if (unmet == 0) {
      RegistrationComplete();
    }
  }
  // This is where you do stuff with your dependency
  // It *could* get invoked during "Constructed"
  // or it could be invoked much later
  virtual void RegisterDependency(Registerable* r) = 0;
  // This is only called once all the deps of your class are met
  virtual void AllDependenciesMet() = 0;

 public:
  ModuleId ID() const {
    return name;
  }
};

#endif