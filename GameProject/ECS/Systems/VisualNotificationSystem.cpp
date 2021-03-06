#include "VisualNotificationSystem.h"
#include "../../DiContainer/DiContainer.h"
#include "../../Events/Events.h"
#include "../../Events/EventDispatcher.h"
#include "../../ECS/EntityContainer.h"
#include "../../Window.h"

VisualNotificationSystem::VisualNotificationSystem(DiContainer* container): SystemBase(typeName<VisualNotificationSystem>())
{
	m_entityContainer = container->get<EntityContainer>();
	m_eventDispatcher = container->get<EventDispatcher>();
	//m_eventDispatcher->subscribe(typeName<EntityCreatedEvent>(), this);
	//registerCallBack(typeName<EntityCreatedEvent>(), std::bind(&VisualNotificationSystem::handleEntitySpawnEvent, this, std::placeholders::_1));
}


VisualNotificationSystem::~VisualNotificationSystem()
{
}

void VisualNotificationSystem::update(sf::Time deltaTime)
{
}

//void VisualNotificationSystem::notify(IEvent * event)
//{
//}

void VisualNotificationSystem::draw(std::shared_ptr<Window> window)
{
}

void NotificationBase::draw(std::shared_ptr<Window> window)
{
	window->draw(m_sprite);
}
