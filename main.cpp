#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>

// Task structure
struct Task {
    std::string name;
    int priority;
    std::string dueDate;
    std::string category;
    bool completed;
};

// Function to display the menu
void displayMenu() {
    std::cout << "==== To-Do List ====" << std::endl;
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. View Tasks" << std::endl;
    std::cout << "3. Sort and Display Tasks" << std::endl;
    std::cout << "4. Mark Task as Completed" << std::endl;
    std::cout << "5. Remove Task" << std::endl;
    std::cout << "6. Save and Quit" << std::endl;
    std::cout << "====================" << std::endl;
}

// Function to add a task to the list
void addTask(std::vector<Task>& taskList) {
    Task task;
    std::cout << "Enter Task Name: ";
    std::cin.ignore();
    std::getline(std::cin, task.name);

    std::cout << "Enter Priority (1-5): ";
    std::cin >> task.priority;

    std::cout << "Enter Due Date (YYYY-MM-DD): ";
    std::cin >> task.dueDate;

    std::cout << "Enter Category: ";
    std::cin.ignore();
    std::getline(std::cin, task.category);

    task.completed = false;
    taskList.push_back(task);
    std::cout << "Task added successfully!" << std::endl;
}

// Function to view tasks
void viewTasks(const std::vector<Task>& taskList) {
    std::cout << "==== Task List ====" << std::endl;
    for (size_t i = 0; i < taskList.size(); ++i) {
        std::cout << "[" << i + 1 << "] ";
        if (taskList[i].completed) {
            std::cout << "[Completed] ";
        }
        std::cout << "Name: " << taskList[i].name << " | Priority: " << taskList[i].priority
                  << " | Due Date: " << taskList[i].dueDate << " | Category: " << taskList[i].category << std::endl;
    }
    std::cout << "====================" << std::endl;
}

// Function to sort tasks by priority
bool sortByPriority(const Task& a, const Task& b) {
    return a.priority > b.priority;
}

// Function to sort tasks by due date
bool sortByDueDate(const Task& a, const Task& b) {
    return a.dueDate < b.dueDate;
}

// Function to sort and display tasks
void sortAndDisplayTasks(std::vector<Task>& taskList) {
    int sortChoice;
    std::cout << "Sort tasks by:" << std::endl;
    std::cout << "1. Priority" << std::endl;
    std::cout << "2. Due Date" << std::endl;
    std::cin >> sortChoice;

    if (sortChoice == 1) {
        std::sort(taskList.begin(), taskList.end(), sortByPriority);
    } else if (sortChoice == 2) {
        std::sort(taskList.begin(), taskList.end(), sortByDueDate);
    } else {
        std::cout << "Invalid choice. Sorting by priority by default." << std::endl;
        std::sort(taskList.begin(), taskList.end(), sortByPriority);
    }

    viewTasks(taskList);
}

// Function to mark a task as completed
void markCompleted(std::vector<Task>& taskList) {
    int index;
    std::cout << "Enter the index of the task to mark as completed: ";
    std::cin >> index;

    if (index >= 1 && index <= static_cast<int>(taskList.size())) {
        taskList[index - 1].completed = true;
        std::cout << "Task marked as completed!" << std::endl;
    } else {
        std::cout << "Invalid task index." << std::endl;
    }
}

// Function to remove a task
void removeTask(std::vector<Task>& taskList) {
    int index;
    std::cout << "Enter the index of the task to remove: ";
    std::cin >> index;

    if (index >= 1 && index <= static_cast<int>(taskList.size())) {
        taskList.erase(taskList.begin() + index - 1);
        std::cout << "Task removed successfully!" << std::endl;
    } else {
        std::cout << "Invalid task index." << std::endl;
    }
}

// Function to save tasks to a file
void saveTasks(const std::vector<Task>& taskList) {
    std::ofstream file("tasks.txt");
    if (!file) {
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
        return;
    }

    for (const Task& task : taskList) {
        file << task.name << "," << task.priority << "," << task.dueDate << ","
             << task.category << "," << task.completed << std::endl;
    }

    file.close();
}

// Function to load tasks from a file
void loadTasks(std::vector<Task>& taskList) {
    std::ifstream file("tasks.txt");
    if (!file) {
        std::cerr << "No existing tasks file found. Starting with an empty task list." << std::endl;
        return;
    }

    taskList.clear();

    std::string line;
    while (std::getline(file, line)) {
        Task task;
        std::istringstream iss(line);
        std::getline(iss, task.name, ',');
        iss >> task.priority;
        std::getline(iss >> std::ws, task.dueDate, ',');
        std::getline(iss >> std::ws, task.category, ',');
        iss >> std::boolalpha >> task.completed;

        taskList.push_back(task);
    }

    file.close();
}

int main() {
    std::vector<Task> taskList;
    loadTasks(taskList);

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addTask(taskList);
                break;
            case 2:
                viewTasks(taskList);
                break;
            case 3:
                sortAndDisplayTasks(taskList);
                break;
            case 4:
                markCompleted(taskList);
                break;
            case 5:
                removeTask(taskList);
                break;
            case 6:
                saveTasks(taskList);
                std::cout << "Tasks saved. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
