module Main (main) where

-- import Data.List (transpose)
-- import Data.List.Split (splitWhen)
import Data.List (nub)

main :: IO ()
main = do
  contents <- readFile "input/day7.txt"
  let l = lines contents
  print $ fst . (!! (length l)) $ iterate (emit (getSplits l) nub) (0,[getStart l])
  print $ (+) 1 . fst . !! (length l) $ iterate (emit (getSplits l) id) (0,[getStart l])

emit :: [(Int,Int)] -> ([(Int,Int)] -> [(Int,Int)]) -> (Int, [(Int,Int)]) -> (Int, [(Int,Int)])
emit splits postprocess (cnt, fronteir) = (cnt', fronteir')
  where
    inF = filter (`elem` splits) $ moveDown fronteir
    notInF = filter (not . (`elem` splits)) $ moveDown fronteir
    fronteir' = postprocess $ notInF ++ horizontal inF
    cnt' = cnt + length inF

moveDown :: [(Int, Int)] -> [(Int, Int)]
moveDown = map (\(a,b) -> (a+1,b))

horizontal :: [(Int, Int)] -> [(Int, Int)]
horizontal v = (map (\(a,b) -> (a,b+1)) v) ++ (map (\(a,b) -> (a,b-1)) v)

getStart :: [String] -> (Int, Int)
getStart = (,) 0 . length . fst . break (=='S') . head

getSplits :: [String] -> [(Int, Int)]
getSplits g =
  [ (i,j)
  | (i,row) <- zip [0..] g
  , (j,cell) <- zip [0..] row
  , cell == '^'
  ]

-- replace :: Char -> Char -> String -> String
-- replace c t = map (\cur -> if cur == c then t else cur)
--
-- emit :: String -> String -> String
-- emit ls rs = split $ zipWith (\l r -> if l == '|' then (if r == '^' then r else l) else '.') ls rs
--
-- split :: String -> String
-- split s = map toRay $ zipWith3 or3 (False:(init $ map (== '^') s)) ((tail $ map (== '^') s)++[False]) (map (== '|') s)
--   where
--     toRay = \b -> if b then '|' else '.'
--     or3 = \a b c -> a || b || c
