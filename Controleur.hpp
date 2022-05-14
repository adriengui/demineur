#pragma once

#include <string>
#include <iostream>

#include <gtkmm/button.h>
#include <gtkmm/main.h>
#include <gtkmm/table.h>
#include <gtkmm/window.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>

#include <vector>

#include "Modele.hpp"
#include "Vue.hpp"

using namespace std;

class Controleur {
	private :
		Modele *modele_;
		Vue *vue_;
		bool debut,end;
		int nbBombes_;
      
    public :
        Controleur(Modele *m, Vue *v) : modele_(m), vue_(v) {
			vue_->resize(600,600);
			vue_->set_title("Demineur");
			vue_->add(vue_->getAppliRef());
			
			vue_->getBoutonsAccueilRef().push_back(Gtk::Button("8x8"));
			vue_->getBoutonsAccueilRef().push_back(Gtk::Button("16x16"));
			vue_->getBoutonsAccueilRef().push_back(Gtk::Button("30x16"));
			for(int x=0;x<3;x++) {
				vue_->getBoutonsAccueilRef()[x].set_can_focus(false);
				vue_->getBoutonsAccueilRef()[x].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &Controleur::genere),x));
			}
			
			afficheAccueil();
			
			vue_->getFenetreRef().attach(vue_->getGrilleRef(), 0,1,0,1);
			vue_->getFenetreRef().attach(vue_->getInfoRef(), 0,1,1,2);
			
			vue_->getAppliRef().attach(vue_->getFenetreRef(), 0,1,0,1);
			
			
			vue_->getBoutonsMenuRef().push_back(Gtk::Button("Accueil"));
			vue_->getBoutonsMenuRef().push_back(Gtk::Button("Quitter"));
					
			
			vue_->getBoutonsMenuRef()[0].signal_clicked().connect(sigc::mem_fun(*this, &Controleur::afficheAccueil));
			vue_->getBoutonsMenuRef()[1].signal_clicked().connect([]() { Gtk::Main::quit(); });

			for(auto &x:vue_->getBoutonsMenuRef())
				vue_->getMenuRef().pack_start(x);
			
			vue_->getAppliRef().attach(vue_->getMenuRef(), 1,2,0,1);//, Gtk::SHRINK, Gtk::SHRINK);
			
			vue_->show_all();
		}
		
		void afficheAccueil() {
			
			vue_->getGrilleRef().resize(2,2);
			for(auto &x:vue_->getBoutonsGrilleRef())
				vue_->getGrilleRef().remove(x);
			for(auto &x:vue_->getBoutonsAccueilRef())
				vue_->getGrilleRef().remove(x);
				
			vue_->getGrilleRef().attach(vue_->getBoutonsAccueilRef()[0], 0,1,0,1);
			vue_->getGrilleRef().attach(vue_->getBoutonsAccueilRef()[1], 1,2,0,1);
			vue_->getGrilleRef().attach(vue_->getBoutonsAccueilRef()[2], 0,1,1,2);
			
			vue_->getInfoRef().set_text("");
			
			vue_->show_all();
		}
		
		void afficheJeu() {
			
			vue_->getBoutonsGrilleRef().clear();
			vue_->getGrilleRef().resize(modele_->getLignes(),modele_->getColonnes());
			for(auto &x:vue_->getBoutonsAccueilRef())
				vue_->getGrilleRef().remove(x);
			for(int x=0;x<modele_->getLignes();x++) {
				for(int y=0;y<modele_->getColonnes();y++) {
					vue_->getBoutonsGrilleRef().push_back(Gtk::Button(""));				
					vue_->getBoutonsGrilleRef()[x*modele_->getColonnes()+y].set_can_focus(false);
					vue_->getBoutonsGrilleRef()[x*modele_->getColonnes()+y].set_relief(Gtk::RELIEF_NORMAL);
					vue_->getBoutonsGrilleRef()[x*modele_->getColonnes()+y].signal_clicked().connect(sigc::bind<int, int>(sigc::mem_fun(*this, &Controleur::open),x,y));
				}
			}
			for(int x=0;x<modele_->getLignes();x++) {
				for(int y=0;y<modele_->getColonnes();y++) {
					vue_->getGrilleRef().attach(vue_->getBoutonsGrilleRef()[x*modele_->getColonnes()+y], y, y+1, x, x+1);
				}
			}
			
			vue_->show_all();
		}
		
		void genere(const int x) {
			debut=true;
			end=false;
			
			switch(x) {
				case 0:
					modele_->init(8,8);
					nbBombes_=10;
					break;
				case 1:
					modele_->init(16,16);
					nbBombes_=40;
					break;
				case 2:
					modele_->init(16,30);
					nbBombes_=99;
					break;
			}
			afficheJeu();
			
		}
		
		void open(const int x, const int y) {
			if(!end) {
				if(debut) {
					modele_->genererBombes(nbBombes_, x, y);
					modele_->calculerGrille();
					debut=false;
				}
				
				modele_->openCell(x,y);
				
				if(modele_->gagne()) {
					vue_->getInfoRef().set_text("GAGNE !");
					modele_->openAll();
					end=true;
				} else if(modele_->getCellRef(x,y).isBombe()) {
					vue_->getInfoRef().set_text("PERDU !");
					modele_->openAll();
					end=true;
				}
				
				fillGrille();
			}
		}
        
       void fillGrille() {
		   int l=modele_->getLignes(),c=modele_->getColonnes();
		   for(int x=0;x<l;x++) {
			   for(int y=0;y<c;y++) {
				   if(modele_->getCell(x,y).getOpen()) {
					   vue_->getBoutonsGrilleRef()[x*c+y].set_relief(Gtk::RELIEF_NONE);
					int n=modele_->getCell(x,y).getNb();
					if(n!=0) {
						if(n!=-1)
							vue_->getBoutonsGrilleRef()[x*c+y].set_label(to_string(n));
						else
							vue_->getBoutonsGrilleRef()[x*c+y].set_label("B");
					}
				   }
				   
			   }
		   }
	   }		
    
    
};

//#endif
