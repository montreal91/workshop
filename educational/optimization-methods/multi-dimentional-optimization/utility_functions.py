
from vector import Vector

header_string = """
<style>
    table {
        border-collapse: collapse;
        font-family: monospace;
    }
    table, tr, td, th {
        border-style: solid;
        border-width: 1px;
        border-color: black;
    }
</style>

<table>
\t<tr>
\t\t<th>#</th>
\t\t<th>Direction</th>
\t\t<th>Alpha</th>
\t\t<th>Beta</th>
\t\t<th>Current X</th>
\t\t<th>Previous X</th>
\t\t<th>f(X)</th>
\t</tr>
"""
open_table_line     = "\t\t<td>"
close_table_line    = "</td>"
footer_string       = "</table>"
def GetBeta( vec1, vec0, callback ):
    one = callback( vec1 )
    two = callback( vec0 )
    return one.DotProduct( one - two ) / ( two.length ** 2 )

def FunctionPhi( old_x, antigradient, callback ):
    def SomeInnerFun( alpha ):
        new_vec = Vector( old_x.x + alpha * antigradient.x, old_x.y + alpha * antigradient.y )
        return callback( new_vec )
    return SomeInnerFun

def PrintTableHeader():
    print( header_string )

def PrintTableLine(
    iteration=0,
    direction=Vector(),
    alpha=0,
    beta=0,
    curr_vec=Vector(),
    prev_vec=Vector(),
    func_val=0
):
    print( "\t<tr>" )
    print( open_table_line + str( iteration ) + close_table_line )
    print( open_table_line + str( direction ) + close_table_line )
    print( open_table_line + "{0:.4f}".format( alpha ) + close_table_line )
    print( open_table_line + "{0:.4f}".format( beta ) + close_table_line )
    print( open_table_line + str( curr_vec ) + close_table_line )
    print( open_table_line + str( prev_vec ) + close_table_line )
    print( open_table_line + "{0:.4f}".format( func_val ) + close_table_line )
    print( "\t</tr>")

def PrintTableFooter():
    print( "<table>" )
