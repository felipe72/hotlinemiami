#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include "Cooldown.h"
#include "SDLGameObject.h"

#include <SDL2/SDL.h>
#include <vector>

class Player;
class XuxaBoss;

namespace engine{
	class Game{
	public:
		
		static Game& Instance(){
			static Game game;

			return game;
		}

		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

		bool init(const char*, int, int, int, int, bool);

		void render();
		void update();
		void handleEvents();
		void clean();
		void draw();
		void quit();

		SDL_Renderer* getRenderer(){
			return m_pRenderer;
		}

		bool running() { return m_bRunning; }
		GameStateMachine* getStateMachine(){
			return m_pGameStateMachine;
		}

		int getGameWidth() const{
			return m_gameWidth;
		}

		int getGameHeight() const {
			return m_gameHeight;
		}

		void addCooldown(Cooldown<int>* cooldown){
			m_cooldowns.push_back(cooldown);
		}

		std::vector<GameObject*> m_gameObjects;
		
		void setScore(int score){
			m_score = score;
		}

		int getScore(){
			return m_score;
		}

		int getCenterScreen(){
			return SDL_WINDOWPOS_CENTERED;
		}

		Player* getPlayer(){
			return m_player;
		}

		void setPlayer(Player* p_player){
			m_player = p_player;
		}

		void addEnemy(XuxaBoss *p_enemy){
			m_enemies.push_back(p_enemy);
		}

		std::vector<XuxaBoss*> getEnemies(){
			return m_enemies;
		}

		void addCollider(SDLGameObject *p_collider){
			m_colliders.push_back(p_collider);
		}

		std::vector<SDLGameObject*> getColliders(){
			return m_colliders;
		}

	private:
		Game() {
			m_score = 0;
		}

		Player* m_player;

		int m_gameWidth;
		int m_gameHeight;

		std::vector<SDLGameObject*> m_colliders;
		std::vector<XuxaBoss*> m_enemies;

		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;

		int m_score;
		int m_currentFrame;
		bool m_bRunning;

		std::vector<Cooldown<int>*> m_cooldowns;

		GameStateMachine *m_pGameStateMachine;
	};
}
#endif
