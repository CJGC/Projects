import random as rand
from Tools import *
compl = Complements()

class _2048:
    def __init__(self):
        self.board = [  # Board game
            [0,0,0,0],
            [0,0,0,0],
            [0,0,0,0],
            [0,0,0,0]
        ]
        self.emptyCells = [] # will save empty cells coordinates ('0' -> [x,y])
        self.key = ''   # will store user order for moves
        self.num = 0 # number that will appear randomly
        self.numsSum = 0 # will store appearing random number's add
        self.topNum = 2048 # top number of game
        self.validMove = False # will check if exist a valid move (putting or mixing numbers)
        self.firstMoves() # will begin putting two random numbers

    def firstMoves(self): # will make the first move game
        self.savEmptCells()
        self.makeNum(),self.putNum()
        self.makeNum(),self.putNum()

    def printBoard(self): # will print board game
        for _list in self.board: print _list,'\n'

    def haveYouWin(self): # will check if user won game
        if self.numsSum >= self.topNum: # will begin to check only when necessary
            for _list in self.board:
                if self.topNum in _list: return True

    def savEmptCells(self): # will save empty cells coordinates from current board game
        rowCount = len(self.board)
        colCount = len(self.board[0])
        for _list,x in zip(self.board,range(0,rowCount)):
            for item,y in zip(_list,range(0,colCount)):
                if not item: self.emptyCells.append([x,y])

    def delEmptCells(self): # will delete empty cells coordinates from past board game
        self.emptyCells = []

    def makeNum(self): # will make 2 or 4 number randomly
        self.num = rand.randrange(2,5,2)
        self.numsSum += self.num

    def putNum(self): # will put 2 or 4 number into board random position
        sizeEmptyCells = len(self.emptyCells)
        if sizeEmptyCells:
            index = rand.randint(1,sizeEmptyCells)-1
            coordinates = self.emptyCells[index]
            x = coordinates[0]
            y = coordinates[1]
            self.board[x][y] = self.num
            del self.emptyCells[index]

    def mixNumbs(self,_list): # will mix two equal consecutives numbers on given list from board game
        indexes = Fifo() # fifo queue, will save indexes of list whose content be '0'
        lenList = len(_list)
        for item,index in zip(_list,range(0,lenList)):
            if item and indexes.size():
                lastIndex = indexes.pop()
                if item == _list[lastIndex]:
                    _list[lastIndex] += _list[index]
                    _list[index] = 0
                    self.validMove = True
                else: indexes.push(index)
            elif item: indexes.push(index)

    def move(self,_list): # will move all numbers to left of given list from board game
        indexes = Fifo() # fifo queue, will save indexes of list whose content be '0'
        lenList = len(_list)
        for item,index in zip(_list,range(0,lenList)):
            if item and indexes.size():
                _list[indexes.pop()] = item
                _list[index] = 0
                indexes.push(index)
                self.validMove = True
            elif not item: indexes.push(index)

    def exeKeyOrder(self): # will perform the move into board game, ordered by user
        if self.key == 'a': # move leftward
            for _list in self.board:
                self.mixNumbs(_list)
                self.move(_list)
        elif self.key == 's': # move downward
            self.board = compl.transSquaredMatrix(self.board)
            for _list in self.board:
                _list.reverse()
                self.mixNumbs(_list)
                self.move(_list)
                _list.reverse()
            self.board = compl.transSquaredMatrix(self.board)
        elif self.key == 'd': # move rightward
            for _list in self.board:
                _list.reverse()
                self.mixNumbs(_list)
                self.move(_list)
                _list.reverse()
        elif self.key == 'w': # move upward
            self.board = compl.transSquaredMatrix(self.board)
            for _list in self.board:
                self.mixNumbs(_list)
                self.move(_list)
            self.board = compl.transSquaredMatrix(self.board)
        if self.validMove: # will upgrade some game attributes, only when be necessary
            self.delEmptCells()
            self.savEmptCells()
            self.makeNum()
            self.putNum()
            self.validMove = False

    def getKeyUser(self): # will get user move order
        self.key = raw_input('Give me a key: ')
        self.key = self.key.lower()

if __name__ == "__main__":
    game = _2048()
    while not game.haveYouWin():
        game.printBoard()
        game.getKeyUser()
        game.exeKeyOrder()
