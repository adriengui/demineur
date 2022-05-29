#pragma once

#include <list>

#include "Observer.hpp"

using namespace std;

template<typename T>

class Observable {
private:
  list<Observer<T> *> list_observers;

  virtual void savePreviousCommand() = 0;
  
public:
  void notifyObservers(T info) {
    for (auto obs : this->list_observers) {
      obs->update(info);
    }
  }
		
  void addObserver(Observer<T> * observer) {
    this->list_observers.push_back(observer);
  }
};
