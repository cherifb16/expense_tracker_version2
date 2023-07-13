#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

struct Expense {
    string category;
    float amount;
};

class ExpenseTracker {
private:
    string filename;

public:
    ExpenseTracker(const string& filename) : filename(filename) {}

    int getMenuChoice() {
        int choice;
        cout << "Menu:\n";
        cout << "1. Add an expense\n";
        cout << "2. View expenses by category\n";
        cout << "3. Calculate total expenses\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    void addExpense(const string& category, float amount) {
        if (amount <= 0) {
            throw invalid_argument("Negative or zero expense amount not allowed.");
        }

        ofstream file(filename, ios::app);
        if (!file) {
            throw runtime_error("Error: Failed to open expenses file for writing.");
        }

        file << category << "," << fixed << setprecision(2) << amount << endl;
        file.close();

        cout << "Expense added successfully!" << endl;
    }

    vector<Expense> readExpenses() {
        vector<Expense> expenses;

        ifstream file(filename);
        if (!file) {
            throw runtime_error("Error: Failed to open expenses file for reading.");
        }

        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string category = line.substr(0, commaPos);
                float amount = stof(line.substr(commaPos + 1));
                Expense expense;
                expense.category = category;
                expense.amount = amount;
                expenses.push_back(expense);
            }
        }

        file.close();
        return expenses;
    }

    void viewExpensesByCategory(const string& category) {
        vector<Expense> expenses = readExpenses();
        cout << "Expenses for Category: " << category << endl;
        cout << "| Category  |  Amount  |" << endl;
        cout << "************************" << endl;
        for (const Expense& expense : expenses) {
            if (expense.category == category) {
                cout << "| " << setw(10) << left << expense.category << " | $" << setw(8) << fixed << setprecision(2) << expense.amount << " |" << endl;
            }
        }
    }

    float calculateTotalExpenses() {
        vector<Expense> expenses = readExpenses();
        float totalExpenses = 0.0f;
        for (const Expense& expense : expenses) {
            totalExpenses += expense.amount;
        }
        return totalExpenses;
    }
};

int main() {
    ExpenseTracker expenseTracker("expenses.txt");

    while (true) {
        int choice = expenseTracker.getMenuChoice();

        if (choice == 1) {
            string category;
            float amount;

            cout << "Add an Expense" << endl;
            cout << "Expense Category: ";
            cin.ignore();
            getline(cin, category);
            cout << "Expense Amount: $";
            cin >> amount;

            try {
                expenseTracker.addExpense(category, amount);
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        } else if (choice == 2) {
            string category;

            cout << "View Expenses by Category" << endl;
            cout << "Enter the category name: ";
            cin.ignore();
            getline(cin, category);

            expenseTracker.viewExpensesByCategory(category);
        } else if (choice == 3) {
            float totalExpenses = expenseTracker.calculateTotalExpenses();
            cout << "Total Expenses: $" << fixed << setprecision(2) << totalExpenses << endl;
        } else if (choice == 4) {
            cout << "Exiting the Expense Tracker Application..." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
