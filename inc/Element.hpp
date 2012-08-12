#ifndef Element_HPP
#define Element_HPP
/// En-Têtes.
// STL.
#include <unordered_map>
// SFML.
#include <SFML/System.hpp>
// Thor.
#include <Thor/Animation.hpp>
// Projet.
#include "Types.hpp"

class Element
{
/// Interface.
public:
	Element( ptrImage p_image, const sf::Vector2f& p_position = sf::Vector2f( 0.0f,0.0f ) );

	virtual sf::Vector2f position() const;
	virtual void position( sf::Vector2f p_position );
	virtual void deplacer( float p_x, float p_y );
	
	sf::IntRect rectangleTexture() const;
	void rectangleTexture( sf::IntRect p_rectangle );
	
	sf::Sprite& sprite();
	sf::RectangleShape& aabb();
	void chargerAnimations( std::string p_fichier );
	void ajouterAnimation( std::string p_nom, thor::FrameAnimation, float p_duree );
	void ajouterAnimation( std::string p_nom, float p_duree );
	void ajouterPose( std::string p_animation, sf::IntRect p_rectangle, float p_dureeRelative = 1.0f );
	
//	void maj( sf::Time p_duree );
	void animer( sf::Time p_duree );
	
	void animationDefaut( std::string p_nom, float p_duree );
	void jouerAnimation( std::string p_nom, bool p_enBoucle );
	void arreterAnimation();
	
    virtual void maj();
	virtual void dessiner( sf::RenderWindow& p_fenetre );
/// Implémntation.
protected:
	sf::Texture m_texture;
	sf::Sprite  m_sprite;
	
	sf::Vector2f m_position;
	
	thor::Animator<sf::Sprite, std::string> m_animator;
	std::unordered_map< std::string, thor::FrameAnimation > m_animations;
	
	// Box2D.
    sf::RectangleShape m_aabb;
    
    
};

typedef std::shared_ptr< Element > ptrElement;
#endif// Fin Element_HPP.