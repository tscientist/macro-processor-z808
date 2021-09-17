Dados SEGMENT 
 Var1 DW 5 
 Var2 DW 8 
 Var3 DW 3 
 Dados ENDS 
 Codigo SEGMENT 
 ASSUME CS: Codigo 
 ASSUME DS: Dados 
 
 Inicio: 
 mov AX , Dados 
 mov DS , AX 
 mov AX , 2 
 mov AX , DX 
 mul DX 
 mov AX , SomaMem 
 push AX 
 mov AX , Var1 
 mov DX , AX 
 pop AX 
 add AX , DX 
 mov SomaMem , AX 
 mov AX , SomaMem 
 push AX 
 mov AX , mov 
 mov DX , AX 
 pop AX 
 add AX , DX 
 mov SomaMem , AX 
 
 mov AX , Var1 
 add AX , DX 
 mov Var2 , AX 
 mov AX , Var3 
 push AX 
 mov AX , mov 
 mov DX , AX 
 pop AX 
 add AX , DX 
 mov Var3 , AX 
 
 mov AX , 
 
 push AX 
 mov AX , mov 
 mov DX , AX 
 pop AX 
 add AX , DX 
 mov 
 , AX 
 
 CODIGO ENDS 
 END Inicio 