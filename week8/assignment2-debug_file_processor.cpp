#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm> // For std::max and std::min

using namespace std;

struct Student {
    string lastName;
    string firstName;
    int g1, g2, g3;
    double average;
    int high;
    int low;
};

int main() {
    // --- Read input file ---
    ifstream inFile("grades.txt");
    
    // BUG 1: File I/O — the input file is opened but the program never checks whether it actually opened successfully.
    // FIX: I added an 'if (!inFile)' safety check to notify exit early if the file is missing.
    if (!inFile) {
        cerr << "Error: Could not open input file 'grades.txt'!" << endl;
        return 1;
    }

    cout << "Reading records from grades.txt..." << endl;
    vector<Student> students;
    string line;

    // BUG 2 & BUG 4: The original loop used while (!inFile.eof()) which causes trailing duplicate reads, 
    // and used a global 'stringstream' that bled data between lines.
    // FIX: Standard practice is to replace the loop entirely with 'while (getline(inFile, line))' 
    // and place a fresh stringstream inside the block (handled in the loop below).
    while (getline(inFile, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        // BUG 4: Parsing — the stringstream object was declared in the wrong place, causing data from one line to bleed into the next.
        // FIX: Moved the stringstream declaration inside the loop body so it completely recreates/resets on every line.
        stringstream ss(line); 
        
        Student s;
        if (ss >> s.lastName >> s.firstName >> s.g1 >> s.g2 >> s.g3) {
            s.high = max({s.g1, s.g2, s.g3});
            s.low = min({s.g1, s.g2, s.g3});
            int total = s.g1 + s.g2 + s.g3;
            
            // BUG 5: Math — the average calculation uses the wrong types (int / int), silently dropping all decimal precision.
            // FIX: Divided by the double literal '3.0' instead of '3' to force standard floating-point division.
            s.average = total / 3.0; 
            
            students.push_back(s);
        }
    }
    inFile.close();

    if (students.empty()) {
        cerr << "Error: No student records loaded." << endl;
        return 1;
    }

    cout << students.size() << " students loaded." << endl << endl;

    // BUG 3: File I/O — output file opened in overwrite mode; instructions state it should preserve previous runs by appending.
    // FIX: Added 'ios::app' flag inside the ofstream declartion to safely open the file stream in append mode.
    ofstream outFile("grade_report.txt", ios::app); 
    if (!outFile) {
        cerr << "Error: Could not open output file 'grade_report.txt'!" << endl;
        return 1;
    }

    // --- Display to console and write to file ---
    auto printReport = [&](ostream& out) {
        out << "GRADE REPORT" << endl;
        out << string(20, '-') << endl;
        
        // Setup initial table headers
        out << left << setw(20) << "Name" 
            << right << setw(7) << "Avg" 
            << setw(7) << "High" 
            << setw(7) << "Low" << endl;
        out << string(20, '-') << endl;

        double classTotal = 0;
        int topIdx = 0, lowIdx = 0;

        for (int i = 0; i < (int)students.size(); i++) {
            Student& s = students[i];
            string name = s.lastName + ", " + s.firstName;

            // BUG 6: Formatting — setw() was set once outside the loop instead of being applied to each row (not sticky).
            // FIX: Placed 'setw(20)' explicitly right before streaming the 'name' string variable on every iteration.
            
            // BUG 7: Formatting was the numeric columns use the wrong alignment manipulator (left), stretching headers out of line.
            out << left << setw(20) << name 
                << right << setw(7) << fixed << setprecision(1) << s.average 
                << setw(7) << s.high 
                << setw(7) << s.low << endl;

            classTotal += s.average;
            if (s.average > students[topIdx].average) topIdx = i;
            if (s.average < students[lowIdx].average) lowIdx = i;
        }

        double classAvg = classTotal / students.size();
        out << endl << "CLASS STATISTICS" << endl;
        out << string(20, '-') << endl;
        out << fixed << setprecision(1);
        out << "Class average: " << classAvg << endl;
        out << "Top student: " << students[topIdx].lastName << ", " << students[topIdx].firstName << " (" << students[topIdx].average << ")" << endl;
        out << "Low student: " << students[lowIdx].lastName << ", " << students[lowIdx].firstName << " (" << students[lowIdx].average << ")" << endl;
    };

    printReport(cout);
    printReport(outFile);
    outFile.close();

    cout << endl << "Report written to grade_report.txt" << endl;
    return 0;
}
