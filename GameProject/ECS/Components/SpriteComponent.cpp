#include <sstream>
#include "SpriteComponent.h"


SpriteComponent::SpriteComponent() : ComponentBase(typeName<SpriteComponent>()), m_isCastsShadow(false)
{
}


SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::create(sf::Texture & texture)
{
	m_sprite.setTexture(texture);
}

void SpriteComponent::create(sf::Texture & texture, const sf::IntRect& textureRect)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(textureRect);
}

sf::Sprite & SpriteComponent::getSprite()
{
	return m_sprite;
}

void SpriteComponent::setPosition(const Vector2f & position)
{
	m_sprite.setPosition(position.x, position.y);
}

Vector2f & SpriteComponent::getSize()
{
	return m_size;
}

void SpriteComponent::readData(std::stringstream & stream)
{
    //TODO remove this method and replace with setters
	int x = 0;
	int y = 0;
	stream >> x >> y;
	stream >> m_size.x >> m_size.y;
    stream >> m_isCastsShadow;
	m_sprite.setOrigin(float(x), float(y));
    m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
}

bool SpriteComponent::isCastsShadow()
{
    return m_isCastsShadow;
}
