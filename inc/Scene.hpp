#ifndef Scene_HPP
#define Scene_HPP
/// En-Têtes.
// std.
#include <unordered_map>
#include <string>
// SFML.
#include <SFML/Graphics.hpp>
// Box2D.
#include <Box2D/Box2D.h>
// LCDB.
#include "Types.hpp"
#include "Acteur.hpp"


class Scene
{
/// Interface.
public:
// Constructeurs.
    Scene( b2Vec2 p_gravite );

// Méthodes.
    // Images.
	ptrImage creerImage( std::string p_nom, std::string p_fichier );
	ptrImage image( std::string p_nom );
    // Acteurs.
    ptrActeur creerActeur( std::string p_nom, std::string p_image, sf::Vector2f p_position ); 
	ptrActeur acteur( std::string p_nom ) const;
    
    void step();
    void dessiner( sf::RenderWindow& p_fenetre );
    const b2Body* corps() const;
    
/// Implémentation.
protected:
	std::unordered_map< std::string, ptrImage > m_images;
	std::unordered_map< std::string, ptrActeur > m_acteurs;

    // Box2D.   
	b2World m_world;
    	
    float32 m_timeStep;
    int32 m_velocityIterations; 
    int32 m_positionIterations; 
                                                                                                                                          
	b2PolygonShape  m_groundBox; 
	b2Body*         m_groundBody;
    
    sf::RectangleShape m_aabb;
};


typedef std::shared_ptr< Scene > ptrScene;
#endif// Fin Scene_HPP.