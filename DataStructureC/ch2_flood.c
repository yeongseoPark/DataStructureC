#define WHITE 0
#define BLACK 1
#define YELLOW 2

int screen[10][10];

char read_pixel(int x, int y)
{
	return screen[x][y];
}

void write_pixel(int x, int y, int color)
{
	screen[x][y] = color;
}

void flood_fill(int x, int y)
{
	if (read_pixel(x, y) == WHITE) {
		write_pixel(x, y, BLACK);
		int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
		for (int i = 0; i < 4; i++) {
			int nextX = x + directions[i][0];
			int nextY = y + directions[i][1];

			if (nextX >= 0 && nextX <= 9 && nextY >= 0 && nextY <= 9) {
				flood_fill(nextX, nextY);
			}
		}
	}
}

int main(void) {
	return 0;
}