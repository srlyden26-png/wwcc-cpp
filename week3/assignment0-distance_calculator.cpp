#include <iostream>
#include <cmath>   // For sqrt() and pow()
#include <iomanip> // For setprecision()
#include <utility> // For pair (Bonus)

using namespace std;

// Function to calculate the distance between two points
double calculateDistance(double x1, double y1, double x2, double y2) {
    // Distance formula: sqrt((x2-x1)^2 + (y2-y1)^2)
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Bonus: Function to calculate the midpoint
pair<double, double> calculateMidpoint(double x1, double y1, double x2, double y2) {
    double midX = (x1 + x2) / 2.0;
    double midY = (y1 + y2) / 2.0;
    return make_pair(midX, midY);
}

int main() {
    double x1, y1, x2, y2;

    // Prompt user for the first point
    cout << "Enter the coordinates of the first point:" << endl;
    cout << "x1: "; cin >> x1;
    cout << "y1: "; cin >> y1;

    // Prompt user for the second point
    cout << "Enter the coordinates of the second point:" << endl;
    cout << "x2: "; cin >> x2;
    cout << "y2: "; cin >> y2;

    // Calculate distance and midpoint
    double distance = calculateDistance(x1, y1, x2, y2);
    pair<double, double> midpoint = calculateMidpoint(x1, y1, x2, y2);

    // Format output to 2 decimal places
    cout << fixed << setprecision(2);

    // Final output
    cout << "\nThe distance between (" << x1 << "," << y1 << ") and (" 
         << x2 << "," << y2 << ") is: " << distance << endl;

    cout << "The midpoint is: (" << midpoint.first << ", " << midpoint.second << ")" << endl;

    return 0;
}
