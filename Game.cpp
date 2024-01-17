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
SDL_Rect Game::camera = { 0, 0, MAX_WIDTH, MAX_HEIGHT };
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);
ItemMap harta(32, 20);
bool Game::isRunning = false;
bool Game::esc = false;
auto& imaginemenuesc(manager.addEntity());
auto& imaginemenu(manager.addEntity());
auto& imaginistart(manager.addEntity());
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
	
	mapa = new Map("terrain", 1, 64);

	assets->AddTexture("terrain", "assets/Lvl1MapTileset.png");
	assets->AddTexture("player", "assets/Luffy.png");
	assets->AddTexture("rock", "assets/Rock-animation360.png");
	assets->AddTexture("meat", "assets/meat.png");

	assets->AddTexture("1face", "assets/Luffy_face1.png");
	assets->AddTexture("2faces", "assets/Luffy_face2.png");
	assets->AddTexture("3faces", "assets/Luffy_face3.png");

	assets->AddTexture("0", "assets/Fundal/menu_esc.png");			
	assets->AddTexture("1", "assets/Fundal/menu_final_or_dead.png");	
	assets->AddTexture("2", "assets/Fundal/you_died.png");			
	assets->AddTexture("3", "assets/Fundal/omae_wa_mou_shindeiru.png");	
	assets->AddTexture("4", "assets/Fundal/Level1clear.png");			
	assets->AddTexture("5", "assets/Fundal/Level2clear.png");			
	assets->AddTexture("6", "assets/Fundal/lastLevelclear.png");	
	assets->AddTexture("7", "assets/Fundal/imag1.png");					
	assets->AddTexture("8", "assets/Fundal/imag2.png");					
	assets->AddTexture("9", "assets/Fundal/imag3.png");					
	assets->AddTexture("10", "assets/Fundal/imag4.png");					
	assets->AddTexture("11", "assets/Fundal/imag5.png");					
	assets->AddTexture("12", "assets/Fundal/imag6.png");					
	assets->AddTexture("13", "assets/Fundal/imag7.png");					
	assets->AddTexture("14", "assets/Fundal/imag8.png");					
	assets->AddTexture("15", "assets/Fundal/imag9.png");					
	assets->AddTexture("16", "assets/Fundal/imag10.png");				
	assets->AddTexture("17", "assets/Fundal/imag11.png");				
	assets->AddTexture("18", "assets/Fundal/The_Meat.png");			
	//assets->AddFont("arial", "assets/arial.ttf", 16);
	
	assets->addImages();
	assets->addFaces();
	player.addComponent<TransformComponent>( 0, 1152 );//(64*0, 64*18)
	player.addComponent<SpriteComponent>("player");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	//SDL_Color white = { 255, 255, 255, 255 };
	//label.addComponent<UILabel>(10, 10, "Test String", "arial", white);
}

auto& imagini(manager.getGroup(Game::groupImages));
auto& rocks(manager.getGroup(Game::groupRocks));
auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& players(manager.getGroup(Game::groupPlayers));
auto& meats(manager.getGroup(Game::groupMeats));

