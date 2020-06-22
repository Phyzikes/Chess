#include <iostream>
//#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

////////////////////////////////////////////////   КОНСТАНТЫ, ГЛОБАЛЬНЫЕ ПАРАМЕТРЫ, ДОСКА   ////////////////////////////////////////////////
//Массив рамки доски
char s1 = 201;
char s2 = 200;
char s3 = 187;
char s4 = 188;
char s5 = 205;
char s6 = 186;
char s7 = 209;
char s8 = 207;
char s9 = 199;
char s10 = 182;
char s11 = 197;
char s12 = 179;
char s13 = 196;
char fr = 176;

// Чей ход
string moveState = "white";
// Конец игры
bool endGame = false;
// Начальный король
string curKing = "WQ";

// Ходили ли фигуры уже (для рокировки)
bool movedWQ_d1 = false;
bool movedWR_a1 = false;
bool movedWR_h1 = false;
bool movedBQ_d8 = false;
bool movedBR_a8 = false;
bool movedBR_h8 = false;

//Объявляем заранее (для рокировки)
void showMenu();

// Забиваем вектор парами "название ячейки -> что в ней"
vector<vector<pair<string, string>>> desk;
void fillDesk() {
	//ряд 1
	vector<pair<string, string>> row1;
	row1.emplace_back("a1", "WR");
	row1.emplace_back("b1", "WN");
	row1.emplace_back("c1", "WB");
	row1.emplace_back("d1", "WQ");
	row1.emplace_back("e1", "WK");
	row1.emplace_back("f1", "WB");
	row1.emplace_back("g1", "WN");
	row1.emplace_back("h1", "WR");
	desk.push_back(row1);
	//ряд 2
	vector<pair<string, string>> row2;
	
	row2.emplace_back("a2", "WP");
	row2.emplace_back("b2", "WP");
	row2.emplace_back("c2", "WP");
	row2.emplace_back("d2", "WP");
	row2.emplace_back("e2", "WP");
	row2.emplace_back("f2", "WP");
	row2.emplace_back("g2", "WP");
	row2.emplace_back("h2", "WP");
	/*
	row2.emplace_back("a2", "  ");
	row2.emplace_back("b2", "  ");
	row2.emplace_back("c2", "  ");
	row2.emplace_back("d2", "  ");
	row2.emplace_back("e2", "  ");
	row2.emplace_back("f2", "  ");
	row2.emplace_back("g2", "  ");
	row2.emplace_back("h2", "  ");
	*/
	desk.push_back(row2);
	//ряд 3-6
	for (int i = 3; i < 7; i++) {
		vector<pair<string, string>> rowMiddle;
		for (char j = 'a'; j < 'i'; j++) {
			rowMiddle.emplace_back(j+to_string(i), "  ");
		}
		desk.push_back(rowMiddle);
	}
	//ряд 7
	vector<pair<string, string>> row7;
	
	row7.emplace_back("a7", "BP");
	row7.emplace_back("b7", "BP");
	row7.emplace_back("c7", "BP");
	row7.emplace_back("d7", "BP");
	row7.emplace_back("e7", "BP");
	row7.emplace_back("f7", "BP");
	row7.emplace_back("g7", "BP");
	row7.emplace_back("h7", "BP");
	/*
	row7.emplace_back("a7", "  ");
	row7.emplace_back("b7", "  ");
	row7.emplace_back("c7", "  ");
	row7.emplace_back("d7", "  ");
	row7.emplace_back("e7", "  ");
	row7.emplace_back("f7", "  ");
	row7.emplace_back("g7", "  ");
	row7.emplace_back("h7", "  ");
	*/
	desk.push_back(row7);
	//ряд 8
	vector<pair<string, string>> row8;
	row8.emplace_back("a8", "BR");
	row8.emplace_back("b8", "BN");
	row8.emplace_back("c8", "BB");
	row8.emplace_back("d8", "BQ");
	row8.emplace_back("e8", "BK");
	row8.emplace_back("f8", "BB");
	row8.emplace_back("g8", "BN");
	row8.emplace_back("h8", "BR");
	desk.push_back(row8);
}
// Показываем на экран текущую доску
void showDesk() {
	// ПОКАЗЫВАЕТ НА ЭКРАН
	cout << endl;
	cout << "     a" << "   b" << "   c" << "   d" << "   e" << "   f" << "   g" << "   h" << endl;
	//верхний ряд
	cout << "   " << s1;
	cout << s5 << s5;
	for (int i = 0; i < 7; i++) {
		cout << s5 << s7 << s5 << s5;
	}
	cout << s5 << s3;
	cout << endl;
	//Основной блок
	for (int t = 0; t < 7; t++) {
		//ряд с буквами
		cout << " " << t + 1 << " ";
		cout << s6;
		for (int i = 0; i < 7; i++) {
			cout << desk[t][i].second << " " << s12;
		}
		cout << desk[t][7].second << " " << s6 << " " << t + 1;
		//ряд без букв
		cout << endl;
		cout << "   " << s9;
		for (int i = 0; i < 7; i++) {
			cout << s13 << s13 << s13 << s11;
		}
		cout << s13 << s13 << s13 << s10;
		cout << endl;
	}
	//еще раз ряд с буквами
	cout << " 8 " << s6;
	for (int i = 0; i < 7; i++) {
		cout << desk[7][i].second << " " << s12;
	}
	cout << desk[7][7].second << " " << s6 << " 8";
	//нижний ряд
	cout << endl;
	cout << "   " << s2;
	cout << s5 << s5;
	for (int i = 0; i < 7; i++) {
		cout << s5 << s8 << s5 << s5;
	}
	cout << s5 << s4;
	cout << endl;
	cout << "     a" << "   b" << "   c" << "   d" << "   e" << "   f" << "   g" << "   h" << endl << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Объявление для рокировки
bool validMoveCheck(string figure, string fromTo, string whereTo);
// Проверка рокировки (разрешено ли)
bool validCheckCastling(string castleCell) {
	bool CC = true;
	if (castleCell == "h8") {
		// Идет ли какая - нибудь белая фигура на одну из позиций длинной рокировки
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'W') {
					string tempWhiteFigure = desk[i][j].second;
					string tempWhitePos = desk[i][j].first;
					if (validMoveCheck(tempWhiteFigure, tempWhitePos, "d8") ||
						validMoveCheck(tempWhiteFigure, tempWhitePos, "e8") ||
						validMoveCheck(tempWhiteFigure, tempWhitePos, "f8") ||
						validMoveCheck(tempWhiteFigure, tempWhitePos, "g8") ) {
						CC = false;
					}
				}
			}
		}
	}
	if (castleCell == "a8") {
		// Идет ли какая - нибудь белая фигура на одну из позиций короткой рокировки
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'W') {
					string tempWhiteFigure = desk[i][j].second;
					string tempWhitePos = desk[i][j].first;
					if (validMoveCheck(tempWhiteFigure, tempWhitePos, "d8") ||
						validMoveCheck(tempWhiteFigure, tempWhitePos, "c8") ||
						validMoveCheck(tempWhiteFigure, tempWhitePos, "b8")) {
						CC = false;
					}
				}
			}
		}
	}
	if (castleCell == "h1") {
		// Идет ли какая - нибудь черная фигура на одну из позиций длинной рокировки
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'B') {
					string tempBlackFigure = desk[i][j].second;
					string tempBlackPos = desk[i][j].first;
					if (validMoveCheck(tempBlackFigure, tempBlackPos, "d1") ||
						validMoveCheck(tempBlackFigure, tempBlackPos, "e1") ||
						validMoveCheck(tempBlackFigure, tempBlackPos, "f1") ||
						validMoveCheck(tempBlackFigure, tempBlackPos, "g1")) {
						CC = false;
					}
				}
			}
		}
	}
	if (castleCell == "h1") {
		// Идет ли какая - нибудь черная фигура на одну из позиций короткой рокировки
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'B') {
					string tempBlackFigure = desk[i][j].second;
					string tempBlackPos = desk[i][j].first;
					if (validMoveCheck(tempBlackFigure, tempBlackPos, "d1") ||
						validMoveCheck(tempBlackFigure, tempBlackPos, "c1") ||
						validMoveCheck(tempBlackFigure, tempBlackPos, "b1")) {
						CC = false;
					}
				}
			}
		}
	}
	return CC;
}

