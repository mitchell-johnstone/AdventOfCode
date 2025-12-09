module Main (main) where

import Data.List (transpose)
import Data.List.Split (splitWhen)

main :: IO ()
main = do
  contents <- readFile "input/day6.txt"
  let part1input = transpose $ map words $ lines contents
  let part2input = splitWhen (all (== ' ')) $ transpose $ lines contents
  print $ sum $ map (equate . reverse) part1input
  print $ sum $ map (equate . reverse . extractFunc) part2input

-- converts head of "13 *" -> "13" : .. : ["*"]
extractFunc :: [String] -> [String]
extractFunc (f:xs) = init f : xs ++ [[last f]]
extractFunc _ = undefined

-- expects list of (func, values)
equate :: [String] -> Int
equate (f:vs) = foldl1 (getFunc $ head f) $ map read vs
equate _ = undefined

getFunc :: Char -> (Int -> Int -> Int)
getFunc f
  | f == '+' = (+)
  | f == '*' = (*)
  | otherwise = undefined
