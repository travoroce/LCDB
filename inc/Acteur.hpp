#ifndef Acteur_HPP
#define Acteur_HPP
/// En-T�tes.
// STL.
#include <unordered_map>
// SFML.
#include <SFML/System.hpp>
// Thor.
#include <Thor/Animation.hpp>
// Box2D.
#include <Box2D/Box2D.h>
// Projet.
#include "Types.hpp"

class Acteur
{
/// Interface.
public:
	Acteur( ptrImage p_image );

	sf::Vector2f position() const;
	void position( sf::Vector2f p_position );
	void deplacer( float p_x, float p_y );
	
	sf::IntRect rectangleTexture() const;
	void rectangleTexture( sf::IntRect p_rectangle );
	
	sf::Sprite& sprite();
	
	void chargerAnimations( std::string p_fichier );
	void ajouterAnimation( std::string p_nom, thor::FrameAnimation, float p_duree );
	void ajouterAnimation( std::string p_nom, float p_duree );
	void ajouterPose( std::string p_animation, sf::IntRect p_rectangle, float p_dureeRelative = 1.0f );
	
//	void maj( sf::Time p_duree );
	void animer( sf::Time p_duree );
	
	void animationDefaut( std::string p_nom, float p_duree );
	void jouerAnimation( std::string p_nom, bool p_enBoucle );
	void arreterAnimation();
	
    void maj();
	
/// Impl�mntation.
protected:
	sf::Texture m_texture;
	sf::Sprite  m_sprite;
	
	thor::Animator<sf::Sprite, std::string> m_animator;
	std::unordered_map< std::string, thor::FrameAnimation > m_animations;
	
	// Box2D.
    b2BodyDef       m_bodyDef; 
    b2PolygonShape  m_dynamicBox; 
    b2FixtureDef    m_fixtureDef; 
};

typedef std::shared_ptr< Acteur > ptrActeur;
#endif// Fin Acteur_HPP.