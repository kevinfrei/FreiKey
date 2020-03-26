#pragma once

// Shamelessly stolen from
// https://www.fluentcpp.com/2017/05/19/crtp-helper/

template <typename T/*, template <typename> class crtpType*/>
struct crtp {
  T& underlying() {
    return static_cast<T&>(*this);
  }
  T const& underlying() const {
    return static_cast<T const&>(*this);
  }

 private:
  crtp() {}
/*  friend crtpType<T>; */
};