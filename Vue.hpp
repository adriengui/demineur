//#ifndef DEF_FENETRE
//#define DEF_FENETRE

#pragma once

#include <string>
#include <iostream>

#include <gtkmm/button.h>
#include <gtkmm/main.h>
#include <gtkmm/table.h>
#include <gtkmm/window.h>
#include <vector>

using namespace std;

class Vue : public Gtk::Window {
	private :
		Gtk::Table appli, grille;
		vector<Gtk::Button> boutons_accueil, boutons_grille;
		Gtk::Button bouton_retour;
      //  Gtk::Button bouton1, bouton2;
      
    public :
        Vue() : appli(1,2) { 
			//int l=4,c=4;
			// Gtk::Table tableau(l, c);
			/*add(tableau);
			
			
			for(int x=0;x<l*c;x++) {
				boutons.push_back(Gtk::Button(""));
				
				boutons[x].set_can_focus(false);
				boutons[x].set_relief(Gtk::RELIEF_NORMAL);
				// boutons[x].signal_clicked().connect(sigc::mem_fun(*this, &Vue::vider));
				
			}
			
			for(int x=0;x<l;x++) {
				for(int y=0;y<c;y++) {
					tableau.attach(boutons[x*c+y], y, y+1, x, x+1);
				}
			}
			
			show_all();	*/
		}
		
		const Gtk::Table& getAppli() const {
			return appli;
		  }
		  
		   Gtk::Table& getAppliRef() {
			return appli;
		  }
		
		const Gtk::Table& getGrille() const {
			return grille;
		  }
		  
		   Gtk::Table& getGrilleRef() {
			return grille;
		  }
		  
		  const vector<Gtk::Button>& getBoutonsAccueil() const {
			return boutons_accueil;
		  }
		  
		vector<Gtk::Button>& getBoutonsAccueilRef() {
			return boutons_accueil;
		  }
		
		const vector<Gtk::Button>& getBoutonsGrille() const {
			return boutons_grille;
		  }
		  
		vector<Gtk::Button>& getBoutonsGrilleRef() {
			return boutons_grille;
		  }
		  
		  const Gtk::Button& getBoutonRetour() const {
			return bouton_retour;
		  }
		  
		Gtk::Button& getBoutonRetourRef() {
			return bouton_retour;
		  }
    
    
};

//#endif
