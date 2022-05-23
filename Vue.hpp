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

#include "Observer.hpp"
#include "Cell.hpp"

class Controleur;

using namespace std;

class Vue : public Gtk::Window, public Observer<vector<vector<Cell>>> {
	private :
		Gtk::Table appli, fenetre, grille;
		Gtk::VButtonBox menu;
		vector<Gtk::Button> boutons_accueil, boutons_grille, boutons_menu;
		Gtk::Label info;
		
    public :
        Vue();
        virtual ~Vue();
		
		void update(vector<vector<Cell>> g) override;
		
		void afficheAccueil();
		void afficheJeu(Controleur *c, int x, int y);
		void fillGrille(vector<vector<Cell>> g);
		
		void addExitListener(Controleur *c);
		void addAccueilListener(Controleur *c);
		void addDimensionListener(Controleur *c, int x);
		void addOpenListener(Controleur *c, int m, int n, int x, int y);
		
		void on_button_exit();
		void on_button_accueil();
    
};
