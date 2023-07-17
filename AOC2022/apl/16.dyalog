 solution←{
     (flow from to)←↓⍉↑({(⍎1⊃⍵)(2⊃⍵)(2↓⍵)})¨(({⍵∊⎕D}⊆⊢),{⍵∊⎕A}⊆⍥(1∘↓)⊢)¨⊃⎕NGET ⍵ 1
     flow,←0 ⍝catch out of array for from
     states←('AA',⍥⊂'AA')(⍬,⍥⊂⍬)(0 0)
     update←{
         ⍝ ⍵ is the current states
⍝         single←{
⍝            ⍝ ⍵ is a single state
⍝             (cur on sum)←⍵
⍝
⍝             sum+←+/flow[from⍳on] ⍝ update flows
⍝             next←on~⍨⊃to[from⍳⊂cur]
⍝             f←flow[from⍳⊂cur]
⍝
⍝             0=f:(⊂¨next),¨⊂on sum ⍝ if the flow is 0, move on
⍝
⍝             ~(⊂cur)∊on: ⍝ if we haven't already turned it on
⍝             past,←cur ⍝ update past to include ourselves
⍝         }
⍝         single ⍵
         (cur on sum)←⍵
         ⍝{+/flow[from⍳⍵]}¨on
         nf←sum+{⊂+/flow[from⍳⍵]}¨on
         nc←(to[from⍳cur])~⍥⊆¨on
         rep←≢¨nc
         turn←nf,⍨¨(⊣,⍥⊂∪⍥⊆)/⍉↑cur on

         (↓⍉↑turn),¨(⊃,/nc)(rep/on)(rep/nf)
         ⍝nc,⍥⊂¨on,⍥⊂¨nf

     }
     ⍝update states
     (c o s)←(update⍣30)states
     ⌈/s

 }
