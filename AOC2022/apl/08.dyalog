 solution←{
⍝⍵ is the filename
     trees←1+↑⍎¨¨⊃⎕NGET ⍵ 1
     (height width)←⍴trees
     ⍝process←{⍺⍺⍣¯1∧/(⍺⍺ trees)∘{⍺>height↑⍵↓⍺}¨⍳height}
     up←⊃∧/trees∘{⍺>height∘↑⍵↓⍺}¨⍳height
     down←⊖⊃∧/(⊖trees)∘{⍺>height∘↑⍵↓⍺}¨⍳height
     right←⍉⊃∧/(⍉trees)∘{⍺>width∘↑⍵↓⍺}¨⍳width
     left←⍉⊖⊃∧/(⊖⍉trees)∘{⍺>width∘↑⍵↓⍺}¨⍳width
     seen←up∨down∨left∨right
     ⎕←'part1 :',+/∊seen
     r←{h←⍵⊃⍺ ⋄ ⍺{cur←⍵+1 ⋄ cur>⍴⍺:0 ⋄ h≤cur⊃⍺:1 ⋄ 1+(⍺ ∇ cur)}⍵}
     l←{h←⍵⊃⍺ ⋄ ⍺{cur←⍵-1 ⋄ ~×cur:0 ⋄ h≤cur⊃⍺:1 ⋄ 1+(⍺ ∇ cur)}⍵}
     ⎕←'part2 :',⌈/trees∘{
         (y x)←⍵
         row←y⊃↓⍺
         col←x⊃↓⍉⍺
         (row r x)×(row l x)×(col r y)×(col l y)
     }¨,⍳⍴trees
 }
