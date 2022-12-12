 solution←{
     (a b c d e f g h i j k l m n o p q r s t u v w x y z)←2+⍳26
     in←↑⊃⎕NGET ⍵ 1
     map←⍎¨¨('S'⎕R'a')¨('E'⎕R'z')¨in
     end←⍸in='E'
     update←{
         cur←⍵×map
         check←{1≥map-(⍺⍺⍣¯1)0⍪⍨1↓⍺⍺ ⍵}
         ⊃∨/(⊢check cur)(⊖check cur)(⍉check cur)(⊖∘⍉check cur)
     }
     search←{
         end⊃⍺:⍵
         (⍺∨update ⍺)∇ ⍵+1
     }
     ⎕←'part1 :',(in='S')search 0
     ⎕←'part2 :',(map=3)search 0
 }
