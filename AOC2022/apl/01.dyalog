 solution←{
     packs←(≢¨⊆⊢),⎕CSV ⍵ ⍬ 4
     sums←+/¨packs
     ⎕←'part1: ',⌈/sums
     ⎕←'part2: ',+/3↑sums[⍒sums]
 }
