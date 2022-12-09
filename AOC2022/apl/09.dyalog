 solution←{
     in←⎕CSV ⍵ ⍬ 1
     rope←10/⊂(0 0)
     pos1←⍬
     pos9←⍬
     update←{
        ⍝ ⍵ is the direction
         old←¯1⌽rope
         (⊃rope)+←⍵
         segment←{
             p←(⍵-1)⊃rope
             c←⍵⊃rope
             (∨/p=c)∧(∨/1<|p-c):(p+c)÷2
             ∨/1<|p-c:c+(1+2⊥c<p)⊃(⊆(¯1 ¯1)(¯1 1)(1 ¯1)(1 1))
             c
         }
         none←{(⍵⊃rope)←segment ⍵ ⋄ ⍵}¨1+⍳⍴1↓rope
         pos1,←⊂2⊃rope
         pos9,←⊂10⊃rope
         rope
     }
     none←{
         (dir mag)←' '(≠⊆⊢)⍵
         mag←⍎mag
         update¨mag/⊂(⍸(⊃dir)⍷'UDLR')⊃(⊆(0 1)(0 ¯1)(¯1 0)(1 0))
     }¨in
     ⎕←'part1 :',≢∪pos1
     ⎕←'part2 :',≢∪pos9
 }
