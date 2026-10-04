#pragma once
// Game state machine: Menu -> Playing -> LevelDone -> GameOver
enum class GameState { Menu, Playing, Paused, LevelDone, GameOver };
class Game {
public:
    void Update(float dt) { (void)dt; /* TODO */ }
    GameState state = GameState::Menu;
};