void Game::lvlinit(int lvl){
	for (auto &r : rocks) {
		r->destroy();
	}
	for (auto &m : meats) {
		m->destroy();
	}
	for (auto &c : colliders) {
		c->destroy();
	}
	
	manager.refresh();
	manager.update();
	player.getComponent<TransformComponent>().setposition({ 0, 1152 });
	player.getComponent<TransformComponent>().setvelocity({ 0, 0 });
	if (lvl == 1) {
		mapa->LoadMap("assets/Lvl1Map.map", 32, 20);
		assets->createMandR(harta, "assets/Lvl1ItemMap.Map", 32, 20);
	}else if (lvl == 2) {
		mapa->LoadMap("assets/Lvl2Map.map", 32, 20);
		assets->createMandR(harta, "assets/Lvl2ItemMap.Map", 32, 20);
	}else if (lvl == 3) {
		mapa->LoadMap("assets/Lvl3Map.map", 32, 20);
		assets->createMandR(harta, "assets/Lvl3ItemMap.Map", 32, 20);
	}
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

void Game::update() {
	if (!playerdied) {
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
				//daca piatra cade si are coliziune cu jucatorul(sub piatra) - jucatorul moare
				if (player.getComponent<TransformComponent>().pgetx() >= r->getComponent<Rock>().getPosition().getx() + 60 ||
					player.getComponent<TransformComponent>().pgetx() <= r->getComponent<Rock>().getPosition().getx() - 60) {

					player.getComponent<TransformComponent>().setposition(playerPos);
				}else {
					playerdied = true;
					livesleft--;
					break;
				}
			}
			else if (r->getComponent<Rock>().getcase() == 0 && !ok && !(harta.WhatatPos(rockpos, 4) ||
				(Collision::AABBy(player.getComponent<ColliderComponent>().getcollider(), r->getComponent<ColliderComponent>().getcollider()) &&
					player.getComponent<TransformComponent>().pgety() > rockpos.gety()))) {
				//daca piatra sta si nu are sub ea jucatorul, alta piatra, zid sau carne - piatra cade
				r->getComponent<Rock>().setcase(1);
			}
			else if (r->getComponent<Rock>().getcase() == 0 && !ok && !(harta.WhatatPos(rockpos, 4)==1 || harta.WhatatPos(rockpos, 4) == 3  ||
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
				r->getComponent<Rock>().getTrComp()->psetx(rockPos[i].getx());
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
		
		
		if (!playerdied) {
			
			for (auto& m : meats) {
				Vector2D pPos = player.getComponent<TransformComponent>().getposition();
				Vector2D mPos = m->getComponent<TransformComponent>().getposition();
				if (mPos == pPos ||	
				  (mPos.getx() == pPos.getx() && (mPos.gety() + 1 == pPos.gety() || mPos.gety() + 2 == pPos.gety()) 
				|| mPos.gety() == pPos.gety() && (mPos.getx() + 1 == pPos.getx() || mPos.getx() + 2 == pPos.getx()))) {
					harta.MeatDestroy(mPos);
					m->destroy();
					meateat++;
					if (meateat == 100) {
						meateat = 0;
						if(livesleft<3)
							livesleft++;
					}
				}
			}

			for (auto& c : colliders) {
				SDL_Rect cCol = c->getComponent<ColliderComponent>().getcollider();
				
				if (Collision::AABBxplayer(player.getComponent<ColliderComponent>().getcollider(), cCol) &&
					player.getComponent<TransformComponent>().pgetx() != playerPos.getx()) {

					player.getComponent<TransformComponent>().setposition(playerPos);
				}
				if (Collision::AABByplayer(player.getComponent<ColliderComponent>().getcollider(), cCol) &&
					player.getComponent<TransformComponent>().pgety() != playerPos.gety()) {

					player.getComponent<TransformComponent>().setposition(playerPos);
				}
			}
			if (harta.WhatatPos(player.getComponent<TransformComponent>().getposition(), 6) == 9) {
				levelclear = true;
			}
			else if (player.getComponent<TransformComponent>().pgetx()<0) {
				player.getComponent<TransformComponent>().psetx(0);
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
	int count = 0;
	for (auto& i : imagini) {
		if (count == 0 && esc)
			i->draw();//escape
		if (count == 1 && ((curentlevel == 4 && exitlvl4) || (!livesleft && exitdead)))
			i->draw();//menu - you died for good or finished game
		if (count == 2 && playerdied && livesleft)
			i->draw();//you died
		if (count == 3 && !livesleft && !exitdead)
			i->draw();//omae wa mou shindeiru
		if (count == 4 && levelclear && curentlevel == 1)
			i->draw();//level 1 clear
		if (count == 5 && levelclear && curentlevel == 2)
			i->draw();//level 2 clear
		if (count == 6 && levelclear && curentlevel == 3)
			i->draw();//last level clear
		if (count == 7 + right && right >= 0 && right<=10)
			i->draw();//begining panels
		if (count == 18 && curentlevel == 4 && !exitlvl4)
			i->draw();//the Meat
		if (count == 19 && livesleft == 1)
			i->draw();//o fata
		if (count == 20 && livesleft == 2)
			i->draw();//doua fete
		if (count == 21 && livesleft == 3)
			i->draw();//trei fete
		count++;
	}
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

void Game::setlevelclear(bool ok) {
	levelclear = ok;
}

bool Game::getesc() {
	return esc;
}

void Game::setesc(bool _esc) {
	esc = _esc;
}

int Game::getclevel() {
	return curentlevel;
}

void Game::setclevel(int lvl) {
	curentlevel = lvl;
}

void Game::setmeat(int m) {
	meateat = m;
}