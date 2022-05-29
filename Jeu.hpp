#pragma once

#include <iostream>

#include "Cell.hpp"

using namespace std;
typedef enum { encours, victoire, perdu } Etat;

class Jeu {
private:			
  vector<vector<Cell>> grille_;
  Etat etat{encours};
  bool debut = true;
  bool fin = false;
  
public:		
  Jeu(const Etat e = encours) : etat(e) {}
  void reset() {
    grille_.clear();
    etat = encours;
    debut = true;
    fin = false;
  }
  
  void setDebut(bool value) { debut = value; }
  void setFin(bool value) { fin = value; }

  bool getDebut() const { return debut; }
  bool getFin() const { return fin; }
  
  const Cell& getCell(const int i, const int j) const {
    return grille_[i][j];
  }
		  
  Cell& getCellRef(const int i, const int j) {
    return grille_[i][j];
  }
		
  vector<vector<Cell>>& getGrille() {
    return grille_;
  }

  vector<vector<Cell>> getGrilleConst() const {
    return grille_;
  }
		
  Etat getEtat() const {
    return etat;
  }
		
  void setEtat(const Etat e = encours) {
    etat = e;
  }
  
  static bool isNotEqual(const Jeu& lhs, const Jeu& rhs) {
    if(lhs.getGrilleConst().empty() || rhs.getGrilleConst().empty())
      return true;
    
    if(lhs.getEtat() != rhs.getEtat())
      return true;

    for(size_t i = 0; i < lhs.getGrilleConst().size(); i++)
      for(size_t j = 0; j < lhs.getGrilleConst()[i].size(); j++)
	if(Cell::isNotEqual(lhs.getCell(i,j), rhs.getCell(i,j)))
	  return true;

    return false;
  }
};
