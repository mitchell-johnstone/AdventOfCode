 solution←{
    ⍝ ⍵ is the filename
     ranges←⍎¨¨'-'(≠⊆⊢)¨⎕CSV ⍵ ⍬ 1
     left←∨/¨≥/ranges
     right←∨/¨≤/ranges
     ⎕←'part1: ',+/left∧right
     a←⊣/¨⊣/ranges
     b←⊢/¨⊣/ranges
     l←⊣/¨⊢/ranges
     r←⊢/¨⊢/ranges
     ⎕←'part2: ',+/(a≤r)∧(b≥l)
 }
