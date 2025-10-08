#include "grid.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

Grid::Grid(sf::Vector2u tileSize)
{
	m_tileSize = tileSize;
}

void Grid::SetTile(sf::Vector2u position, sf::Color color, sf::Texture* texture)
{
	Tile tile = Tile(position, m_tileSize, color, texture);
	if (position.x >= m_tiles.size()) {
		m_tiles.push_back(std::vector<std::unique_ptr<Tile>>());
		if (position.y >= m_tiles[m_tiles.size()-1].size()) {
			m_tiles[m_tiles.size() - 1].push_back(std::make_unique<Tile>(tile));
		}
		else {
			m_tiles[m_tiles.size() - 1].insert(m_tiles[m_tiles.size() - 1].begin(), std::make_unique<Tile>(tile));
		}
	}
	else if (position.x == m_tiles.size()) {
		m_tiles[position.x][position.y].reset(&tile);
	}
	else {
		m_tiles.insert(m_tiles.begin()+position.x, std::vector<std::unique_ptr<Tile>>());
		if (position.y >= m_tiles[m_tiles.size() - 1].size()) {
			m_tiles[m_tiles.size() - 1].push_back(std::make_unique<Tile>(tile));
		}
		else {
			m_tiles[m_tiles.size() - 1].insert(m_tiles[m_tiles.size() - 1].begin(), std::make_unique<Tile>(tile));
		}
	}
}

void Grid::RemoveTile(sf::Vector2u position)
{
	for (size_t x = 0; x < m_tiles.size(); x++)
		for (size_t y = 0; y < m_tiles[x].size(); y++)
			if (m_tiles[x][y].get()->GetPosition() == position) {
				m_tiles[x].erase(m_tiles[x].begin()+y);
				return;
			}
	std::cout << "No Tile Here: " << position.x << " " << position.y << std::endl;
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
			sf::RectangleShape shape((sf::Vector2f)y.get()->GetSize());
			shape.setPosition(sf::Vector2f(y.get()->GetPosition().x * y.get()->GetSize().x, y.get()->GetPosition().y * y.get()->GetSize().y));
			if (y.get()->getTexture() != nullptr)
				shape.setTexture(y.get()->getTexture());
			shape.setFillColor(y.get()->getColor());
			window.draw(shape);
		}
	}
}

void Grid::DrawGrid(sf::RenderTarget& window)
{
	sf::VertexArray grid(sf::PrimitiveType::Lines);

	for (float x = 0.f; x <= window.getSize().x; x += m_tileSize.x) {
		grid.append({ sf::Vector2f(x, 0.f), sf::Color(100, 100, 100)});
		grid.append({ sf::Vector2f(x, window.getSize().y), sf::Color(100, 100, 100) });
	}

	// Lignes horizontales
	for (float y = 0.f; y <= window.getSize().y; y += m_tileSize.y) {
		grid.append({ sf::Vector2f(0.f, y), sf::Color(100, 100, 100)});
		grid.append({ sf::Vector2f(window.getSize().x, y), sf::Color(100, 100, 100) });
	}

	window.draw(grid);
}
