#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Task {
    int id;
    string description;
};

// Function prototypes
void addTask(vector<Task>& tasks, int& nextId);
void viewTasks(const vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void saveTasks(const vector<Task>& tasks, const string& filename);
void loadTasks(vector<Task>& tasks, int& nextId, const string& filename);

int main() {
    vector<Task> tasks;
    int nextId = 1;
    string filename = "tasks.txt";

    // Load tasks from file
    loadTasks(tasks, nextId, filename);

    int choice;
    do {
        cout << "\nTask Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks, nextId);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                deleteTask(tasks);
                break;
            case 4:
                saveTasks(tasks, filename);
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}

void addTask(vector<Task>& tasks, int& nextId) {
    Task newTask;
    newTask.id = nextId++;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, newTask.description);
    tasks.push_back(newTask);
    cout << "Task added successfully.\n";
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to display.\n";
        return;
    }
    for (const auto& task : tasks) {
        cout << "ID: " << task.id << ", Description: " << task.description << "\n";
    }
}

void deleteTask(vector<Task>& tasks) {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;
    auto it = remove_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.id == id; });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        cout << "Task deleted successfully.\n";
    } else {
        cout << "Task not found.\n";
    }
}

void saveTasks(const vector<Task>& tasks, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error saving tasks to file.\n";
        return;
    }
    for (const auto& task : tasks) {
        outFile << task.id << '\n' << task.description << '\n';
    }
}

void loadTasks(vector<Task>& tasks, int& nextId, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "No existing task file found. Starting fresh.\n";
        return;
    }
    Task task;
    while (inFile >> task.id) {
        inFile.ignore();
        getline(inFile, task.description);
        tasks.push_back(task);
        nextId = task.id + 1;
    }
}
