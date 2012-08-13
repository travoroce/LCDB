////////////////
/// En-têtes.
// systeme.
#include <iostream>
#include <sstream>
#include <unordered_map>
// Thor.
#include <Thor/Animation.hpp>
// SFML.
#include <SFML/Graphics.hpp>
// Projet.
#include "Types.hpp"
#include "Scene.hpp"
#include "Acteur.hpp"


int main()
{

    
	sf::RenderWindow window(sf::VideoMode(600, 400), "FPS: 0");

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	// Instruction text
	sf::Font font;
	//	font.loadFromFile( "res/UnZialish.ttf" );
		font.loadFromFile( "res/ProFontWindows.ttf" );
	//	font.loadFromFile( "res/profont-x11/ProFont_r400-29.pcf" );
		
	std::string	texteInstruction = "Droite/Gauche:  Marche droite/gauche\n"
								   "Bas: s'accroupir\n"
								   "Echap:  Quit";
	sf::Text instructions( texteInstruction, font, 30);
		instructions.setColor( sf::Color::Red );
        instructions.setCharacterSize(12);

	/// Bidule.
    // Image.
	Scene scene;
		scene.creerImage( "bidule_image", "res/bidule2.png" );
	
	ptrActeur bidule = scene.creerActeur( "bidule", "bidule_image", sf::Vector2f( 100.0f, 400.0f ) );
		//bidule->deplacer( 150.f-32.f, 200.f-128.f );
		bidule->chargerAnimations( "res/bidule2.anim" );
		//bidule->chargerAnimations( "res/bidule_pinceau.anim" );
		bidule->animationDefaut( "PoseD", 1.0f );
		
	ptrActeur bidule2 = scene.creerActeur( "bidule2", "bidule_image", sf::Vector2f( 250.0f, 400.0f ) );
		//bidule->deplacer( 150.f-32.f, 200.f-128.f );
		bidule2->chargerAnimations( "res/bidule2.anim" );
		//bidule->chargerAnimations( "res/bidule_pinceau.anim" );
		bidule2->animationDefaut( "PoseD", 1.0f );
	// Create clock to measure frame time
	
	sf::Clock frameClock;
	int fps = 0;
	
    int direction = 0;
	bool deplacement = false;
    std::string suffixe_bidule = "";
    

	// Main loop
	for (;;)
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{	
					case sf::Keyboard::Num1:
						suffixe_bidule = "";
						break;
					case sf::Keyboard::Num2:
						suffixe_bidule = "_pinceau";
						break;
					case sf::Keyboard::RControl:	
                        if ( direction >= 0 )
                        {
							bidule->jouerAnimation( "AttaqueD_main"+suffixe_bidule, true );
                        }
                        else
                        {
							bidule->jouerAnimation( "AttaqueG_main"+suffixe_bidule, true );
                        }
                        break;
					case sf::Keyboard::Right:	
						bidule->jouerAnimation( "MarcheD"+suffixe_bidule, true );
						bidule->animationDefaut( "PoseD"+suffixe_bidule, 1.0f );
						deplacement = true;
                        direction = 1;
                        break;
					case sf::Keyboard::Left:	
						bidule->jouerAnimation( "MarcheG"+suffixe_bidule, true );
						bidule->animationDefaut( "PoseG"+suffixe_bidule, 1.0f );
						deplacement = true;
                        direction = -1;
                        break;
					case sf::Keyboard::Up:	
						bidule->jouerAnimation( "MarcheH"+suffixe_bidule, true );
                        break;
					case sf::Keyboard::Down:	
                        if ( direction >= 0 )
                        {
							bidule->jouerAnimation( "AccroupiD_down"+suffixe_bidule, false );
							bidule->animationDefaut( "AccroupiD"+suffixe_bidule, 1.0f );
                        }
                        else
                        {
							bidule->jouerAnimation( "AccroupiG_down"+suffixe_bidule, false );	
							bidule->animationDefaut( "AccroupiG"+suffixe_bidule, 1.0f );
                        }
                        break;
					case sf::Keyboard::S:		
						bidule->arreterAnimation();
                        break;
					case sf::Keyboard::Escape:	return 0;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::RControl:	
						bidule->arreterAnimation();
                        break;
					case sf::Keyboard::Right:
                        if ( direction >= 0 )
                        {
							bidule->arreterAnimation();
							deplacement = false;
                        }
                        break;
					case sf::Keyboard::Left:
                        if ( direction < 0 )
                        {
							bidule->arreterAnimation();
							deplacement = false;
                        }
                        break;
					case sf::Keyboard::Down:	
                        if ( direction >= 0 )
                        {
							bidule->jouerAnimation( "AccroupiD_up"+suffixe_bidule, false );
							bidule->animationDefaut( "PoseD"+suffixe_bidule, 1.0f );
                        }
                        else
                        {
							bidule->jouerAnimation( "AccroupiG_up"+suffixe_bidule, false );	
							bidule->animationDefaut( "PoseG"+suffixe_bidule, 1.0f );
                        }
                        break;
				}
			}
			else if (event.type == sf::Event::Closed)
			{
				return 0;
			}
		}

		float vitesse = 2.0f;
		if ( deplacement )
		{
			bidule->deplacer( direction*vitesse, 0 );
		}
		
		++fps;
		if ( frameClock.getElapsedTime().asSeconds() > 1.0f )
		{
			sf::Time time = frameClock.restart();
			// Mise a jour de l'animator et application de l'etat courant de l'animation au sprite.
			std::ostringstream titre;
				titre << "FPS: " << fps;
			window.setTitle( titre.str() );
			fps = 0;
		}
        scene.step();
		
		
		std::ostringstream texte;
            texte << texteInstruction << std::endl;
			texte << "sprite x: ";
			texte << bidule->position().x << std::endl;
			texte << "sprite y: ";
			texte << bidule->position().y << std::endl;

		instructions.setString( texte.str() );
		// Draw everything
        scene.dessiner( window );

		window.draw(instructions);
		
		window.display();
        
	}	
}