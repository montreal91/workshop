
import sys

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from cube_edge import RcEdge

BLACK   = ( 0.0, 0.0, 0.0 )
RED     = ( 1.0, 0.0, 0.0 )
GREEN   = ( 0.0, 1.0, 0.0 )
BLUE    = ( 0.0, 0.0, 1.0 )
YELLOW  = ( 1.0, 1.0, 0.0 )
ORANGE  = ( 1.0, 0.5, 0.0 )

class RcPoint( object ):
    """docstring for RcPoint"""
    def __init__( self, x, y ):
        super( RcPoint, self ).__init__()
        self.coord_x = x
        self.coord_y = y


class RcCube( object ):
    """docstring for RcCube1"""
    def __init__( self ):
        super( RcCube, self ).__init__()
        self._face      = RcEdge( [ BLACK, BLACK, BLACK, BLACK ] )
        self._left      = RcEdge( [ GREEN, YELLOW, GREEN, YELLOW ] )
        self._right     = RcEdge( [ BLUE, BLUE, BLUE, BLUE ] )
        self._top       = RcEdge( [ RED, RED, RED, RED ] )
        self._bottom    = RcEdge( [ ORANGE, ORANGE, ORANGE, ORANGE ] )
        self._back      = RcEdge( [ GREEN, YELLOW, GREEN, YELLOW ] )

    def _RenderQuadrangle( self, vertex_a, vertex_b, vertex_c, vertex_d ):
        glBegin( GL_POLYGON )

        glVertex2d( vertex_a.coord_x, vertex_a.coord_y )
        glVertex2d( vertex_b.coord_x, vertex_b.coord_y )
        glVertex2d( vertex_d.coord_x, vertex_d.coord_y )

        glVertex2d( vertex_a.coord_x, vertex_a.coord_y )
        glVertex2d( vertex_c.coord_x, vertex_c.coord_y )
        glVertex2d( vertex_d.coord_x, vertex_d.coord_y )

        glEnd()

    def Render( self ):
        va = RcPoint( 300, 400 )
        vb = RcPoint( 350, 400 )
        vc = RcPoint( 300, 450 )
        vd = RcPoint( 350, 450 )

        color = self._face.all[ 0 ]
        glColor3d( color[0], color[1], color[2] )
        self._RenderQuadrangle( va, vb, vc, vd )
