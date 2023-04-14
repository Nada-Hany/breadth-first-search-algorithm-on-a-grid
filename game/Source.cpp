#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;
using namespace sf;

enum class tile_type {
	none, wall, start, target
};

int walls[3][3] = {
	{0 , 0, 1},
	{-1 ,0,-1},
	{2 , 0, 0},
};
// 1-> start  [0][2]
// 2-> target [2][0]
typedef struct tile {
	tile_type type;
	int row;
	int column;
	struct tile* parent = NULL;

	void view() {
		cout << "row : " << row << " , column : " << column<<endl;
	} 
};
tile mp[3][3];

vector <tile> closed;

//bool exist_in_closed(tile& current, vector<tile>& closed);
void main() {


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (walls[i][j] == -1) {
				mp[i][j].type = tile_type::wall;
			}
			else if (walls[i][j] == 2) {
				mp[i][j].type = tile_type::target;
			}
			else if (walls[i][j] == 1) {
				mp[i][j].type = tile_type::start;
			}
			if (walls[i][j] == 0) {
				mp[i][j].type = tile_type::none;
			}

			mp[i][j].row = i;
			mp[i][j].column = j;
		}
	}
	

	queue <tile> open;
	vector <tile> get_path;


	tile* target = & mp[2][0];
	tile* start = &mp[0][2];
	tile* current = & mp[0][2];
	open.push(*current);

	while (!open.empty()) {

		//current.row+1 , curent.column
		//current.row-1 , curent.column
		//current.row   , curent.column +1
		//current.row   , curent.column -1
		current = &mp[open.front().row][open.front().column];
		open.pop();
		bool found = 0;

		if (current==target)
		{
			/*cout << "found target : " << current->row << " " << current->column << endl;
			cout << current->parent <<" " << current->parent->row << " " << current->parent->column;*/

			break;
		}
		if (current->column + 1 <= 2) {
			tile* right_tile = &mp[current->row][current->column + 1];
			if (right_tile->type != tile_type::wall)
			{/*
				bool check_right = exist_in_closed(right_tile);
				if (!check_right) {
					open.push(right_tile);
					right_tile.parent = &current;
				}*/
				bool ans = 0;
				for (int i = 0; i < closed.size(); i++) {
					
					if (right_tile->row == closed[i].row && right_tile->column == closed[i].column) {
						ans = 1;
						break;
					}
				}
				if (!ans) {
					open.push(*right_tile);
					right_tile->parent = &mp[current->row][current->column];
				/*	cout << right_tile.row << " " << right_tile.column << endl;
					cout << right_tile.parent->row << "  " << right_tile.parent->column << endl;
					cout << right_tile.parent;*/

				}
			}
		}
		if (current->column - 1 >= 0) {
			tile* left_tile = &mp[current->row][current->column - 1];

			if (left_tile->type != tile_type::wall)
			{
				bool ans = 0;
				for (int i = 0; i < closed.size(); i++) {

					if (left_tile->row == closed[i].row && left_tile->column == closed[i].column)
						ans = 1;
				}
				if (!ans) {
					open.push(*left_tile);
					left_tile->parent = &mp[current->row][current->column];;
				}
			}
		}
			
		if (current->row - 1 >= 0) {
			tile up_tile = mp[current->row - 1][current->column];
			if (up_tile.type != tile_type::wall)
			{
				bool ans = 0;
				for (int i = 0; i < closed.size(); i++) {

					if (up_tile.row == closed[i].row && up_tile.column == closed[i].column)
						ans = 1;
				}
				if (!ans) {
					open.push(up_tile);
					up_tile.parent = &mp[current->row][current->column];;
				}
			}
		}
		if (current->row + 1 <= 2) {
			tile *down_tile = &mp[current->row + 1][current->column];

			if (down_tile->type != tile_type::wall)
			{
				bool ans = 0;
				for (int i = 0; i < closed.size(); i++) {

					if (down_tile->row == closed[i].row && down_tile->column == closed[i].column)
						ans = 1;
				}
				if (!ans) {
					open.push(*down_tile);
					down_tile->parent = &mp[current->row][current->column];
				}
			}
		}
		closed.push_back(*current);
		/*if (!open.empty())
			current = open.front();*/
	}
	while (current != start) {
		get_path.push_back(*current);
		current = current->parent;
	}
	for (int i = get_path.size() - 1; i >= 0; i--) {
		cout << get_path[i].row << " " << get_path[i].column << endl;
	}
	/*cout << "\n path to the target \n" << endl;*/
	//current = target;
	//cout  << target->parent->row << " " << target->parent->column << endl;
	//// shayf en el parent bta3 el target null.
	//while (current->parent != NULL) {
	//	current->view();
	//	current = current->parent;
	//}
	//current = target;
	//cout << current.row << current.column << endl;

	//closed.back().row == target.row && closed.back().column == target.column

	//while (current.parent != &start)
	//{
	//	cout << current.row << current.column << endl;
	//	//get_path.push_back(*(current.parent));//ghalt hna 

	//	//cout << current.row << current.column << endl;
	//	current = *(current.parent);// w hna 
	//	cout << current.row << current.column << endl;

	//}
}


//bool exist_in_closed(tile& current) {
//	bool ans = 0;
//	for (int i = 0; i < closed.size(); i++) {
//
//	if (current.row == closed[i].row && current.column == closed[i].column)
//			ans = 1;
//	}
//	return ans;
//}
