class Complements:

    def transSquaredMatrix(self,matrix):
        rowCount = len(matrix)
        for item in matrix:
            if not len(item) == rowCount: raise AssertionError("Must be squared matrix")
        return [[row[i] for row in matrix] for i in range(0,rowCount)]

class Fifo:
    def __init__(self):
        self.fifo = []

    def push(self,item):
        self.fifo.append(item)

    def pop(self):
        if len(self.fifo):
            return self.fifo.pop(0)

    def size(self):
        return len(self.fifo)
