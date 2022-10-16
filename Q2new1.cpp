// CPP program to solve Rat in a maze
// problem with backtracking using stack

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

// maze of n*m matrix
// int n = N, m = M;

// Coordinates of endpoints

int endx, endy;
// bool visited[N][M];

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
    // setting map to visited
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            visited[make_pair(i, j)] = false;
        }
    }

    stack<node> stackk;

    // Initially starting at (0, 0).
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

        // Checking the Up direction.
        if (d == 0)
        {
            if (i - 1 >= 0 && maze[i - 1][j] && !visited[{i - 1, j}])
            {
                node temporary(i - 1, j);
                visited[{i - 1, j}] = true;
                stackk.push(temporary);
            }
        }

        // Checking the left direction
        else if (d == 1)
        {
            if (j - 1 >= 0 && maze[i][j - 1] && !visited[{i, j - 1}])
            {
                node temporary(i, j - 1);
                visited[{i, j - 1}] = true;
                stackk.push(temporary);
            }
        }

        // Checking the down direction
        else if (d == 2)
        {
            if (i + 1 < row && maze[i + 1][j] && !visited[{i + 1, j}])
            {
                node temporary(i + 1, j);
                visited[{i + 1, j}] = true;
                stackk.push(temporary);
            }
        }
        // Checking the right direction
        else if (d == 3)
        {
            if (j + 1 < col && maze[i][j + 1] && !visited[{i, j + 1}])
            {
                node temporary(i, j + 1);
                visited[{i, j + 1}] = true;
                stackk.push(temporary);
            }
        }

        // If none of the direction can take
        // the rat to the Food, retract back
        // to the path where the rat came from.
        else
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

    // Print the current top
    // of the stack i.e., x
    cout << "(" << x.x << ',' << x.y << ") ,";
    if (index == 4)
    {
        cout << endl;
        index = 0;
    }
    index++;

    // Proceed to print
    // remaining stack
    PrintStack(s);

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
