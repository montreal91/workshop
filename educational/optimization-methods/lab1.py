
class RMinimumSeeker( object ):
    """
    Класс, реализующий функции для поиска минимума на отрезке, 
    и поиска отрезка, содержащего минимум функции."""
    def __init__( self, callback, accuracy=0.01 ):
        """
        Конструктор класса, входными аргументами которого являются 
        функция и точность, с которой вычисляется минимум.
        Значение точности по умолчанию 0.01
        """
        super( RMinimumSeeker, self ).__init__()
        self._callback = callback
        self._accuracy = accuracy

    def _IsTripleLucky( self, start, end, middle ):
        """
        Вспомогательный метод, определяющая, является ли тройка значений счастливой.
        """
        start_value     = self._callback( start )
        end_value       = self._callback( end )
        middle_value    = self._callback( middle )

        return middle_value < start_value and middle_value < end_value

    def GetLuckyTriple( self ):
        """
        Метод, который ищет отрезок, содержащий минимум функции.
        """
        start   = -1
        end     = self._accuracy * 2 - 1
        for i in range( 10000 ):
            middle  = ( start + end ) / 2

            if self._IsTripleLucky( start, end, middle ):
                return start, middle, end
            length  = end - start
            start   = end
            end     = start + length * 2

        start   = 1
        end     = -self._accuracy * 2 + 1
        for i in range( 10000 ):
            middle  = ( start + end ) / 2

            if self._IsTripleLucky( start, end, middle ):
                return start, end, middle

            length  = start - end
            start   = end
            end     = start - length * 2
        return None


    def GetLocalMinimum( self, start, end ):
        """
        Метод, который ищет минимальное значение функции методом дихотомии.
        """
        while True:
            middle      = ( start + end ) / 2 # c -- середина отрезка 
            epsilon     = self._accuracy / 4
            left        = middle - epsilon # yk
            right       = middle + epsilon # zk
            call_left   = self._callback( left ) # f( yk )
            call_right  = self._callback( right ) # f( zk )
            # print( 
            #     "{0:.4f} {1:.4f} {2:.4f} {3:.4f} {4:.4f} {5:.4f}".format(
            #         start, 
            #         end, 
            #         left, 
            #         right, 
            #         call_left, 
            #         call_right
            #     )
            # )

            if call_left >= call_right:
                start = left
            elif call_left < call_right:
                end = right

            if abs( start - end ) < self._accuracy:
                print( "\t{0:.4f}\n".format( ( start + end ) / 2 ) )
                return


    def GetMinimum( self ):
        """
        Метод, который ищет минимум функции на всей числовой прямой в два этапа:
        На первом этапе производится поиск отрезка, содержащего минимум функции;
        На втором этапе производится поиск минимума на отрезке.
        """
        lucky_triple = self.GetLuckyTriple()
        if lucky_triple is not None:
            return self.GetLocalMinimum( lucky_triple[ 0 ], lucky_triple[ -1 ] )
        else:
            return None


def TestFunction1( arg ):
    """
    Тестовая функция, принимающее минимальное значение при arg=2
    """
    return ( arg - 2 ) ** 2


def TestFunction2( arg ):
    """
    Тестовая функция, принимающее минимальное значение при arg=3
    """
    return abs( arg - 3 )


def TestFunction3( arg ):
    """
    Тестовая функция, принимающее минимальное значение при arg=2 и терпящая в этой точке разрыв
    """
    if arg <=2:
        return -arg
    else:
        return arg


def TestFunction4( arg ):
    """
    Тестовая функция, принимающее минимальное значение при arg=3 и терпящая разрыв при arg=1 
    """
    if arg <= 1:
        return 0
    elif 1 < arg < 3:
        return -arg
    else:
        return arg - 6


def TestFunction5( arg ):
    """
    Тестовая функция, имеющая два локальных минимума при arg=1 и arg=3
    """
    if arg <= 1:
        return 1 - arg
    elif 1 < arg < 3:
        return 1 - ( arg - 2 ) ** 2
    else:
        return arg - 3


# Вычсление тестовых значений
if __name__ == '__main__':
    ms1 = RMinimumSeeker( TestFunction1, accuracy=0.02 )
    ms1.GetLocalMinimum( 1, 3 )
    
    ms2 = RMinimumSeeker( TestFunction2, accuracy=0.02 )
    ms2.GetLocalMinimum( 1, 3 )

    ms3 = RMinimumSeeker( TestFunction3, accuracy=0.02 )
    ms3.GetLocalMinimum( 1, 3 )

    ms4 = RMinimumSeeker( TestFunction4, accuracy=0.02 )
    ms4.GetLocalMinimum( 1, 3 )

    ms5 = RMinimumSeeker( TestFunction5, accuracy=0.02 )
    ms5.GetLocalMinimum( 1, 3 )

    ms2.GetMinimum()

