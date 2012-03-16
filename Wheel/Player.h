#ifndef _H_PLAYER_H
#define _H_PLAYER_H

#include "Engine/Advanced2D.h"
#include "Wheel.h"
#include "Keyboard.h"
#include "Quiz.h"

extern Keyboard* keyboard;

using namespace Advanced2D;
using namespace	std;

class Player : public Sprite {
	enum P_STATUS {AWAIT=100,PLAYING,CHOSING,CHOSED,LOSED,WIN_STAGE};
	private:
		string name;
		static int numberPlayer;
		static int currentPlayer;
		int total_score;
		int score;
		int status;
		int turn_left;
		int turn_gift;
	public :
		Player();
		Player(string );
		~Player() {Sprite::~Sprite();}
		static int getCurrentPlayer() {return currentPlayer;}
		static int getNumPlayer() {return numberPlayer;}
		string getName() const {return name;}
		int getScore() const {return score;}
		int getLeftover() const {return turn_left;}
		int getStatus() const {return status;}
		int getGiftturn() const {return turn_gift;}

		static void setCurrentPlayer(int current) {currentPlayer =  current;}
		static void setNumPlayer(int num) {numberPlayer = num;}
		void setName(string na) {name = na;}
		void setScore(int s) {score = s;}
		void setTurnLeft(int l) {turn_left = l; if(turn_left == 0) status = LOSED;}
		void setTurnLeft() {turn_left--;if(turn_left == 0) status = LOSED;}
		void setStatus(P_STATUS sta) {status = sta;}
		void winScore(int sco) {score = sco;}

		void winStage();
		void reset();

		int start_play();
		int spin(Wheel*);
		bool answer();
		bool fullanswer();
		void end_play(P_STATUS);
};

#endif
