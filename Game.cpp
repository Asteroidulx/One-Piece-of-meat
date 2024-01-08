#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "ItemMap.h"
#include <sstream>

Map* mapa;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, MAX_WIDTH, MAX_HEIGHT};

AssetManager* Game::assets = new AssetManager(&manager);
ItemMap harta(32, 20);
bool Game::isRunning = false;

auto& player(manager.addEntity());
//auto& label(manager.addEntity());

Game::Game(const char* title, atom x, atom y, atom w, atom h, bool fullscreen) {
	atom flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf("Subsystems Initialised!...\n");

		window=SDL_CreateWindow(title, x, y, w, h, flags);
		if (window) {
			printf("Window created!\n");
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			printf("Renderer created!\n");
		}
		isRunning = true;
	}

	/*if (TTF_Init() == -1) {
		cout << "Error : SDL_TTF" << endl;
	}*/
	
	assets->AddTexture("terrain", "assets/Lvl1MapTileset.png");
	assets->AddTexture("player", "assets/Luffy.png");
	assets->AddTexture("rock", "assets/Rock-animation360.png");
	assets->AddTexture("meat", "assets/meat.png");
	//assets->AddFont("arial", "assets/arial.ttf", 16);

	mapa = new Map("terrain", 1, 64);
	mapa->LoadMap("assets/Lvl1Map.map", 32, 20);

	player.addComponent<TransformComponent>(0, 1152);//(64*0, 64*18)
	player.addComponent<SpriteComponent>("player");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	assets->createMandR(harta, "assets/ItemMap.Map", 32, 20);

	//SDL_Color white = { 255, 255, 255, 255 };
	//label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
}

Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned!\n");
}

void Game::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT: isRunning = false;
		break;
	default:
		break;
	}
}

auto& rocks(manager.getGroup(Game::groupRocks));
auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& players(manager.getGroup(Game::groupPlayers));
auto& meats(manager.getGroup(Game::groupMeats));

