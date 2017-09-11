#pragma once
#include <SFML\Graphics.hpp>

#include <vector>

class Trail : public sf::Drawable, public sf::Transformable
{
public:
	void addVertex(sf::Vector2f&);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<sf::Vertex> vertex;
};