#pragma once

#include <iostream>

#include "Modele.hpp"
#include "Vue.hpp"

using namespace std;

class Controleur {
	private :
		Modele *modele_;
		Vue *vue_;
      
    public :
        Controleur(Modele *m, Vue *v) : modele_(m), vue_(v) {
			vue_->addAccueilListener(this);
			vue_->addExitListener(this);
			
			for(int x=0;x<3;x++)
				vue_->addDimensionListener(this, x);		
		}
		
		void on_button_exit() {
			vue_->on_button_exit();
		}
		
		void on_button_accueil() {
			vue_->on_button_accueil();
		}
		
		void on_button_open(int x, int y) {
			modele_->open(x, y);
		}
		
		void on_button_dimension(int x) {
			switch(x) {
				case 0:
					modele_->init(8,8,10);
					break;
				case 1:
					modele_->init(16,16,40);
					break;
				case 2:
					modele_->init(16,30,99);
					break;
			}
			vue_->afficheJeu(this, modele_->getLignes(), modele_->getColonnes());
			
		}
};
