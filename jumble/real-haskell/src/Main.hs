
{-# LANGUAGE MultiWayIf #-}

module Main where

square :: Int -> Int
square v = v * v

checkLocalHost :: String -> String
checkLocalHost ip =
    -- True or false
    if ip == "127.0.0.1" || ip == "0.0.0.0"
        then "It's a localhost!"
        else "No, it's not a localhost."

analyzeGold :: Int -> String
analyzeGold standard
    | standard == 999 = "Wow! 999 standard!"
    | standard == 858 = "Not bad! 858 standard!"
    | standard == 755 = "Great! 755 standard!"
    | otherwise = "I don't know such a standard..."

calculateTime :: Int -> Int
calculateTime timeInS =
    let threshold = 40
        correction = 120
        delta = 8

    in
    if | timeInS < threshold -> timeInS + correction
       | timeInS >= threshold -> timeInS + delta + correction


calculateTime2 :: Int -> Int
calculateTime2 timeInS =
    if  | timeInS < threshold -> timeInS + correction
        | otherwise -> timeInS + delta + correction
    where
        threshold = 40
        correction = 120
        delta = 8

isEqualTo :: Int -> Int -> Bool
isEqualTo x y = x == y


main :: IO ()
main = do
  putStrLn (checkLocalHost "127.0.0.1")
  putStrLn (checkLocalHost "192.22.0.1")
  putStrLn (analyzeGold 999)
  putStrLn (analyzeGold 755)
  putStrLn (analyzeGold 858)
  putStrLn (analyzeGold 9000)
  print (calculateTime 10)
  print (5 foo 6)
