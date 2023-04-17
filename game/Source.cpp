#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>

#define TILESIZE 20

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

bool exist_in_closed(tile* current, vector<struct tile>& closed);

void find_optimal_path(tile* current, tile* target, vector <tile>* get_path) {
	queue <tile> open;
	vector <tile> closed;
	open.push(*current);

	while (!open.empty()) {

		current = &mp[open.front().row][open.front().column];
		open.pop();

		if (current == target)
			break;

		if (current->column + 1 <= 2) {
			tile* right_tile = &mp[current->row][current->column + 1];
			if (right_tile->type != tile_type::wall)
			{
				bool check_right = exist_in_closed(right_tile, closed);
				if (!check_right) {
					open.push(*right_tile);
					right_tile->parent = &mp[current->row][current->column];
				}
			}
		}
		if (current->column - 1 >= 0) {
			tile* left_tile = &mp[current->row][current->column - 1];

			if (left_tile->type != tile_type::wall)
			{
				bool check_left = exist_in_closed(left_tile, closed);
				if (!check_left) {
					open.push(*left_tile);
					left_tile->parent = &mp[current->row][current->column];
				}
			}
		}
		if (current->row - 1 >= 0) {
			tile* up_tile = &mp[current->row - 1][current->column];
			if (up_tile->type != tile_type::wall)
			{
				bool check_up = exist_in_closed(up_tile, closed);
				if (!check_up) {
					open.push(*up_tile);
					up_tile->parent = &mp[current->row][current->column];
				}
			}
		}
		if (current->row + 1 <= 2) {
			tile* down_tile = &mp[current->row + 1][current->column];

			if (down_tile->type != tile_type::wall)
			{
				bool check_down = exist_in_closed(down_tile, closed);
				if (!check_down) {
					open.push(*down_tile);
					down_tile->parent = &mp[current->row][current->column];
				}
			}
		}
		closed.push_back(*current);
	}

	(*get_path).clear();
	while (current->parent != NULL) {
		(*get_path).push_back(*current);
		current = current->parent;
	}
}
int main() {


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

	
	vector <tile> get_path;

	tile* target = &mp[2][0];
	tile* current = &mp[0][2];
	
	find_optimal_path(current, target, &get_path);

	
	for (int i = get_path.size() - 1; i >= 0; i--) {
		cout << get_path[i].row << " " << get_path[i].column << endl;
	}

	return 0;
}

	bool exist_in_closed(tile* tile, vector <struct tile>& closed) {
		bool ans = 0;
		for (int i = 0; i < closed.size(); i++) {

			if (tile->row == closed[i].row && tile->column == closed[i].column)
				ans = 1;
		}
		return ans;
	}
