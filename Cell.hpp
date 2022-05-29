#pragma once

#include <iostream>

using namespace std;

typedef enum {open = 0, closed, flag} State;

class Cell {
private:
  int nb;
  State state;

public:
  Cell(const int n = 0, const State s = closed) : nb(n), state(s) {}
		
  void init() {
    setNb();
    setState(closed);
  }
		
  void setNb(const int n=0) {
    nb = n;
  }
		
  void setState(const State s) {
    state = s;
  }
		
  int getNb() const {
    return nb;
  }
		
  State getState() const {
    return state;
  }

  bool getOpen() const {
    return state == open;
  }
		
  bool isBombe() const {
    return getNb() == -1;
  }
		
  void setBombe() {
    setNb(-1);
  }

  static bool isNotEqual(const Cell& lhs, const Cell& rhs) {
    return lhs.getNb() != rhs.getNb() || lhs.getState() != rhs.getState();
  }
};
