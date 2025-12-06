module Main (main) where

main :: IO ()
main = do
  contents <- readFile "input/day3.txt"
  let banks = lines contents
  print . sum $ map (dpJoltage 2) banks
  print . sum $ map (dpJoltage 12) banks

dpJoltage :: Int -> String -> Int
dpJoltage n = read . (!!n) . foldl dpJoltageSingle [""]

dpJoltageSingle :: [String] -> Char -> [String]
dpJoltageSingle dp c = zipWith max (dp++[""]) $ "":(map (++[c]) dp)

-- joltage :: String -> String
-- joltage "" = "00"
-- joltage [x] = '0':[x]
-- joltage (x:xs) = max (x:(maximum xs):[]) (joltage xs)
