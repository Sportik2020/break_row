#include "settings.h" 
#include "function.h" 
#include "Textobj.h" 
#include "ball.h" 
#include "bat.h" 
#include "break.h" 
#include "breakrow.h"
using namespace sf;
int main()
{
	srand(time(nullptr));
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);

	Bat bat;
	batInit(bat);
	float BatSpeedX = 0.f;

	Ball ball;
	ballInit(ball);

	TextObj scoreText;
	initText(scoreText, ball.Score);
	Brick brick;
	brickInit(brick, Brick_Color, brickStartPos);
	BrickField brickField;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			brickInit(brickField.arr[i][j], Brick_Color, brickStartPos);
		}
	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		brickUpdate(brick);
		ballUpdate(ball);
		batUpdate(bat);
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLUMNS; j++) {
				brickUpdate(brickField.arr[i][j]);
			}
		}
		textUpdate(scoreText, ball.Score);
		if (ball.shape.getPosition().y >= (WINDOW_HEIGHT - 2 * BALL_RADIUS)) {
			ball.speedy = -ball.speedy;
			window.close();
		}
		float ballX = ball.shape.getPosition().x;
		float ballY = ball.shape.getPosition().y;
		Vector2f midTop{ ballX + BALL_RADIUS,  ballY };
		Vector2f  mid{ ballX, ballY + BALL_RADIUS };
		Vector2f midBottom{ ballX + BALL_RADIUS,  ballY + 2 * BALL_RADIUS };
		if (pointInRect(bat.shape, mid)) {
			ball.speedx = -ball.speedx;
			ball.Score++;
		}
		if (pointInRect(bat.shape, midBottom)) {
			ball.speedy = -ball.speedy;
			ball.Score++;
		}
		if (pointInRect(bat.shape, midTop)) {
			ball.speedy = -ball.speedy;
			ball.Score++;
		}
		window.clear(sf::Color::Black);
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLUMNS; j++) {
				brickDraw(window, brickField.arr[i][j]);
			}
		}
		ballDraw(window, ball);
		batDraw(window, bat);
		brickDraw(window, brick);
		textDraw(window, scoreText);
		window.display();
	}
	return 0;
}