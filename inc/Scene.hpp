#ifndef Scene_HPP
#define Scene_HPP
/// En-T�tes.
// std.
#include <unordered_map>
#include <string>
// SFML.
#include <SFML/Graphics.hpp>
// Projet.
#include "Types.hpp"

class Scene
{
/// Interface.
public:


// M�thodes.
	void creerImage( std::string p_nom, std::string p_fichier );
	ptrImage image( std::string p_nom );
/// Impl�mentation.
protected:
	std::unordered_map< std::string, ptrImage > m_images;

};
#endif// Fin Scene_HPP.