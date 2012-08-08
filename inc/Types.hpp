#ifndef Types_HPP
#define Types_HPP
/// En-T�tes.
// std.
#include <memory>
// SFML.
#include <SFML/Graphics.hpp>

typedef std::shared_ptr< sf::Image > ptrImage;

#define PixelParMetres(x) x*128.0f
#define MetreParPixels(x) x/128.0f
/*
#define PixelParMetres(x) x
#define MetreParPixels(x) x
*/

#endif// Fin Types_HPP.