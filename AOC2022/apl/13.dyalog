 solution←{
     pairs←(⎕JSON¨¨(×≢¨)⊆⊢)⊃⎕NGET ⍵ 1
     comp←{
         (i1 i2)←0=≡¨⍺ ⍵
         i1∧i2:⍺(<->)⍵   ⍝ compare integers
         i1:(,⍺)∇ ⍵      ⍝ make ⍺ a list
         i2:⍺ ∇(,⍵)      ⍝ make ⍵ a list
         (e1 e2)←0=≢¨⍺ ⍵
         e1∨e2:e1-e2     ⍝ empty?
         0≠f←∇/⊃¨⍺ ⍵:f   ⍝ head
         ∇/1↓¨⍺ ⍵        ⍝ tail
     }
     ⎕←'part 1: ',+/⍸1=comp/¨pairs
     ⎕←'part 2: ',×/1 2++⌿(⊃,/pairs)∘.(1=comp)⎕JSON¨'[[2]]' '[[6]]'
 }
