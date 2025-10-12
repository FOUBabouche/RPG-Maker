#include "grid.h"

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

Grid::Grid(sf::Vector2u tileSize)
{
	m_tileSize = tileSize;
}

void Grid::SetTile(sf::Vector2u position, sf::Color color, sf::Texture* texture)
{
	if (m_tiles.size() <= position.x) {
		m_tiles.resize(position.x + 1);
	}

	if (m_tiles[position.x].size() <= position.y) {
		m_tiles[position.x].resize(position.y + 1);
	}


	m_tiles[position.x][position.y] = std::make_unique<Tile>(position, m_tileSize, color, texture);
}

void Grid::RemoveTile(sf::Vector2u position)
{
	if (position.x >= m_tiles.size() || position.y >= m_tiles[position.x].size())return;

	auto& tilePtr = m_tiles[position.x][position.y];
	if (tilePtr && tilePtr->GetPosition() == position) {
		tilePtr.reset(); // Remplace par nullptr
		// Optionnel : nettoyage de la colonne si elle ne contient que des nullptr
		bool empty = true;
		for (const auto& t : m_tiles[position.x]) {
			if (t) { empty = false; break; }
		}
		if (empty) {
			m_tiles[position.x].clear();
		}
		return;
	}
}

sf::Vector2u Grid::GetCoordToGridPos(sf::Vector2f mousePos)
{
	return sf::Vector2u(std::floor(mousePos.x / m_tileSize.x), std::floor(mousePos.y / m_tileSize.y));
}

bool Grid::FindAt(sf::Vector2u position)
{
	for (auto&& x : m_tiles)
		for (auto&& y : x)
			if (y.get()->GetPosition() == position)
				return true;
	return false;
}

void Grid::Draw(sf::RenderTarget& window)
{
	for (auto&& x : m_tiles) {
		for (auto&& y : x)
		{
			if (!y) continue;
			sf::RectangleShape shape((sf::Vector2f)y.get()->GetSize());
			shape.setPosition(sf::Vector2f(y.get()->GetPosition().x * y.get()->GetSize().x, y.get()->GetPosition().y * y.get()->GetSize().y));
			if (y.get()->getTexture() != nullptr)
				shape.setTexture(y.get()->getTexture());
			shape.setFillColor(y.get()->getColor());
			window.draw(shape);
		}
	}
}

void Grid::DrawGrid(sf::RenderTarget& window, sf::Vector2f cameraSize)
{
	sf::VertexArray grid(sf::PrimitiveType::Lines);

	for (float x = 0.f; x <= cameraSize.x; x += m_tileSize.x) {
		grid.append({ sf::Vector2f(x, 0.f), sf::Color(100, 100, 100)});
		grid.append({ sf::Vector2f(x, cameraSize.y), sf::Color(100, 100, 100) });
	}

	// Lignes horizontales
	for (float y = 0.f; y <= cameraSize.y; y += m_tileSize.y) {
		grid.append({ sf::Vector2f(0.f, y), sf::Color(100, 100, 100)});
		grid.append({ sf::Vector2f(cameraSize.x, y), sf::Color(100, 100, 100) });
	}

	window.draw(grid);
}
