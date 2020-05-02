#pragma once
#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string.h>
#include <string>
#include <Windows.h>
using namespace std;

namespace HighScoreListLT {
	class NodeScore
	{
	public:
		int score;
		string name;
	};
	class HighScore
	{
	private:
		list<NodeScore>* ListScores;
	public:
		int sizeList;
		HighScore(bool _defaultList, int _sizeList);
		int InsertScore(int score, string name);
		NodeScore GetNodeScore(int indexScore);
		void ClearListHighScore();
		int GetSizeListHighScore();
		int GetSizeInternalListHighScore();
		~HighScore();
	};
	
}
#endif