 solution←{
    ⍝ ⍵ is the filename
     sacks←⎕CSV ⍵ ⍬ 1
     splitunion←{(2÷⍨⍴⍵)(↑∩⍥∪↓)⍵}
     common←splitunion¨sacks
     vals←('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ',⌸⍳52)
     value←{vals⌷⍨0 1+∊⍸⍵⍷vals}
     ⎕←'part1: ',+/∊value¨common
     groups←((3÷⍨≢sacks),3)⍴sacks
     ⎕←'part2: ',+/value¨∩⍥∪/groups
 }
