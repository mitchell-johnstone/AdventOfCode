module Main (main) where

import Data.List.Split (splitOn, chunksOf)

main :: IO ()
main = do
  contents <- readFile "input/day2.txt"
  let ranges = map (map read . splitOn "-") . (splitOn ",") $ init contents
  print . sum $ map (handleRange halfMatches) ranges
  print . sum $ map (handleRange chunkMatches) ranges

handleRange :: (Integer -> Bool) -> [Integer] -> Integer
handleRange invalidFunc [b,t] = sum $ filter invalidFunc [b..t]
handleRange _ _ = error ":("

-- part 1
halfMatches :: Integer -> Bool
halfMatches v =
  uncurry (==) $ splitAt (length s `quot` 2) s
  where
    s = show v

-- part 2
allMatch :: (Eq a) => [a] -> Bool
allMatch [] = True
allMatch (x:xs) = all (== x) xs

chunkMatches :: Integer -> Bool
chunkMatches v =
  any (\n -> allMatch $ chunksOf n s) [1..((length s) `div` 2)]
  where
    s = show v




-- Old initial version
-- module Main (main) where
--
-- import Data.List.Split (splitOn)
--
-- main :: IO ()
-- main = do
--   contents <- readFile "input/day2ex.txt"
--   print $ map (splitOn "-") . (splitOn ",") $ init contents
--   let ranges = map (splitOn "-") $ splitOn "," $ init contents
--   print ranges
--   let res = map (\x -> (directAbove (head x), directBelow (last x))) ranges
--   print res
--   print $ filter (\(a,b) -> a <= b) res
--   print $ sum $ map (\(a,b) -> max 0 $ b-a+1) res
--
-- directAbove :: String -> Integer
-- directAbove s
--   | (length topHalf) == (length bottomHalf) = resolveAbove topHalf bottomHalf
--   | otherwise = 10 ^ (length topHalf)
--   where
--     (topHalf, bottomHalf) = splitAt (length s `quot` 2) s
--
-- resolveAbove :: String -> String -> Integer
-- resolveAbove t b
--   | t < b = tv + 1
--   | otherwise = tv
--   where
--     tv = read t
--
-- directBelow :: String -> Integer
-- directBelow s
--   | length s <= 1 = -100000
--   | (length topHalf) == (length bottomHalf) = resolveBelow topHalf bottomHalf
--   | otherwise = (10 ^ (length topHalf)) - 1
--   where
--     (topHalf, bottomHalf) = splitAt (length s `quot` 2) s
--
-- resolveBelow :: String -> String -> Integer
-- resolveBelow t b
--   | t > b = tv - 1
--   | otherwise = tv
--   where
--     tv = read t
