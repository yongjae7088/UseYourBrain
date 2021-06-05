#include <bangtal.h>

SceneID scene1, scene2, stage1, stage2, stage3;
ObjectID start, go, giveup1, keypad1, next, button[4], restart, giveup2, final, keypad2, giveup3, end;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown = true)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) showObject(object);

	return object;
}
void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == start) enterScene(scene2);

	if (object == go) enterScene(stage1);

	if (object == keypad1) showKeypad("115", giveup1);

	if (object == next) enterScene(stage2);

	if (object == giveup1) endGame();

	if (object == button[0] || object == button[1] || object == button[3])
	{
		showMessage("오답...");
		hideObject(button[0]);
		hideObject(button[1]);
		hideObject(button[2]);
		hideObject(button[3]);
		showObject(restart);
		showObject(giveup2);
	}

	if (object == button[2])
	{
		showMessage("정답!!");
		hideObject(button[0]);
		hideObject(button[1]);
		hideObject(button[2]);
		hideObject(button[3]);
		showObject(final);
	}

	if (object == restart)
	{
		hideObject(restart);
		hideObject(giveup2);
		showObject(button[0]);
		showObject(button[1]);
		showObject(button[2]);
		showObject(button[3]);
	}

	if (object == giveup2) endGame();

	if (object == final) enterScene(stage3);

	if (object == keypad2) showKeypad("9", giveup3);

	if (object == giveup3) endGame();

	if (object == end) endGame();
}

void objectCallback(ObjectID object, EventID event)
{
	if (object == giveup1 && event == EventID::EVENT_KEYPAD)
	{
		showMessage("정답!!");
		hideObject(keypad1);
		showObject(next);
	}
	if (object == giveup3 && event == EventID::EVENT_KEYPAD)
	{
		showMessage("정답!!");
		hideObject(keypad2);
		hideObject(giveup3);
		showObject(end);
	}
}

int main() {
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);
	setObjectCallback(objectCallback);

	scene1 = createScene("brain", "scene1.png");
	scene2 = createScene("rule", "scene2.png");
	stage1 = createScene("stage1", "stage1.png");
	stage2 = createScene("stage2", "stage2.png");
	stage3 = createScene("stage3", "stage3.png");

	start = createObject("start.png", scene1, 900, 100);
	go = createObject("go.png", scene2, 950, 100);
	keypad1 = createObject("bingo.png", stage1, 900, 400);
	giveup1 = createObject("giveup.png", stage1, 900, 100);
	next = createObject("next.png", stage1, 900, 400, false);
	button[0] = createObject("button0.png", stage2, 800, 400);
	button[1] = createObject("button1.png", stage2, 1000, 400);
	button[2] = createObject("button2.png", stage2, 800, 160);
	button[3] = createObject("button3.png", stage2, 1000, 160);
	restart = createObject("restart.png", stage2, 900, 400, false);
	giveup2 = createObject("giveup.png", stage2, 900, 100, false);
	final = createObject("next.png", stage2, 900, 100, false);
	keypad2 = createObject("bingo.png", stage3, 900, 400);
	giveup3 = createObject("giveup.png", stage3, 900, 100);
	end = createObject("end.png", stage3, 900, 100, false);

	startGame(scene1);
}