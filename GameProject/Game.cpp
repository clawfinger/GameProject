#include "stdafx.h"
#include "GameLevelState.h"
#include "game.h"
#include <iostream>
#include <assert.h>
#include <fstream>

Game::Game() : isRunning(true), m_map(&m_textureManager), m_commandDispatcher(m_map, m_window)
{
	m_window.setup("SFML", sf::Vector2u(1280, 720));
	m_timePerFrame = sf::seconds(1.0f / 60.0f);

	StateSharedContext context;
	context.commandDispatcher = &m_commandDispatcher;
	context.window = &m_window;
	context.player = &m_player;
	context.map = &m_map;
	context.textureManager = &m_textureManager;

	m_stateManager.setSharedContext(context);

	m_textureManager.load(TextureId::wall(), "images/3.png");
	m_textureManager.load(TextureId::floor1(), "images/1.png");
	m_textureManager.load(TextureId::floor2(), "images/2.png");
	m_textureManager.load(CharacterId::swordsman(), "images/player.png");

	m_map.loadLevel(LevelNames::dungeon);
	m_stateManager.activateState(GameStateType::level);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (isRunning)
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			processEvents();
			update(m_timePerFrame);

			timeSinceLastUpdate -= m_timePerFrame;
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.getRenderWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			isRunning = false;
			return;
		}
		m_stateManager.currentState()->handlePlayerInput(event);
	}
}

void Game::update(sf::Time deltaTime)
{
	m_stateManager.currentState()->update(deltaTime);
}

void Game::render()
{
	m_stateManager.currentState()->render();	
}



