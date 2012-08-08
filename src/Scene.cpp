#include "Scene.hpp"
Scene::Scene( b2Vec2 p_gravite )
    : m_world( p_gravite )
    , m_timeStep( 1.0f / 60.0f )
    , m_velocityIterations( 8 )
    , m_positionIterations( 3 )
    , m_groundBox()
    , m_groundBody( nullptr )
    , m_aabb( sf::Vector2f(1.0f, 1.0f) )
    {
    
        b2BodyDef groundBodyDef;  
            groundBodyDef.position.Set(0.0f, -10.0f);
            groundBodyDef.allowSleep = false; 
            groundBodyDef.awake = true;
        m_groundBody = m_world.CreateBody(&groundBodyDef);
        m_groundBox.SetAsBox(50.0f, 10.0f);
        m_groundBody->CreateFixture(&m_groundBox, 0.0f);
        
        
        m_aabb.setSize( sf::Vector2f( PixelParMetres(50.0f), 10.0f ) );
        m_aabb.setFillColor( sf::Color::Transparent );
        m_aabb.setOutlineColor( sf::Color::Green );
        m_aabb.setOutlineThickness( 2.0f );
        m_aabb.setPosition( sf::Vector2f(0.0f, 400-m_aabb.getSize().y+PixelParMetres(10.0f)) );
    }

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
                m_acteurs[ p_nom ] = std::shared_ptr< Acteur >( new Acteur( this->image( p_texture ), m_world, b2Vec2(p_position.x,p_position.y) ) );
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
        //m_world.Step( m_timeStep/10000, m_velocityIterations, m_positionIterations ); 

        for ( auto acteur : m_acteurs )
        {
            acteur.second->maj();
        }
    }
    

void Scene::dessiner( sf::RenderWindow& p_fenetre )
    {
		p_fenetre.clear(sf::Color(50, 50, 50));
		//p_fenetre.draw( instructions );
		//p_fenetre.draw( bidule.sprite() );
		//p_fenetre.draw( bidule2.sprite() );
        
        p_fenetre.draw( m_aabb );
        
        for ( auto acteur : m_acteurs )
        {
            acteur.second->dessiner( p_fenetre );
            //p_fenetre.draw( acteur.second->sprite() );
        }
        
    }
const b2Body* Scene::corps() const
    {
        return m_groundBody;
    }