#include "Trail.h"

void Trail::addVertex(sf::Vector2f& pos)
{
	sf::Vertex newVertex;
	newVertex.color = color;
	newVertex.position = pos;
	vertexes.push_back(newVertex);
}

void Trail::clearVertex()
{
	if (!vertexes.empty())
	{
		vertexes.clear();
	}
}

void Trail::setColor(sf::Color col)
{
	color = col;
}

void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	

	if (!vertexes.empty())
	{
		target.draw(&vertexes[0], vertexes.size(), sf::LineStrip, states);
	}
}
