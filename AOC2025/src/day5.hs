module Main (main) where

import Data.List.Split (splitWhen, splitOn)
import Data.Range (Range, (+=+), inRanges, mergeRanges)

main :: IO ()
main = do
  contents <- readFile "input/day5.txt"
  -- let (strRanges:ids:[]) = splitWhen (null) $ lines contents
  let (strRanges, ids) =
        case splitWhen null (lines contents) of
          [s, i] -> (s, i)
          _      -> error "Expected exactly two blocks"

  let ranges = map strToRange strRanges
  print $ length $ filter (inRanges ranges) $ map read ids
  print $ sum $ map countRange $ mergeRanges ranges

strToRange :: String -> Range Int
strToRange s =
  let (a, rest) = break (== '-') s
      b         = drop 1 rest
  in (read a) +=+ (read b)

countRange :: Range Int -> Int
countRange r
  | (lb:"+=+":ub:[]) <- s = (read ub) - (read lb) + 1
  | ("SingletonRange":_:[]) <- s = 1
  | otherwise = error "Failed to count size of range"
  where
    s = splitOn " " $ show r
