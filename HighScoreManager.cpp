#include "HighScoreManager.h"

HighScoreManager::HighScoreManager() : high_score_(0) {
    LoadHighScore(); // Tải điểm cao nhất từ file khi khởi tạo
}

HighScoreManager::~HighScoreManager() {
    SaveHighScore(); // Lưu điểm cao nhất khi hủy đối tượng
}

void HighScoreManager::UpdateHighScore(int new_score) {
    if (new_score > high_score_) {
        high_score_ = new_score;
    }
}

int HighScoreManager::GetHighScore() const {
    return high_score_;
}

void HighScoreManager::LoadHighScore() {
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> high_score_;
        file.close();
    }
}

void HighScoreManager::SaveHighScore() const {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << high_score_;
        file.close();
    }
}
