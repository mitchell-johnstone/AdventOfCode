 solution←{
     content←⊃⊃⎕NGET ⍵ 1
     ⎕←'part1: ',3+⊃⍸(⊃∪(=⍥⍴)⊢)¨4,⌿content
     ⎕←'part2: ',13+⊃⍸(⊃∪(=⍥⍴)⊢)¨14,⌿content
 }
