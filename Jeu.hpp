#pragma once

#include <iostream>

#include "Cell.hpp"

using namespace std;

typedef enum {encours, victoire, perdu} Etat;

class Jeu {
	private:			
		vector<vector<Cell>> grille_;
		int minutes;
		int secondes;
		Etat etat;
		bool grilleTime;
		bool debut;
		bool fin;
	
	public:
		
		Jeu(const int m=0, const int s=0, const Etat e=encours, const bool g=0, const bool d=true, const bool f=false) : minutes(m), secondes(s), etat(e), grilleTime(g), debut(d), fin(f) { }
		
		void reset() {
			grille_.clear();
			etat = encours;
			debut = true;
			fin = false;
		}
		
		void setDebut(bool value) { 
			debut = value; 
		}
		
		void setFin(bool value) { 
			fin = value; 
		}
		
		bool getDebut() const { 
			return debut; 
		}
		
		bool getFin() const { 
			return fin; 
		}
		
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
		
		void setEtat(const Etat e=encours) {
			etat=e;
		}
		
		int getMinutes() const {
			return minutes;
		}
		
		void setMinutes(const int m=0) {
			minutes=m;
		}
		
		void incMinutes() {
			minutes++;
		}
		
		int getSecondes() const {
			return secondes;
		}
		
		void setSecondes(const int s=0) {
			secondes=s;
		}
		
		void incSecondes() {
			secondes++;
		}
		
		bool getGrilleTime() const {
			return grilleTime;
		}
		
		void setGrilleTime(const bool g=0) {
			grilleTime=g;
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
