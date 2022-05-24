#include <iostream>
#include <vector>

#include "Vue.hpp"
#include "Controleur.hpp"

using namespace std;

Vue::Vue() : appli(1,2), fenetre(2,1), grille(2,2), info("") {
		
	resize(600,600);
	set_title("Demineur");
				
	boutons_accueil.push_back(Gtk::Button("8x8"));
	boutons_accueil.push_back(Gtk::Button("16x16"));
	boutons_accueil.push_back(Gtk::Button("30x16"));
	
	for(int x=0;x<3;x++)
		boutons_accueil[x].set_can_focus(false);
				
	afficheAccueil();
	
	boutons_menu.push_back(Gtk::Button("Accueil"));
	boutons_menu.push_back(Gtk::Button("Quitter"));
	
	for(int x=0;x<2;x++)
		boutons_menu[x].set_can_focus(false);
	
	for(auto &x:boutons_menu)
		menu.pack_start(x);
			
	fenetre.attach(grille, 0,1,0,1);
	fenetre.attach(info, 0,1,1,2);
	appli.attach(fenetre, 0,1,0,1);
	appli.attach(menu, 1,2,0,1);
	
	add(appli);
		
	show_all();
}

Vue::~Vue() { } 

void Vue::update(Jeu g) {
	fillGrille(g);
}

void Vue::afficheAccueil() {
			
	grille.resize(2,2);
	for(auto &x:boutons_grille)
		grille.remove(x);
	for(auto &x:boutons_accueil)
		grille.remove(x);
		
	grille.attach(boutons_accueil[0], 0,1,0,1);
	grille.attach(boutons_accueil[1], 1,2,0,1);
	grille.attach(boutons_accueil[2], 0,1,1,2);
	
	info.set_text("");
	
	show_all();
}

void Vue::afficheJeu(Controleur *c, int m, int n) {
	
	boutons_grille.clear();
	grille.resize(m, n);
	for(auto &x:boutons_accueil)
		grille.remove(x);
	for(int x=0;x<m;x++) {
		for(int y=0;y<n;y++) {
			boutons_grille.push_back(Gtk::Button());				
			boutons_grille[x*n+y].set_can_focus(false);
			boutons_grille[x*n+y].set_relief(Gtk::RELIEF_NORMAL);
			addOpenListener(c,m,n,x,y);
		}
	}
	
	for(int x=0;x<m;x++)
		for(int y=0;y<n;y++) 
			grille.attach(boutons_grille[x*n+y], y, y+1, x, x+1);
	
	show_all();
}

void Vue::fillGrille(Jeu g) {
	int l=g.getGrille().size(),c=g.getGrille()[0].size();
	switch(g.getEtat()) {
	case 1:
		info.set_text("GAGNE !");
		break;
	case 2:
		info.set_text("PERDU !");
		break;
	}
	for(int x=0;x<l;x++) {
		for(int y=0;y<c;y++) {
			if(g.getCell(x,y).getOpen()) {
				boutons_grille[x*c+y].set_relief(Gtk::RELIEF_NONE);
				int n=g.getCell(x,y).getNb();
				if(n!=0) {
					if(n!=-1)
						boutons_grille[x*c+y].set_label(to_string(n));
					else {
						bombe = Gtk::manage(new Gtk::Image{"bombe.png"});
						boutons_grille[x*c+y].add(*bombe);
					}
				}
			}
		}
	}
	show_all();
}

void Vue::addAccueilListener(Controleur *c) {
	boutons_menu[0].signal_clicked().connect(sigc::mem_fun(*c, &Controleur::on_button_accueil));
}

void Vue::addExitListener(Controleur *c) {
	boutons_menu[1].signal_clicked().connect(sigc::mem_fun(*c, &Controleur::on_button_exit));
}

void Vue::addDimensionListener(Controleur *c, int x) {
	boutons_accueil[x].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*c, &Controleur::on_button_dimension),x));
}

void Vue::addOpenListener(Controleur *c, int m, int n, int x, int y) {
	boutons_grille[x*n+y].signal_clicked().connect(sigc::bind<int, int>(sigc::mem_fun(*c, &Controleur::on_button_open),x,y));
}

void Vue::on_button_accueil() {
	afficheAccueil();
}

void Vue::on_button_exit() {
	hide();
}
