 solution←{
     ⎕PP←20
     row←2000000
     start←¯1784133
     end←5696467
     points←↑2(↑,⍥⊂↓)¨(⍎¨{⍵∊⎕D,'-'}⊆⊢)¨⊃⎕NGET ⍵ 1
     (scan beac)←↓⍉points
     manh←{+/|⍺-⍵}
     manhv←{+/¨|⍺-⍵}
     dist←manh/points

     check←{∨/dist≥scan manhv ⍵}
     process←{
         ⍺←0
         ⍝⎕←⍵
         end≤⊃⊃⍵:⍺
         (⍺+{
             ⍵∊beac:0
             check ⍵
         }⍵)∇ ⍵+⊂1 0
     }
     ⍝⎕←'part1: ',process(⊂start row)
     t←{
         ⍝⎕←⍵
         ~check ⍵:⍵
         ⍝∇ 21|⍵+(⊂1,(20≤⊃⊃⍵))
         ∇ 4000001|⍵+(⊂1,(4000000≤⊃⊃⍵))
     }
     ⎕←'part2: ',c←t(⊂0 0)
     ⎕←(4000000×⊃⊃c)+2⊃⊃c
 }
