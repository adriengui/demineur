#pragma once

#include <iostream>

using namespace std;

class Cell {
	private:
		int nb;
		bool open;
	public:
		Cell(const int n=0, const bool o=false) : nb(n), open(o) { }
		
		void init() {
			setNb();
			setOpen();
		}
		
		void setNb(const int n=0) {
			nb=n;
		}
		
		void setOpen(const bool o=false) {
			open=o;
		}
		
		int getNb() const {
			return nb;
		}
		
		bool getOpen() const {
			return open;
		}
		
		bool isBombe() const {
			return getNb()==-1;
		}
		
		void setBombe() {
			setNb(-1);
		}
	
};
