#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <fstream>

using namespace std;

class HighScoreManager {
public:
    HighScoreManager();
    ~HighScoreManager();

    void UpdateHighScore(int new_score);
    int GetHighScore() const;
    void LoadHighScore();
    void SaveHighScore() const;

private:
    int high_score_;
    
};

#endif // HIGHSCOREMANAGER_H
