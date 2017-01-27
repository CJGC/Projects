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
        self.emptyCells = [] # will save coordinates empty cells '0'
        self.key = ''   # user will give it for moves
        self.number = 0 # number will appear randomly
        self.addedNumbers = 0 # adding random number's during game
        self.topNumber = 2048 # maximum number game
        self.validMove = False # will check if exist a valid move
        self.firstMoves() # will begin putting two random numbers

    def printBoard(self):
        for item in self.board: print item,'\n'

    def firstMoves(self):
        self.saveEmptyCells()
        self.makeNumber(),self.putNumber()
        self.makeNumber(),self.putNumber()

    def haveYouWin(self):
        if self.addedNumbers >= self.topNumber:
            for item in self.board:
                if self.topNumber in item: return True

    def saveEmptyCells(self):
        rowCount = len(self.board)
        colCount = len(self.board[0])
        for _list,x in zip(self.board,range(0,rowCount)):
            for item,y in zip(_list,range(0,colCount)):
                if not item: self.emptyCells.append([x,y])

    def deleteEmptyCells(self):
        self.emptyCells = []

    def makeNumber(self):
        self.number = rand.randrange(2,5,2)
        self.addedNumbers += self.number

    def putNumber(self):
        sizeEmptyCells = len(self.emptyCells)
        if sizeEmptyCells:
            index = rand.randint(1,sizeEmptyCells)-1
            coordinates = self.emptyCells[index]
            x = coordinates[0]
            y = coordinates[1]
            self.board[x][y] = self.number
            del self.emptyCells[index]

    def mixNumbers(self,_list):
        indexes = Fifo() # Fifo queue, will save all indexes whose content be '0'
        sizeList = len(_list)
        for item,index in zip(_list,range(0,sizeList)):
            if item and indexes.size():
                lastIndex = indexes.pop()
                if item == _list[lastIndex]:
                    _list[lastIndex] += _list[index]
                    _list[index] = 0
                    self.validMove = True
                else: indexes.push(index)
            elif item: indexes.push(index)

    def move(self,_list):
        indexes = Fifo()
        sizeList = len(_list)
        for item,index in zip(_list,range(0,sizeList)):
            if item and indexes.size():
                _list[indexes.pop()] = item
                _list[index] = 0
                indexes.push(index)
                self.validMove = True
            elif not item: indexes.push(index)

    def exeKeyOrder(self):
        if self.key == 'a': # move leftward
            for item in self.board:
                self.mixNumbers(item)
                self.move(item)
        elif self.key == 's': # move downward
            self.board = compl.transSquaredMatrix(self.board)
            for item in self.board:
                item.reverse()
                self.mixNumbers(item)
                self.move(item)
                item.reverse()
            self.board = compl.transSquaredMatrix(self.board)
        elif self.key == 'd': # move rightward
            for item in self.board:
                item.reverse()
                self.mixNumbers(item)
                self.move(item)
                item.reverse()
        elif self.key == 'w': # move upward
            self.board = compl.transSquaredMatrix(self.board)
            for item in self.board:
                self.mixNumbers(item)
                self.move(item)
            self.board = compl.transSquaredMatrix(self.board)
        if self.validMove:
            self.deleteEmptyCells()
            self.saveEmptyCells()
            self.makeNumber()
            self.putNumber()
            self.validMove = False

    def getKeyUser(self):
        self.key = raw_input('Give me a key: ')
        self.key = self.key.lower()

if __name__ == "__main__":
    game = _2048()
    while not game.haveYouWin():
        game.printBoard()
        game.getKeyUser()
        game.exeKeyOrder()
