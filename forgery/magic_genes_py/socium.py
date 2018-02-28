
import human
import random

class ASocium( object ):
    def __init__( self ):
        object.__init__( self )
        self.__women    = []
        self.__men      = []

    def AddHuman( self, new_human ):
        """
        Adds new human to the socium.
        """
        if new_human.GetGender() == human.MALE:
            self.__men.append( new_human )
        else:
            self.__women.append( new_human )

    def GetTotalPopulation( self ):
        return len( self.__women ) + len( self.__men )

    def GetTotalMalePopulation( self ):
        return len( self.__men )

    def GetFemalePopulation( self ):
        return len( self.__women )

    def GetCustomMageStatusPopulation( self, mage_status ):
        res = 0
        for man in self.__men:
            if man.GetMageStatus() == mage_status:
                res += 1
        for woman in self.__women:
            if woman.GetMageStatus() == mage_status:
                res += 1
        return res 

    def __Reproduce( self ):
        for woman in self.__women:
            if woman.IsReadyToGiveBirth():
                father = random.choice( self.__men )
                child = woman.GiveBirth( father )
                self.AddHuman( child )

    def __GrowUp( self ):
        for man in self.__men:
            man.IncreaseAge()
        for woman in self.__women:
            woman.IncreaseAge()

    def __ExcludeDead( self ):
        self.__women    = [ woman for woman in self.__women if woman.IsAlive() ]
        self.__men      = [ man for man in self.__men if man.IsAlive() ]

    def LiveOneYear( self ):
        self.__Reproduce()
        self.__GrowUp()
        self.__ExcludeDead()

    def GetAverageAge( self ):
        age_sum = 0
        for woman in self.__women:
            age_sum += woman.GetActualAge()
        for man in self.__men:
            age_sum += man.GetActualAge()

        if age_sum == 0:
            return age_sum
        else:
            return round( float( age_sum ) / self.GetTotalPopulation(), 2 )
