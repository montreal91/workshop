
import json
import sys
import numpy as np

# We assume that there IS identity submatrix in A
class LpDualSimplex(object):
    def __init__(self, data_file):
        super(LpDualSimplex, self).__init__()
        with open(data_file) as datafile:
            data = json.load(datafile)
        self._b_column = np.array(data["B"])
        # print(self._b_column.shape)
        self._b_column.reshape(len(data["B"]), 1)
        # print(self._b_column.shape)
        self._c_line = np.array(data["C"])
        self._c_line.reshape(1, len(data["C"]))
        self._a_matrix = np.array(data["A"])

    def CalculateMinimum(self):
        is_solution_possible = True
        is_solution_found = False
        c_in_basis = None
        while is_solution_possible and not is_solution_found:
            if self._GetLeadingRow() is None:
                is_solution_found = True
                continue
            self._basis = self._GetBasis()
            c_in_basis = self._GetBasisCoefficients(self._basis)
            deltas = self._GetDeltas(c_in_basis)
            leading_row = self._GetLeadingRow()
            leading_column = self._GetLeadingColumn(deltas)
            if leading_column is None:
                is_solution_possible = False
                continue
            self._SwitchToAnotherBasis(row=leading_row, column=leading_column)

        if is_solution_possible:
            return self._CalculateFunctionValue(c_in_basis)
        else:
            return None

    def _CalculateFunctionValue(self, c_in_basis):
        return self._b_column.dot(c_in_basis)

    def _CheckIfAllElementsInLeadingRowInAPositive(self, leading_row):
        for a in self._a_matrix[leading_row]:
            if a < 0:
                return False
        return True

    def _GetBasis(self):
        height = len(self._a_matrix[:,0])
        width = len(self._a_matrix[0])

        basis = []
        for k in range(height):
            identity_column = np.array([int(i == k) for i in range(height)])
            for j in range(width):
                if LpDualSimplex._CompareArrays(identity_column, self._a_matrix[:,j]):
                    basis.append(j)
        if basis:
            return basis
        else:
            return None

    def _GetBasisCoefficients(self, basis):
        return np.array([self._c_line[i] for i in basis])

    def _GetDeltas(self, c_in_basis):
        return [c_in_basis.dot(self._a_matrix[:,j]) - self._c_line[j] for j in range(len(self._a_matrix[0]))]

    def _GetLeadingColumn(self, deltas):
        lr = self._GetLeadingRow()
        min_val, min_ind = None, None
        for j in range(len(self._a_matrix[0])):
            if self._a_matrix[lr, j] >= 0:
                continue
            val = -deltas[j] / self._a_matrix[lr, j]
            if min_val is None:
                min_val = val
                min_ind = j
            elif val < min_val:
                min_val = val
                min_ind = j
        return min_ind


    def _GetLeadingRow(self):
        argmin = self._b_column.argmin()
        if self._b_column[argmin] < 0:
            return argmin
        else:
            return None

    def _SwitchToAnotherBasis(self, row=0, column=0):
        val = self._a_matrix[row, column]
        self._a_matrix[row] *= 1 / val
        self._b_column[row] *= 1 / val

        for i in range(len(self._a_matrix[:,0])):
            if i != row:
                # print(self._b_column[i], self._b_column[i] - self._b_column[row] * self._a_matrix[i, column])
                self._b_column[i] -= self._b_column[row] * self._a_matrix[i, column]
                self._a_matrix[i] -= self._a_matrix[row] * self._a_matrix[i, column]
    
    @staticmethod
    def _CompareArrays(a1, a2):
        res = a1 == a2
        return res.all()


if __name__ == '__main__':
    simplex = LpDualSimplex(sys.argv[1])
    print(simplex.CalculateMinimum())
