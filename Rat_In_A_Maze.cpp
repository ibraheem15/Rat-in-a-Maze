// CPP program to solve Rat in a maze
// problem with backtracking using stack
//switched to Without Stack Implementaion
#include <cstring>
#include <iostream>
#include <fstream>
#include <stack>
#include <map>

using namespace std;

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

// Coordinates of Endpoints
int endx, endy;

stack<node> isReachable(int **maze, int row, int col)
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
    // setting map to visited(False)
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            visited[make_pair(i, j)] = false;
        }
    }

    stack<node> stackk;

    // Initially pushing (0, 0) in stack
    int i = 0, j = 0;
    node temp(i, j);

    stackk.push(temp);

    while (!stackk.empty())
    {

        temp = stackk.top();
        int d = temp.dir;

        i = temp.x, j = temp.y;

        temp.dir++;
        stackk.pop();
        stackk.push(temp);

        if (i == endx && j == endy)
        {
            return stackk;
        }

        // Checking the Right direction
        if (d == 0)
        {
            if (j + 1 < col && maze[i][j + 1] && !visited[{i, j + 1}])
            {
                node point(i, j + 1);
                visited[{i, j + 1}] = true;
                stackk.push(point);
            }
        }

        // Checking the Down direction
        else if (d == 1)
        {
            if (i + 1 < row && maze[i + 1][j] && !visited[{i + 1, j}])
            {
                node point(i + 1, j);
                visited[{i + 1, j}] = true;
                stackk.push(point);
            }
        }

        // Checking the Left direction
        else if (d == 2)
        {
            if (j - 1 >= 0 && maze[i][j - 1] && !visited[{i, j - 1}])
            {
                node point(i, j - 1);
                visited[{i, j - 1}] = true;
                stackk.push(point);
            }
        }
        // Checking the Up direction
        else if (d == 3)
        {
            if (i - 1 >= 0 && maze[i - 1][j] && !visited[{i - 1, j}])
            {
                node point(i - 1, j);
                visited[{i - 1, j}] = true;
                stackk.push(point);
            }
        }

        // If none of the direction can take
        // the rat to the Food, retract back
        // to the path where the rat came from.
        else // come back to previous known point and check other direction and make visited false for points coming back to
        {
            visited[{temp.x, temp.y}] = false;
            stackk.pop();
        }
    }

    // If the stack is empty and
    // no path is found return false.
    cout << "\nNo path found.\n"
         << endl;
}

int index = 0;
void PrintStack(stack<node> s)
{
    // If stack is empty
    if (s.empty())
        return;

    // Extract top of the stack
    node x = s.top();

    // Pop the top element
    s.pop();

    // Proceed to put the rest of the stack to stack
    PrintStack(s);

    if(index==0)
    {
        cout << "\nPath is: " << endl;
    }
    if (index == 4)
    {
        cout << endl;
        index = 0;
    }
    index++;


    // Print the current Bottom
    // of the stack i.e., x
    cout << "(" << x.x << ',' << x.y << "),";
    
    

    

    // Push the element back
    s.push(x);
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

    stack<node> bla = (isReachable(Maze, row, col));
    PrintStack(bla);

    return 0;
}
