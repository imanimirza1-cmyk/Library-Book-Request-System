#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Book Request Node
struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};
// Priority Queue Class
class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Add request according to priority (smaller number = higher priority)
    void Add(BookRequestNode* request)
    {
        request->next = nullptr;

        // Case 1: Queue is empty
        if (front == nullptr)
        {
            front = request;
            rear = request;
        }
        // Case 2: New request has higher priority than front
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        // Case 3: Insert somewhere after front
        else
        {
            BookRequestNode* current = front;
            while (current->next != nullptr &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }
            request->next = current->next;
            current->next = request;

            if (request->next == nullptr)
            {
                rear = request;
            }
        }
        count++;
    }

    // Remove highest-priority request
    BookRequestNode* Remove()
    {
        if (front == nullptr)
        {
            return nullptr;
        }

        BookRequestNode* request = front;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        request->next = nullptr;
        count--;
        return request;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        BookRequestNode* current = front;
        while (current != nullptr)
        {
            cout << "Student ID:   " << current->studentID << endl;
            cout << "Student Name: " << current->studentName << endl;
            cout << "Book ID:      " << current->bookID << endl;
            cout << "Book Title:   " << current->bookTitle << endl;
            cout << "Priority:     " << current->priority << endl;
            cout << "-----------------------------" << endl;
            current = current->next;
        }
    }

    // Copy Constructor
    PriorityQueue(const PriorityQueue& other)
    {
        front = nullptr;
        rear = nullptr;
        count = 0;

        BookRequestNode* current = other.front;
        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;
            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;
            Add(newNode);
            current = current->next;
        }
    }

    // Assignment Operator
    PriorityQueue& operator=(const PriorityQueue& other)
    {
        if (this == &other)
        {
            return *this;
        }

        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;

        BookRequestNode* current = other.front;
        while (current != nullptr)
        {
            BookRequestNode* newNode = new BookRequestNode;
            newNode->studentID = current->studentID;
            newNode->studentName = current->studentName;
            newNode->bookID = current->bookID;
            newNode->bookTitle = current->bookTitle;
            newNode->priority = current->priority;
            newNode->next = nullptr;
            Add(newNode);
            current = current->next;
        }
        return *this;
    }

    // Destructor
    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

// ==========================================
// Helper: Create Book Request
// ==========================================
BookRequestNode* CreateRequest(int studentID, string studentName,
                               int bookID, string bookTitle, int priority)
{
    BookRequestNode* request = new BookRequestNode;
    request->studentID = studentID;
    request->studentName = studentName;
    request->bookID = bookID;
    request->bookTitle = bookTitle;
    request->priority = priority;
    request->next = nullptr;
    return request;
}

// ==========================================
// Helper: Safe integer input
// ==========================================
int ReadInt(const string& prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}
// Menu
void ShowMenu()
{
    cout << "\n===== Library Book Request System =====" << endl;
    cout << "1. Add Book Request" << endl;
    cout << "2. Process Highest Priority Request" << endl;
    cout << "3. Display All Requests" << endl;
    cout << "4. Check Queue Status" << endl;
    cout << "5. Exit" << endl;
}
// Main
int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        ShowMenu();
        choice = ReadInt("Enter your choice: ");

        switch (choice)
        {
        case 1:
        {
            int studentID = ReadInt("Enter Student ID: ");

            string studentName;
            cout << "Enter Student Name: ";
            getline(cin, studentName);

            int bookID = ReadInt("Enter Book ID: ");

            string bookTitle;
            cout << "Enter Book Title: ";
            getline(cin, bookTitle);

            int priority;
            do
            {
                priority = ReadInt("Enter Priority (1=Exam/Urgent, 2=Assignment/Project, 3=Normal Reading): ");
                if (priority < 1 || priority > 3)
                {
                    cout << "Priority must be 1, 2, or 3." << endl;
                }
            } while (priority < 1 || priority > 3);

            BookRequestNode* request =
                CreateRequest(studentID, studentName, bookID, bookTitle, priority);
            requests.Add(request);

            cout << "Request added successfully." << endl;
            break;
        }

        case 2:
        {
            BookRequestNode* processed = requests.Remove();
            if (processed != nullptr)
            {
                cout << "\n===== Processing Request =====" << endl;
                cout << "Student ID:   " << processed->studentID << endl;
                cout << "Student Name: " << processed->studentName << endl;
                cout << "Book ID:      " << processed->bookID << endl;
                cout << "Book Title:   " << processed->bookTitle << endl;
                cout << "Priority:     " << processed->priority << endl;
                delete processed;
            }
            else
            {
                cout << "No requests to process. The queue is empty." << endl;
            }
            break;
        }

        case 3:
        {
            if (requests.IsEmpty())
            {
                cout << "No pending requests." << endl;
            }
            else
            {
                cout << "\n===== Pending Requests (Highest to Lowest Priority) =====" << endl;
                requests.PrintQueue();
            }
            break;
        }

        case 4:
        {
            if (requests.IsEmpty())
            {
                cout << "Queue Status: EMPTY" << endl;
            }
            if (requests.IsNotEmpty())
            {
                cout << "Queue Status: NOT EMPTY (pending requests exist)" << endl;
            }
            break;
        }

        case 5:
            cout << "Exiting... Releasing memory." << endl;
            break;

        default:
            cout << "Invalid choice. Please select 1-5." << endl;
        }

    } while (choice != 5);

    // Destructor of 'requests' frees any remaining nodes automatically
    return 0;
}
