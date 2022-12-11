 solution←{
     in←(×⍥≢¨⊆⊢)⊃⎕NGET ⍵ 1
     ops←{24⊃3⊃⍵}¨in
     vals←{25↓3⊃⍵}¨in
     divs←{⍎21↓4⊃⍵}¨in
     cap←∧/divs
     trues←{1+⍎29↓5⊃⍵}¨in
     falses←{1+⍎30↓6⊃⍵}¨in
     business←{
         ⍝⍺ is the divisor number after worrying
         ⍝⍵ is the number of rounds
         calm←⍺
         items←{⍎18↓2⊃⍵}¨in
         seen←(⍴ops)/0
         monkey←{
            ⍝⍵ is the monkey number
             0=≢⍵⊃items:⍵
             (⍵⊃seen)+←≢⍵⊃items
             num←⍵
             worry←{'old'≡⍵:⍺ ⋄ ⍎⍵}
             res←cap∘|⌊calm÷⍨{ops[num]='*':⍵×(⍵ worry num⊃vals) ⋄ ⍵+(⍵ worry num⊃vals)}¨⍵⊃items
             to←{⍵⊃((num⊃trues)(num⊃falses))}¨(⊃1+×divs[num]|⊂res)
             items[to],←res
             (num⊃items)←⍬
             ⍵
         }
         done←monkey¨∊⍵/⊂⍳⍴ops
         ×/2↑seen[⍒seen]
     }
     ⎕PP←11
     ⎕←'part1: ',3 business 20
     ⎕←'part2: ',1 business 10000
 }
