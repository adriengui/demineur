#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using State = enum {open = 0, closed, flag};

class Cell {
private:
  int nb;
  State state;
public:
  Cell(const int n=0, const State s = closed ) : nb(n), state(s) { }
		
  void init() {
    setNb();
    setState(closed);
  }
		
  void setNb(const int n=0) {
    nb=n;
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
    return getNb()==-1;
  }
		
  void setBombe() {
    setNb(-1);
  }
	
};

class Modele {
private:
  int nbLignes_;
  int nbColonnes_;
  int nbElems_;
  vector<Cell> grille_;
	
public :
  /*Modele(const int nbL, const int nbC) : nbLignes_(nbL), nbColonnes_(nbC), nbElems_(nbL*nbC) {
    grille_.resize(nbElems_);
    }*/
		
  Modele() { }
		
  const Cell& getCell(const int i, const int j) const {
    return grille_[i * nbColonnes_ + j];
  }
		  
  Cell& getCellRef(const int i, const int j) {
    return grille_[i * nbColonnes_ + j];
  }
		
  void toString() {
    Cell cell;
    for(int x=0;x<nbLignes_;x++) {
      for(int y=0;y<nbColonnes_;y++) {
	cell=getCell(x,y);
	if(cell.getOpen()) {
	  if(cell.isBombe())
	    cout << "B ";
	  else
	    cout << cell.getNb() << " ";
	}
	else
	  cout << "  ";
      }
      cout << endl;	
    }
    cout << endl;
  }
		
  void toStringBis() {
    Cell cell;
    for(int x=0;x<nbLignes_;x++) {
      for(int y=0;y<nbColonnes_;y++) {
	cell=getCell(x,y);
	cout << cell.getOpen() << " - " << cell.getNb() << "       ";
      }
      cout << endl;	
    }
    cout << endl;
  }

  void calculerGrille() {
    static int n;
    for(int l=0;l<nbLignes_;l++) {
      for(int c=0;c<nbColonnes_;c++) {
	if(!getCell(l,c).isBombe()) {
	  n=0;
	  for(int x=l-1;x<=l+1;x++) 
	    for(int y=c-1;y<=c+1;y++)
	      if(x>=0 && x<nbLignes_ && y>=0 && y<nbColonnes_ && !(x==l && y==c))
		if(getCell(x,y).isBombe())
		  n++;
					
	  getCellRef(l,c).setNb(n);
	}
      }
    }
  }
		
  int getNbBombes() {
    int n=0;
    for(int x=0;x<nbLignes_;x++)
      for(int y=0;y<nbColonnes_;y++)
	if(getCell(x,y).isBombe())
	  n++;
						
    return n;
  }
		
  bool in_entourage(const int ligne, const int colonne, const int a, const int b) {
    for(int x=ligne-1;x<=ligne+1;x++)
      for(int y=colonne-1;y<=colonne+1;y++)
	if(a==x && b==y)
	  return true;
    return false;
  }
		
  void genererBombes(const int nbBombes, const int ligne, const int colonne) {
    srand(time(nullptr));
    int a,b;
    // vector<pair<int,int>> b = {{0,2},{1,1},{2,0},{0,6},{3,5},{5,5},{5,8},{6,1},{6,2},{7,1}};
    while(getNbBombes()!=nbBombes) {
      //			for(const auto& x : b)
      a=rand()%nbLignes_;
      b=rand()%nbColonnes_;
      if(!in_entourage(ligne, colonne, a, b))
	getCellRef(a, b).setBombe();
    }
  }
		
  void init(const int nbL, const int nbC) {
    nbLignes_=nbL;
    nbColonnes_=nbC;
    nbElems_=nbL*nbC;
    grille_.resize(nbElems_);
			
    for(auto &x:grille_)
      x.init();
    // toStringBis();
    //genererBombes(nbBombes, ligne, colonne);
    //calculerGrille();
    // toStringBis();
  }

  void openCell(const int i, const int j) {
    Cell cell=getCell(i,j);
    if(!cell.isBombe() && !cell.getOpen()){
      getCellRef(i,j).setState(open);
      if(cell.getNb()==0) {
	for(int x=i-1;x<=i+1;x++)
	  for(int y=j-1;y<=j+1;y++)
	    if(x>=0 && x<nbLignes_ && y>=0 && y<nbColonnes_ && !(x==i && y==j))
	      openCell(x,y);
      }
    }
  }

  bool gagne() {
    Cell cell;
    for(int x=0;x<nbLignes_;x++) {
      for(int y=0;y<nbColonnes_;y++) {
	cell=getCell(x,y);
	if(!cell.isBombe() && !cell.getOpen())
	  return false;
      }
    }
    return true;
  }
		
  void openAll() {
    for(int i=0;i<nbLignes_;i++)
      for(int j=0;j<nbColonnes_;j++)
	getCellRef(i,j).setState(open);
  }
		
  int getLignes() const {
    return nbLignes_;
  }

  int getColonnes() const {
    return nbColonnes_;
  }
};
