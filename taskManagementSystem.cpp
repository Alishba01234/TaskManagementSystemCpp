#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <regex>
#include <windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

class Task {
protected:
    int id;
    string title;
    string description;
    string dueDate;
    int priority;
    string status;

public:
    static int taskCount;

    // Constructor
    Task(string t, string d, string dd, int p, string s) {
        id = ++taskCount;
        title = t;
        description = d;
        dueDate = dd;
        priority = p;
        status = s;
    }

    // Virtual Destructor
    virtual ~Task() {}

    // Encapsulation (Getters & Setters)
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getDueDate() const { return dueDate; }
    int getPriority() const { return priority; }
    string getStatus() const { return status; }

    void setTitle(string t) { title = t; }
    void setDescription(string d) { description = d; }
    void setDueDate(string dd) { dueDate = dd; }
    void setPriority(int p) { priority = p; }
    void setStatus(string s) { status = s; }

    // Display Task
    virtual void displayTask() const {
        cout << "ID: " << id << " , Title: " << title << " , Due Date: " << dueDate
             << " , Priority: " << priority << " , Status: " << status << ".\n";
    }

    // Save Task to File
    virtual string toFileString() const {
        return to_string(id) + "," + title + "," + description + "," + dueDate + "," +
               to_string(priority) + "," + status + "\n";
    }
};

int Task::taskCount = 0; // Initialize static variable

bool containsDigits(const string &str) {
    return any_of(str.begin(), str.end(), ::isdigit);
}

// Function to validate the date format (YYYY-MM-DD)
bool isValidDate(const string &date) {
    regex datePattern("\\d{4}-\\d{2}-\\d{2}");
    return regex_match(date, datePattern);
}

// Task Manager Class
class TaskManager {
private:
    vector<Task> tasks;

public:
    // Load tasks from file
    void loadTasks() {
        ifstream file("tasks.txt");
        if (!file) return;

        string title, description, dueDate, status;
        int priority, id;
        while (file >> id) {
            file.ignore();
            getline(file, title, ',');
            getline(file, description, ',');
            getline(file, dueDate, ',');
            file >> priority;
            file.ignore();
            getline(file, status);
            tasks.emplace_back(title, description, dueDate, priority, status);
        }
        file.close();
    }

    // Save tasks to file
    void saveTasks() {
        ofstream file("tasks.txt");
        for (const auto &task : tasks) {
            file << task.toFileString();
        }
        file.close();
    }

    // Add Task
    void addTask() {
        string title, description, dueDate, status;
        int priority;

        // Title validation
        while (true) {
            cout << "Enter Task Title: ";
            getline(cin, title);
            if (containsDigits(title)) {
                SetConsoleTextAttribute(hConsole, 12); // Red for error
                cout << "Title should not contain digits. Please enter a valid title.\n";
                SetConsoleTextAttribute(hConsole, 9);
            } else {
                break;
            }
        }

        // Description
        cout << "Enter Description: ";
        getline(cin, description);

        // Due Date validation
        while (true) {
            cout << "Enter Due Date (YYYY-MM-DD): ";
            getline(cin, dueDate);
            if (isValidDate(dueDate)) {
                break;
            } else {
                SetConsoleTextAttribute(hConsole, 12); // Red for error
                cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
                SetConsoleTextAttribute(hConsole, 9);
            }
        }

        // Priority validation
        while (true) {
            cout << "Enter Priority (1-5): ";
            cin >> priority;
            cin.ignore();
            if (priority < 1 || priority > 5) {
                SetConsoleTextAttribute(hConsole, 12); // Red for error
                cout << "Priority must be between 1 and 5.\n";
                SetConsoleTextAttribute(hConsole, 9);
            } else {
                break;
            }
        }

        // Status validation
        while (true) {
            cout << "Enter Status (Pending/In Progress/Completed): ";
            getline(cin, status);
            if (status == "Pending" || status == "In Progress" || status == "Completed") {
                break;
            } else {
                SetConsoleTextAttribute(hConsole, 12); // Red for error
                cout << "Invalid status. Please enter 'Pending', 'In Progress', or 'Completed'.\n";
                SetConsoleTextAttribute(hConsole, 9);
            }
        }

        tasks.emplace_back(title, description, dueDate, priority, status);
        saveTasks();
        SetConsoleTextAttribute(hConsole, 2); // Green for success
        cout << "\tTask added successfully!.......\n\n";
    }

