#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

struct Task {
    int id;
    string title, desc, due;
    bool done;
    Task* next;
};

Task* head = nullptr;
stack<Task> undoStack;
queue<Task*> pending;
int countID = 0;

Task* findTask(int id) {
    for (Task* t = head; t; t = t->next)
        if (t->id == id) return t;
    return nullptr;
}

void addTask() {
    Task* t = new Task();
    t->id = ++countID;
    cin.ignore();
    cout << "Title: "; getline(cin, t->title);
    cout << "Description: "; getline(cin, t->desc);
    cout << "Due Date: "; getline(cin, t->due);
    t->done = false; t->next = head; head = t;
    pending.push(t);
    cout << "✅ Task Added!\n";
}

void viewTasks() {
    if (!head) return void(cout << "No tasks.\n");
    cout << "\nID | Title | Description | Due | Done\n";
    for (Task* t = head; t; t = t->next)
        cout << t->id << " | " << t->title << " | " << t->desc
             << " | " << t->due << " | " << (t->done ? "Yes" : "No") << '\n';
}

void editTask() {
    int id; cout << "Enter ID: "; cin >> id;
    Task* t = findTask(id);
    if (!t) return void(cout << "Not found.\n");
    cin.ignore();
    cout << "New Title: "; getline(cin, t->title);
    cout << "New Desc: "; getline(cin, t->desc);
    cout << "New Due: "; getline(cin, t->due);
    cout << "✏️ Task Updated!\n";
}

void deleteTask() {
    int id; cout << "Enter ID: "; cin >> id;
    Task *t = head, *p = nullptr;
    while (t && t->id != id) { p = t; t = t->next; }
    if (!t) return void(cout << "Not found.\n");
    undoStack.push(*t);
    if (p) p->next = t->next; else head = t->next;
    delete t; cout << "🗑️ Task Deleted!\n";
}

void undoDelete() {
    if (undoStack.empty()) return void(cout << "Nothing to undo.\n");
    Task t = undoStack.top(); undoStack.pop();
    Task* n = new Task(t);
    n->next = head; head = n;
    cout << "🔁 Undo Successful!\n";
}

void markDone() {
    int id; cout << "Enter ID: "; cin >> id;
    Task* t = findTask(id);
    if (!t || t->done) return void(cout << "Invalid.\n");
    t->done = true; cout << "✔️ Task Completed!\n";
}

int main() {
    int c;
    do {
        cout << "\n1.Add  2.View  3.Edit  4.Delete  5.Undo  6.MarkDone  7.Exit\nChoice: ";
        cin >> c;
        switch (c) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: editTask(); break;
            case 4: deleteTask(); break;
            case 5: undoDelete(); break;
            case 6: markDone(); break;
            case 7: cout << "Bye!\n"; break;
            default: cout << "Invalid!\n";
        }
    } while (c != 7);
}
s