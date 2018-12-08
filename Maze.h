#ifndef ALGORITHMDEMO_MAZE_H
#define ALGORITHMDEMO_MAZE_H
#include <ctime>

class Maze
{
private:
    int **map;
    int width, height;
    int startX, startY, endX, endY;
    bool solved;
    bool toShowSolution;
    enum NodeType
    {
        Wall = 0,
        Road,
        Start,
        End,
        Path
    };

    enum Direction
    {
        Up = 0,
        Down,
        Left,
        Right
    };

public:
    Maze(int x, int y, int toShowSolution) : width(x / 2 * 2 + 1), height(y / 2 * 2 + 1), toShowSolution(toShowSolution)
    {
        cout << "Generating [" << width << ", " << height << "] maze..." << endl;
        assert(width > 2 && height > 2);
        map = new int*[width]();
        for(int i = 0; i < width; i++)
            map[i] = new int[height]();
        Set(0, 1, Start);
        Set(width - 1, height - 2, End);
        startX = 1;
        startY = 1;
        endX = width - 2;
        endY = height - 2;
        srand(time(NULL) + clock());
        GenerateMap();
        cout << "Done!" << endl;
        if(toShowSolution)
        {
            solved = false;
            DFS(startX, startY);
            Set(endX, endY, Path);
        }
    }
    ~Maze()
    {
        for(int i = 0; i < width; i++)
        {
            delete [] map[i];
        }
        delete [] map;
    }
    void Show()
    {
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                switch(map[x][y])
                {
                    case Start:
                        cout << "¡ú";
                        break;
                    case End:
                        cout << ">>";
                        break;
                    case Road:
                        cout << "  ";
                        break;
                    case Wall:
                        cout << "¡ö";
                        break;
                    case Path:
                        cout << (toShowSolution ? "¡¤" : "  ");
                        break;
                }
            }
            cout << endl;
        }
        cout << endl;
    }

private:
    void Set(int x, int y, NodeType t)
    {
        assert(x >= 0 && x < width);
        assert(y >= 0 && y < height);
        map[x][y] = t;
    }

    void Connect(int x, int y, Direction d)
    {
        assert(x >= 0 && x < width);
        assert(y >= 0 && y < height);
        int nextX = x, nextY = y, midX = x, midY = y;
        switch(d)
        {
            case Up:
                nextY -= 2;
                midY -= 1;
                break;
            case Down:
                nextY += 2;
                midY += 1;
                break;
            case Left:
                nextX -= 2;
                midX -= 1;
                break;
            case Right:
                nextX += 2;
                midX += 1;
                break;
            default:
                cout << "Unknown direction!" << endl;
                return;
        }
        if(OutOfRange(nextX, nextY)) return;
        if(Road == map[nextX][nextY]) return;
        Set(nextX, nextY, Road);
        Set(midX, midY, Road);
        //cout << "Connect to [" << nextX << ", " << nextY << "]" << endl; 
        return DFT(nextX, nextY);
    }

    bool OutOfRange(int x, int y)
    {
        return x < 1 || y < 1 || x > width - 2 || y > height - 2;
    }


    void GenerateMap()
    {
        int x = rand() % (width - 1)/ 2 * 2 + 1;
        int y = rand() % (height - 1) / 2 * 2 + 1;
        Set(x, y, Road);
        DFT(x, y);
    }

    void DFT(int x, int y)
    {
        assert(x >= 0 && x < width);
        assert(y >= 0 && y < height);
        bool visited[4] = {false};
        int n = rand() % 24; //24ÖÖÑ¡Ôñ
        for(int i = 4; i > 0; i--)
        {
            int d = 0;
            for(int j = 0; j <= n % i; d++)
            {
                if(!visited[d % 4])
                    j++;
            }
            d = (d - 1) % 4;
            visited[d] = true;
            //printf("Connect to [%d, %d], d(%d) n(%d).\n", x, y, d, n);
            Connect(x, y, (Direction)d);
        }
    }

    void DFS(int x, int y)
    {
        assert(x >= 0 && x < width);
        assert(y >= 0 && y < height);
        if(x == endX && y == endY || true == solved) 
        {
            solved = true;
            return;
        }
        Set(x, y, Path);
        for(int d = 0; d < 4; d++)
        {
            Search(x, y, (Direction)d);
        }
        if(!solved)
        {
            Set(x, y, Road);
        }

    }

    void Search(int x, int y, Direction d)
    {
        assert(x >= 0 && x < width);
        assert(y >= 0 && y < height);
        int nextX = x, nextY = y;
        switch(d)
        {
            case Up:
                nextY -= 1;
                break;
            case Down:
                nextY += 1;
                break;
            case Left:
                nextX -= 1;
                break;
            case Right:
                nextX += 1;
                break;
            default:
                cout << "Unknown direction!" << endl;
                return;
        }
        if(OutOfRange(nextX, nextY)) return;
        if(Path == map[nextX][nextY] || Wall == map[nextX][nextY]) return;
        DFS(nextX, nextY);
    }
};

#endif
