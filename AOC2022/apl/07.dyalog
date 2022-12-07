 solution←{
    ⍝ ⍵ is the filename
     lines←' '(≠⊆⊢)¨⊃⎕NGET ⍵ 1
     (unused folders files)←{
     ⍝{
        ⍝ ⍺ is 3 tuple of (current folder, folders, files)
         ⍺←''⍬ ⍬
         (cur folders files)←⍺
         0=≢⍵:⍺
         line←⊃⍵
         updateCur←{
            ⍝ ⍺ is the original
            ⍝ ⍵ is the line
             1≠⍴⊃⍵:⍺ ⍝ check ⍵[1] is of length 1
             '$'≠1⊃⍵:⍺ ⍝ check ⍵[1] = '$'

             2≠⍴2⊃⍵:⍺ ⍝ check ⍵[2] is of length 2
             ∧/'cd'≠(2⊃⍵):⍺ ⍝ check ⍵[2] = 'cd'

             f←3⊃⍵ ⍝ f is dir to cd to
             1=⍴f:⍺{ ⍝ handle when f = '/'
                 '/'=⍵:∊'/'
                 ∊⍺,⍵,'/'
             }f
             2=⍴f:⍺{ ⍝ handle when f = '..'
                 ∧/'..'=⍵:∊'/',⍨¯2↓('/'∘=⊂⊢)⍺
                 ∊⍺,⍵,'/'
             }f
             ⍺,(3⊃⍵),'/'
         }
         cur←cur updateCur line
         ⍝⎕←cur
         folders←∪folders,⊂cur ⍝ folders are a unique set
         ⍝⎕←folders
         updateFiles←{
           ⍝ ⍺ is the original
           ⍝ ⍵ is the line
             2≠≢⍵:⍺ ⍝ each file entry has 2 items
             ∧/⎕D∊⍨⊃⍵:⍺,⊂((⊂cur,2⊃⍵),⊂(⍎⊃⍵)) ⍝ if first entry is all numbers, add the file to list
             ⍺ ⍝ line wasn't a file, return original
         }
         files←files updateFiles line
         ⍝⎕←files
         (cur folders files)∇ 1↓⍵ ⍝ recurse to next line
     }lines
     match←folders∘.(⊃⍷)⊃¨files  ⍝ all files with the folder prefix
     sizes←folders∘.⊢2⊃¨files ⍝ all file sizes
     tree←match×sizes ⍝ the tree of sizes in folders
     folderSizes←+/tree ⍝ sum up to get folder sizes
     ⎕←'part1: ',+/∊(100000∘≥⊆⊢)folderSizes
     target←(⊃folderSizes)-40000000 ⍝ need at least 40000000
     ⎕←'part2: ',⌊/∊target(≤⊆⊢)folderSizes
 }
