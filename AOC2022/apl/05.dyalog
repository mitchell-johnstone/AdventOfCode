 solution←{
    ⍝ ⍵ is an array.
    ⍝ ⍵[1] is the filename
    ⍝ ⍵[2] is the max height
    ⍝ ⍵[3] is the rows
     name←⍵[1]
     height←⍵[2]
     width←⍵[3]
     content←⊃⎕NGET name,1
     rows←' '(⊃≠⊆⊢)¨,/(2+4×¯1+⍳width)∘.⊃height↑content
     moves←,/⍎¨⍉2 4 6∘.⊃' '(≠⊆⊢)¨(height+2)↓content
     res←moves{
         ⍺←⍬
         0=≢⍺:⍵
         move←⊃⍺
         rem←⌽move[1]↑⊃⍵[move[2]]
         neww←((⊂(move[1])↓⊃(move[2])⌷⍵)@(move[2]))⍵
         neww←((⊂rem,⊃(move[3])⌷⍵)@(move[3]))neww
         newa←1↓⍺
         newa ∇ neww
     }rows
     ⎕←'part1: ',,/⊃¨res
     res←moves{
         ⍺←⍬
         0=≢⍺:⍵
         move←⊃⍺
         rem←move[1]↑⊃⍵[move[2]]
         neww←((⊂(move[1])↓⊃(move[2])⌷⍵)@(move[2]))⍵
         neww←((⊂rem,⊃(move[3])⌷⍵)@(move[3]))neww
         newa←1↓⍺
         newa ∇ neww
     }rows
     ⎕←'part2: ',,/⊃¨res
 }
