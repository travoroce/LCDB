#include "Scene.hpp"

void Scene::creerImage( std::string p_nom, std::string p_fichier )
	{
		if ( m_images.find( p_nom ) == m_images.end() )
		{
			m_images[ p_nom ] = std::shared_ptr< sf::Image >( new sf::Image() );
				m_images[ p_nom ]->loadFromFile( p_fichier );
		}
	}
	
ptrImage Scene::image( std::string p_nom )
	{
		if ( m_images.find( p_nom ) != m_images.end() )
		{
			return m_images[ p_nom ];
		}
	}
	
