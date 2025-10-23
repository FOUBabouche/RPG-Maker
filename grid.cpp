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

sf::Vector2u Grid::getTileSize(void) const
{
	return m_tileSize;
}

void Grid::setTileSize(sf::Vector2u tileSize)
{
	m_tileSize = tileSize;
}

void Grid::SetTile(sf::Vector2u position, sf::Color color, sf::Texture* texture, sf::IntRect uvSize)
{
	if (position.x < 0 || position.y < 0) return;

	if (m_tiles.size() <= position.x) {
		m_tiles.resize(position.x + 1);
	}

	if (m_tiles[position.x].size() <= position.y) {
		m_tiles[position.x].resize(position.y + 1);
	}

	Tile tile = Tile(position, m_tileSize, color, new sf::Texture(*texture), uvSize);
	m_tiles[position.x][position.y] = tile;
}

void Grid::RemoveTile(sf::Vector2u position)
{
	if (position.x >= m_tiles.size() || position.y >= m_tiles[position.x].size())return;

	auto& tilePtr = m_tiles[position.x][position.y];
	if (tilePtr.GetPosition() == position) {
		tilePtr = (Tile&)Tile(); // Remplace par nullptr
		// Optionnel : nettoyage de la colonne si elle ne contient que des nullptr
		bool empty = true;
		for (auto& t : m_tiles[position.x]) {
			if (t != (Tile&)Tile()) { empty = false; break; }
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
			if (y.GetPosition() == position)
				return true;
	return false;
}

void Grid::Draw(sf::RenderTarget& window, float zoom)
{
	for (auto x : m_tiles) {
		for (auto y : x)
		{
			if (y == (Tile&)Tile()) continue;
			sf::RectangleShape shape((sf::Vector2f)y.GetSize() * zoom);
			shape.setPosition(sf::Vector2f(y.GetPosition().x * y.GetSize().x * zoom, y.GetPosition().y * y.GetSize().y * zoom));
			if (y.getTexture() != nullptr) {
				shape.setTexture(y.getTexture());
				shape.setTextureRect(y.getUV());
			}
			shape.setFillColor(y.getColor());
			window.draw(shape);
		}
	}
}

void Grid::DrawGrid(sf::RenderTarget& window, sf::Vector2f renderSize, sf::Vector2f cameraPos,float zoom)
{
	sf::VertexArray grid(sf::PrimitiveType::Lines);

	float startX = std::floor(cameraPos.x / (m_tileSize.x * zoom)) / (m_tileSize.x * zoom);
	float startY = std::floor(cameraPos.y / (m_tileSize.y * zoom)) / (m_tileSize.y * zoom);

	for (float x = startX; x <= cameraPos.x + renderSize.x ; x += m_tileSize.x * zoom) {
		grid.append({ sf::Vector2f(x, cameraPos.y), sf::Color(100, 100, 100)});
		grid.append({ sf::Vector2f(x, cameraPos.y + renderSize.y), sf::Color(100, 100, 100) });
	}

	// Lignes horizontales
	for (float y = startY; y <= cameraPos.y + renderSize.y; y += m_tileSize.y * zoom) {
		grid.append({ sf::Vector2f(cameraPos.x, y), sf::Color(100, 100, 100)});
		grid.append({ sf::Vector2f(cameraPos.x + renderSize.x, y), sf::Color(100, 100, 100) });
	}

	window.draw(grid);
}
