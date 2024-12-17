// bees.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Room::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the room
const int MAXCOLS = 25;             // max number of columns in the room
const int MAXBEES = 150;            // max number of bees allowed
const int INITIAL_BEE_HEALTH = 2;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Room;

class Bee
{
public:
    // Constructor
    Bee(Room* rp, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;

    // Mutators
    void move();
    bool getSwatted(int dir);

private:
    Room* m_room;
    int   m_row;
    int   m_col;
    int   m_health;
};

class Player
{
public:
    // Constructor
    Player(Room* rp, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

    // Mutators
    void   stand();
    void   moveOrSwat(int dir);
    void   setDead();

private:
    Room* m_room;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Room
{
public:
    // Constructor/destructor
    Room(int nRows, int nCols);
    ~Room();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     beeCount() const;
    int     numBeesAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

    // Mutators
    bool   addBee(int r, int c);
    bool   addPlayer(int r, int c);
    bool   swatBeeAt(int r, int c, int dir);
    bool   moveBees();

private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Bee* m_bees[MAXBEES];
    int     m_nBees;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nBees);
    ~Game();

    // Mutators
    void play();

private:
    Room* m_room;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Bee implementation
///////////////////////////////////////////////////////////////////////////

Bee::Bee(Room* rp, int r, int c)
{
    if (rp == nullptr)
    {
        cout << "***** A bee must be created in some Room!" << endl;
        exit(1);
    }
    if (r < 1 || r > rp->rows() || c < 1 || c > rp->cols())
    {
        cout << "***** Bee created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_room = rp;
    m_row = r;
    m_col = c;
    m_health = INITIAL_BEE_HEALTH;
}

int Bee::row() const
{
    return m_row;
}

int Bee::col() const
{
    return m_col;
}

void Bee::move()
{
    // attempt to move in random direction - if bee can't move don't move
    int dir = randInt(0, NUMDIRS - 1);
    int newRow = m_row;
    int newCol = m_col;

    if (m_room->determineNewPosition(newRow, newCol, dir))
    {
        m_row = newRow;
        m_col = newCol;
    }
}

bool Bee::getSwatted(int dir) /////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    m_health--;

    if (m_health == 0)
        return true; 
    int beenewRow = m_row;
    int beenewCol = m_col;

    switch (dir)
    {
    case UP:    beenewRow--; break;
    case DOWN:  beenewRow++; break;
    case LEFT:  beenewCol--; break;
    case RIGHT: beenewCol++; break;
    }

    
    if (beenewRow < 1 || beenewRow > m_room->rows() || beenewCol < 1 || beenewCol > m_room->cols())
        return true; 

    
    m_row = beenewRow;
    m_col = beenewCol;
    return false;
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Room* rp, int r, int c)
{
    if (rp == nullptr)
    {
        cout << "***** The player must be created in some Room!" << endl;
        exit(1);
    }
    if (r < 1 || r > rp->rows() || c < 1 || c > rp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_room = rp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::moveOrSwat(int dir)
{
    m_age++;

    int playernewR = m_row;
    int playernewC = m_col;

    if (m_room->determineNewPosition(playernewR, playernewC, dir))
    {
        // check if there are bees in swatted direction
        if (m_room->numBeesAt(playernewR, playernewC) > 0)
        {
            m_room->swatBeeAt(playernewR, playernewC, dir); // swat bee
            return; // player does not move
        }

        // move player if no bee is swatted
        m_row = playernewR;
        m_col = playernewC;
    }
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Room implementations
///////////////////////////////////////////////////////////////////////////

Room::Room(int nRows, int nCols) : m_rows(nRows), m_cols(nCols), m_player(nullptr), m_nBees(0)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Room created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
    for (int i = 0; i < MAXBEES; i++)
        m_bees[i] = nullptr;
}

Room::~Room()
{
    delete m_player;
    for (int i = 0; i < m_nBees; i++)
    {
        if (m_bees[i] != nullptr) 
        {
            delete m_bees[i];
            m_bees[i] = nullptr;
        }
    }
}

int Room::rows() const
{
    return m_rows;
}

int Room::cols() const
{
    return m_cols;
}

Player* Room::player() const
{
    return m_player;
}

int Room::beeCount() const
{
    return m_nBees;
}

int Room::numBeesAt(int r, int c) const
{
    int count = 0;
    for (int i = 0; i < m_nBees; i++)
        if (m_bees[i] != nullptr && m_bees[i]->row() == r && m_bees[i]->col() == c)
            count++;
    return count;
}

bool Room::determineNewPosition(int& r, int& c, int dir) const
{

    switch (dir)
    {
    case UP:    
        if (r > 1) { 
            r--; return true; 
        } 
        break;
    case DOWN:  
        if (r < m_rows) { 
            r++; 
            return true; 
        } 
        break;
    case LEFT:  
        if (c > 1) { 
            c--; 
            return true; 
        } 
        break;
    case RIGHT: 
        if (c < m_cols) { 
            c++; 
            return true; 
        } 
        break;
    }
    return false;
}

void Room::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // fill grid with dots in place of manual initialization
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';


    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
        {
            int numBees = numBeesAt(r, c);
            if (numBees == 1)
                grid[r - 1][c - 1] = 'B';
            else if (numBees > 1)
                grid[r - 1][c - 1] = '0' + numBees;
        }
    }

    // indicate player pos
    if (m_player != nullptr)
    {
        char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

    // draw grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // write message, bee, player info
    cout << "There are " << beeCount() << " bees remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Room::addBee(int r, int c)
{
    if (m_nBees >= MAXBEES)
        return false;

    m_bees[m_nBees++] = new Bee(this, r, c);
    return true;
}

bool Room::addPlayer(int r, int c)
{
    // don't add player if one already exists
    if (m_player != nullptr)
        return false;

    // dynamically allocate new Player and add it to the room
    m_player = new Player(this, r, c);
    return true;
}

bool Room::swatBeeAt(int r, int c, int dir)
{
    for (int i = 0; i < m_nBees; i++)
    {
        if (m_bees[i] != nullptr && m_bees[i]->row() == r && m_bees[i]->col() == c)
        {

            if (m_bees[i]->getSwatted(dir))
            {
  
                delete m_bees[i];
                m_bees[i] = m_bees[m_nBees - 1]; 
                m_bees[m_nBees - 1] = nullptr;
                m_nBees--;
                return true; 
            }
            return false;
        }
    }
    return false;
}

bool Room::moveBees()
{
    for (int i = 0; i < m_nBees; i++)
    {
        m_bees[i]->move();
        if (m_bees[i]->row() == m_player->row() && m_bees[i]->col() == m_player->col())
            m_player->setDead();
    }
    return !m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nBees)
{
    if (nBees < 0)
    {
        cout << "***** Cannot create Game with negative number of bees!" << endl;
        exit(1);
    }
    if (nBees > MAXBEES)
    {
        cout << "***** Trying to create Game with " << nBees
            << " bees; only " << MAXBEES << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1 && cols == 1 && nBees > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the bees!" << endl;
        exit(1);
    }

    // Create room
    m_room = new Room(rows, cols);

    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_room->addPlayer(rPlayer, cPlayer);

    // Populate with bees
    while (nBees > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a bee where the player is
        if (r == rPlayer && c == cPlayer)
            continue;
        m_room->addBee(r, c);
        nBees--;
    }
}

Game::~Game()
{
    delete m_room;
}

void Game::play()
{
    m_room->display();
    Player* player = m_room->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_room->beeCount() > 0)
    {
        cout << endl;
        cout << "Move (u/d/l/r/q or nothing): ";
        string action;
        getline(cin, action);
        if (action.size() == 0)  // player stands
            player->stand();
        else
        {
            switch (action[0])
            {
            default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
            case 'q':
                return;
            case 'u':
            case 'd':
            case 'l':
            case 'r':
                player->moveOrSwat(decodeDirection(action[0]));
                break;
            }
        }
        m_room->moveBees();
        m_room->display();
    }
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
    case 'u':  return UP;
    case 'd':  return DOWN;
    case 'l':  return LEFT;
    case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in
}

// Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rnd;
    static default_random_engine generator(rnd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////
//void doBasicTests();
int main()
{
    //doBasicTests(); // Remove this line after completing test.
    //return 0;       // Remove this line after completing test.
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr || strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
