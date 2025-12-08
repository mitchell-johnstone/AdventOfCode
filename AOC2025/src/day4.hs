module Main (main) where

main :: IO ()
main = do
  contents <- readFile "input/day4ex.txt"
  let grid = lines contents
  let coords = getCoords grid
  -- print $ map (\cur -> length $ filter (isNeighbor cur) coords) coords
  print $ length $ filter (<= 4) $ map (neighborCount coords) coords
  print $ cleanTowels coords

getCoords :: [String] -> [(Int, Int)]
getCoords grid =
  [ (i,j)
  | (i,row) <- zip [0..] grid
  , (j,cell) <- zip [0..] row
  , cell == '@'
  ]

-- part 1
neighborCount :: [(Int, Int)] -> (Int, Int) -> Int
neighborCount coords cur = length $ filter (isNeighbor cur) coords

isNeighbor :: (Int, Int) -> (Int, Int) -> Bool
isNeighbor (r1,c1) (r2,c2) = all ((<= 1) . abs) [r1 - r2, c1 - c2]

-- part 2
cleanTowels :: [(Int, Int)] -> Int
cleanTowels coords
  | removed == 0 = 0
  | otherwise = removed + cleanTowels over4
  where
    over4 = filter ((>4) . neighborCount coords) coords
    removed = (length coords) - (length over4)
