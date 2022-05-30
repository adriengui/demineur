#include <iostream>
#include <vector>

#include "Vue.hpp"
#include "Controleur.hpp"

using namespace std;

Vue::Vue() : appli(1,2), fenetre(2,1), grille(2,2), menu(7,1), info(""), chronomsg(""), titreScores("Meilleurs scores :\n"), scores("") {
		
	resize(600,600);
	set_title("Demineur");
	set_icon_from_file("bombe.png");
	set_position(Gtk::WIN_POS_CENTER);
				
	boutons_accueil.push_back(Gtk::Button("8x8"));
	boutons_accueil.push_back(Gtk::Button("16x16"));
	boutons_accueil.push_back(Gtk::Button("30x16"));
	
	for(int x=0;x<3;x++)
		boutons_accueil[x].set_can_focus(false);
	
	onAccueil=false;
	start=false;
	afficheAccueil();
	onAccueil=true;
	start=true;
	
	boutons_menu.push_back(Gtk::Button("Accueil"));
	boutons_menu.push_back(Gtk::Button("Quitter"));
	boutons_menu.push_back(Gtk::Button("Undo"));
	boutons_menu.push_back(Gtk::Button("Redo"));
	
	for(int x=0;x<4;x++) {
		boutons_menu[x].set_can_focus(false);
		boutons_menu[x].set_size_request(50,50);
	}
	/*string t;
	for(int x=1;x<=10;x++)
		t+=to_string(x)+" :\n";
	scores.set_text(t);*/
		
	menu.attach(boutons_menu[0], 0,1,0,1);
	menu.attach(chronomsg, 0,1,3,4);
	// menu.attach(titreScores, 0,1,2,3);
	// menu.attach(scores, 0,1,3,4);
	menu.attach(boutons_menu[1], 0,1,6,7);
			
	fenetre.attach(grille, 0,1,0,1);
	fenetre.attach(info, 0,1,1,2);
	appli.attach(fenetre, 0,1,0,1);
	appli.attach(menu, 1,2,0,1);
	
	add(appli);
		
	
		
	show_all();
	
}

Vue::~Vue() { }

void Vue::update(Jeu g) {
	switch(g.getGrilleTime()) {
		case 0:
			fillGrille(g);
			
			break;
		case 1:
			afficheTime(g);
			break;
		}
}

void Vue::afficheAccueil() {
	
	if(!onAccueil) {
		
		onAccueil=true;
		resize(600,600);
		
		grille.resize(2,2);
		for(auto &x:boutons_grille)
			grille.remove(x);
		for(auto &x:boutons_accueil)
			grille.remove(x);
		
		if(start) {	
			for(int x=2;x<=3;x++)
				menu.remove(boutons_menu[x]);
							
			menu.remove(titreScores);
			menu.remove(scores);
		}
		
		grille.attach(boutons_accueil[0], 0,1,0,1);
		grille.attach(boutons_accueil[1], 1,2,0,1);
		grille.attach(boutons_accueil[2], 0,1,1,2);
		
		info.set_text("");
		chronomsg.set_text("");
		
		show_all();
		
	}
	
}

void Vue::afficheJeu(Controleur *c, int m, int n) {
	onAccueil=false;
	boutons_grille.clear();
	grille.resize(m, n);
	
	menu.attach(boutons_menu[2], 0,1,1,2);
	menu.attach(boutons_menu[3], 0,1,2,3);
	menu.attach(titreScores, 0,1,4,5);
	menu.attach(scores, 0,1,5,6);
	
	for(auto &x:boutons_accueil)
		grille.remove(x);
	for(int x=0;x<m;x++) {
		for(int y=0;y<n;y++) {
			boutons_grille.push_back(Gtk::Button());				
			boutons_grille[x*n+y].set_can_focus(false);
			boutons_grille[x*n+y].set_relief(Gtk::RELIEF_NORMAL);
			boutons_grille[x*n+y].set_size_request(50,50);
			addOpenListener(c,m,n,x,y);
			addFlagListener(c,n,x,y);
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
	case encours:
		info.set_text("");
		break;
	case victoire:
		info.set_text("GAGNE !");
		break;
	case perdu:
		info.set_text("PERDU !");
		break;
	}
	for(int x=0;x<l;x++) {
		for(int y=0;y<c;y++) {
			auto& bouton = boutons_grille[x*c+y];
			Cell cell = g.getCell(x,y);
			if(cell.getOpen()) {
				boutons_grille[x*c+y].set_relief(Gtk::RELIEF_NONE);
				int n=cell.getNb();
				if(n!=0) {
					if(n!=-1) {
						bouton.set_image(flagImage = Gtk::Image());
						// bouton.set_relief(Gtk::RELIEF_NORMAL);
						bouton.set_label(to_string(n));
					} else {
						bouton.set_always_show_image();
						
						bouton.set_image(bombeImage = Gtk::Image("bombe.png"));
					}
				}
			} else if(cell.getState() == flag) {
				bouton.set_always_show_image();
				
				bouton.set_image(flagImage = Gtk::Image("flag.png"));
			} else {
					bouton.set_image(flagImage = Gtk::Image());
					bouton.set_relief(Gtk::RELIEF_NORMAL);
					bouton.set_label("");
				}
			}
		}
	show_all();
}

void Vue::afficheTime(Jeu g) {
	int m=g.getMinutes(), s=g.getSecondes();
	string t;
	if(m<10)
		t+="0";
	t+=to_string(m)+":";
	if(s<10)
		t+="0";
	t+=to_string(s);
	chronomsg.set_text(t);
}

void Vue::addAccueilListener(Controleur *c) {
	boutons_menu[0].signal_clicked().connect(sigc::mem_fun(*c, &Controleur::on_button_accueil));
}

void Vue::addExitListener(Controleur *c) {
	boutons_menu[1].signal_clicked().connect(sigc::mem_fun(*c, &Controleur::on_button_exit));
}

void Vue::addUndoListener(Controleur* c) {
	boutons_menu[2].signal_clicked().connect([c](){ c->on_button_undo(); });
}

void Vue::addRedoListener(Controleur* c) {
	boutons_menu[3].signal_clicked().connect([c](){ c->on_button_redo(); });
}

void Vue::addDimensionListener(Controleur *c, int x) {
	boutons_accueil[x].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*c, &Controleur::on_button_dimension),x));
}

void Vue::addOpenListener(Controleur *c, int m, int n, int x, int y) {
	boutons_grille[x*n+y].signal_clicked().connect(sigc::bind<int, int>(sigc::mem_fun(*c, &Controleur::on_button_open),x,y));
}

bool Vue::onSetFlag(Controleur* c, GdkEventButton* event, int x, int y) {
	if(event->type != GDK_BUTTON_PRESS) //return if not mouse button press
		return false;
  
	if(event->button != 3) //return if not right click
		return false;

	return c->on_set_flag(x, y);
}

void Vue::addFlagListener(Controleur* c, int n, int x, int y) {
	boutons_grille[x*n+y].signal_button_press_event().connect([this,x,y,c](GdkEventButton* event) { return this->onSetFlag(c,event,x,y); });
}

void Vue::on_button_accueil() {
	afficheAccueil();
}

void Vue::on_button_exit() {
	hide();
}
