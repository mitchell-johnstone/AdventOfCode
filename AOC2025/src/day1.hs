module Main (main) where

main :: IO ()
main = do
  contents <- readFile "input/day1.txt"
  let withoutEmpty = filter (not . null) $ lines contents
  let signed = map parseLine withoutEmpty
  -- let res = foldl (\(cnt, pos) x -> (cnt + (if ( pos + x ) `mod` 100 == 0 then 1 else 0), ( pos + x ) `mod` 100)) (0,50) signed
  print $ foldl (handleTurn countEndOnZero) (0,50) signed
  print $ foldl (handleTurn countAllZeroPasses) (0,50) signed

parseLine :: String -> Integer
parseLine (d:rest)
  | d == 'L' = - read rest
  | otherwise = read rest
parseLine _ = error "Empty or invalid line"

-- Takes the counter, the current (count, position), and a turn amount, returns the (new count, new position)
handleTurn :: (Integer -> Integer -> Integer) -> (Integer, Integer) -> Integer -> (Integer, Integer)
handleTurn counter (c, s) t = (c + counter s t, mod (s + t) 100)

-- Part 1 : Count how many times we end on 0 {{{
countEndOnZero :: Integer -> Integer -> Integer
countEndOnZero s t = if 0 == mod (s + t) 100 then 1 else 0
-- }}}

-- Part 2 : Count how many times we pass 0 {{{
wholeTurns :: Integer -> Integer
wholeTurns = abs . (`quot` 100)

extraTurn :: Integer -> Integer -> Integer
extraTurn s t = if 50 <= ( abs $ 50 - s - t ) && s /= 0 then 1 else 0

countAllZeroPasses :: Integer -> Integer -> Integer
countAllZeroPasses s t = (wholeTurns t) + (extraTurn s $ rem t 100)
-- }}}
