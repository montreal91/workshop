
import socium
import human
import random
import statprof

random.seed(1)

X, Y = human.X_CHROMOSOME, human.Y_CHROMOSOME
M, N = human.MAG_CHROMOSOME, human.NMAG_CHROMOSOME

def TestSocium( iterations, starting_population, years_to_live, year_of_mutation ):
    total, h_mages, mages = 0, 0, 0
    for iteration in xrange( iterations ):
        city = socium.ASocium()
    
        for i in xrange( starting_population ):
            if i % 2 == 0:
                person = human.AHuman( ( X, Y ), ( N, N ) )
            else:
                person = human.AHuman( ( X, X ), ( N, N ) )
            city.AddHuman( person )
        for year in xrange( years_to_live ):
            city.LiveOneYear()
            if year == year_of_mutation:
                woman = human.AHuman()
                city.AddHuman( woman )

        total += city.GetTotalPopulation()
        h_mages += city.GetCustomMageStatusPopulation( human.HALF_MAGE )
        mages += city.GetCustomMageStatusPopulation( human.MAGE )

    total = float( total ) / iterations
    h_mages = float( h_mages ) / iterations
    mages = float( mages ) / iterations
    print
    print "Average total population         : {0:.3f}".format( total )
    print
    print "Average half-mage population     : {0:.3f} ({1:2.2f}%)".format( h_mages, h_mages / total * 100 )
    print "Average mage population          : {0:.3f} ({1:2.2f}%)".format( mages, mages / total * 100 )

statprof.start()

try:
    TestSocium( 10, 20, 500, 150 )
finally:
    statprof.stop()
    statprof.display()
