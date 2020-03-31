![1](https://github.com/hexter-hangzhou/C-/blob/master/monopoly/1.png)
This game is played by two players (you
and computer.in this assignment). The game and its rules are described as the follows.
To play this game, every player must set up an account first with positive balance say the starting
deposit is 10000. This means that you have to set up a data base (a file) which records the players’
information, for example, name, gender and account balance etc. and the program is supposed to be
able to track the balance changes as the game is going.
This game is played on a game board as shown in Fig. 1. This game board consists of 80 squares (20
on each side). Each square has a price tag (this price may be generated randomly within a price range
say from 10 to 500) for the ownership except for the left bottom corner square which is the starting
square (each game starts from here). Each player’s account balance will be increased by 200 for each
time the player passes this square. You and the computer take turns to roll a dice. The outcome of each
rolling (a random number within the range of 1 to 6) decides how many squares you/computer can
advance on the board. You can decide whether or not you should buy the square on which you have
just landed, only if this square is unoccupied (so this means each square except the starting one has an
ownership attribute). On the other hand, you will be fined by 10% of the square price if this square is
occupied by your opponent and the adjacent squares are unoccupied or occupied by you. This fine will
be increased to 15% if one of the adjacent squares is also occupied by your opponent (which means
you opponent has purchased 2 consecutives squares) and further to 20% if both of the adjacent squares
are also occupied by your opponent (which means you opponent has purchased 3 consecutives
squares). The fine is topped at 20% of the square price even if more than 3 consecutive squares have
been occupied by your opponent. The fine for each square can be further increased by 5% if the owner
decides to invest on the square he/she has just bought off. The size of investment is half of the square
price.
The game ends when either one of the players declares bankruptcy (the balance <=0).or you have
chosen to quit the game. You should design and implement at least 3 classes (objects).
Bonus points: your program can resume a game which was played half way through last time and
saved to the database.
Note: you have to make your coding comments as you go
