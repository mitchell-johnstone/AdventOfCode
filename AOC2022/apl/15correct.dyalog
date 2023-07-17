 solution←{
     ⎕IO←0
     ⎕PP←20
     x y bx by←↓⍉↑{⍎¨(⍵∊⎕D,'-')⊆⍵}¨⊃⎕NGET ⍵ 1
     r←⊃+/|x y-bx by
     row←10 2000000[14<≢x]
     to←{(⍺⌊⍵)+⍳1+|⍺-⍵}
     dy←r-|row-y
     covered←⊃{⍵∪⊃(-to+)/⍺}/⌽(⊂⍬),(0≤dy)/x,¨dy
     beacons←(row=by)/bx
     ⎕←≢covered~beacons
     max←20 4000000[14<≢x]
     d1 d2←{(y+⍵)(-∪+)(r+1)}¨(-x)x
     ⎕←⊃∊d1∘.{
         pos←⌊0.5×⍵(-,+)⍺
         (0≥pos)∨.∨(pos≥max):⍬
         r∨.≥⊃pos+.(|-)x y:⍬
         pos+.×4000000 1
     }d2
 }
