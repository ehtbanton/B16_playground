
#include <vector>
using namespace std;

class Image {
public:
	Image(int width, int height) {
		this->width = width;
		this->height = height;
		this->pixels = vector<vector<unsigned char>>(width, vector<unsigned char>(height, 0));
	}

	void set_pixel(int x, int y, unsigned char value) {
		pixels[x][y] = value;
	}

	unsigned char get_pixel(int x, int y) {
		return pixels[x][y];
	}

	void display_image() {
		// Characters arranged from least to most dense visual representation
		const char shades[] = " .:-=+*#@";
		const int shade_count = strlen(shades);
		const int level_size = 256 / shade_count; // Map 256 values to available characters

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// Map pixel value (0-255) to character index (0 to shade_count-1)
				int shade_index = pixels[x][y] / level_size;

				// Ensure we don't exceed array bounds
				shade_index = min(shade_index, shade_count - 1);

				cout << shades[shade_index];
			}
			cout << endl;
		}
	}

	void draw_face() {
		if (this->height < 12 || this->width < 12) {
			cout << "Image too small to draw face" << endl;
			return;
		}
		set_pixel(0, 6, 200);
		set_pixel(0, 7, 200);
		set_pixel(0, 8, 200);
		set_pixel(0, 9, 200);
		set_pixel(1, 10, 200);
		set_pixel(2, 11, 200);
		set_pixel(4, 12, 200);
		set_pixel(6, 13, 200);
		set_pixel(8, 13, 200);
		set_pixel(10, 14, 200);
		set_pixel(12, 14, 200);
		set_pixel(14, 14, 200);
		set_pixel(16, 14, 200);
		set_pixel(18, 13, 200);
		set_pixel(20, 13, 200);
		set_pixel(22, 12, 200);
		set_pixel(24, 11, 200);
		set_pixel(25, 10, 200);
		set_pixel(26, 9, 200);
		set_pixel(26, 8, 200);
		set_pixel(26, 7, 200);
		set_pixel(26, 6, 200);
		set_pixel(25, 5, 200);
		set_pixel(24, 4, 200);
		set_pixel(22, 3, 200);
		set_pixel(20, 2, 200);
	//	set_pixel(18, 2, 200);
		set_pixel(16, 1, 200);
		set_pixel(14, 1, 200);
		set_pixel(12, 1, 200);
		set_pixel(10, 1, 200);
	//	set_pixel(8, 2, 200);
		set_pixel(6, 2, 200);
		set_pixel(4, 3, 200);
		set_pixel(2, 4, 200);
		set_pixel(1, 5, 200);

		set_pixel(9, 6, 200);
		set_pixel(17, 6, 200);


	}
	
private:
	int width;
	int height;
	std::vector<std::vector<unsigned char>> pixels;
};

void b1_example_main() {
	Image img(30, 20);
	img.draw_face();
	img.display_image();
}

// If we are to use a double instead of unsigned char, we would need to change the type of the vector to double and the type of the pixel values to double.
// We would also need to change the set_pixel function to take a double instead of an unsigned char.
// We would also need to change the display_image function to print out somethign which refers to doubles instead of unsigned chars.



// Q2
// A C array is a fixed-size array of elements of the same type. It is a contiguous block of memory that can be accessed using an index. However, a C++ vector
// is a dynamic array that can grow or shrink in size post-compilation. It provides additional functionality such as bounds checking, size tracking, and automatic memory management.
// Vectors are part of the C++ Standard Library and provide a safer and more convenient alternative to C arrays. 
// They are passed by value by default, whereas C arrays are passed by reference.