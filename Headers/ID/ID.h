#ifndef ID
#define ID

enum class GameState {
	MainMenu,
	Playing,
	GameOver
};

enum class Difficulty {
	Easy,
	Medium,
	Hard,
	Insane
};

enum class Type {
	Sushi,
	BonusSushi,
	Poison
};

enum class Point {
	None,
	Moving,
	Earned,
	Small = 2500,
	Big = 40000,
	Dead
};

#endif // ID

