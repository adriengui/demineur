#pragma once

#include <iostream>
#include <vector>

#include <gtkmm/button.h>
#include <gtkmm/main.h>
#include <gtkmm/table.h>
#include <gtkmm/window.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>

#include "Observer.hpp"
#include "Cell.hpp"
#include "Jeu.hpp"

class Controleur;

using namespace std;

class Vue : public Gtk::Window, public Observer<Jeu> {
	private :
		Gtk::Table appli, fenetre, grille;
		Gtk::Label info;
		Gtk::VButtonBox menu;
		vector<Gtk::Button> boutons_accueil, boutons_grille, boutons_menu;
		Gtk::Image* bombe;
		
    public :
        Vue();
        virtual ~Vue();
		
		void update(Jeu g) override;
		
		void afficheAccueil();
		void afficheJeu(Controleur *c, int x, int y);
		void fillGrille(Jeu g);
		
		void addAccueilListener(Controleur *c);
		void addExitListener(Controleur *c);
		void addDimensionListener(Controleur *c, int x);
		void addOpenListener(Controleur *c, int m, int n, int x, int y);
		
		void on_button_accueil();
		void on_button_exit();
    
};
