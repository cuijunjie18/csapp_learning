
|     |iaddq V,rB            |
|-----|----------------------|
|取指 |icode:ifun &larr; $M_1$[PC] <br> rA:rB &larr; $M_1$[PC + 1] <br> valC &larr; $M_8$[PC + 2] <br> valP &larr; PC + 10      |
|译码 | valB &larr; R[rB]   |
|执行 | valE &larr; valB + valC <br> set CC|
|访存 |                     |
|写回 | R[rB] &larr; valE   |
|更新PC | PC &larr; valP    |
