#ifndef Acteur_HPP
#define Acteur_HPP
/// En-Têtes.
// STL.
#include <unordered_map>
// SFML.
#include <SFML/System.hpp>
// Thor.
#include <Thor/Animation.hpp>
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
	
	
/// Implémntation.
protected:
	sf::Texture m_texture;
	sf::Sprite  m_sprite;
	
	thor::Animator<sf::Sprite, std::string> m_animator;
	std::unordered_map< std::string, thor::FrameAnimation > m_animations;
	
	
};
#endif// Fin Acteur_HPP.