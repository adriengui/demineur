#include <gtkmm/application.h>

#include "Modele.hpp"
#include "Vue.hpp"
#include "Controleur.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	
    auto app = Gtk::Application::create(argc, argv);
    
    Modele *modele=new Modele;
    Vue *vue=new Vue;
    Controleur(modele,vue);
    
    modele->addObserver(vue);
    
    return app->run(*vue);
}
