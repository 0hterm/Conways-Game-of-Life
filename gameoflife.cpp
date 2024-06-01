#include <iostream>
#include <vector>
#include <cstdlib>

#if defined (_WIN32) || defined (_WIN64) 
	#include <windows.h>
	void clear_console() {
		system("cls");
	}
	
	void wait(int ms) {
		Sleep(ms);
	}
#else 
	#include <unistd.h>
	void clear_console() {
		system("clear");
	}

	void wait(int ms) {
		usleep(ms * 1000);
	}
#endif 


class gridRow {
	public:
		std::vector<char> row;

		gridRow(int num) {
			this->set_length(num);
			this->init_row(num);
		}

		int get_length() {
			return this->length;	
		}

		void set_length(int num) {
			this->length = num;
		}

		void init_row(int length) {
			this->row = std::vector<char>(length, ' ');
			for (int i=0; i<length; i++) {
				if (rand() % 100 > 92) {
					this->row[i] = '#';
				}
			}
		}

		void display_row(std::string * outputString) {
			if (this->length == 0) {
				*outputString += "ERROR: Row has length 0 or doesn't exist.\n";
			}
			else {
				*outputString += "[";
				for (int i=0; i<this->length; i++) {
					if (i == 0) {
						*outputString += " ";
					}
					*outputString += this->row[i];
					*outputString += " ";
				}
				*outputString += "]\n";
			}
		}

	private:
		int length;
		
};

class gridCol {
	public:
		std::vector<gridRow*> col;

		gridCol(int num, int rowLength) {
			this->set_height(num);
			this->col.resize(num);
			for (int i=0; i<num; i++) {
				this->col[i] = new gridRow(rowLength);
			}
		}
		
		int get_height() {
			return this->height;
		}

		void set_height(int num) {
			this->height = num;
		}

		void display_grid() {
			std::string outputString = "";
			if (this->height == 0) {
				outputString += "ERROR: Grid has size 0 or doesn't exist.\n";
			}
			else {
				for (int i=0; i<this->height; i++) {
					this->col[i]->display_row(&outputString);
				}
			}
			std::cout << outputString;
		}

	private:
		int height;
		
};

int countNeighbors(int row, int column, gridCol * grid) {
	//grid->col[row]->row[column];
	int numNeighbors = 0;

	for (int i=row-1; i<=row+1; i++) {
		if (i < 0) {i = 0;}
		int tmpI = i;
		if (i >= grid->get_height() - 1) {
			i = grid->get_height() - 2;
		}
		for (int j=column-1; j<=column+1; j++) {
			if (j < 0) {j = 0;}
			int tmpJ = j;
			if (j >= grid->col[i]->get_length() - 1) {
				j = grid->col[i]->get_length() - 2;
			}
			if (grid->col[i]->row[j] == '#' && !(i == row && j == column)) {
				numNeighbors++;
			}
			j = tmpJ;
		}
		i = tmpI;
	}
	return numNeighbors;	
}

void ConwaysGameOfLife(gridCol * grid) {
	int height = grid->get_height();
	int length = grid->col[0]->get_length();

	for (int i=0; i<height; i++) {
		for (int j=0; j<length; j++) {
			int numNeighbors = countNeighbors(i,j,grid);
			// Cell is dead and has 3 neighbors, it becomes alive
			if (grid->col[i]->row[j] != '#' && numNeighbors == 3) {
				grid->col[i]->row[j] = '#';
			}
			// Cell is alive
			else if (grid->col[i]->row[j] == '#') {
				// Cell has less than 2 neighbors, it dies
				if (numNeighbors < 2) {
					grid->col[i]->row[j] = ' ';
				}
				else if (numNeighbors > 3) {
					grid->col[i]->row[j] = ' ';	
				}
			}
		}
	}

}

int main(int argc, char * argv[]) {
	int numRows, numColumns;
	
	if (argc == 1) {
		numRows = 20;
		numColumns = 20;
	}
	else {
		numRows = atoi(argv[1]);
		numColumns = atoi(argv[2]);
	}


	srand(time(0));

	std::cout << "Creating grid... (" << numRows << "x" << numColumns << ")" << std::endl;

	// Create the grid
	gridCol grid(numRows, numColumns);

	
	std::cout << "Performing game...\n";
	int generation = 0;

	while(1) {
		generation++;
		// Clear screen
		clear_console();
		// Print screen
		grid.display_grid();
		// Update values
		ConwaysGameOfLife(&grid);
		//Print current generation
		std::cout << "Generation: " << generation << std::endl;
		// Sleep
		wait(200);
	}
	
	return 0;
}
