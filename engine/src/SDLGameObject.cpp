#include "SDLGameObject.h"
#include "Game.h"

#include "Player.h"

using namespace engine;

SDLGameObject::SDLGameObject() : GameObject() {
}

void SDLGameObject::load(const LoaderParams *pParams){
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0,0);
	m_acceleration = Vector2D(0,0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
	m_numFrames = pParams->getNumFrames();
	m_angle = pParams->getAngle();
	m_collider = pParams->getCollider();
}

void SDLGameObject::draw(){
	int x = (int) m_position.getX();
	int y = (int) m_position.getY();

	TextureManager::Instance().drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer(), SDL_FLIP_NONE, m_angle );
}

void SDLGameObject::update(){
	
	Vector2D vec = Game::Instance().getPlayer()->getVelocity();
	vec = Vector2D(-vec.getX(), -vec.getY()/10);

	m_velocity = vec;
	m_position += m_velocity;
}

void SDLGameObject::clean(){

}
