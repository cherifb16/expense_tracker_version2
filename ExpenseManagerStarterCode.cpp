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
    

    int getMenu(){

        bool isChoiceOk=false;
        int selectedChoice = -1;
        while (!isChoiceOk)
        {
            cout<<"Menu:"<<endl;
            cout<<"1. Add an expense"<<endl;
            cout<<"2. View expenses by category"<<endl;
            cout<<"3. Calculate total expenses"<<endl;
            cout<<"4. Exit"<<endl;

            // Select a value between 1 and 4
            cout<<"Enter your choice: ";

            // Add here, code for reading user input and update user choice
            
         
            if(cin.fail() || selectedChoice<1 || selectedChoice>4 ){

                cout<<"Enter a valid choice"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            else{
                // Add code here to stop while loop while when user input right number
            }

        }
        
        return selectedChoice;
    }



    void addExpense(string category, float expense){

        /* Write expense to the expenses.txt file

        input: category and expense
        output: category,expense i.e if category="Water Bills" and expense=200.23 
        on the file it will be written like: Water Bills,200.23
        */

       // Using If, else if, else handle exception on expense and category

       // Check if expense amount is greater than 0. throw std::invalid_argument error if amount is negative or equal to zer0.

       if (expense<=0){
        throw std::invalid_argument("Negative or zero expense not allowed.");
       }

       // Check if category is at least 3 characters. throw std::invalid_argument error if category length is not at least 3 characters.
       else if(category.length()<3){
        throw std::invalid_argument("Expense category should be at least 3 characters.");
       }

       // Write to the file
       else{

        // Add code here, Open file for appending mode remember to add end of line statement and close file after writing is done
        

        // Display Successful message
        cout<<"Expense Category: "<< category <<" Amount: $"<< expense <<" Expense added successfully!";
       }

        

    }

    vector<CategoryExpensePair> readExpenses(){

        /* Read All expenses saved on the expenses.txt file 

        */

       // Check if file exists first if not raise an invalid_argument error
       // Use getline method to get each category, expense pair at once
       // While loop can be used for reading content of the file.
       // after getting each line split line to extract and get expense category and expense amount for that category
       // As you read update the vector of the struct CategoryExpensePair list.
       vector<CategoryExpensePair> expenses;


       //ADD CODE HERE for reading filename(expenses.txt)  using public defined variable filename 


       return expenses;       

    }


    void printHeader(){
        cout<<"| Category | Amount   |"<<endl;
        cout<<"***********************"<<endl;
        cout<<endl;

    }



    /* Method for view expenses by category*/
    void viewExpenseByCategory(string category){

        //Get All expenses
        // print the the title and Header
        // loop them through and print expenses where category is the same as the category from user input
        vector<CategoryExpensePair> expenses;
        

        // ADD CODE To  Reading all expenses
        

        // Printing title
        cout<<"Expenses for Category: "<<category<<endl;
        // Printing header
        printHeader();

        // ADD CODE HERE print expenses for given category
        // Print using printExpense method


    }


    /* Method for calculating expenses*/
    float calculateExpenses(){

        /* To do

        Read All Expenses and store them in a vector
        Calculate total Expenses

        return the calculated total amount        
        */
        vector<CategoryExpensePair> expenses;
    
        float totalExpense = 0;

        // ADD CODE HERE to Read All expenses
        // ADD CODE HERE to calculate total expenses
    

        return 12; // UPDATE ME To return right value

    }

    
    string sizeTextto10(string expenseCategory) {
        /*Method to always limit text to a certain length is reached. 
    
        If max length is 10
        e.g1: "House Materials" will be formatted to "House Mate"
        e.g2: "Clothes" will be formated to "Clothes   " it means 3spaces added to make charaters to 10
        */

       
        // ADD CODE HERE to return formated string

    }

    string sizeExpAmountTo9 (float amount){

        /* 
        in: (5.5525) -> out: "5.55     "
        in: (1234567.690) -> out: "1234567.6" 
        */

       // ADD CODE HERE to return formated string
    }

    void printExpense(CategoryExpensePair expense){

        /* Prints an instance of an expense.

        Args:
            - expense: the expense to be displayed. type: a structure of CategoryExpensePair of a string(category) and a floating number(expense amount)

        Returns:
            - The string representation to be displayed 
        */
       
        //TODO:Produce an output such that the line starts with a | and ends with the same |.
        /*
        the category should be output by using 10 characters, left-aligned, space-filled.
        the amount is preceded by a $ sign, and occupies as well 10 characters, left-aligned, space filled.
        here space filled means that if there is less than 10 characters, you should fill the
        line with spaces. Extra characters can be truncated. Use 2 decimal positions for the amount.
        Below two examples

        in: (Clothes,5.5525) -> out: |Clothes   |$5.55     |
        in: (House Materials,2424.69) -> out: |House Mate|$2424.69  |
        */

       // Method call for sizing expense category text to 10 characters
       std::cout << "|" << sizeTextto10(expense.category);

       // Method call for sizing expense amount to 10 characters inclusive of the $ sign
       cout << "|$"<< sizeExpAmountTo9(expense.expense) << "|" << std::endl;

    }
};


int main(){

    // Variable declaration
    int choice = -1;
    string category;
    float expense;
    float totalExpenses;
    ExpenseManager expmanager;

    // Set File Name to expenses.txt
    expmanager.filename = "expenses.txt";


    // Getting user's choices
    while (choice!=4)
    {
        //Calling Method that displays the Menu
        choice = expmanager.getMenu();

        //Handling the Add expense choice
        if(choice == 1){
            cout<<"Add an Expense"<<endl;
            cout<<"Enter Expense Category: ";

            /* cin.ignore() is used after reading choice to discard any remaining characters in the input stream, including the newline character. */
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            /*getline is used to get user input of string that can contains more than one words. normal cin stops once a whitespace is detected.*/
            getline(cin, category);
            cout<<"Enter Expense Amount: "<<endl;
            cin>>expense;

            /*Checks if user input

            Category should at least have 3 characters
            expense should be a positve float number. i.e expense is greater than zero. 

            on wrong inputs i.e when cin functions failed or category or expense condition not met.
            clear cin and prompt user again to select from choices(1-4). 

            else call the expense methods.
            */

            if (cin.fail() || category.length()<3 || expense<=0)
            {
                cout<<"Enter a valid Expense: "<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }
            else{
            
                expmanager.addExpense(category, expense);
            }
            

            
        }

        // Handleling view expenses by category
        else if(choice == 2){
            cout<<"View Expenses by Category"<<endl;
            cout<<"Enter Expense Category Name: ";

             /* cin.ignore() is used after reading choice to discard any remaining characters in the input stream, including the newline character. */
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            /*getline is used to get user input of string that can contains more than one words. normal cin stops once a whitespace is detected.*/
            getline(cin, category);

            // Call the viewExpenseByCategory Method
            expmanager.viewExpenseByCategory(category);

        }

        // Handleling total expenses calculations
        else if(choice == 3){

            //Call the calculateExpenses method
            totalExpenses = expmanager.calculateExpenses();

            //Displaying total expenses
            cout<<"Total Expenses: $"<<totalExpenses<<endl;
        }

        // Exiting the Expense Tracker Application
        else if(choice == 4){

            //Displaying Exit Message
            cout<<"Exiting the Expense Tracker Application...";

            // Ending the program normally.
            return 0;
        }
    }
       
    cout<<"Exiting the Expense Tracker Application...";

    return 0;
}
