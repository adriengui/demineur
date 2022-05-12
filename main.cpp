#include <gtkmm/main.h>

#include "Modele.hpp"
#include "Vue.hpp"
#include "Controleur.hpp"

int main(int argc, char* argv[]) {
	// const int l=9, c=9;
    Gtk::Main app(argc, argv);
    Vue *vue=new Vue;
    Modele *modele=new Modele;
    // modele->init();
    Controleur(modele,vue);
    
    /*modele->openCell(3,2);
    controleur->fillGrille();
    */
    Gtk::Main::run(*vue);
    return 0;
}
