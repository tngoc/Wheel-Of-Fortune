#ifndef H_QUIZ_H
#define H_QUIZ_H

#include "Engine/Advanced2D.h"
#include "button.h"
#include <atlbase.h>
#include "xmllite.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "utils.h"

using namespace std;
using namespace Advanced2D;
using namespace Utils;

class Quiz : public Sprite {
private:
	string question;
	string answer;
	std::vector<int> count_words; //lưu index vị trí bắt đầu kết thúc của mỗi từ (index các khoảng trống)
	int number_of_words; //số từ trong answer
	std::list<Button*> letters; //lưu từng ký tự answers trong này
public:
	Quiz();
	Quiz(string,string);

	string getQuestion() const {return question;}
	string getAnswer() const {return answer;}
	void setQuestion(string pquestion) {question = pquestion;}
	void setAnswer(string panswer) {
		answer.clear();
		answer = panswer;}
	void setQuizPos(double width_button, double height_button, double x1, double y1, double x2, double y2);
	void drawQuiz();
	void addQuizEntity();
	int inputQuiz(int i);
	void addLetter(int );
	void arrangeLetter();
	void update();
	void reset();
};

#endif