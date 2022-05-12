#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

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
		
		void genererBombes(const int nbBombes) {
			srand(time(nullptr));
			// vector<pair<int,int>> b = {{0,2},{1,1},{2,0},{0,6},{3,5},{5,5},{5,8},{6,1},{6,2},{7,1}};
			while(getNbBombes()!=nbBombes)
//			for(const auto& x : b)
				getCellRef(rand()%nbLignes_, rand()%nbColonnes_).setBombe();
		  }
		
		void init(const int nbL, const int nbC, const int nbBombes) {
			nbLignes_=nbL;
			nbColonnes_=nbC;
			nbElems_=nbL*nbC;
			grille_.resize(nbElems_);
			
			for(auto &x:grille_)
				x.init();
			// toStringBis();
			genererBombes(nbBombes);
			calculerGrille();
			// toStringBis();
		  }

		void openCell(const int i, const int j) {
			Cell cell=getCell(i,j);
			// cout << 5 << endl;
			if(!cell.isBombe() && !cell.getOpen()){
				getCellRef(i,j).setOpen(true);
				// cout << "a" << endl;
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
					getCellRef(i,j).setOpen(true);
		}
		
		int getLignes() const {
			return nbLignes_;
		  }

		  int getColonnes() const {
			return nbColonnes_;
		  }
};
