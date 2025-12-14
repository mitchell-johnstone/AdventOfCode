module Main (main) where

import qualified Data.Map as Map

data State = State {splitCount :: Int, histogram :: Map.Map (Int, Int) Int}

main :: IO ()
main = do
  contents <- readFile "input/day7.txt"
  let l = lines contents
  let startState = State {splitCount = 0, histogram = Map.fromList [(getStart l, 1)]}
  -- iterate till 1 past the end, to make sure we capture all splits
  let endState = (!! (1 + length l)) $ iterate (emit (getSplits l)) startState
  print $ splitCount endState
  print $ sum . Map.elems $ histogram endState

emit :: [(Int,Int)] -> State -> State
emit splits (State cnt hist) = (State cnt' hist')
  where
    (split, stay) = Map.partitionWithKey (\k _ -> elem k splits) hist
    cnt' = cnt + (length $ Map.keys split)
    hist' = Map.mapKeys moveDown $ Map.unionsWith (+) [(Map.mapKeys moveLeft split), stay, (Map.mapKeys moveRight split)]

move :: (Int, Int) -> (Int, Int) -> (Int, Int)
move (r',c') (r,c) = (r+r',c+c')

moveDown = move (1,0)
moveLeft = move (0,-1)
moveRight = move (0,1)

getStart :: [String] -> (Int, Int)
getStart = (,) 0 . length . fst . break (=='S') . head

getSplits :: [String] -> [(Int, Int)]
getSplits g =
  [ (i,j)
  | (i,row) <- zip [0..] g
  , (j,cell) <- zip [0..] row
  , cell == '^'
  ]
