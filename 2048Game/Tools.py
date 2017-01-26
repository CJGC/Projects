class Complements:

    def matrixTransposed(self,matrix):
        rowsAmount = len(matrix)
        columnsAmount = len(matrix[0])
        assert rowsAmount == columnsAmount, "Error, must be a squared matrix"
        times = []
        [times.append(i) for i in range(0,rowsAmount)]
        return [[row[i] for row in matrix] for i in times]

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
