#include "Scene.hpp"
#include <iostream>


Scene::Scene()
    {}

ptrImage Scene::creerImage( std::string p_nom, std::string p_fichier )
	{
		if ( m_images.find( p_nom ) == m_images.end() )
		{
			m_images[ p_nom ] = std::shared_ptr< sf::Image >( new sf::Image() );
				m_images[ p_nom ]->loadFromFile( p_fichier );
            return m_images[ p_nom ];
		}
        return nullptr;
	}
	
ptrImage Scene::image( std::string p_nom )
	{
		if ( m_images.find( p_nom ) != m_images.end() )
		{
			return m_images[ p_nom ];
		}
        return nullptr;
	}
	

ptrActeur Scene::creerActeur( std::string p_nom, std::string p_texture, sf::Vector2f p_position )
	{
		if ( m_acteurs.find( p_nom ) == m_acteurs.end() )
		{
            if ( this->image( p_texture ) )
            {
                m_acteurs[ p_nom ] = std::shared_ptr< Acteur >( new Acteur( this->image( p_texture ), p_position ) );
                return m_acteurs[ p_nom ];
            }
		}
        return nullptr;
	}
	
ptrActeur Scene::acteur( std::string p_nom ) const
	{
		if ( m_acteurs.find( p_nom ) != m_acteurs.end() )
		{
			return  m_acteurs.find( p_nom )->second;
		}
        return nullptr;
	}
	
void Scene::step()
    {
		this->testCollisions();
		this->effectuerCollision();
		
        for ( auto acteur : m_acteurs )
        {
            acteur.second->maj();
        }
    }
    
void Scene::testCollisions()
	{
        for ( auto acteur : m_acteurs )
        {
            std::string acteur_nom = acteur.first;
			acteur.second->aabb().setOutlineColor( sf::Color::Blue );
			sf::FloatRect acteur_aabb = acteur.second->aabb().getGlobalBounds();
			
			for ( auto acteur2 : m_acteurs )
			{
				std::string acteur2_nom = acteur2.first;
				
				if ( acteur_nom != acteur2_nom )
				{
						
					sf::FloatRect acteur2_aabb = acteur2.second->aabb().getGlobalBounds();
					if( acteur_aabb.intersects( acteur2_aabb ) )
					{
						m_contacts[ acteur_nom ].insert( acteur2_nom );
						acteur.second->aabb().setOutlineColor( sf::Color::Red );
					}
				}
			}
        }	
	}
	
void Scene::effectuerCollision()
	{
		for ( auto acteur1 : m_acteurs )
		{
			ptrActeur acteur1_ptr = acteur1.second;
			std::string acteur1_nom = acteur1.first;
		
			if ( m_contacts.find( acteur1_nom ) != m_contacts.end() )
			{
				for ( auto acteur2_nom : m_contacts[ acteur1_nom ] )
				{
					if ( m_acteurs.find( acteur2_nom ) != m_acteurs.end() )
					{
						ptrActeur acteur2_ptr = m_acteurs.find( acteur2_nom )->second;
						
						
						
					}
				}
			}
		}
	}
	
void Scene::dessiner( sf::RenderWindow& p_fenetre )
    {
		p_fenetre.clear(sf::Color(50, 50, 50));
		//p_fenetre.draw( instructions );
		//p_fenetre.draw( bidule.sprite() );
		//p_fenetre.draw( bidule2.sprite() );
                
        for ( auto acteur : m_acteurs )
        {
            acteur.second->dessiner( p_fenetre );
            //p_fenetre.draw( acteur.second->sprite() );
        }
        
    }