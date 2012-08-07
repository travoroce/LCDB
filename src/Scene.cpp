#include "Scene.hpp"
Scene::Scene( b2Vec2 p_gravite )
    : m_world( p_gravite )
    , m_timeStep( 1.0f / 60.0f )
    , m_velocityIterations( 8 )
    , m_positionIterations( 3 )
    , m_groundBodyDef()
    , m_groundBox()
    , m_groundBody( world.CreateBody(&groundBodyDef) )
    {
        groundBodyDef.position.Set(0.0f, -10.0f);
        groundBox.SetAsBox(50.0f, 10.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

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
	

void Scene::creerActeur( std::string p_nom, std::string p_fichier )
	{
		if ( m_Acteurs.find( p_nom ) == m_Acteurs.end() )
		{
			m_Acteurs[ p_nom ] = std::shared_ptr< sf::Acteur >( new sf::Acteur() );
				m_Acteurs[ p_nom ]->loadFromFile( p_fichier );

            b2Body* body = world.CreateBody(&bodyDef); 
            bodyDef.type = b2_dynamicBody; 
            bodyDef.position.Set(0.0f, 25.0f); 	
		}
	}
	
ptrActeur Scene::Acteur( std::string p_nom )
	{
		if ( m_Acteurs.find( p_nom ) != m_Acteurs.end() )
		{
			return m_Acteurs[ p_nom ];
		}
	}
	
void Scene::step()
    {
        m_world.Step( m_timeStep, m_velocityIterations, m_positionIterations ); 

        for ( auto acteur : m_acteurs )
        {
            acteur.maj();
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
            p_fenetre.draw( acteur.sprite() );
        }
        
    }