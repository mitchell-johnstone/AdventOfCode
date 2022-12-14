 solution←{
     ⍝ x values are from 490 to 559. (let's go 450 to 600 for wiggle room)
     ⍝ y values are from 15 to 160.
     ⍝ starting at 450. Then sand comes in at index 50
     ⎕IO←0
     s←¯100
     w←700
     in←⌽¨¨(s 0)∘+¨¨⍎¨¨' '(≠⊆⊢)¨(' -> '⎕R' ')⊃⎕NGET ⍵ 1
     d←2+⊃⊃⌈/⊃,/in

     grid←170 w⍴0
     addLine←{
         ((⊆⍵)⊃grid)←1
         ⍵≡⍺:0
         ⍺ ∇ ⍵-(×⍵-⍺)
     }
     _←2 addLine/¨in
     addPixel←{
         ⍝ ⍵ is graph
         ⍝ ⍺ is the location
         ⍺←0 50
         169≤⊃⍺:⍵
         ~(⊆⍺+1 0)⊃⍵:(⍺+1 0)∇ ⍵  ⍝ down
         ~(⊆⍺+1 ¯1)⊃⍵:(⍺+1 ¯1)∇ ⍵  ⍝ down-left
         ~(⊆⍺+1 1)⊃⍵:(⍺+1 1)∇ ⍵  ⍝ down-right

         ⍝⎕←(⍴⍵)⍴(⊆⍺)≡¨,⍳⍴⍵
         (1@(⊆⍺))⍵
         ⍝pic∘←(1@(⊆⍺))⍵
         ⍝cur∘←'.#'[pic]
         ⍝pic
     }
     p1←0
     _←(0(s+500))({p1+←1 ⋄ ⍺ addPixel ⍵}⍣≡)grid
     _←(d 0)addLine(d(w-1))
     p2←0
     _←(0(s+500))({p2+←1 ⋄ ⍺ addPixel ⍵}⍣≡)grid
     ⎕←'part1 :',p1-1
     ⎕←'part1 :',p2-1
 }
