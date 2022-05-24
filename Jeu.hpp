#pragma once

#include <iostream>

#include "Cell.hpp"

using namespace std;

class Jeu {
	private:			
		vector<vector<Cell>> grille_;
		int etat;
	
	public:
		
		Jeu(const int e=0) : etat(e) { }
		
		const Cell& getCell(const int i, const int j) const {
			return grille_[i][j];
		}
		  
		Cell& getCellRef(const int i, const int j) {
			return grille_[i][j];
		}
		
		vector<vector<Cell>>& getGrille() {
			return grille_;
		}
		
		int getEtat() const {
			return etat;
		}
		
		void setEtat(const int e=0) {
			etat=e;
		}
};
