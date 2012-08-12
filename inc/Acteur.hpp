#ifndef Acteur_HPP
#define Acteur_HPP
/// En-Têtes.
// STL.
#include <unordered_map>
// LCDB.
#include "Element.hpp"
// Projet.
#include "Types.hpp"

class Acteur : public Element
{
/// Interface.
public:
	Acteur( ptrImage p_image, const sf::Vector2f& p_position = sf::Vector2f( 0.0f,0.0f ) );

};

typedef std::shared_ptr< Acteur > ptrActeur;
#endif// Fin Acteur_HPP.