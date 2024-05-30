#include <iostream>
#include <vector>
#include <cstdlib>

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
		}

		void display_row() {
			if (this->length == 0) {
				std::cout << "ERROR: Row has length 0 or doesn't exist.\n";
			}
			else {
				std::cout << "[";
				for (int i=0; i<this->length; i++) {
					if (i == 0) {
						std::cout << " ";
					}
					std::cout << this->row[i] << " ";
				}
				std::cout << "]\n";
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
			if (this->height == 0) {
				std::cout << "ERROR: Grid has size 0 or doesn't exist.\n";
			}
			else {
				for (int i=0; i<this->height; i++) {
					this->col[i]->display_row();
				}
			}
		}

	private:
		int height;
		
};

void countNeighbors(int row, int column, gridCol * grid) {
	//grid->col[row]->row[column];

	
}

void ConwaysGameOfLife(gridCol * grid) {
	int height = grid->get_height();
	int length = grid->col[0]->get_length();

	for (int i=0; i<height; i++) {
		for (int j=0; j<length; j++) {
			
		}
	}

}

int main(int argc, char * argv[]) {
	int numRows, numColumns;
	
	if (argc == 1) {
		numRows = 10;
		numColumns = 10;
	}
	else {
		numRows = atoi(argv[1]);
		numColumns = atoi(argv[2]);
	}

	std::cout << "Creating grid... (" << numRows << "x" << numColumns << ")" << std::endl;

	// Create the grid
	gridCol grid(numRows, numColumns);
	
	std::cout << "Performing game...\n";

	while(1) {
		// Print screen
		grid.display_grid();
		// Update values
		ConwaysGameOfLife(&grid);
	}
	
	return 0;
}
