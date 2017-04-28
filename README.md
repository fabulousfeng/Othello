# Othello Game Interface 
<img width="1278" alt="screen shot 2017-04-21 at 6 48 35 pm" src="https://cloud.githubusercontent.com/assets/15232969/25298512/75ee7396-26c3-11e7-803f-d836844971ee.png">


# Introduction

QT framework is used to build the interface of this game. 

This game supports one or two players. 

For one player mode, it uses Minimax search algorithm in general. Alpha-Beta pruning search is also used to minimize the branches of the whole game searching tree.

The static heuristic maxtrix(8•8) for calculating utility of the game state is as follows:
weights = {
    {100000, -10000, 5000, 2000,  2000, 5000, -10000, 100000},
    {-10000, -30000, -1500, -1500,  -1500, -1500, -30000, -10000},
    {5000,   -1500,  5000,    1000,   1000, 5000,  -1500,  5000},
    {2000,    -1500, 1000,    50,      50,     1000,  -1500,  2000},
    {2000,    -1500, 1000,    50,      50,     1000,  -1500,   2000},
    {5000,   -1500,  5000,    1000,    1000,  5000,  -1500,   5000},
    {-10000, -30000, -1500, -1500,  -1500, -1500, -30000, -10000},
    {100000, -10000, 5000, 2000,  2000, 5000,  -10000, 100000},
};


# Future work
The weights can be improved by more experiments. For example, a machine learning stratage can be utilized .

# About me
<img width="374" alt="screen shot 2017-04-21 at 3 31 52 am" src="https://cloud.githubusercontent.com/assets/15232969/25267539/2a765a62-2643-11e7-90b1-d26848761b1f.png">
