#include "BossBullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "Enemy.h"
#include "Physics.h"
#include "GameOverState.h"
#include "XuxaBoss.h"
#include <iostream>

using namespace engine;

BossBullet::~BossBullet(){
	INFO("Boss Bullet destroyed")
}

BossBullet::BossBullet(Player *target) : SDLGameObject(){
	setPlayer(target);
	timeToLive = 1000;
	m_active = true;
}

void BossBullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}

double BossBullet::rotateTowards(Vector2D pPosition){
	Vector2D target = InputHandler::Instance().getMousePosition() - pPosition;
	target = target.norm();

	Vector2D horizontal(0,1);

	return Vector2D::angle(target, Vector2D(0, 1));
}
void BossBullet::load(Vector2D pVelocity, Vector2D pPosition){
	double angle = rotateTowards(pPosition);

	m_moveSpeed = 3;
	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 16, 16, "bulletboss", 0, 0, 0, angle);
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	bornTime = Timer::Instance().step();
	m_velocity = pVelocity.norm() * m_moveSpeed;
	//m_velocity = Vector2D(0.5, 0.5);
}

void BossBullet::draw(){
	SDLGameObject::draw();
}

void BossBullet::update(){
	m_position += m_velocity - Game::Instance().getPlayer()->getVelocity();

	if(Timer::Instance().step() >= bornTime + timeToLive){
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}

	checkCollision();
}

void BossBullet::checkCollision(){
	if(m_active){
		Vector2D pos = m_player->getPosition();
		Vector2D thisPos = getPosition();
		for(auto enemy : Game::Instance().getEnemies()){
			if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(enemy), dynamic_cast<SDLGameObject*>(this))){
				if(enemy->getTextureID() == "collider"){
					m_active = false;
					m_position = Vector2D(10000, 10000);
					Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
					return;
				}
			}
		}


		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_player), dynamic_cast<SDLGameObject*>(this))){
			m_active = false;
			Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
			INFO("Bullet collided");
			m_player->setLife((m_player->getLife()) - 15);
			//Game::Instance().getStateMachine()->changeState(new GameOverState());
		}
	}
}

void BossBullet::clean(){
	SDLGameObject::clean();
}

