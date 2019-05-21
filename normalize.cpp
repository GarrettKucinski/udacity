#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector< vector<float> > normalize(vector< vector <float> > grid);
vector < vector <float> > blur(vector < vector < float> > grid, float blurring);
vector< vector <float> > initialize_beliefs(vector< vector <char> > grid);
vector< vector <float> > sense(char color, 
	vector< vector <char> > grid, 
	vector< vector <float> > beliefs, 
	float p_hit,
	float p_miss);

int main() {
  vector < vector <char> > initial_grid = {
    {'g', 'g', 'g'},
    {'g', 'r', 'g'},
    {'g', 'g', 'g'},
  };

  vector < vector <float> > initial_beliefs (3, vector <float> (3, 0.111111));

  vector < vector <float> > new_grid = sense('r', initial_grid, initial_beliefs, 3.0, 1.0);

  for(int i = 0; i < new_grid.size(); i++) {
    for(int j = 0; j < new_grid[0].size(); j++) {
      cout << new_grid[i][j] << " ";
    }
    cout << endl;
  }
}

vector< vector<float> > normalize(vector< vector <float> > grid) {
	
	vector< vector<float> > newGrid;
  vector<float> new_row;

  float total = 0;
  for(int i = 0; i < grid.size(); i++) {
    for(int j = 0; j < grid[0].size(); j++) {
      total = total + grid[i][j];
    }
  }

  for(int i = 0; i < grid.size(); i++) {
    new_row.clear();
    for(int j = 0; j < grid[0].size(); j++) {
      new_row.push_back(grid[i][j] / total);
    }
    newGrid.push_back(new_row);
  }

	return newGrid;
}

vector < vector <float> > blur(vector < vector <float> > grid, float blurring) {

  int height = grid.size();
  int width = grid[0].size();

  float centerProb = 1.0 - blurring;
  float cornerProb = blurring / 12.0;
  float adjacentProb = blurring / 6.0;

  vector < vector <float> > window = {
    {cornerProb, adjacentProb, cornerProb},
    {adjacentProb, centerProb, adjacentProb},
    {cornerProb, adjacentProb, cornerProb}
  };

	vector < vector <float> > newGrid (height, vector <float> (width, 0.0));
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      float gridVal = grid[i][j];
      for(int x = -1; x < 2; x++) {
        for(int y = -1; y < 2; y++) {
          float mult = window[x+1][y+1];
          int xIndex = (i + y);
          int yIndex = (j + x);

          int new_i =  xIndex < 0 ? xIndex + height : xIndex % height;
          int new_j = yIndex < 0 ? yIndex + width : yIndex % width;

          newGrid[new_i][new_j] += (mult * gridVal);
        }
      }
    }
  }

	return normalize(newGrid);
}

vector< vector <float> > initialize_beliefs(vector< vector <char> > grid) {
  int height = grid.size();
  int width = grid[0].size();
  int area = height * width;

  float beliefPerCell = 1.0 / area;
  vector < vector <float> > beliefs = {};

  for(int i = 0; i < height; i++) {
    vector <float> row = {};
    for(int j = 0; j < width; j++) {
      row.push_back(beliefPerCell);
    }
    beliefs.push_back(row);
  }
  
	return beliefs;
}

vector< vector <float> > sense(char color, 
	vector< vector <char> > grid, 
	vector< vector <float> > beliefs, 
	float p_hit,
	float p_miss) 
{
	int height = grid.size();
  int width = grid[0].size();
	vector< vector <float> > newGrid (height, vector <float> (width, 0));

	for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      if(color == grid[i][j]) {
        newGrid[i][j] = beliefs[i][j] * p_hit;
      } else {
        newGrid[i][j] = beliefs[i][j] * p_miss;
      }
    }
  }
    
  float sum = 0;

  for(int i = 0; i < width; i++) {
    sum = sum + newGrid[0][i];
    cout << "sum: i" << endl;
  }

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      cout << newGrid[i][j] << endl;
      newGrid[i][j] = newGrid[i][j] / sum;
    }
  }
    
  return normalize(newGrid);
}