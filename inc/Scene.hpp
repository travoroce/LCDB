#ifndef Scene_HPP
#define Scene_HPP
/// En-Têtes.
// std.
#include <unordered_map>
#include <set>
#include <string>
// SFML.
#include <SFML/Graphics.hpp>
// LCDB.
#include "Types.hpp"
#include "Acteur.hpp"


class Scene
{
/// Interface.
public:
// Constructeurs.
    Scene();

// Méthodes.
    // Images.
	ptrImage creerImage( std::string p_nom, std::string p_fichier );
	ptrImage image( std::string p_nom );
    // Acteurs.
    ptrActeur creerActeur( std::string p_nom, std::string p_image, sf::Vector2f p_position ); 
	ptrActeur acteur( std::string p_nom ) const;
    
    void step();
	
	void testCollisions();
	void effectuerCollision();
	
    void dessiner( sf::RenderWindow& p_fenetre );
    
/// Implémentation.
protected:
	std::unordered_map< std::string, ptrImage > m_images;
	std::unordered_map< std::string, ptrActeur > m_acteurs;
	
	std::unordered_map< std::string, std::set< std::string > > m_contacts;
};


typedef std::shared_ptr< Scene > ptrScene;
#endif// Fin Scene_HPP.