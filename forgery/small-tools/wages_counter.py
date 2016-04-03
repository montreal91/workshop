
import sys

roster = [
    ( "Julius Benning", "M", 53700 ),
    ( "Anastas Lyubenov", "D", 52600 ),
    ( "Jamey Gossard", "F", 51100 ),
    ( "Adri Maachi", "M", 48500 ),
    ( "Oystein Redkal", "M", 46900 ),
    ( "Devin Korsgaard", "D", 46000 ),
    ( "Marty Emmeche", "M", 46000 ),
    ( "Gilbert Wedgwood", "G", 45000 ),
    ( "Dennis Ayre", "D", 44200 ),
    ( "Adil Mazure", "M", 43000 ),
    ( "Claudiu Bolohan", "F", 43000 ),
    ( "Daren Kaldor", "F", 39000 ),
    ( "Andy Christou", "F", 38700 ),
    ( "Jorn Dreschler", "F", 37600 ),
    ( "Murray McQueen", "M", 36900 ),
    ( "Norman Plympton", "D", 35200 ),
    ( "Erich Lux", "F", 34400 ),
    ( "Mohamed De Meyer", "D", 33900 ),
    ( "Jerry Omeara", "G", 27000 ),
]

former_players = [
    ( "Rengin Mahir", "M", 28800 ),
    ( "Nikolaj Schwartz", "M", 43000 ),
    ( "Miljan Maravic", "D", 30200 ),
    ( "Dougie Logie", "F", 41000 ),
    ( "Charles Robbins", "G", 27500 ),
    ( "Elizbar Radimov", "M", 30000 ),
    ( "Hans Kaspersen", "F", 39000 ),
    ( "Philip Ortega", "F", 24500 ),
    ( "Henk Troost", "M", 34300 ),
    ( "Bert Buekens", "D", 64500 ),
    ( "Brad Landa", "D", 33900 ),
    ( "Wayne Casullo", "G", 37400 ),
    ( "Nikolaj Schwartz", "D", 22700 ),
    ( "Jorens Labeckis", "F", 23200 ),
    ( "Aarni Tapaninen", "M", 34000 ),
    ( "Glen Schultz", "M", 18000 ),
    ( "Yakov Dorogin", "M", 31200 ),
    ( "Keith Gingrich", "D", 19600 ),
    ( "Brian Zeman", "F", 17300 ),
    ( "Radjin van der Ark", "F", 42900 ),
    ( "Bryant Gemes", "M", 43000 ),
    ( "Tibor Csizar", "F", 26600 ),
]

def CountWages( team ):
    res = 0
    for player in team:
        res += player[-1]
    return res


def CalculateWages( capacity, ticket_price, home_games, sponsor_funds ):
    sponsor_income  = sponsor_funds * 50
    tickets_income  = capacity * ticket_price * home_games
    total_income    = sponsor_income + tickets_income
    wages           = total_income / ( home_games * 2 )
    print( "Season income       : {0:.2f}".format( total_income ) )
    print( "Match income        : {0:.2f}".format( capacity * ticket_price ) )
    print( "Team wages per match: {0:.2f}\n".format( wages * 0.8 ) )
    print( "Wages cap           : {0:.2f}".format( wages * 0.8 - CountWages( roster ) ) )
    print( "'Free' money        : {0:.2f}\n".format( wages * 0.2 ) )


if __name__ == '__main__':
    if sys.argv[1] == "--Sum":
        w = CountWages( roster )
        l = len( roster )
        print( "Total wages  : {0:d}".format( w ) )
        print( "Total players: {0:d}".format( l ) )
        print( "Average wage : {0:.2f}\n".format( w / l ) )
    elif sys.argv[1] == "--Calc" and len( sys.argv ) == 6:
        cap = int( sys.argv[2] )
        tp = float( sys.argv[3] )
        hg = int( sys.argv[4] )
        sf = int( sys.argv[5] )
        CalculateWages( cap, tp, hg, sf )
