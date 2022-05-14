//#ifndef DEF_FENETRE
//#define DEF_FENETRE

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

using namespace std;

class Vue : public Gtk::Window {
	private :
		Gtk::Table appli, grille,fenetre;
		Gtk::VButtonBox menu;
		vector<Gtk::Button> boutons_accueil, boutons_grille, boutons_menu;
		Gtk::Label info;
      
    public :
        Vue() : appli(1,2), fenetre(2,1) { 
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
		  
		  const Gtk::Table& getFenetre() const {
			return fenetre;
		  }
		  
		   Gtk::Table& getFenetreRef() {
			return fenetre;
		  }
		  
		  const Gtk::VButtonBox& getMenu() const {
			return menu;
		  }
		  
		   Gtk::VButtonBox& getMenuRef() {
			return menu;
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
		  
		  const vector<Gtk::Button>& getBoutonsMenu() const {
			return boutons_menu;
		  }
		  
		vector<Gtk::Button>& getBoutonsMenuRef() {
			return boutons_menu;
		  }   
		  
		  const Gtk::Label& getInfo() const {
			return info;
		  }
		  
		Gtk::Label& getInfoRef() {
			return info;
		  }  
    
};

//#endif
