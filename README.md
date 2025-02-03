# Task Management System

## Overview
The **Task Management System** is a console-based C++ application designed to help users efficiently manage their tasks. The application provides functionality to add, view, update, delete, search, and sort tasks based on priority or due date. Tasks are persisted using a text file, ensuring data retention between program executions.

## Features
- **Add Task**: Create a new task with a title, description, due date, priority, and status.
- **View Tasks**: Display all existing tasks.
- **Search Task**: Find tasks by title or due date.
- **Update Task**: Modify an existing task’s details.
- **Delete Task**: Remove a task by its unique ID.
- **Sort Tasks**:
  - By Due Date (earliest first)
  - By Priority (highest priority first)
- **Task Persistence**: Tasks are saved to and loaded from a file (`tasks.txt`).
- **Input Validation**: Ensures correct data entry for date format, priority range, and status.
- **Colored Console Output**: Uses Windows API (`SetConsoleTextAttribute`) for colored messages.

## Technologies Used
- **Programming Language**: C++
- **File Handling**: Used to persist tasks (`tasks.txt`)
- **Windows API**: For console color customization
- **Regular Expressions**: Used for date format validation

## Installation & Setup
### Prerequisites
- A C++ compiler (MinGW for Windows or g++ for Linux/macOS)
- Windows OS (for colored output, otherwise modify/remove `SetConsoleTextAttribute` calls)

### Compilation & Execution
1. Clone or download the repository.
2. Open a terminal or command prompt in the project directory.
3. Compile the program:
   ```sh
   g++ -o task_manager task_manager.cpp
   ```
4. Run the executable:
   ```sh
   ./task_manager  # (or `task_manager.exe` on Windows)
   ```

## Usage Instructions
Upon running the program, a menu-driven interface appears:
1. **Add a Task**: Enter task details with validation checks.
2. **View All Tasks**: Displays stored tasks.
3. **Search for a Task**: Find tasks using title or due date.
4. **Update a Task**: Modify an existing task’s attributes.
5. **Delete a Task**: Remove an unwanted task.
6. **Sort Tasks**: Order tasks by due date or priority.
7. **Exit**: Save changes and close the program.

## File Format (`tasks.txt`)
Each task is stored in the format:
```
ID,Title,Description,DueDate,Priority,Status
```
Example:
```
1,Project Report,Complete final report,2024-06-15,3,Pending
2,Meeting,Team discussion,2024-06-10,2,In Progress
```

## Contribution
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-branch`).
3. Commit changes (`git commit -m "Add new feature"`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

## License
This project is open-source under the MIT License.

## Author
Developed by ALISHBA JAWAID.

