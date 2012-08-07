////////////////
/// En-têtes.
// systeme.
#include <iostream>
#include <unordered_map>
// Box2D.
#include <Box2D/Box2D.h>
// Thor.
#include <Thor/Animation.hpp>
// SFML.
#include <SFML/Graphics.hpp>
// Projet.
#include "Scene.hpp"
#include "Acteur.hpp"

int main()
{

	/// Box2D.
	// World.
	b2Vec2 gravity(0.0f, -10.0f); 
	bool doSleep = true; 
    
	b2World world(gravity);
    //    world.SetAllowSleeping( doSleep );
	// Ground.
	b2BodyDef groundBodyDef; 
        groundBodyDef.position.Set(0.0f, -10.0f);                                                                                                                                          

	b2PolygonShape groundBox; 
        groundBox.SetAsBox(50.0f, 10.0f); 

	b2Body* groundBody = world.CreateBody(&groundBodyDef); 
        groundBody->CreateFixture(&groundBox, 0.0f);
	// Dynamic body.
	b2BodyDef bodyDef; 
        bodyDef.type = b2_dynamicBody; 
        bodyDef.position.Set(0.0f, 25.0f); 
        b2Body* body = world.CreateBody(&bodyDef); 	
	
	b2PolygonShape dynamicBox; 
        dynamicBox.SetAsBox(1.0f, 1.0f); 
	
	b2FixtureDef fixtureDef; 
        fixtureDef.shape = &dynamicBox; 
        fixtureDef.density = 1.0f; 
        fixtureDef.friction = 0.3f;
        
	body->CreateFixture(&fixtureDef); 
	// simulation.
	float32 timeStep = 1.0f / 60.0f;
    
    int32 velocityIterations = 8; 
    int32 positionIterations = 3; 
    
    
	sf::RenderWindow window(sf::VideoMode(600, 400), "Thor Animation");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	// Instruction text
	sf::Text instructions(
		"Droite/Gauche:  Marche droite/gauche\n"
		"Bas: s'accroupir\n"
		"Echap:  Quit");
	instructions.setCharacterSize(12);
	instructions.setColor(sf::Color::White);

	/// Bidule.
    // Image.
	Scene scene;
		scene.creerImage( "bidule", "res/bidule2.png" );
		ptrImage image_bidule = scene.image( "bidule" );
	
	Acteur bidule( image_bidule );
		bidule.position( sf::Vector2f( 150.f-32.f, 200.f-128.f ) );
		bidule.chargerAnimations( "res/bidule2.anim" );
		//bidule.chargerAnimations( "res/bidule_pinceau.anim" );
		bidule.animationDefaut( "PoseD", 1.0f );

	Acteur bidule2( image_bidule );
		bidule2.position( sf::Vector2f( 150.f-32.f+100.f, 200.f-128.f ) );
		bidule2.chargerAnimations( "res/bidule2.anim" );
		//bidule.chargerAnimations( "res/bidule_pinceau.anim" );
		bidule2.animationDefaut( "PoseD", 1.0f );	
		
	// Create clock to measure frame time
	sf::Clock frameClock;
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
						//bidule.animationDefaut( "PoseD", 1.0f );
						break;
					case sf::Keyboard::Num2:
						suffixe_bidule = "_pinceau";
						//bidule.animationDefaut( "PoseD_pinceau", 1.0f );
						break;
					case sf::Keyboard::RControl:	
                        if ( direction >= 0 )
                        {
							bidule.jouerAnimation( "AttaqueD_main"+suffixe_bidule, true );
                        }
                        else
                        {
							bidule.jouerAnimation( "AttaqueG_main"+suffixe_bidule, true );
                        }
                        break;
					case sf::Keyboard::Right:	
						bidule.jouerAnimation( "MarcheD"+suffixe_bidule, true );
						bidule.animationDefaut( "PoseD"+suffixe_bidule, 1.0f );
						deplacement = true;
                        direction = 1;
                        break;
					case sf::Keyboard::Left:	
						bidule.jouerAnimation( "MarcheG"+suffixe_bidule, true );
						bidule.animationDefaut( "PoseG"+suffixe_bidule, 1.0f );
						deplacement = true;
                        direction = -1;
                        break;
					case sf::Keyboard::Up:	
						bidule.jouerAnimation( "MarcheH"+suffixe_bidule, true );
                        break;
					case sf::Keyboard::Down:	
                        if ( direction >= 0 )
                        {
							bidule.jouerAnimation( "AccroupiD_down"+suffixe_bidule, false );
							bidule.animationDefaut( "AccroupiD"+suffixe_bidule, 1.0f );
                        }
                        else
                        {
							bidule.jouerAnimation( "AccroupiG_down"+suffixe_bidule, false );	
							bidule.animationDefaut( "AccroupiG"+suffixe_bidule, 1.0f );
                        }
                        break;
					case sf::Keyboard::S:		
						bidule.arreterAnimation();
                        break;
					case sf::Keyboard::Escape:	return 0;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::RControl:	
						bidule.arreterAnimation();
                        break;
					case sf::Keyboard::Right:
                        if ( direction >= 0 )
                        {
							bidule.arreterAnimation();
                        }
						deplacement = false;
                        break;
					case sf::Keyboard::Left:
                        if ( direction < 0 )
                        {
							bidule.arreterAnimation();
                        }
						deplacement = false;
                        break;
					case sf::Keyboard::Up:	

					case sf::Keyboard::Down:	
                        if ( direction >= 0 )
                        {
							bidule.jouerAnimation( "AccroupiD_up"+suffixe_bidule, false );
							bidule.animationDefaut( "PoseD"+suffixe_bidule, 1.0f );
                        }
                        else
                        {std::cout << "UPG" << std::endl;
							bidule.jouerAnimation( "AccroupiG_up"+suffixe_bidule, false );	
							bidule.animationDefaut( "PoseG"+suffixe_bidule, 1.0f );
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
			bidule.deplacer( direction*vitesse, 0 );
		}
		
        sf::Time time = frameClock.restart();
        // Mise a jour de l'animator et application de l'etat courant de l'animation au sprite.

		bidule.animer( time );
		bidule2.animer( time );
		
        // Simulation physique et collisions.
        world.Step(timeStep, velocityIterations, positionIterations); 
        b2Vec2 position = body->GetPosition(); 
        float32 angle = body->GetAngle(); 
        bidule.position( sf::Vector2f( 0.0f, (window.getSize().y-position.y)-bidule.rectangleTexture().height ) );
        dynamicBox.SetAsBox( bidule.rectangleTexture().width, bidule.rectangleTexture().height );
        std::cout << position.y << ", " << window.getSize().y-position.y << " - " << bidule.rectangleTexture().height << "= " << bidule.position().y << std::endl;

		// Draw everything
		window.clear(sf::Color(50, 50, 50));
		window.draw(instructions);
		window.draw( bidule.sprite() );
		window.draw( bidule2.sprite() );
		window.display();
	}	
}