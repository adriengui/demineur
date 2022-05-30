#pragma once

#include <iostream>
#include <cstdlib>
#include <glibmm.h>

#include "Observable.hpp"
#include "Cell.hpp"
#include "Jeu.hpp"

using namespace std;

class Modele : public Observable<Jeu> {
private:
  int nbLignes_;
  int nbColonnes_;
  int nbElems_;
  int nbBombes_;
  bool accueil;
  sigc::connection timeoutConnection_;
  
  Jeu jeu, predJeu, nextJeu;
		
  void savePreviousCommand() override {
    if(Jeu::isNotEqual(predJeu, jeu))
      predJeu = jeu;
  }
	
public :
		
  Modele() : accueil(true) { }
		
  const Cell& getCell(const int i, const int j) const {
    return jeu.getCell(i,j);
  }
		  
  Cell& getCellRef(const int i, const int j) {
    return jeu.getCellRef(i,j);
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
			
    while(getNbBombes()!=nbBombes) {

      a=rand()%nbLignes_;
      b=rand()%nbColonnes_;
      if(!in_entourage(ligne, colonne, a, b))
	getCellRef(a, b).setBombe();
    }
  }
		
  bool computeTime() {
    if(!jeu.getFin() && !accueil) {
      if(jeu.getSecondes()==59) {
	jeu.setSecondes(0);
	jeu.incMinutes();
      }
      else
	jeu.incSecondes();
				
      jeu.setGrilleTime(true);
      notifyObservers(jeu);

      return true;
    }
    return false;
  }
		
  void setAccueil() {
    accueil=true;
    nextJeu = predJeu = Jeu();
  }
		
  void init(const int nbL, const int nbC, const int nbB) {
    jeu.reset();
    accueil=false;

    nbLignes_=nbL;
    nbColonnes_=nbC;
    nbElems_=nbL*nbC;
    nbBombes_=nbB;

    for(int x=0;x<nbLignes_;x++) {
      vector<Cell> a;
      for(int y=0;y<nbColonnes_;y++)
	a.push_back(Cell());
      jeu.getGrille().push_back(a);
    }
    jeu.setGrilleTime(true);
    notifyObservers(jeu);
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
		
  void saveScore() {
    
  }
		
  void processOpenCell(const int x, const int y) {
    Cell& cell = getCellRef(x,y);
    if(cell.getState() == flag || cell.getState() == open)
      return;

    if(!jeu.getFin()) {
      if(jeu.getDebut()) {
	genererBombes(nbBombes_, x, y);
	calculerGrille();
	jeu.setDebut(false);
	timeoutConnection_ = Glib::signal_timeout().connect([this] {return this->computeTime();}, 1000);
      }
			
      savePreviousCommand();
      openCell(x,y);
				
      if(gagne() || getCellRef(x,y).isBombe()) {
	if(gagne()) {
	  jeu.setEtat(victoire);
	  saveScore();
	}
	else
	  jeu.setEtat(perdu);
	openAll();
	jeu.setFin(true);
      }
				
      jeu.setGrilleTime(false);
      notifyObservers(jeu);
      clearRedo();
    }
  }
		
  bool processSetFlag(int x, int y) {
    savePreviousCommand();
    
    Cell& cell = getCellRef(x, y);
    switch(cell.getState()){
    case closed:
      cell.setState(flag);
      break;
    case flag:
      cell.setState(closed);
      break;
    default:
      return false;
    }
			
    jeu.setGrilleTime(false);
    notifyObservers(jeu);
    clearRedo();
    
    return true;
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

  void undo() {
    if(predJeu.getGrilleConst().empty())
      return;
    
    if(Jeu::isNotEqual(predJeu, jeu)) {
      nextJeu = jeu;
      if(jeu.getFin()){
	timeoutConnection_.disconnect();
	timeoutConnection_ = Glib::signal_timeout().connect([this] {return this->computeTime();}, 1000);
      }
      jeu = predJeu;
    }

    jeu.setGrilleTime(false);
    notifyObservers(jeu);
  }

  void redo() {
    if(nextJeu.getGrilleConst().empty())
      return;

    if(Jeu::isNotEqual(nextJeu, jeu)) {
      predJeu = jeu;
      jeu = nextJeu;
    }
    
    jeu.setGrilleTime(false);
    notifyObservers(jeu);
  }

  void clearRedo() {
    // Pour eviter un redo qui mettrait le jeu sous un ancien etat
    //  non valide
    nextJeu = jeu;
  }
		
  int getLignes() const {
    return nbLignes_;
  }

  int getColonnes() const {
    return nbColonnes_;
  }
};