////////////////////////////////////////////////   ФУНКЦИИ НЕПОСРЕДСТВЕННОЙ ОБРАБОТКИ   ////////////////////////////////////////////////
///////////////////////////  1. ФУНКЦИИ МЕНЮ   ///////////////////////////
void move() {
	cout << "Let's move:";
};
// Рокировка
void castling() {
	cout << "You are doing castling..." << endl;
	string posRook;
	if (moveState == "white") {
		do {
			cout << "Choose [a1] or [h1]:\t";
			cin >> posRook;
		} while (posRook != "a1" && posRook != "h1");
	}
	else {
		do {
			cout << "Choose [a8] or [h8]:\t";
			cin >> posRook;
		} while (posRook != "a8" && posRook != "h8");
	}
	// Рокировка для черных
	if (movedBQ_d8 == false && moveState == "black") {
		if (posRook == "h8" && movedBR_h8 == false) {
			if (desk[7][4].second[0] == ' ' && desk[7][5].second[0] == ' ' && desk[7][6].second[0] == ' ') {
				for (int i = 3; i <= 7; i++) {
					if (validCheckCastling("h8")) {
						desk[7][3].second = "  ";
						desk[7][4].second = "  ";
						desk[7][5].second = "BR";
						desk[7][6].second = "BQ";
						desk[7][7].second = "  ";
						movedBQ_d8 = true;
						movedBR_h8 = true;
						moveState = "white";
						showMenu();
					}
				}
			}
		}
		else if (posRook == "a8" && movedBR_a8 == false) {
			if (desk[7][1].second[0] == ' ' && desk[7][2].second[0] == ' ') {
				for (int i = 0; i <= 3; i++) {
					if (validCheckCastling("a8")) {
						desk[7][0].second = "  ";
						desk[7][1].second = "BQ";
						desk[7][2].second = "BR";
						desk[7][3].second = "  ";
						movedBQ_d8 = true;
						movedBR_a8 = true;
						moveState = "white";
						showMenu();
					}
				}
			}
		}
	}
	// Рокировка для белых
	if (movedWQ_d1 == false && moveState == "white") {
		if (posRook == "h1" && movedWR_h1 == false) {
			if (desk[0][4].second[0] == ' ' && desk[0][5].second[0] == ' ' && desk[0][6].second[0] == ' ') {
				for (int i = 3; i <= 7; i++) {
					if (validCheckCastling("h1")) {
						desk[0][3].second = "  ";
						desk[0][4].second = "  ";
						desk[0][5].second = "WR";
						desk[0][6].second = "WQ";
						desk[0][7].second = "  ";
						movedWQ_d1 = true;
						movedWR_h1 = true;
						moveState = "black";
						showMenu();
					}
				}
			}
		}
		else if (posRook == "a1" && movedWR_a1 == false) {
			if (desk[0][1].second[0] == ' ' && desk[0][2].second[0] == ' ') {
				for (int i = 0; i <= 3; i++) {
					if (validCheckCastling("a1")) {
						desk[0][0].second = "  ";
						desk[0][1].second = "WQ";
						desk[0][2].second = "WR";
						desk[0][3].second = "  ";
						movedWQ_d1 = true;
						movedWR_a1 = true;
						moveState = "black";
						showMenu();
					}
				}
			}
		}
	}
	cout << "Can't do castling!" << endl;
};

