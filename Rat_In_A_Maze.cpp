// CPP program to solve Rat in a maze
// problem with backtracking using stack

//Solving without using #include<Stack> and by creating our OWN STACK
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class node;

class node
{
public:
    int x, y;
    int dir;
    node *next;

    node(int i, int j)
    {
        x = i;
        y = j;

        // Initially direction
        // set to 0
        dir = 0;
    }
};

class Stack
{
public:
    node *data;
    Stack()
    {
        data = NULL;
    }
    void push(node *n)
    {
        if (data == NULL)
        {
            data = n;
        }
        else
        {
            n->next = data;
            data = n;
        }
    }
    node *pop()
    {
        if (data == NULL)
        {
            return NULL;
        }
        else
        {
            node *temp = data;
            data = data->next;
            return temp;
        }
    }

    bool isEmpty()
    {
        if (data == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    node *top()
    {
        return data;
    }
    void print()
    {
        node *temp = data;
        while (temp != NULL)
        {
            cout << temp->x << " " << temp->y << endl;
            temp = temp->next;
        }
    }
};

int endx, endy;

Stack isReachable(int **maze, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    // creating map
    map<pair<int, int>, bool> visited;
    // setting map to visited
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            visited[make_pair(i, j)] = false;
        }
    }

    // stack<node> stackk;
    Stack stack;

    int i = 0, j = 0;
    node *n = new node(i, j);
    // node temp(i, j);

    stack.push(n);
    stack.print();
    // stackk.push(temp);

    while (!stack.isEmpty())
    {
        node *temp = stack.top();
        int d = temp->dir;
        // stackk.pop();

        i = temp->x;
        j = temp->y;
        visited[make_pair(i, j)] = true;

        temp->dir++;
        stack.pop();
        stack.push(temp);

        if (i == endx && j == endy)
        {
            return stack;
        }

        // checking if the next cell is valid
        // and not visited
        if (d == 0)
        {
            if (j + 1 < col && maze[i][j + 1] && !visited[{i, j + 1}])
            {
                visited[{i, j + 1}] = true;
                node *n = new node(i, j + 1);
                stack.push(n);
            }
        }

        // Checking the left direction //now down
        else if (d == 1)
        {
            if (i + 1 < row && maze[i + 1][j] && !visited[{i + 1, j}])
            {
                visited[{i + 1, j}] = true;
                node *n = new node(i + 1, j);
                stack.push(n);
            }
        }

        // Checking the down direction //now left
        else if (d == 2)
        {
            if (j - 1 >= 0 && maze[i][j - 1] && !visited[{i, j - 1}])
            {
                visited[{i, j - 1}] = true;
                node *n = new node(i, j - 1);
                stack.push(n);
            }
        }
        // Checking the right direction //converted to up
        else if (d == 3)
        {
            if (i - 1 >= 0 && maze[i - 1][j] && !visited[{i - 1, j}])
            {
                visited[{i - 1, j}] = true;
                node *n = new node(i - 1, j);
                stack.push(n);
            }
        }

        else // come back to previous known point and check other direction and make visited false for points coming back to
        {
            visited[{i, j}] = false;
            stack.pop();
        }
    }

    // If the stack is empty and
    // no path is found return false.
    cout << "\nNo path found.\n"
         << endl;
}

int index = 0;
void printPath(Stack stack)
{
    if (stack.isEmpty())
    {
        return;
    }

    node *temp = stack.data;

    int array[100];
    while (temp != NULL)
    {
        array[index] = temp->x;
        index++;
        array[index] = temp->y;
        index++;
        temp = temp->next;
    }

    for (int i = index - 1; i >= 0; i -= 2)
    {
        cout << "(" << array[i - 1] << ", " << array[i] << ") ";
    }
}
// Driver code
int main()
{

    fstream file;
    file.open("maze.txt", ios::in);

    int row = 0;
    int col = 0;
    file >> row;
    file >> col;
    cout << row << " " << col << endl;

    int arr[row][col];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            arr[i][j] = 1;
        }
    }

    int hurdles = 0;
    string str;
    file >> str;
    if (str == "hurdles")
    {
        file >> hurdles;
    }
    cout << "Hurdles: " << hurdles << endl;

    // Creating Array with Hurdles
    int num1 = 0;
    int num2 = 0;
    while (file >> num1)
    {
        file >> num2;
        arr[num1][num2] = 0;
    }

    // Creating 2D Array
    int **Maze = new int *[row];
    for (int i = 0; i < row; i++)
    {
        Maze[i] = new int[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Maze[i][j] = arr[i][j];
        }
    }

    // Endpoints
    endx = row - 1;
    endy = col - 1;

    // stack<node> Path = (isReachable(Maze, row, col));
    Stack Path = (isReachable(Maze, row, col));
    printPath(Path);

    return 0;
}
