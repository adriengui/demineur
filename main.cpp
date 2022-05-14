#include <gtkmm/main.h>

#include "Modele.hpp"
#include "Vue.hpp"
#include "Controleur.hpp"

int main(int argc, char* argv[]) {
	
    Gtk::Main app(argc, argv);
    Vue *vue=new Vue;
    Modele *modele=new Modele;
    Controleur(modele,vue);
    
    Gtk::Main::run(*vue);
    return 0;
}