void restart() {
	cout << "restart";
	desk.clear();
	fillDesk();
	showDesk();
	moveState = "white";
	movedWQ_d1 = false;
	movedWR_a1 = false;
	movedWR_h1 = false;
	movedBQ_d8 = false;
	movedBR_a8 = false;
	movedBR_h8 = false;
};

void showMenu() {
	// Показываем доску
	showDesk();
	// Кто сейчас ходит
	cout << "Now " << moveState << " play:" << endl;
	// Показываем меню
	for (int i = 0; i < 20; i++) cout << fr; cout << " MENU "; for (int i = 0; i < 20; i++) cout << fr; cout << endl;
	cout << fr << "m - move\t" << fr << " c - castling\t" << fr << " r - restart" << fr << endl;
	for (int i = 0; i < 46; i++) cout << fr; cout << endl;
	// Выбираем пункт меню
	string menuChoise;
	bool cor = false;
	do {
		cin >> menuChoise;
		if (menuChoise[0] == 'm') {
			move();
			cor = true;
		}
		else if (menuChoise[0] == 'c') {
			castling();
			cor = true;
		}
		else if (menuChoise[0] == 'r') {
			cout << "If you wish to restart, press [y]?" << endl;
			string yes;
			cin >> yes;
			if (yes[0] == 'y') {
				restart();
				cout << "White begins:";
				cor = true;
			}
			else {
				cor = false;
				cout << "Please, make a correct choise!" << endl;
			}
		}
		else {
			cout << "Your choise is incorrect! Please, make a correct choise!" << endl;
		}
	} while (!cor);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////  2. ФУНКЦИИ ПРОВЕРКИ ХОДА   ///////////////////////
string figure;
string fromTo;
string whereTo;

// Вводим параметры хода
void enterMove() {
	cout << endl;
	do {
		cout << "Enter correct figure's name:\t\t";
		cin >> figure;
	} while (figure != "WR" && figure != "WN" && figure != "WB" && figure != "WQ" && figure != "WK" && figure != "WP" &&
			 figure != "BR" && figure != "BN" && figure != "BB" && figure != "BQ" && figure != "BK" && figure != "BP"
			);
	do {
		cout << "Enter correct figure's position:\t";
		cin >> fromTo;
	} while (
			 (fromTo[0] != 'a' && fromTo[0] != 'b' && fromTo[0] != 'c' && fromTo[0] != 'd' && 
			  fromTo[0] != 'e' && fromTo[0] != 'f' && fromTo[0] != 'g' && fromTo[0] != 'h') ||
			 (fromTo[1] != '1' && fromTo[1] != '2' && fromTo[1] != '3' && fromTo[1] != '4' &&
			  fromTo[1] != '5' && fromTo[1] != '6' && fromTo[1] != '7' && fromTo[1] != '8') ||
			 (fromTo[2] != '\0')
			);
	do {
	cout << "Enter correct place you wish to go:\t";
	cin >> whereTo;
	} while (
			 (whereTo[0] != 'a' && whereTo[0] != 'b' && whereTo[0] != 'c' && whereTo[0] != 'd' &&
			  whereTo[0] != 'e' && whereTo[0] != 'f' && whereTo[0] != 'g' && whereTo[0] != 'h') ||
			 (whereTo[1] != '1' && whereTo[1] != '2' && whereTo[1] != '3' && whereTo[1] != '4' &&
			  whereTo[1] != '5' && whereTo[1] != '6' && whereTo[1] != '7' && whereTo[1] != '8') ||
			 (whereTo[2] != '\0')
			);
}

int validNum = 0;
///////  ПОДФУНКЦИИ ПРОВЕРКИ  ///////
// 2.1. Цвет выбранной фигуры верный
void ownColorChoise(string figure, string fromTo, string whereTo) {
	int temp = 0;
	if ((moveState == "white" && figure[0] == 'W') || (moveState == "black" && figure[0] == 'B')) {
		++validNum;
		++temp;
	}
	if (temp == 0) {
		//cout << "Pick your color team!" << endl;
	}
}
// 2.2. Есть фигура с таким именем в такой позиции 
void enableFigureFrom(string figure, string fromTo, string whereTo) {
	int temp = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((desk[i][j].second == figure) && (desk[i][j].first == fromTo)) {
				++validNum;
				++temp;
			}
		}
	}
	if (temp == 0) {
		//cout << "ERROR 2. Can't find this figure on desk! Please, reenter!" << endl;
	}
}
// 2.3. Выходим ли за рамки доски
void limitsFromWhere(string figure, string fromTo, string whereTo) {
	if (fromTo[0] >= 97 && fromTo[0] <= 104 && fromTo[1] >= 49 && fromTo[1] <= 56 && whereTo[0] >= 97 && whereTo[0] <= 104 && whereTo[1] >=49 && whereTo[1] <= 56) {
		++validNum;
	}
	else {
		//cout << "Desk has only 64 cells!" << endl;
	}
}
// 2.4. На where не стоит фигура своего цвета
void notRelationsWhere(string figure, string fromTo, string whereTo) {
	int temp = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((desk[i][j].first == whereTo) && (desk[i][j].second[0] != figure[0])) {
				++validNum;
				++temp;
			}
		}
	}
	if (temp == 0) {
		//cout << "You can't go there, there has already chills your Ally!" << endl;
	}
}
// ДЛЯ 2.5. ПИШЕМ ОТДЕЛЬНО ПРОВЕРКИ ХОДОВ ПО ДОСКЕ
// Проверка на ход горизонтально
bool validHorisontal(string fromTo, string whereTo) {
	int num = fromTo[1];
	int sym;
	if (fromTo[0] < whereTo[0]) {
		for (sym = fromTo[0] - 97 + 1; sym < whereTo[0] - 97; sym++) {
			if (desk[num - 1 - 48][sym].second[0] != ' ') {
				return false;
			}
		}
	}
	else if (fromTo[0] > whereTo[0]) {
		for (sym = fromTo[0] - 97 - 1; sym > whereTo[0] - 97; sym--) {
			if (desk[num - 1 - 48][sym].second[0] != ' ') {
				return false;
			}
		}
	}
	return true;
}
// Проверка на ход вертикально
bool validVertical(string fromTo, string whereTo) {
	int sym = fromTo[0];
	int num;
	if (fromTo[1] < whereTo[1]) {
		for (num = fromTo[1] - 49 + 1; num < whereTo[1] - 49; num++) {
			if (desk[num][sym - 97].second[0] != ' ') {
				return false;
			}
		}
	}
	else if (fromTo[1] > whereTo[1]) {
		for (num = fromTo[1] - 49 - 1; num > whereTo[1] - 49; num--) {
			if (desk[num][sym - 97].second[0] != ' ') {
				return false;
			}
		}
	}
	return true;
}
// Проверка на ход диагонально
bool validDiagonal(string fromTo, string whereTo) {
	int sym;
	int num;
	if (fromTo[0] < whereTo[0]) {
		// leftTop --> rightBottom
		if (fromTo[1] < whereTo[1]) {
			for (num = fromTo[1] - 49 + 1, sym = fromTo[0] - 97 + 1; num < whereTo[1] - 49, sym < whereTo[0] - 97; num++, sym++) {
				if (num < 0) num++;
				if (num > 7) num--;
				if (desk[num][sym].second[0] != ' ') {
					return false;
				}
			}
		}
		// leftBottom --> rightTop
		else if (fromTo[1] > whereTo[1]) {
			for (num = fromTo[1] - 49 - 1, sym = fromTo[0] - 97 + 1; num > whereTo[1] - 49, sym < whereTo[0] - 97; num--, sym++) {
				if (num < 0) num++;
				if (num > 7) num--;
				if (desk[num][sym].second[0] != ' ') {
					return false;
				}
			}
		}
	}///////////////////////////////////////////////////////////////////////////////////убрал вначале else
	if (fromTo[0] > whereTo[0]) {
		// rightTop --> leftBottom
		if (fromTo[1] < whereTo[1]) {
			for (num = fromTo[1] - 49 + 1, sym = fromTo[0] - 97 - 1; num < whereTo[1] - 49, sym > whereTo[0] - 97; num++, sym--) {
				if (num < 0) num++;
				if (num > 7) num--;
				if (desk[num][sym].second[0] != ' ') {
					return false;
				}
			}
		}
		// rightBottom --> leftTop
		else if (fromTo[1] > whereTo[1]) {
			for (num = fromTo[1] - 49 - 1, sym = fromTo[0] - 97 - 1; num > whereTo[1] - 49, sym > whereTo[0] - 97; num--, sym--) {
				if (num < 0) num++;
				if (num > 7) num--;
				if (desk[num][sym].second[0] != ' ') {
					return false;
				}
			}
		}
	}
	return true;
}
// 2.5. Фигура может идти по этой траектории
void trueTrajectory(string figure, string fromTo, string whereTo) {
	// ЛОЩАДЬ
	if (figure == "WN" || figure == "BN") {
		if (
			((fromTo[0] == whereTo[0] + 2) && (fromTo[1] == whereTo[1] + 1)) ||
			((fromTo[0] == whereTo[0] + 2) && (fromTo[1] == whereTo[1] - 1)) ||
			((fromTo[0] == whereTo[0] - 2) && (fromTo[1] == whereTo[1] + 1)) ||
			((fromTo[0] == whereTo[0] - 2) && (fromTo[1] == whereTo[1] - 1)) ||
			((fromTo[0] == whereTo[0] + 1) && (fromTo[1] == whereTo[1] + 2)) ||
			((fromTo[0] == whereTo[0] + 1) && (fromTo[1] == whereTo[1] - 2)) ||
			((fromTo[0] == whereTo[0] - 1) && (fromTo[1] == whereTo[1] + 2)) ||
			((fromTo[0] == whereTo[0] - 1) && (fromTo[1] == whereTo[1] - 2))
			) {
			++validNum;
		}
		else {
			//cout << "This is not HORSE style!" << endl;
		}
	}
	// ЛАДЬЯ
	if (figure == "WR" || figure == "BR") {
		int temp = 0;
		if (fromTo[0] == whereTo[0] || fromTo[1] == whereTo[1]) { 
			++validNum;
			++temp;
		}
		if (fromTo[1] == whereTo[1]) {
			if (validHorisontal(fromTo, whereTo) == false) {
				--validNum; 
			}
		}
		else if (fromTo[0] == whereTo[0]) {
			if (validVertical(fromTo, whereTo) == false) {
				--validNum;
			}
		}
		if (temp == 0) {
			//cout << "This is not ROOK style!" << endl;
		}
	}
	// СЛОН
	if (figure == "WB" || figure == "BB") {
		//int temp = 0;
		for (int i = 1; i < 8; i++) {
			if (
				((fromTo[0] == whereTo[0] + i) && (fromTo[1] == whereTo[1] + i)) ||
				((fromTo[0] == whereTo[0] + i) && (fromTo[1] == whereTo[1] - i)) ||
				((fromTo[0] == whereTo[0] - i) && (fromTo[1] == whereTo[1] + i)) ||
				((fromTo[0] == whereTo[0] - i) && (fromTo[1] == whereTo[1] - i))
				) {
				++validNum;
				//++temp;
			}
		}
		if (validDiagonal(fromTo, whereTo) == false) { 
			--validNum; 
		}
		//if (temp == 0) {
			//cout << "This is not ELEPHANT style!" << endl;
		//}
	}
	// ФЕРЗЬ
	if (figure == "WK" || figure == "BK") {
		if (fromTo[0] == whereTo[0] || fromTo[1] == whereTo[1]) { ++validNum; }
		if (fromTo[1] == whereTo[1]) {
			if (validHorisontal(fromTo, whereTo) == false) { 
				--validNum; 
			}
		}
		else if (fromTo[0] == whereTo[0]) {
			if (validVertical(fromTo, whereTo) == false) { 
				--validNum; 
			}
		}
		for (int i = 1; i < 8; i++) {
			if (
				((fromTo[0] == whereTo[0] + i) && (fromTo[1] == whereTo[1] + i)) ||
				((fromTo[0] == whereTo[0] + i) && (fromTo[1] == whereTo[1] - i)) ||
				((fromTo[0] == whereTo[0] - i) && (fromTo[1] == whereTo[1] + i)) ||
				((fromTo[0] == whereTo[0] - i) && (fromTo[1] == whereTo[1] - i))
				) {
				++validNum;
			}
		}
		if (validDiagonal(fromTo, whereTo) == false) { 
			--validNum; 
		}
	}
	// КОРОЛЬ
	if (figure == "WQ" || figure == "BQ") {
		int temp = 0;
		if (
			((fromTo[0] == whereTo[0] + 1) && (fromTo[1] == whereTo[1] + 1)) ||
			((fromTo[0] == whereTo[0] + 1) && (fromTo[1] == whereTo[1] - 1)) ||
			((fromTo[0] == whereTo[0] - 1) && (fromTo[1] == whereTo[1] + 1)) ||
			((fromTo[0] == whereTo[0] - 1) && (fromTo[1] == whereTo[1] - 1)) ||
			((fromTo[0] == whereTo[0]) && (fromTo[1] == whereTo[1] + 1)) ||
			((fromTo[0] == whereTo[0]) && (fromTo[1] == whereTo[1] - 1)) ||
			((fromTo[0] == whereTo[0] + 1) && (fromTo[1] == whereTo[1])) ||
			((fromTo[0] == whereTo[0] - 1) && (fromTo[1] == whereTo[1]))
			) {
			++validNum;
			++temp;
		}
		if (temp == 0) {
			//cout << "This is not KING style!" << endl;
		}
	}
	// ПЕШКА
	if (figure == "WP" || figure == "BP") {
		int temp = 0;
		// Проверка боя пешкой противника по диагонали 
		string posPawn = desk[fromTo[1] - 49][fromTo[0] - 97].first; //координаты на доске этой пешки
		if (figure == "WP") {
			if (fromTo[0] - 97 == 0) {
				string tempPos = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 + 1].first;
				string tempVal = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 + 1].second;
				if (whereTo == tempPos && tempVal[0] != figure[0] && tempVal[0] != ' ') {
					++validNum;
					++temp;
				}
			}
			else if (fromTo[0] - 97 == 7) {
				string tempPos = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 - 1].first;
				string tempVal = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 - 1].second;
				if (whereTo == tempPos && tempVal[0] != figure[0] && tempVal[0] != ' ') {
					++validNum;
					++temp;
				}
			}
			else if (fromTo[0] - 97 > 0 && fromTo[0] - 97 < 7) {
				string tempPos1 = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 + 1].first;
				string tempVal1 = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 + 1].second;
				string tempPos2 = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 - 1].first;
				string tempVal2 = desk[fromTo[1] - 49 + 1][fromTo[0] - 97 - 1].second;
				if (whereTo == tempPos1 && tempVal1[0] != figure[0] && tempVal1[0] != ' ') {
					++validNum;
					++temp;
				}
				if (whereTo == tempPos2 && tempVal2[0] != figure[0] && tempVal2[0] != ' ') {
					++validNum;
					++temp;
				}
			}
		}
		else if (figure == "BP") {
			if (fromTo[0] - 97 == 0) {
				string tempPos = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 + 1].first;
				string tempVal = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 + 1].second;
				if (whereTo == tempPos && tempVal[0] != figure[0] && tempVal[0] != ' ') {
					++validNum;
					++temp;
				}
			}
			else if (fromTo[0] - 97 == 7) {
				string tempPos = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 - 1].first;
				string tempVal = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 - 1].second;
				if (whereTo == tempPos && tempVal[0] != figure[0] && tempVal[0] != ' ') {
					++validNum;
					++temp;
				}
			}
			else if (fromTo[0] - 97 > 0 && fromTo[0] - 97 < 7) {
				string tempPos1 = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 + 1].first;
				string tempVal1 = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 + 1].second;
				string tempPos2 = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 - 1].first;
				string tempVal2 = desk[fromTo[1] - 49 - 1][fromTo[0] - 97 - 1].second;
				if (whereTo == tempPos1 && tempVal1[0] != figure[0] && tempVal1[0] != ' ') {
					++validNum;
					++temp;
				}
				if (whereTo == tempPos2 && tempVal2[0] != figure[0] && tempVal2[0] != ' ') {
					++validNum;
					++temp;
				}
			}
		}
		// Стандартный ход пешкой
		if (whereTo[0] == fromTo[0] && desk[whereTo[1] - 49][whereTo[0] - 97].second[0] == ' ') {
			// Белая пешка
			if (figure == "WP") {
				if (whereTo[1] > fromTo[1]) {
					if ((fromTo[1] == '2' && (whereTo[1] == '3' || whereTo[1] == '4')) || (whereTo[1] == fromTo[1] + 1)) {
						++validNum;
						++temp;
					}
				}
			}
			// Черная пешка
			if (figure == "BP") {
				if (whereTo[1] < fromTo[1]) {
					if ((fromTo[1] == '7' && (whereTo[1] == '6' || whereTo[1] == '5')) || (whereTo[1] == fromTo[1] - 1)) {
						++validNum;
						++temp;
					}
				}
			}
		}
		if (temp == 0) {
			//cout << "This is not PAWN style!" << endl;
		}
	}
}
//////////////////////////////////////

