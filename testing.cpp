#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <limits>


using namespace std;

// Data structure to hold Category and Expense
struct CategoryExpensePair
{
    string category;
    float expense;
};

class ExpenseManager
{
private:
    int maxSize = 10;

public:
    string filename;
    

    int getMenu()
    {
        bool isChoiceOk = false;
        int selectedChoice = -1;

        while (!isChoiceOk)
        {
            cout << "Menu:" << endl;
            cout << "1. Add an expense" << endl;
            cout << "2. View expenses by category" << endl;
            cout << "3. Calculate total expenses" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";

            // Read user input and update selectedChoice
            cin >> selectedChoice;
         
            if (cin.fail() || selectedChoice < 1 || selectedChoice > 4)
            {
                cout << "Enter a valid choice" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            else
            {
                isChoiceOk = true;
            }
        }
        
        return selectedChoice;
    }



    void addExpense(string category, float expense)
    {
        if (expense <= 0)
        {
            throw std::invalid_argument("Negative or zero expense not allowed.");
        }
        else if (category.length() < 3)
        {
            throw std::invalid_argument("Expense category should be at least 3 characters.");
        }
        else
        {
            // Open the file in appending mode, write the expense category and amount, and close the file
            ofstream outputFile(filename, ios::app);
            if (!outputFile)
            {
                throw std::invalid_argument("Failed to open the file for writing.");
            }
            outputFile << category << "," << expense << endl;
            outputFile.close();

            // Display successful message
            cout << "Expense Category: " << category << " Amount: $" << fixed << setprecision(2) << expense << " Expense added successfully!"<< endl;
        }
    }

    vector<CategoryExpensePair> readExpenses()
    {
        vector<CategoryExpensePair> expenses;

        // Check if the file exists
        ifstream inputFile(filename);
        if (!inputFile)
        {
            throw std::invalid_argument("Expense file does not exist or cannot be opened.");
        }

        // Read each line from the file
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string category;
            float expense;

            // Split the line into category and expense
            if (getline(ss, category, ',') && ss >> expense)
            {
                // Create a CategoryExpensePair and add it to the vector
                CategoryExpensePair pair = {category, expense};
                expenses.push_back(pair);
            }
        }

        inputFile.close();
        return expenses;
    }

    void printHeader()
    {
        cout << "| Category | Amount   |" << endl;
        cout << "***********************" << endl;
        cout << endl;
    }

    void viewExpenseByCategory(string category)
    {
        vector<CategoryExpensePair> expenses = readExpenses();

        cout << "Expenses for Category: " << category << endl;
        printHeader();

        for (const auto& expense : expenses)
        {
            if (expense.category == category)
            {
                printExpense(expense);
            }
        }
    }

    float calculateExpenses()
    {
        vector<CategoryExpensePair> expenses = readExpenses();
        float totalExpense = 0.0f;

        for (const auto& expense : expenses)
        {
            totalExpense += expense.expense;
        }

        return totalExpense;
    }

    string sizeTextto10(string expenseCategory)
    {
        if (expenseCategory.length() > 10)
        {
            return expenseCategory.substr(0, 10);
        }
        else
        {
            return expenseCategory + string(10 - expenseCategory.length(), ' ');
        }
    }

    string sizeExpAmountTo9(float amount)
    {
        stringstream ss;
        ss << fixed << setprecision(2) << amount;
        string formattedAmount = ss.str();

        if (formattedAmount.length() > 9)
        {
            return formattedAmount.substr(0, 9);
        }
        else
        {
            return formattedAmount + string(9 - formattedAmount.length(), ' ');
        }
    }

    void printExpense(CategoryExpensePair expense)
    {
        cout << "|" << sizeTextto10(expense.category) << "|$" << sizeExpAmountTo9(expense.expense) << "|" << endl;
    }
};

int main()
{
    int choice = -1;
    string category;
    float expense;
    float totalExpenses;
    ExpenseManager expmanager;
    expmanager.filename = "expenses.txt";

    while (choice != 4)
    {
        choice = expmanager.getMenu();

        if (choice == 1)
        {
            cout << "Add an Expense" << endl;
            cout << "Enter Expense Category: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, category);
            cout << "Enter Expense Amount: " << endl;
            cin >> expense;

            if (cin.fail() || category.length() < 3 || expense <= 0)
            {
                cout << "Enter a valid Expense: " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                expmanager.addExpense(category, expense);
            }
        }
        else if (choice == 2)
        {
            cout << "View Expenses by Category" << endl;
            cout << "Enter Expense Category Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, category);
            expmanager.viewExpenseByCategory(category);
        }
        else if (choice == 3)
        {
            totalExpenses = expmanager.calculateExpenses();
            cout << "Total Expenses: $" << fixed << setprecision(2) << totalExpenses << endl;
        }
        else if (choice == 4)
        {
            cout << "Exiting the Expense Tracker Application...";
            return 0;
        }
    }
       
    cout << "Exiting the Expense Tracker Application...";

    return 0;
}
