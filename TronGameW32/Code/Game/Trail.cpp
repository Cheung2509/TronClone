#include "Trail.h"

void Trail::addVertex(sf::Vector2f& pos)
{
	sf::Vertex newVertex;
	newVertex.position = pos;
	vertex.push_back(newVertex);
}

void Trail::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(&vertex[0], vertex.size(), sf::LineStrip, states);
}
