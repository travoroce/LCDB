#include "Acteur.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Acteur::Acteur( ptrImage p_image )
	: m_texture()
	, m_sprite()
	{
		if ( m_texture.loadFromImage( *p_image ) )
		{
			m_sprite.setTexture( m_texture );
		}
	}
	
sf::Vector2f Acteur::position() const
	{
		return m_sprite.getPosition();
	}
void Acteur::position( sf::Vector2f p_position )
	{
		m_sprite.setPosition( p_position );
	}
		
void Acteur::deplacer( float p_x, float p_y )
	{
		m_sprite.move( p_x, p_y );
	}		
		
sf::IntRect Acteur::rectangleTexture() const
	{
		return m_sprite.getTextureRect();
	}
void Acteur::rectangleTexture( sf::IntRect p_rectangle )
	{
		m_sprite.setTextureRect( p_rectangle );
	}
	

sf::Sprite& Acteur::sprite()
	{
		return m_sprite;
	}
	
	
void Acteur::chargerAnimations( std::string p_fichier )
	{
		//std::string animation = "";
		bool image = false;
		float d = 0.0f;
		unsigned int x=0, y=0, l=0, h=0;
	
		std::ifstream fichier( p_fichier, std::ios::in );  // on ouvre le fichier en lecture
		std::string contenu;
		
        if(fichier)  // si l'ouverture a réussi
        { 
			std::string ligne;
			while( getline(fichier, ligne) )
			{
				contenu += ligne + '\n';
			}
			
			//std::cout << contenu << std::endl;
			
			
            // instructions
            fichier.close();  // on ferme le fichier
        }
		
		bool ok = true;
		std::size_t pos = 0;
		while ( contenu.find( "animation", pos ) != std::string::npos )
		{
			thor::FrameAnimation animation;
			
			std::string animationTexte 
				= contenu.substr( contenu.find( "animation", pos )
								, contenu.find( "finAnimation", pos )
									-contenu.find( "animation", pos ) );

			std::string anim_nom 
				= animationTexte.substr( animationTexte.find( "animation" )+10
									   , animationTexte.find( '\n' )
											-(animationTexte.find( "animation" )+10) );
			float anim_d;
			std::istringstream iss( animationTexte.substr( animationTexte.find( "d=" )+2
														 , animationTexte.find( '\n' )
															-(animationTexte.find( "d=" )+2)) );
			iss >> anim_d;

			std::size_t posImage = 0;
			while ( animationTexte.find( "image", posImage ) != std::string::npos )
			{
				std::string imageTexte = animationTexte.substr( animationTexte.find( "image", posImage ), animationTexte.find( "finImage", posImage )-animationTexte.find( "image", posImage ) );

				std::size_t posImage_d = imageTexte.find( "d=" )+2;
				std::size_t posImage_d_fin = imageTexte.find( "\n", posImage_d );
					std::istringstream iss_d( imageTexte.substr( posImage_d , posImage_d_fin-posImage_d) );
					iss_d >> d;
			
				std::size_t posImage_x = imageTexte.find( "x=" )+2;
				std::size_t posImage_x_fin = imageTexte.find( "\n", posImage_x );
					std::istringstream iss_x( imageTexte.substr( posImage_x , posImage_x_fin-posImage_x) );
					iss_x >> x;
			
				std::size_t posImage_y = imageTexte.find( "y=" )+2;
				std::size_t posImage_y_fin = imageTexte.find( "\n", posImage_y );
					std::istringstream iss_y( imageTexte.substr( posImage_y , posImage_y_fin-posImage_y) );
					iss_y >> y;
			
				std::size_t posImage_l = imageTexte.find( "l=" )+2;
				std::size_t posImage_l_fin = imageTexte.find( "\n", posImage_l );
					std::istringstream iss_l( imageTexte.substr( posImage_l , posImage_l_fin-posImage_l) );
					iss_l >> l;
			
				std::size_t posImage_h = imageTexte.find( "h=" )+2;
				std::size_t posImage_h_fin = imageTexte.find( "\n", posImage_h );
					std::istringstream iss_h( imageTexte.substr( posImage_h , posImage_h_fin-posImage_h) );
					iss_h >> h;
			
					
				animation.addFrame(d, sf::IntRect(x, y, l, h));
					
				posImage = animationTexte.find( "finImage", posImage )+8;
			}
			
			this->ajouterAnimation( anim_nom, animation, anim_d );
			pos = contenu.find( "finAnimation", pos )+12;
		}
	}

void Acteur::ajouterAnimation( std::string p_nom, thor::FrameAnimation p_animation, float p_duree )
	{
		if ( m_animations.find( p_nom ) == m_animations.end() )
		{
			m_animations[ p_nom ] = p_animation;
			m_animator.addAnimation( p_nom, m_animations.find( p_nom )->second, sf::seconds( p_duree ));
		}
	}
	
void Acteur::ajouterAnimation( std::string p_nom, float p_duree )
	{
		if ( m_animations.find( p_nom ) == m_animations.end() )
		{
			m_animations[ p_nom ] = thor::FrameAnimation();
			//m_animator.addAnimation( p_nom, m_animations.find( p_nom )->second, sf::seconds( p_duree ));
		}
	}

void Acteur::ajouterPose( std::string p_animation, sf::IntRect p_rectangle, float p_dureeRelative )
	{
		if ( m_animations.find( p_animation ) != m_animations.end() )
		{
			m_animations.find( p_animation )->second.addFrame( p_dureeRelative, p_rectangle );
		}
	}
			/*
void Acteur::maj( sf::Time p_duree )
	{
		m_animator.update( p_duree );
	}
	*/
void Acteur::animer( sf::Time p_duree )
	{
		m_animator.update( p_duree );
		m_animator.animate( m_sprite );
	}
	
void Acteur::animationDefaut( std::string p_nom, float p_duree )
	{
		if ( m_animations.find( p_nom ) != m_animations.end() )
		{
			m_animator.setDefaultAnimation( m_animations.find( p_nom )->second, sf::seconds(p_duree) );
		}
	}

void Acteur::jouerAnimation( std::string p_nom, bool p_enBoucle )
	{
		if ( m_animations.find( p_nom ) != m_animations.end() )
		{
			m_animator.playAnimation( p_nom, p_enBoucle );
		}
	}
	
void Acteur::arreterAnimation()
	{
		m_animator.stopAnimation();
	}