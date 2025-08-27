#include <iostream>
#include <iomanip>
using namespace std;

// Function to convert grade into grade points
double gradeToPoint(char grade) {
    switch (toupper(grade)) {
    case 'A': return 4.0;
    case 'B': return 3.0;
    case 'C': return 2.0;
    case 'D': return 1.0;
    case 'F': return 0.0;
    default:
        cout << "Invalid grade entered! Defaulting to 0.0\n";
        return 0.0;
    }
}

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    double totalCredits = 0, totalGradePoints = 0;

    cout << "\n--- Enter course details ---\n";

    for (int i = 1; i <= numCourses; i++) {
        char grade;
        double creditHours;

        cout << "\nCourse " << i << ":\n";
        cout << "Enter grade (A, B, C, D, F): ";
        cin >> grade;

        cout << "Enter credit hours: ";
        cin >> creditHours;

        double gradePoint = gradeToPoint(grade);

        cout << "Course " << i << " -> Grade: " << grade
            << " | Grade Point: " << gradePoint
            << " | Credit Hours: " << creditHours << endl;

        totalCredits += creditHours;
        totalGradePoints += gradePoint * creditHours;
    }

    double GPA = totalGradePoints / totalCredits;

    cout << "\n---------------------------------\n";
    cout << fixed << setprecision(2);
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "Final CGPA: " << GPA << endl;
    cout << "---------------------------------\n";

    return 0;
}
