
def CalculateEloRating( p1_rating, p2_rating, p1_points, p2_points ):
    p1_expected_score = 21 / ( 1 + 10 ** ( ( p1_rating - p2_rating ) / 400 ) )
    p2_expected_score = 21 / ( 1 + 10 ** ( ( p1_rating - p2_rating ) / 400 ) )
    # print( "P1 expected score: {0:.2f}".format( p1_expected_score ) )
    # print( "P2 expected score: {0:.2f}".format( p2_expected_score ) )
    p1_new_rating = p1_rating + ( p1_points - p1_expected_score )
    p2_new_rating = p2_rating + ( p2_points - p2_expected_score )
    return p1_new_rating, p2_new_rating

if __name__ == '__main__':
    r1, r2 = CalculateEloRating( 0, 0, 21, 19 )
    print( "P1 new rating: {0:.2f}\nP2 new rating: {1:.2f}".format( r1, r2 ) )
    r1, r2 = CalculateEloRating( r1, r2, 21, 23 )
    print( "P1 new rating: {0:.2f}\nP2 new rating: {1:.2f}\n".format( r1, r2 ) )

    r1, r2 = CalculateEloRating( 0, 0, 19, 21 )
    print( "P1 new rating: {0:.2f}\nP2 new rating: {1:.2f}".format( r1, r2 ) )
    r1, r2 = CalculateEloRating( r1, r2, 23, 21 )
    print( "P1 new rating: {0:.2f}\nP2 new rating: {1:.2f}".format( r1, r2 ) )


