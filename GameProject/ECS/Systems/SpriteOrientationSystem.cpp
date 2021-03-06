#include "SpriteOrientationSystem.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../ECS/EntityContainer.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/SpriteOrientationComponent.h"

SpriteOrientationSystem::SpriteOrientationSystem(DiContainer * container): SystemBase(typeName<SpriteOrientationSystem>())
{
	m_requirements << typeName<SpriteOrientationComponent>();
	m_requirements << typeName<SpriteComponent>();

	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();

	m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
	m_eventDispatcher->subscribe(typeName<EntityChangedOrientationEvent>(), this);
	registerCallBack(typeName<EntityCreatedEvent>(), std::bind(&SpriteOrientationSystem::handleEntitySpawnEvent, this, std::placeholders::_1));
	registerCallBack(typeName<EntityChangedOrientationEvent>(), std::bind(&SpriteOrientationSystem::handleOrientationChangeEvent, this, std::placeholders::_1));
}

SpriteOrientationSystem::~SpriteOrientationSystem()
{
}

//void SpriteOrientationSystem::notify(IEvent * event)
//{
//	if (event->name() == typeName<EntityCreatedEvent>())
//		handleEntitySpawnEvent(event);
//	else if (event->name() == typeName<EntityChangedOrientationEvent>())
//		handleOrientationChangeEvent(event);
//}

void SpriteOrientationSystem::handleEntitySpawnEvent(IEvent * event)
{
	EntityCreatedEvent *currentEvent = dynamic_cast<EntityCreatedEvent *>(event);
	if (nullptr != currentEvent)
	{
		if (fitsRequirements(currentEvent->components))
		{
			SpriteComponent* spriteComponent =
                m_entityContainer->getComponent<SpriteComponent>(currentEvent->id);
			SpriteOrientationComponent* orientationComponent =
                m_entityContainer->getComponent<SpriteOrientationComponent>(currentEvent->id);

			updateSpriteOrientation(spriteComponent, orientationComponent);
		}
	}
}

void SpriteOrientationSystem::handleOrientationChangeEvent(IEvent * event)
{
	EntityChangedOrientationEvent *currentEvent = dynamic_cast<EntityChangedOrientationEvent *>(event);
	if (nullptr != currentEvent)
	{
		SpriteComponent* spriteComponent =
            m_entityContainer->getComponent<SpriteComponent>(currentEvent->entity);
		SpriteOrientationComponent* orientationComponent =
            m_entityContainer->getComponent<SpriteOrientationComponent>(currentEvent->entity);

		updateSpriteOrientation(spriteComponent, orientationComponent);
	}
}

void SpriteOrientationSystem::updateSpriteOrientation(SpriteComponent* spriteComponent,
													SpriteOrientationComponent* orientationComponent)
{
//	sf::IntRect textureRect = orientationComponent->getRightTextureRect();

//	if (orientationComponent->orientation() == SpriteOrientation::left)
//	{
//		textureRect.left = 0;
//		textureRect.top = 0;
//		spriteComponent->getSprite().setTextureRect(textureRect);
//	}
//	else if (orientationComponent->orientation() == SpriteOrientation::right)
//	{
//		spriteComponent->getSprite().setTextureRect(textureRect);
//	}
}