void Game::update() {
	if (manager.getNrInGroup(groupPlayers)) {
		SDL_Rect playerCol = player.getComponent<ColliderComponent>().getcollider();
		Vector2D playerPos = player.getComponent<TransformComponent>().getposition();

		int i = 0;
		for (auto& r : rocks) {
			i++;
		}
		Vector2D* rockPos = new Vector2D[i];
		int size = i;
		for (auto& r : rocks) {
			rockPos[size - i] = r->getComponent<Rock>().getPosition();
			i--;
		}
		/*stringstream ss;
		ss << "Player position: " << playerPos;
		label.getComponent<UILabel>().SetLabelText(ss.str(), "arial");*/

		manager.refresh();
		manager.update();

		//	bool colx = Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), 
		//										   r->getComponent<ColliderComponent>().getcollider());
		//	if (colx) {
		//		if (r->getComponent<Rock>().getTrComp()->pgetx() >
		//			player.getComponent<TransformComponent>().pgetx() &&
		//			player.getComponent<TransformComponent>().vgetx() > 0) {

		//			r->getComponent<Rock>().setcase(2);//right
		//			r->getComponent<Rock>().getTrComp()->setsp(1);
		//			player.getComponent<TransformComponent>().setsp(1);
		//			if (player.getComponent<TransformComponent>().pgetx() + 64 >
		//				r->getComponent<Rock>().getTrComp()->pgetx()) {

		//				player.getComponent<TransformComponent>().vsetx(0);
		//				player.getComponent<TransformComponent>().psetx(r->getComponent<Rock>().getTrComp()->pgetx() - 64);
		//			}
		//			
		//		}
		//		else if (r->getComponent<Rock>().getTrComp()->pgetx() <
		//			player.getComponent<TransformComponent>().pgetx() &&
		//			player.getComponent<TransformComponent>().vgetx() < 0) {

		//			r->getComponent<Rock>().setcase(3);//left
		//			r->getComponent<Rock>().getTrComp()->setsp(1);
		//			player.getComponent<TransformComponent>().setsp(1);
		//			if (player.getComponent<TransformComponent>().pgetx() - 64 <
		//				r->getComponent<Rock>().getTrComp()->pgetx()){

		//				player.getComponent<TransformComponent>().vsetx(0);
		//				player.getComponent<TransformComponent>().psetx(r->getComponent<Rock>().getTrComp()->pgetx() + 64);
		//			}
		//		}
		//	}
		//	else if (r->getComponent<Rock>().getcase() == 3 || r->getComponent<Rock>().getcase() == 2) {
		//		r->getComponent<Rock>().setcase(0);
		//		r->getComponent<Rock>().getTrComp()->setsp(2);
		//		player.getComponent<TransformComponent>().setsp(3);
		//	}
		//	i++;
		//}
		//i = 0;
		//for (auto& r : rocks) {
		//	if (r->getComponent<Rock>().getcase()) {
		//		for (auto& r1 : rocks) {
		//			if (!r1->getComponent<Rock>().getcase()) {
		//				if (Collision::AABBy(r->getComponent<ColliderComponent>().getcollider(),
		//					r1->getComponent<ColliderComponent>().getcollider()) &&
		//					r->getComponent<Rock>().getTrComp()->pgety() != rockPos[i].gety() &&
		//					r->getComponent<Rock>().getTrComp()->pgetx() == r1->getComponent<Rock>().getTrComp()->pgetx()) {

		//					r->getComponent<Rock>().setcase(0);//not moving
		//					r->getComponent<Rock>().setPosition(rockPos[i]);
		//					cout << "rock hit rock\n";
		//					break;
		//				}
		//			}
		//			if (!r1->getComponent<Rock>().getcase()) {
		//				if (Collision::AABBx(r->getComponent<ColliderComponent>().getcollider(),
		//					r1->getComponent<ColliderComponent>().getcollider()) &&
		//					r->getComponent<Rock>().getTrComp()->pgetx() != rockPos[i].getx() &&
		//					r->getComponent<Rock>().getTrComp()->pgety() == r1->getComponent<Rock>().getTrComp()->pgety()) {

		//					r->getComponent<Rock>().setcase(0);//not moving
		//					r->getComponent<Rock>().setPosition(rockPos[i]);
		//					cout << "rock hit rock\n";
		//					break;
		//				}
		//			}
		//		}
		//	}
		//	i++;
		//}
		
		//koko kara
		i = 0;
		for (auto& r : rocks) {
			Vector2D rockpos = r->getComponent<Rock>().getPosition();
			harta.UpdatePos(rockPos[i], rockpos);
			if (!harta.WhatatPos(rockpos, 9)) {
				r->destroy();
				player.getComponent<TransformComponent>().setsp(3);
				manager.update();
				continue;
			}
			bool ok = false, ok1 = false, rockBellowNMov = false, rockBellow1NMov = false;
			for (auto& r1 : rocks) {
				if (r1 != r && Collision::AABBy(
					r->getComponent<ColliderComponent>().getcollider(),
					r1->getComponent<ColliderComponent>().getcollider()) &&
					rockpos.gety() < r1->getComponent<Rock>().getPosition().gety() &&
					rockpos.getx() == r1->getComponent<Rock>().getPosition().getx()) {
					//daca sub piatra curenta e alta piatra
					if (!r1->getComponent<Rock>().getcase())
						rockBellowNMov = true;
					ok = true;
					Vector2D rockpos1 = r1->getComponent<Rock>().getPosition();
					for (auto& r2 : rocks) {
						if (r2 != r1 && r2 != r && Collision::AABBy(
							r1->getComponent<ColliderComponent>().getcollider(),
							r2->getComponent<ColliderComponent>().getcollider()) &&
							rockpos1.gety() < r2->getComponent<Rock>().getPosition().gety()) {
							if (!r2->getComponent<Rock>().getcase())
								rockBellow1NMov = true;
							ok1 = true;
							break;
						}
					}
					break;
				}
			}
			if (r->getComponent<Rock>().getcase() == 1 && (harta.WhatatPos(rockpos, 4)==1 || harta.WhatatPos(rockpos, 4) == 3 || ok)) {
				//daca piatra cade si sub ea am zid, carne sau alta piatra - o opresc si ii dau pozitia trecuta
				r->getComponent<Rock>().setcase(0);
				r->getComponent<Rock>().setPosition({rockpos.getx(), rockPos[i].gety()});
			
			}else if (r->getComponent<Rock>().getcase() == 1 && Collision::AABByplayer(
				player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				player.getComponent<TransformComponent>().pgety() > rockpos.gety()) {
				//daca piatra cade is are coliziune cu jucatorul(sub piatra) - jucatorul moare
				if (player.getComponent<TransformComponent>().pgetx() >= r->getComponent<Rock>().getPosition().getx() + 60 ||
					player.getComponent<TransformComponent>().pgetx() <= r->getComponent<Rock>().getPosition().getx() - 60) {

					player.getComponent<TransformComponent>().setposition(playerPos);
				}else {
					cout << "Omae wa mou shindeiru!\n";
					player.destroy();
					manager.refresh();
					break;
				}
			}
			else if (r->getComponent<Rock>().getcase() == 0 && !ok && !(harta.WhatatPos(rockpos, 4) == 1 || harta.WhatatPos(rockpos, 4) == 3 ||
				(Collision::AABBy(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
					player.getComponent<TransformComponent>().pgety() > rockpos.gety()))) {
				//daca piatra sta si nu are sub ea jucatorul, alta piatra, zid sau carne - piatra cade
				r->getComponent<Rock>().setcase(1);
			}
			else if (r->getComponent<Rock>().getcase() == 0 && 
				Collision::AABByplayer(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				player.getComponent<TransformComponent>().pgety() > rockpos.gety() && player.getComponent<TransformComponent>().pgety() != playerPos.gety()){					
				//daca jucatorul e sub piatra care sta si jucatorul incearca sa intre in piatra - playerul se opreste + poz trecuta
				player.getComponent<TransformComponent>().setposition(playerPos);
			}else if (r->getComponent<Rock>().getcase() == 1 && Collision::AABBy(
				player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				player.getComponent<TransformComponent>().pgety() < rockpos.gety()) {
				//daca piatra cade si playerul e deasupra si incearca sa intre in piatra - playerul se opreste + poz trecuta
				player.getComponent<TransformComponent>().setposition(playerPos);
				player.getComponent<TransformComponent>().vsety(0);
			}else if (r->getComponent<Rock>().getcase() == 0 && Collision::AABByplayer(
				player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				player.getComponent<TransformComponent>().pgety() < rockpos.gety()) {
				//daca piatra nu cade si playerul e deasupra si incearca sa intre in piatra - playerul se opreste + poz trecuta
				player.getComponent<TransformComponent>().setposition(playerPos);
			}
			else if ((r->getComponent<Rock>().getcase() == 2 || r->getComponent<Rock>().getcase() == 3) && !ok && !harta.WhatatPos(rockpos, 4)) {
				//daca am impins piatra si ea nu are nimic acum sub ea - piatra cade
				r->getComponent<Rock>().setcase(1);
				r->getComponent<Rock>().getTrComp()->setsp(2);
				r->getComponent<Rock>().getTrComp()->psetx(rockPos[i].getx() - 1);
				player.getComponent<TransformComponent>().setsp(3);
			}else if ((harta.WhatatPos(rockpos,2)==1 || harta.WhatatPos(rockpos, 2) == 2 || harta.WhatatPos(rockpos, 2) == 3) && 
				rockpos.getx()>rockPos[i].getx()) {
				//daca am miscat piatra si are spatiu ocupat in dreapta - se opreste
				player.getComponent<TransformComponent>().setsp(3);
				r->getComponent<Rock>().setcase(0);
				r->getComponent<Rock>().getTrComp()->setsp(2);
				r->getComponent<Rock>().getTrComp()->psetx(rockPos[i].getx()/*-1*/);
				if (Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
					player.getComponent<TransformComponent>().pgetx()>playerPos.getx()) {
					player.getComponent<TransformComponent>().psetx(playerPos.getx()-1);
				}
			}else if ((harta.WhatatPos(rockpos, 6) == 1 || harta.WhatatPos(rockpos, 6) == 2 || harta.WhatatPos(rockpos, 6) == 3) &&
				rockpos.getx() < rockPos[i].getx()) {
				//daca am miscat piatra si are spatiu ocupat in stanga - se opreste
				player.getComponent<TransformComponent>().setsp(3);
				r->getComponent<Rock>().setcase(0);
				r->getComponent<Rock>().getTrComp()->setsp(2);
				r->getComponent<Rock>().getTrComp()->psetx(rockPos[i].getx()-1);
				if (Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
					player.getComponent<TransformComponent>().pgetx() < playerPos.getx()) {
						player.getComponent<TransformComponent>().psetx(playerPos.getx()+1);
				}
			}else if (Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				!r->getComponent<Rock>().getTrComp()->vgety() && player.getComponent<TransformComponent>().pgetx() < rockpos.getx() &&
				(harta.WhatatPos(rockpos, 2) == 0 || harta.WhatatPos(rockpos, 2) == 9)) {
				//daca am col pe ox intre player si piatra si piatra sta in drt si in partea op a pietrei nu e nimic - playerul impinge piatra
				r->getComponent<Rock>().setcase(2);
				r->getComponent<Rock>().getTrComp()->setsp(1);
				player.getComponent<TransformComponent>().setsp(1);
			}else if(Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				!r->getComponent<Rock>().getTrComp()->vgety() && player.getComponent<TransformComponent>().pgetx() < rockpos.getx()){
				//daca nu e liber dupa piatra jucatorul se opreste in piatra
				player.getComponent<TransformComponent>().setposition(playerPos);
			}
			else if (Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				!r->getComponent<Rock>().getTrComp()->vgety() && player.getComponent<TransformComponent>().pgetx() > rockpos.getx() &&
				!harta.WhatatPos(rockpos, 6)) {
				//daca am col pe ox intre player si piatra si piatra sta in stg si in partea op a pietrei nu e nimic - playerul impinge piatra
				r->getComponent<Rock>().setcase(3);
				r->getComponent<Rock>().getTrComp()->setsp(1);
				player.getComponent<TransformComponent>().setsp(1);
			}
			else if (Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
				!r->getComponent<Rock>().getTrComp()->vgety() && player.getComponent<TransformComponent>().pgetx() > rockpos.getx()) {
				//daca nu e liber dupa piatra - jucatorul se opreste in piatra
				player.getComponent<TransformComponent>().setposition(playerPos);
			}else if((r->getComponent<Rock>().getcase() == 2 || r->getComponent<Rock>().getcase() == 3) && player.getComponent<TransformComponent>().getsp() == 1){
				//daca am miscat piatra revin la viteza normala
				player.getComponent<TransformComponent>().setsp(3);
				r->getComponent<Rock>().setcase(0);
				r->getComponent<Rock>().getTrComp()->setsp(2);
				if (player.getComponent<TransformComponent>().pgetx() == playerPos.getx() && rockpos.getx()>rockPos[i].getx()) {
					r->getComponent<Rock>().setPosition({ rockPos[i].getx() - 1, rockpos.gety() });
				}else if(rockpos.getx() < rockPos[i].getx())
					r->getComponent<Rock>().setPosition({ rockPos[i].getx() + 1, rockpos.gety() });
			}
			else if ((ok && rockBellowNMov) && (!ok1 || (ok1 && rockBellow1NMov)) && r->getComponent<Rock>().getcase() == 0 && !(harta.WhatatPos(rockpos, 2) || harta.WhatatPos(rockpos, 3))){
				if(!((player.getComponent<TransformComponent>().pgetx() < rockpos.getx()+128 && player.getComponent<TransformComponent>().pgetx() > rockpos.getx()) &&
			 (player.getComponent<TransformComponent>().pgety() > rockpos.gety()-64 && player.getComponent<TransformComponent>().pgety() < rockpos.gety()+128)))
				//daca piatra sta pe alta piatra(doar a doua piatra de jos in sus) si are liber in drt - cade acolo
				//MERGE LA MAX 4 PIETRE SUPRAPUSE
				r->getComponent<Rock>().setcase(2);
			}else if ((ok && rockBellowNMov) && (!ok1 || (ok1 && rockBellow1NMov)) && r->getComponent<Rock>().getcase() == 0 && !(harta.WhatatPos(rockpos, 6) || harta.WhatatPos(rockpos, 5))){
				if(!((player.getComponent<TransformComponent>().pgetx() > rockpos.getx() - 128 && player.getComponent<TransformComponent>().pgetx() < rockpos.getx()) &&
					(player.getComponent<TransformComponent>().pgety() > rockpos.gety() - 64 && player.getComponent<TransformComponent>().pgety() < rockpos.gety() + 128))) {
					//daca piatra sta pe alta piatra(doar a doua piatra de jos in sus) si are liber in stg - cade acolo
					r->getComponent<Rock>().setcase(3); }
			}else if ((!ok && r->getComponent<Rock>().getcase() == 3 && !harta.WhatatPos(rockpos, 4))||
					  (!ok && r->getComponent<Rock>().getcase() == 2 && !harta.WhatatPos(rockpos, 4))) {
				//daca piatra a mers la stg sau la drt si nu mai are nimic sub ea - cade acolo
				r->getComponent<Rock>().setcase(1);
				r->getComponent<Rock>().setPosition(rockPos[i]);
				r->getComponent<Rock>().getTrComp()->setsp(2);
			}


			i++;
		}
		
		//koko made
		
		if (manager.getNrInGroup(groupPlayers)) {
			
			for (auto& m : meats) {
				Vector2D pPos = player.getComponent<TransformComponent>().getposition();
				Vector2D mPos = m->getComponent<TransformComponent>().getposition();
				if (mPos == pPos ||	
				  (mPos.getx() == pPos.getx() && (mPos.gety() + 1 == pPos.gety() || mPos.gety() + 2 == pPos.gety()) 
				|| mPos.gety() == pPos.gety() && (mPos.getx() + 1 == pPos.getx() || mPos.getx() + 2 == pPos.getx()))) {
					harta.MeatDestroy(mPos);
					m->destroy();
					meateat++;
					cout <<"Carne mancata: " << meateat << endl;
				}
			}

			for (auto& c : colliders) {
				SDL_Rect cCol = c->getComponent<ColliderComponent>().getcollider();
				
				if (Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), cCol) &&
					player.getComponent<TransformComponent>().pgetx() != playerPos.getx()) {

					player.getComponent<TransformComponent>().setposition(playerPos);
				}
				else if (harta.WhatatPos(player.getComponent<TransformComponent>().getposition(), 6)==9) {
					levelclear = true;
				}
				if (Collision::AABByplayer(player.getComponent<ColliderComponent>().getcollider(), cCol) &&
					player.getComponent<TransformComponent>().pgety() != playerPos.gety()) {

					player.getComponent<TransformComponent>().setposition(playerPos);
				}
			}
		
			camera.x = player.getComponent<TransformComponent>().pgetx() - (MAX_WIDTH - 64) / 2;
			camera.y = player.getComponent<TransformComponent>().pgety() - (MAX_HEIGHT - 64) / 2;

			if (camera.x < 0)
				camera.x = 0;
			if (camera.y < 0)
				camera.y = 0;
			if (camera.x > 2048 - MAX_WIDTH)
				camera.x = 2048 - MAX_WIDTH;
			if (camera.y > 1280 - MAX_HEIGHT)
				camera.y = 1280 - MAX_HEIGHT;
		}
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	//add stuff to render
	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& m : meats) {
		m->draw();
	}

	player.draw();

	for (auto& r : rocks) {
		r->draw();
	}
	/*for (auto& c : colliders) {
		c->draw();
	}*/
	//label.draw();

	//until here
	SDL_RenderPresent(renderer);
}

bool Game::running() {
	return isRunning;
}

void Game::setisrunning(bool cond) {
	isRunning = cond;
}

SDL_Renderer* Game::getrenderer() {
	return renderer;
}

SDL_Event Game::getevent() {
	return event;
}

void Game::setevent(SDL_Event e) {
	event = e;
}

AssetManager* Game::getassets() {
	return assets;
}

bool Game::getlevelclear() {
	return levelclear;
}