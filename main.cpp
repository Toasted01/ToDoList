#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/*
used to clear the input buffer
called before std::getline
*/
void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

struct ToDoItem
{
    std::string task;
    bool completed;
};

class ToDoList
{
private:
    std::vector<ToDoItem> items;

public:
    std::string addTask(const std::string &task);
    std::string markCompleted(int index);
    std::string deleteTask(int task);
    void display();
    void saveToFile();
};

/*
takes a string input for task name and adds it to the back of the vector
*/
std::string ToDoList::addTask(const std::string &newTask)
{
    if (newTask.empty())
    {
        return "cannot add task";
    }
    items.push_back({newTask, false});
    return "added task: " + newTask + "\n";
}

/*
checks if index is valid
then completes item at index
*/
std::string ToDoList::markCompleted(int index)
{
    if (index >= 0 && index < items.size())
    {
        items[index].completed = true;
        return "Task completed: " + std::to_string(index + 1) + "\n";
    }
    return "Unable to complete task: " + std::to_string(index + 1) + "\n";
}

/*
checks if index is valid
then erases item at index
*/
std::string ToDoList::deleteTask(int index)
{
    if (index >= 0 && index < items.size())
    {
        items.erase(items.begin() + index);
        return "Task deleted: " + std::to_string(index + 1) + "\n";
    }
    return "Unable to delete task: " + std::to_string(index + 1) + "\n";
}
/*
prints to console:
1. [X] "This task"
or
1. [ ] "This task"
*/
void ToDoList::display()
{
    std::cout << "ToDo List:\n";
    for (size_t i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ". " << (items[i].completed ? "[X] " : "[ ] ") << items[i].task << std::endl;
    }
}

/*
takes a string input for filename
checks to see if the file is opened by the stream
then if true, saves to file
*/
void ToDoList::saveToFile()
{
    std::string filename;
    std::cout << "Enter filename to save: ";
    clearInputBuffer();
    std::getline(std::cin, filename); // Get filename from user input

    std::ofstream file(filename); // Open a file for writing

    if (file.is_open())
    {
        for (const ToDoItem &item : items)
        {
            file << item.task << "," << item.completed << std::endl; // Write each task and its completion status to the file
        }
        std::cout << "Todo list saved to: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

int main()
{
    ToDoList todoList;
    int choice;
    std::string task;
    const std::string filename = "todo_list.txt";

    do
    {
        std::cout << "\nTodo List Application\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Mark Task as Completed\n";
        std::cout << "3. Delete Task\n";
        std::cout << "4. Display Tasks\n";
        std::cout << "5. Save Todo List to File\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Enter task: ";
            clearInputBuffer();
            std::getline(std::cin, task);
            std::cout << todoList.addTask(task);
            break;
        case 2:
            int index;
            std::cout << "Enter task index to mark as completed: ";
            std::cin >> index;
            std::cout << todoList.markCompleted(index - 1);
            break;
        case 3:
            int delIndex;
            std::cout << "Enter task index to delete: ";
            std::cin >> delIndex;
            todoList.deleteTask(delIndex - 1);
            break;
        case 4:
            todoList.display();
            break;
        case 5:
            todoList.saveToFile();
            break;
        case 6:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
        clearInputBuffer();
    } while (choice != 6);

    return 0;
}