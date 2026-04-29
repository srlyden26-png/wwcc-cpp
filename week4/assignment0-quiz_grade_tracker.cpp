#include <iostream>
#include <string>

using namespace std;

// Helper function to convert a numeric score to a letter
char getLetterGrade(double score) {
    if (score >= 90) return 'A';
    if (score >= 80) return 'B';
    if (score >= 70) return 'C';
    if (score >= 60) return 'D';
    return 'F';
}

int main() {
    const int NUM_QUIZZES = 5;
    double scores[NUM_QUIZZES];
    int distA = 0, distB = 0, distC = 0, distD = 0, distF = 0;
    double sum = 0;

    cout << "QUIZ GRADE TRACKER" << endl;
    cout << "------------------" << endl;

    // 1. Input Loop
    for (int i = 0; i < NUM_QUIZZES; i++) {
        cout << "Enter score for Quiz " << (i + 1) << " (0-100): ";
        cin >> scores[i];
        sum += scores[i];
    }

    // 2. Results & Distribution Loop
    cout << "\nQuiz Results:" << endl;
    for (int i = 0; i < NUM_QUIZZES; i++) {
        char grade = getLetterGrade(scores[i]);
        cout << "  Quiz " << (i + 1) << ":  " << scores[i] << "  (" << grade << ")" << endl;

        // Count distribution
        if (grade == 'A') distA++;
        else if (grade == 'B') distB++;
        else if (grade == 'C') distC++;
        else if (grade == 'D') distD++;
        else distF++;
    }

    // 3. Calculate Stats
    double average = sum / NUM_QUIZZES;
    int highIdx = 0, lowIdx = 0;

    for (int i = 1; i < NUM_QUIZZES; i++) {
        if (scores[i] > scores[highIdx]) highIdx = i;
        if (scores[i] < scores[lowIdx]) lowIdx = i;
    }

    // 4. Final Output
    cout << "\nStatistics:" << endl;
    cout << "  Average score:  " << average << endl;
    cout << "  Highest score:  " << scores[highIdx] << "  (Quiz " << (highIdx + 1) << ")" << endl;
    cout << "  Lowest score:   " << scores[lowIdx] << "  (Quiz " << (lowIdx + 1) << ")" << endl;
    cout << "  Overall grade:  " << getLetterGrade(average) << endl;

    cout << "\nGrade Distribution:" << endl;
    cout << "  A: " << distA << "\n  B: " << distB << "\n  C: " << distC << "\n  D: " << distD << "\n  F: " << distF << endl;

    return 0;
}
