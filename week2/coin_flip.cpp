    cout << "Simulating " << flips << " coin flips..." << endl << endl;

    for (int i = 0; i < flips; i++) {
        // rand() % 2 returns 0 or 1
        if (rand() % 2 == 0) {
            heads++;
        } else {
            tails++;
        }
    }

    
    // (double) is used to ensure the division doesn't truncate to zero, if so then... Dumb
    double headsPercent = ((double)heads / flips) * 100;
    double tailsPercent = ((double)tails / flips) * 100;

    cout << "Results:" << endl;
    cout << "Heads: " << heads << " (" << headsPercent << "%)" << endl;
    cout << "Tails: " << tails << " (" << tailsPercent << "%)" << endl;
