 solution←{
    ⍝ ⍵ is the name of the file
     in←1,⊃,/' '(⍎¨≠⊆⊢)¨('noop|addx'⎕R'0')⊃⎕NGET ⍵ 1
     vals←(+\in)
     ind←vals∘{⍵(⊣×⊃)⍺}¨¯20+40×⍳6
     match←1≥|¯1+(1,⍨∊6/⊂⍳40)-vals
     ⎕←'part1: ',+/ind
     ⎕←'part2: ',⊂6 40⍴'.#'[match+1]
 }