// Возможность хода
bool validMove(string figure, string fromTo, string whereTo) {
	ownColorChoise(figure, fromTo, whereTo);	// 1
	enableFigureFrom(figure, fromTo, whereTo);	// 2
	limitsFromWhere(figure, fromTo, whereTo);	// 3
	notRelationsWhere(figure, fromTo, whereTo); // 4
	trueTrajectory(figure, fromTo, whereTo);	// 5
	if (validNum == 5) {
		validNum = 0;
		return true;
	}
	validNum = 0;
	//cout << "No valid move!" << endl;
	return false;
}

string oldFigure;
// Делаем ход
void makeMove(string figure, string fromTo, string whereTo) {
	for (auto& i : desk) {
		for (auto& j : i) {
			if (j.first == fromTo && j.second == figure) {
				j.second = "  ";
			}
			if (j.first == whereTo) {
				oldFigure = j.second; // старое значение клетки
				j.second = figure;
				// 1. Проверяем Ладьи и Королей для дальнейших рокировок
				if (figure == "WR") {
					if (fromTo == "a1") {
						movedWR_a1 = true;
					}
					else if (fromTo == "h1") {
						movedWR_h1 = true;
					}
				}
				else if (figure == "BR") {
					if (fromTo == "a8") {
						movedBR_a8 = true;
					}
					else if (fromTo == "h8") {
						movedBR_h8 = true;
					}
				}
				else if (figure == "WQ") {
					movedWQ_d1 = true;
				}
				else if (figure == "BQ") {
					movedBQ_d8 = true;
				}
				// 2. Проверка пешки на дамку
				else if (figure == "BP" || figure == "WP") {
					// Проверяем пешку на дамку следующим ходом
					bool promo = false;
					string promoWhite;
					// БЕЛЫЕ:
					if (figure == "WP" && whereTo[1] == '8' && fromTo[1] == '7') {
						cout << "Write FIGURE to Promotion:" << endl;
						cout << "WR | WN | WB | WK" << endl;
						do {
							cin >> promoWhite;
							if (promoWhite == "WR" || promoWhite == "WN" || promoWhite == "WB" || promoWhite == "WK") {
								promo = true;
							}
						} while (promo == false);
						desk[7][int(whereTo[0] - 97)].second = promoWhite;
					}
					// ЧЕРНЫЕ:
					string promoBlack;
					if (figure == "BP" && whereTo[1] == '1' && fromTo[1] == '2') {
						cout << "Write FIGURE to Promotion:" << endl;
						cout << "BR | BN | BB | BK" << endl;
						do {
							cin >> promoBlack;
							if (promoBlack == "BR" || promoBlack == "BN" || promoBlack == "BB" || promoBlack == "BK") {
								promo = true;
							}
						} while (promo == false);
						desk[0][int(whereTo[0] - 97)].second = promoBlack;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////   ФУНКЦИИ  ШАХ | МАТ | ПАТ /////////////////////////////
// Возвращаем ход обратно
void cancelMove(string figure, string fromTo, string whereTo) {
	for (auto& i : desk) {
		for (auto& j : i) {
			if (j.first == whereTo && j.second == figure) {
				j.second = oldFigure;
			}
			if (j.first == fromTo) {
				j.second = figure;
			}
		}
	}
}

// Проверяем возможность хода чужой фмгуры на позицию Короля (проверка шаха)
// 1. Проверка цвета фигуры
void checkColorChoise(string figure, string fromTo, string whereTo) {
	int temp = 0;
	if ((moveState == "white" && figure[0] == 'B') || (moveState == "black" && figure[0] == 'W')) {
		++validNum;
		++temp;
	}
	if (temp == 0) {
		//cout << "Pick your color team!" << endl;
	}
}
// 2. Проверка по всем критериям
bool validMoveCheck(string figure, string fromTo, string whereTo) {
	checkColorChoise(figure, fromTo, whereTo);	// 1
	enableFigureFrom(figure, fromTo, whereTo);	// 2
	limitsFromWhere(figure, fromTo, whereTo);	// 3
	notRelationsWhere(figure, fromTo, whereTo); // 4
	trueTrajectory(figure, fromTo, whereTo);	// 5
	if (validNum == 5) {
		validNum = 0;
		return true;
	}
	validNum = 0;
	//cout << "No valid move!" << endl;
	return false;
}

// ПРОВЕРКА НА ШАХ ///////////////////////////////////////////////////////////////////////
bool isCheck() {
	bool check = false;
	// 1. Проверяем шах БЕЛЫМ
	if (moveState == "white") {
		string posWQ;
		// Берем текущую позицию белого короля
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second == "WQ") {
					posWQ = desk[i][j].first;
				}
			}
		}
		// Идет ли какая - нибудь черная фигура на белого короля
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'B') {
					string tempBlackFigure = desk[i][j].second;
					string tempBlackPos = desk[i][j].first;
					if (validMoveCheck(tempBlackFigure, tempBlackPos, posWQ)) {
						check = true;
					}
				}
			}
		}
	}
	// 2. Проверяем шах ЧЕРНЫМ
	if (moveState == "black") {
		string posBQ;
		// Берем текущую позицию черного короля
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second == "BQ") {
					posBQ = desk[i][j].first;
				}
			}
		}
		// Идет ли какая - нибудь белая фигура на черного короля
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'W') {
					string tempWhiteFigure = desk[i][j].second;
					string tempWhitePos = desk[i][j].first;
					if (validMoveCheck(tempWhiteFigure, tempWhitePos, posBQ)) {
						check = true;
					}
				}
			}
		}
	}
	return check;
}
//////////////////////////////////////////////////////////////////////////
// ПРОВЕРКА ВОЗМОЖНОСТИ ХОДА ////////////////////////////////////////////////////////////////
bool isMovable() {
	bool movable = false;
	// 1. Проверка на возможность хода БЕЛЫХ
	if (moveState == "white") {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'W') {
					string posW = desk[i][j].first;
					string figW = desk[i][j].second;
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (validMove(figW, posW, desk[i][j].first)) {
								movable = true;
							}
						}
					}
				}
			}
		}
	}
	// 2. Проверка на возможность хода БЕЛЫХ
	else if (moveState == "black") {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (desk[i][j].second[0] == 'B') {
					string posB = desk[i][j].first;
					string figB = desk[i][j].second;
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (validMove(figB, posB, desk[i][j].first)) {
								movable = true;
							}
						}
					}
				}
			}
		}
	}
	if (!movable) { cout << moveState << " - YOU CAN NOT MOVE! SLATE-MATE!" << endl; }
	return movable;
}
//////////////////////////////////////////////////////////////////////////
// ПРОВЕРКИ НА МАТ ///////////////////////////////////////////////////////
bool isMate() {
	int act = 0;
	bool mate = true;	
	// Проверка на мат БЕЛЫМ
	if (moveState == "white") {
		// 2. Смотрим все фигуры белых
		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 8; l++) {
				if (desk[k][l].second[0] == 'W') {
					string tryWhiteFigure = desk[k][l].second;
					string tryWhitePos = desk[k][l].first;
					// 3. Ставим с проверкой в любое доступное место
					for (int m = 0; m < 8; m++) {
						for (int n = 0; n < 8; n++) {
							string tryPos = desk[m][n].first;
							if (validMove(tryWhiteFigure, tryWhitePos, tryPos)) {
								makeMove(tryWhiteFigure, tryWhitePos, tryPos);
								if (!isCheck()) {
									++act; 
								}
								cancelMove(tryWhiteFigure, tryWhitePos, tryPos);
							}	
						}
					}
				}
			}
		}
	}
	// Проверка на мат ЧЕРНЫМ
	if (moveState == "black") {
		// 2. Смотрим все фигуры черных
		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 8; l++) {
				if (desk[k][l].second[0] == 'B') {
					string tryBlackFigure = desk[k][l].second;
					string tryBlackPos = desk[k][l].first;
					// 3. Ставим с проверкой в любое доступное место
					for (int m = 0; m < 8; m++) {
						for (int n = 0; n < 8; n++) {
							string tryPos = desk[m][n].first;
							if (validMove(tryBlackFigure, tryBlackPos, tryPos)) {
								makeMove(tryBlackFigure, tryBlackPos, tryPos);
								if (!isCheck()) {
									++act; 
								}
								cancelMove(tryBlackFigure, tryBlackPos, tryPos);
							}
						}
					}
				}
			}
		}
	}
	if (act > 0) mate = false;
	return mate;
}
//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////   ГЛАВНАЯ ФУНКЦИЯ   ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	// Забиваем изначально доску
	fillDesk();

	while (true) {

		if (isCheck() && isMate()) { 
			makeMove(figure, fromTo, whereTo);
			showDesk();
			cout << "MATE! ";
			(moveState == "white") ? (cout << "BLACK WIN!" << endl) : (cout << "WHITE WIN!" << endl);
			break; 
		}
		else if (!isCheck() && !isMovable()) { 
			cout << "SLATE-MATE! ";
			(moveState == "white") ? (cout << "BLACK WIN!" << endl) : (cout << "BLACK WIN!" << endl);
			break;
		}
		else if ((isCheck() && !isMate()) || (!isCheck() && isMovable())) {
			do {
				// Сообщение о шахе
				if (isCheck()) {
					(moveState == "white") ? (cout << "WHITE, you are checked!" << endl) : (cout << "BLACK, you are checked!" << endl);
				}
				// ХОДИМ
				showMenu(); // Показываем доску и меню
				do { enterMove(); } while (!validMove(figure, fromTo, whereTo)); // Вводим, пока не введется верный ход
				makeMove(figure, fromTo, whereTo); // Сам ход
				// ОТМЕНЯЕМ ХОД, ЕСЛИ ШАХ
				if (isCheck()) {
					// Сообщение о шахе
					(moveState == "white") ? (cout << "WHITE, you are checked!" << endl) : (cout << "BLACK, you are checked!" << endl);
					cancelMove(figure, fromTo, whereTo);
					cout << "MOVE WAS CANCELED!" << endl;
					// Повтор ввода
					showMenu(); // Показываем доску и меню
					do { enterMove(); } while (!validMove(figure, fromTo, whereTo)); // Вводим, пока не введется верный ход
					makeMove(figure, fromTo, whereTo); // Сам ход
				}
			} while (isCheck());
		}
		
		// Переключатель хода
		(moveState == "white") ? (moveState = "black") : (moveState = "white");
	}

	cout << "THANK YOU FOR GAME!\nENTER 'Y' IF YOU ENJOYED!\n";
	string quit;
	cin >> quit;
}