    // View All Tasks
    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks available.\n\n";
            return;
        }
        for (const auto &task : tasks) {
            task.displayTask();
        }
    }

    // Search Task
    void searchTask() {
        string keyword;
        cout << "Enter Task Title or Due Date to Search: ";
        getline(cin, keyword);
	    SetConsoleTextAttribute(hConsole, 2);
	    
        bool found = false;
        for (const auto &task : tasks) {
            if (task.getTitle() == keyword || task.getDueDate() == keyword) {
                task.displayTask();
                found = true;
            }
        }
        if (!found) cout << "\tNo matching task found.\n\n";
    }

    // Update Task
    void updateTask() {
        int id;
        cout << "Enter Task ID to Update: ";
        cin >> id;
        cin.ignore();

        for (auto &task : tasks) {
            if (task.getId() == id) {
                string title, description, dueDate, status;
                int priority;
                while (true) {
            		cout << "Enter new Title: ";
            		getline(cin, title);
            		if (containsDigits(title)) {
                		SetConsoleTextAttribute(hConsole, 12); // Red for error
                		cout << "Title should not contain digits. Please enter a valid title.\n";
                		SetConsoleTextAttribute(hConsole, 9);
            		} else {
                		break;
            		}
        		}

			    cout << "Enter new Description: ";
        		getline(cin, description);

			    while (true) {
            		cout << "Enter new Due Date (YYYY-MM-DD): ";
            		getline(cin, dueDate);
            		if (isValidDate(dueDate)) {
                		break;
            		} else {
                		SetConsoleTextAttribute(hConsole, 12); // Red for error
                		cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
                		SetConsoleTextAttribute(hConsole, 9);
            		}
        		}

        		while (true) {
        			cout << "Enter Priority (1-5): ";
        			cin >> priority;
        			cin.ignore();
        			if (priority < 1 || priority > 5) {
       			    	SetConsoleTextAttribute(hConsole, 12); // Red for error
            			cout << "Priority must be between 1 and 5.\n";
            			SetConsoleTextAttribute(hConsole, 9);
            		} else {
            			break;
            		}
        		}

			    while (true) {
            		cout << "Enter Status (Pending/In Progress/Completed): ";
            		getline(cin, status);
            		if (status == "Pending" || status == "In Progress" || status == "Completed") {
            			break;
            		} else {
                		SetConsoleTextAttribute(hConsole, 12); // Red for error
                		cout << "Invalid status. Please enter 'Pending', 'In Progress', or 'Completed'.\n";
                		SetConsoleTextAttribute(hConsole, 9);
            		}
        		}
        			
                task.setTitle(title);
                task.setDescription(description);
                task.setDueDate(dueDate);
                task.setPriority(priority);
                task.setStatus(status);

                saveTasks();
                SetConsoleTextAttribute(hConsole, 2);
                cout << "\tTask updated successfully!.....\n\n";
                return;
            }
        }
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\tTask not found.\n\n";
    }

    // Delete Task
    void deleteTask() {
        int id;
        cout << "Enter Task ID to Delete: ";
        cin >> id;
        cin.ignore();
	    SetConsoleTextAttribute(hConsole, 2);

        auto it = remove_if(tasks.begin(), tasks.end(), [id](const Task &task) {
            return task.getId() == id;
        });

        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            saveTasks();
            cout << "\tTask deleted successfully!.....\n\n";
        } else {
            cout << "\tTask not found.\n\n";
        }
    }

    // Sort Tasks by Due Date
    void sortByDueDate() {
        sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.getDueDate() < b.getDueDate();
        });
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\tTasks sorted by Due Date.....\n\n";
    }

    // Sort Tasks by Priority
    void sortByPriority() {
        sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.getPriority() < b.getPriority();
        });
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\tTasks sorted by Priority.....\n\n";
    }
};

// Main Function
int main() {
    TaskManager manager;
    manager.loadTasks();
    int choice;

    while (true) {
    	SetConsoleTextAttribute(hConsole,13);
    	cout<<"\n----------------------------------------------------------------------\n";
        cout << "\t\t\tTask Management System\n";
        cout<<"----------------------------------------------------------------------\n";
	    SetConsoleTextAttribute(hConsole, 11);
        cout << "1. Add Task\n";
        cout << "2. View All Tasks\n";
        cout << "3. Search Task\n";
        cout << "4. Update Task\n";
        cout << "5. Delete Task\n";
        cout << "6. Sort Tasks by Due Date\n";
        cout << "7. Sort Tasks by Priority\n";
        cout << "8. Exit\n";
        SetConsoleTextAttribute(hConsole, 13);
    	cout << "--------------------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
		system("CLS");
        SetConsoleTextAttribute(hConsole, 9);
        switch (choice) {
            case 1: manager.addTask(); break;
            case 2: manager.viewTasks(); break;
            case 3: manager.searchTask(); break;
            case 4: manager.updateTask(); break;
            case 5: manager.deleteTask(); break;
            case 6: manager.sortByDueDate(); break;
            case 7: manager.sortByPriority(); break;
            case 8: return 0;
            default: {
            	cout << "Invalid choice. Please try again.\n";
                cin.clear();  // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input left in the buffer
			}
        }
    }
}
