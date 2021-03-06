#pragma once
#include <unordered_map>
#include "SharedContext.h"
#include "Actor.h"
#include "ActorManager.h"
#include "Events/Observer.h"

class Window;

class GameEngine : public Observer
{
public:
	GameEngine(StateSharedContext* context);
	~GameEngine();
	void draw(Window* window);
	void update(sf::Time deltaTime);
	void setActiveCharacter(std::string id);
	void createCharacter(std::string id);
	void createEnemy(std::string id);
	Actor* activeCharacter();
	void notify(IEvent* event);

private:
	Actor* m_activeCharacter;
	ActorManager m_actorManager;
	std::unordered_map<std::string, Actor*> m_team;
	std::unordered_map<std::string, Actor*> m_enemies;
	StateSharedContext* m_sharedContext;
};

