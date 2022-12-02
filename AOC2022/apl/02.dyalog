 solution←{
    ⍝ ⍵ is the name of the input file
     data←⎕CSV ⍵ ⍬ 1
     moves←' '(≠⊆⊢)¨data
     theirs←⊃¨moves
     ours←2⊃¨moves
⍝     ⎕←moves
     tr←theirs='A'
     tp←theirs='B'
     ts←theirs='C'

     or←ours='X'
     op←ours='Y'
     os←ours='Z'
⍝     ⎕←op
     loss←(or∧tp),(op∧ts),(os∧tr)
     wins←(or∧ts),(op∧tr),(os∧tp)
     draw←(or∧tr),(op∧tp),(os∧ts)
⍝     ⎕←'wins:'
⍝     ⎕←∊wins
     total←+/∊((3×os),(2×op),(or),(3×draw),(6×wins))
     ⎕←'part1:',total

     sl←or
     sd←op
     sw←os

     shapes←(tp)+(2×ts)
     ns←1+3|(sw∧1+shapes)+(sl∧¯1+shapes)+(sd∧shapes)
     total←+/∊ns,(3×sd),(6×sw)
     ⎕←'part2:',total
 }
