#pragma once
#include <SFML\Graphics.hpp>

#include <vector>

class Trail : public sf::Drawable, public sf::Transformable
{
public:
	Trail() = default;
	~Trail() = default;

	void addVertex(sf::Vector2f&);
	void clearVertex();
	void setColor(sf::Color);
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	std::vector<sf::Vertex> vertexes;
	sf::Color color;
};