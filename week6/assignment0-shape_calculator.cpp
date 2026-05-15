#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

// Global constant for Pi
const double PI = 3.14159265358979323846;

// ==========================================
// RECTANGLE CLASS DEFINITION
// ==========================================
class Rectangle {
private:
    double length;
    double width;

public:
    // Constructor
    Rectangle(double l, double w) {
        setLength(l);
        setWidth(w);
    }

    // Const getters
    double getLength() const { return length; }
    double getWidth() const { return width; }

    // Setters with validation
    void setLength(double l) {
        if (l > 0) {
            length = l;
        } else {
            std::cout << "[Error] Length must be greater than 0. Value unchanged.\n";
        }
    }

    void setWidth(double w) {
        if (w > 0) {
            width = w;
        } else {
            std::cout << "[Error] Width must be greater than 0. Value unchanged.\n";
        }
    }

    // Overloaded area() methods
    double area() const {
        return length * width;
    }

    void area(double& result) const {
        result = length * width;
    }

    // Method chaining resize
    Rectangle& resize(double factor) {
        if (factor > 0) {
            this->length *= factor;
            this->width *= factor;
        } else {
            std::cout << "[Error] Resize factor must be greater than 0.\n";
        }
        return *this;
    }

    // Declaration of outside-class methods
    void printInfo() const;
};

// ==========================================
// CIRCLE CLASS DEFINITION
// ==========================================
class Circle {
private:
    double radius;

public:
    // Constructor
    Circle(double r) {
        setRadius(r);
    }

    // Setter with validation
    void setRadius(double r) {
        if (r > 0) {
            radius = r;
        } else {
            std::cout << "[Error] Radius must be greater than 0. Value unchanged.\n";
        }
    }

    // Const getter
    double getRadius() const { return radius; }

    // Declaration of outside-class methods
    double calculateArea() const;
    double calculateCircumference() const;

    // Overloaded print methods
    void print() const {
        std::cout << "Circle (Radius: " << radius << ")\n";
        std::cout << "Area: " << calculateArea() << "\n";
        std::cout << "Circumference: " << calculateCircumference() << "\n";
    }

    void print(bool detailed) const {
        if (detailed) {
            std::cout << "Circle details:\n";
            std::cout << "  Radius: " << radius << "\n";
            std::cout << "  Area: pi x " << radius << "^2 = " << calculateArea() << "\n";
            std::cout << "  Circumference: 2 x pi x " << radius << " = " << calculateCircumference() << "\n";
        } else {
            print();
        }
    }
};

// ==========================================
// BONUS: TRIANGLE CLASS DEFINITION
// ==========================================
class Triangle {
private:
    double side1, side2, side3;

    // Helper validation method
    bool isValidTriangle(double s1, double s2, double s3) const {
        return (s1 + s2 > s3) && (s1 + s3 > s2) && (s2 + s3 > s1);
    }

public:
    // Constructor with validation
    Triangle(double s1, double s2, double s3) {
        if (isValidTriangle(s1, s2, s3)) {
            side1 = s1;
            side2 = s2;
            side3 = s3;
        } else {
            std::cout << "[Error] Invalid triangle sides! Defaulting to 1.0, 1.0, 1.0.\n";
            side1 = 1.0;
            side2 = 1.0;
            side3 = 1.0;
        }
    }

    // Heron's formula
    double area() const {
        double s = (side1 + side2 + side3) / 2.0;
        return std::sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    // Determine type
    std::string getType() const {
        if (side1 == side2 && side2 == side3) return "equilateral";
        if (side1 == side2 || side2 == side3 || side1 == side3) return "isosceles";
        return "scalene";
    }

    // Method chaining scale
    Triangle& scale(double factor) {
        if (factor > 0) {
            this->side1 *= factor;
            this->side2 *= factor;
            this->side3 *= factor;
        } else {
            std::cout << "[Error] Scale factor must be greater than 0.\n";
        }
        return *this;
    }

    void print() const {
        std::cout << "Triangle (" << side1 << ", " << side2 << ", " << side3 << ") -> Type: " << getType() << ", Area: " << area() << "\n";
    }
};

// ==========================================
// OUTSIDE-CLASS METHOD DEFINITIONS
// ==========================================
void Rectangle::printInfo() const {
    std::cout << "Rectangle (Length: " << length << ", Width: " << width << ")\n";
}

double Circle::calculateArea() const {
    return PI * radius * radius;
}

double Circle::calculateCircumference() const {
    return 2.0 * PI * radius;
}

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    // Formatting setups
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "SHAPE CALCULATOR\n";
    std::cout << "----------------\n";

    // 1. Test Rectangle and Method Overloading
    Rectangle rect(5.0, 3.0);
    rect.printInfo();
    
    std::cout << "Area: " << rect.area() << "\n";
    
    double refArea = 0.0;
    rect.area(refArea);
    std::cout << "Area via reference: " << refArea << "\n\n";

    // 2. Test Circle and Overloaded Print
    Circle circ(4.0);
    circ.print();
    std::cout << "\n";
    circ.print(true);
    std::cout << "\n";

    // 3. Test Method Chaining via resize()
    std::cout << "Method chaining:\n";
    std::cout << "  Original: "; 
    rect.printInfo();
    
    rect.resize(2.0).resize(1.5); // Multi-step method chaining
    std::cout << "  After multi-resize (2.0 then 1.5): ";
    rect.printInfo();
    std::cout << "\n";

    // 4. Test Const Object constraints
    std::cout << "Const Object Demonstration:\n";
    const Circle constCircle(5.0);
    // constCircle.setRadius(10.0); // Compilation Error if uncommented
    std::cout << "  Const Circle Area: " << constCircle.calculateArea() << "\n\n";

    // 5. Test Setters Validation
    std::cout << "Input Validation Check:\n";
    rect.setLength(-2.5);
    circ.setRadius(0.0);
    std::cout << "\n";

    // 6. Bonus Challenge Demonstration
    std::cout << "BONUS: Triangle Demonstration:\n";
    Triangle tri(3.0, 4.0, 5.0);
    tri.print();
    
    std::cout << "  Scaling triangle...\n";
    tri.scale(2.0).scale(0.5); // Chaining test
    tri.print();

    std::cout << "  Testing invalid triangle validation:\n";
    Triangle invalidTri(1.0, 2.0, 10.0);
    
    return 0;
}
