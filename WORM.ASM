; ================================================================
; WORM.COM  --  CP/M Worm Game v1.02  (19 Aug 1983)
; Intel 8080 disassembly with annotated labels
;
; CP/M memory map:
;   0000h  Warm-boot entry (RST 0)
;   0005h  BDOS entry  -- C=function, DE=param
;     C=1  console output  (E = char)
;     C=9  print string$   (DE = address, '$'-terminated)
;     C=10 read console    (DE = buffer)
;   0100h  .COM load address (this file)
;
; Label conventions:
;   func_NN  -- subroutine (reached by CALL)
;   loc_NN   -- local branch target (reached by Jxx/JMP)
; ================================================================


main:          ; 0100h
  LXI D, 07A4h                 
  MVI C, 09h                   
  CALL  bdos                     ; --> BDOS system call

title_loop:          ; 0108h
  CALL  animate_title                
  MVI C, 06h                   
  MVI E, FFh                   
  CALL  bdos                     ; --> BDOS system call
  ORA A                        
  JZ    title_loop                 
  CPI 48h                      
  JZ    start_game                 
  CPI 68h                      

start_game:          ; 011Dh
  CZ    show_help_screen                
  CALL  draw_border                
  CALL  init_playfield                
  CALL  place_food                

game_loop:          ; 0129h
  CALL  read_key_nonblock                
  CPI 6Bh                      
  JZ    move_up                 
  CPI 05h                      
  JZ    move_up                 
  CPI 6Ah                      
  JZ    move_down                 
  CPI 18h                      
  JZ    move_down                 
  CPI 68h                      
  JZ    move_left                 
  CPI 13h                      
  JZ    move_left                 
  CPI 6Ch                      
  JZ    move_right                 
  CPI 04h                      
  JZ    move_right                 
  CPI 03h                      
  JZ    quit_game                 
  CPI 45h                      
  JZ    quit_game                 
  CPI 65h                      
  JZ    quit_game                 
  MVI E, 07h                   
  CALL  putchar                
  JMP   game_loop                 
  DCX D                        
  MOV E,E                      
  STA 244Ah                    

draw_border:          ; 0170h
  LXI D, 016Bh                 
  MVI C, 09h                   
  CALL  bdos                     ; --> BDOS system call
  LXI H, 0000h                 
  CALL  cursor_goto                
  MVI B, 2Bh                   
  MVI C, 2Dh                   
  CALL  draw_border_row                
  MVI A, 14h                   
  STA 085Dh                    

border_fill_loop:          ; 018Ah
  MVI B, 49h                   
  MVI C, 20h                   
  CALL  draw_border_row                
  LDA 085Dh                    
  DCR A                        
  STA 085Dh                    
  JNZ   border_fill_loop                 
  MVI B, 2Bh                   
  MVI C, 2Dh                   
  CALL  draw_border_row                
  MVI H, 0Ah                   
  MVI L, 28h                   
  CALL  cursor_goto                
  MVI E, 4Fh                   
  CALL  putchar                
  MVI E, 3Ch                   
  CALL  putchar                
  MVI E, 3Ch                   
  CALL  putchar                
  RET                          

draw_border_row:          ; 01B9h
  MOV E,B                      
  PUSH B                       
  CALL  putchar                
  POP B                        
  MVI A, 4Eh                   
  STA 085Ch                    

border_col_loop:          ; 01C4h
  MOV E,C                      
  PUSH B                       
  CALL  putchar                
  POP B                        
  LDA 085Ch                    
  DCR A                        
  STA 085Ch                    
  JNZ   border_col_loop                 
  MOV E,B                      
  CALL  putchar                
  MVI E, 0Dh                   
  CALL  putchar                
  MVI E, 0Ah                   
  CALL  putchar                
  RET                          

init_playfield:          ; 01E3h
  LXI D, 0866h                 
  MVI B, 2Bh                   
  MVI C, 2Dh                   
  CALL  write_border_row_buf                
  MVI A, 14h                   
  STA 085Dh                    

playfield_row_loop:          ; 01F2h
  MVI B, 49h                   
  MVI C, 20h                   
  CALL  write_border_row_buf                
  LDA 085Dh                    
  DCR A                        
  STA 085Dh                    
  JNZ   playfield_row_loop                 
  MVI B, 2Bh                   
  MVI C, 2Dh                   
  CALL  write_border_row_buf                
  MVI H, 0Ah                   
  MVI L, 28h                   
  SHLD 085Eh                   
  MVI A, 4Fh                   
  CALL  write_cell                
  MVI A, 3Ch                   
  INX D                        
  STAX D                       
  INX D                        
  STAX D                       
  RET                          

write_border_row_buf:          ; 021Dh
  MOV A,B                      
  STAX D                       
  INX D                        
  MVI A, 4Eh                   
  STA 085Ch                    

playfield_col_loop:          ; 0225h
  MOV A,C                      
  STAX D                       
  INX D                        
  LDA 085Ch                    
  DCR A                        
  STA 085Ch                    
  JNZ   playfield_col_loop                 
  MOV A,B                      
  STAX D                       
  INX D                        
  RET                          

place_food:          ; 0236h
  MVI H, 0Ah                   
  MVI L, 2Ah                   
  SHLD 0860h                   
  LXI H, 0003h                 
  SHLD 0862h                   
  MVI H, 17h                   
  MVI L, 32h                   
  CALL  cursor_goto                
  LXI D, 0862h                 
  CALL  print_string_de                
  MVI A, 05h                   
  STA 0865h                    
  MVI H, 17h                   
  MVI L, 27h                   
  CALL  cursor_goto                
  LXI D, 0841h                 
  MVI C, 09h                   
  CALL  bdos                     ; --> BDOS system call
  CALL  update_score_display                
  RET                          

move_up:          ; 0268h
  LHLD 085Eh                   
  CALL  cursor_goto                
  MVI E, 5Eh                   
  CALL  putchar                
  LHLD 085Eh                   
  MVI A, 5Eh                   
  CALL  write_cell                
  LHLD 085Eh                   
  DCR H                        
  JMP   after_move                 

move_down:          ; 0282h
  LHLD 085Eh                   
  CALL  cursor_goto                
  MVI E, 76h                   
  CALL  putchar                
  LHLD 085Eh                   
  MVI A, 76h                   
  CALL  write_cell                
  LHLD 085Eh                   
  INR H                        
  JMP   after_move                 

move_left:          ; 029Ch
  LHLD 085Eh                   
  CALL  cursor_goto                
  MVI E, 3Ch                   
  CALL  putchar                
  LHLD 085Eh                   
  MVI A, 3Ch                   
  CALL  write_cell                
  LHLD 085Eh                   
  DCR L                        
  JMP   after_move                 

move_right:          ; 02B6h
  LHLD 085Eh                   
  CALL  cursor_goto                
  MVI E, 3Eh                   
  CALL  putchar                
  LHLD 085Eh                   
  MVI A, 3Eh                   
  CALL  write_cell                
  LHLD 085Eh                   
  INR L                        
  JMP   after_move                 

after_move:          ; 02D0h
  SHLD 085Eh                   
  CALL  read_cell                
  CPI 20h                      
  JZ    draw_head                 
  CPI 23h                      
  JNZ   game_over                 
  LDA 0864h                    
  MOV E,A                      
  LDA 0865h                    
  
  STA 0865h                    
  CALL  update_score_display                

draw_head:          ; 02EEh
  LHLD 085Eh                   
  CALL  cursor_goto                
  MVI E, 4Fh                   
  CALL  putchar                
  LDA 0865h                    
  ORA A                        
  JZ    erase_tail                 
  DCR A                        
  STA 0865h                    
  LHLD 0862h                   
  INX H                        
  SHLD 0862h                   
  CALL  advance_worm_tail                
  JMP   end_of_turn                 

erase_tail:          ; 0311h
  LHLD 0860h                   
  CALL  cursor_goto                
  MVI E, 20h                   
  CALL  putchar                
  LHLD 0860h                   
  CALL  read_cell                
  PUSH PSW                     
  LHLD 0860h                   
  MVI A, 20h                   
  CALL  write_cell                
  LHLD 0860h                   
  POP PSW                      
  CPI 5Eh                      
  JZ    tail_was_up                 
  CPI 76h                      
  JZ    tail_was_down                 
  CPI 3Ch                      
  JZ    tail_was_left                 
  CPI 3Eh                      
  JZ    tail_was_right                 
  JMP   hit_wall                 

tail_was_up:          ; 0346h
  DCR H                        
  JMP   save_tail_pos                 

tail_was_down:          ; 034Ah
  INR H                        
  JMP   save_tail_pos                 

tail_was_left:          ; 034Eh
  DCR L                        
  JMP   save_tail_pos                 

tail_was_right:          ; 0352h
  INR L                        
  JMP   save_tail_pos                 

save_tail_pos:          ; 0356h
  SHLD 0860h                   

end_of_turn:          ; 0359h
  CALL  delay                
  JMP   game_loop                 

show_help_screen:          ; 035Fh
  MOV E,A                      
  CALL  putchar                
  LXI D, 0377h                 
  MVI C, 09h                   
  CALL  bdos                     ; --> BDOS system call

help_wait_key:          ; 036Bh
  MVI C, 06h                   
  MVI E, FFh                   
  CALL  bdos                     ; --> BDOS system call
  ORA A                        
  JZ    help_wait_key                 
  RET                          
  DCR C                        
  LDAX B                       
  LDAX B                       
  LDAX B                       
  LDAX B                       
  MOV D,A                      
  MOV C,A                      
  MOV D,D                      
  MOV C,L                      
  DB 20h                       
  MOV L,C                      
  MOV M,E                      
  DB 20h                       
  MOV H,C                      
  DB 20h                       
  MOV H,A                      
  MOV H,C                      
  MOV L,L                      
  MOV H,L                      
  DB 20h                       
  MOV M,A                      
  MOV L,B                      
  MOV H,L                      
  MOV M,D                      
  MOV H,L                      
  DB 20h                       
  MOV H,C                      
  DB 20h                       
  MOV L,H                      
  MOV H,L                      
  MOV M,H                      
  MOV M,H                      
  MOV H,L                      
  MOV M,D                      
  DB 20h                       
  MOV M,A                      
  MOV L,A                      
  MOV M,D                      
  MOV L,L                      
  DB 20h                       
  MOV L,C                      
  MOV M,E                      
  DB 20h                       
  MOV L,L                      
  MOV L,A                      
  HLT                          
  MOV H,L                      
  MOV H,H                      
  DB 20h                       
  MOV H,C                      
  MOV H,E                      
  MOV M,D                      
  MOV L,A                      
  MOV M,E                      
  MOV M,E                      
  DCR C                        
  LDAX B                       
  MOV M,H                      
  MOV L,B                      
  MOV H,L                      
  DB 20h                       
  MOV M,B                      
  MOV L,H                      
  MOV H,C                      
  MOV A,C                      
  MOV L,C                      
  MOV L,M                      
  MOV H,A                      
  DB 20h                       
  MOV H,M                      
  MOV H,L                      
  MOV L,C                      
  MOV L,H                      
  MOV H,H                      
  DB 20h                       
  MOV M,L                      
  MOV M,E                      
  MOV L,C                      
  MOV L,M                      
  MOV H,A                      
  DB 20h                       
  MOV L,B                      
  INR L                        
  DB 20h                       
  MOV L,D                      
  INR L                        
  DB 20h                       
  MOV L,E                      
  INR L                        
  DB 20h                       
  MOV H,C                      
  MOV L,M                      
  MOV H,H                      
  DB 20h                       
  MOV L,H                      
  MVI L, 20h                   
  MOV B,L                      
  MOV H,C                      
  MOV H,E                      
  MOV L,B                      
  DCR C                        
  LDAX B                       
  MOV M,H                      
  MOV L,C                      
  MOV L,L                      
  MOV H,L                      
  DB 20h                       
  MOV M,H                      
  MOV L,B                      
  MOV H,L                      
  DB 20h                       
  MOV M,A                      
  MOV L,A                      
  MOV M,D                      
  MOV L,L                      
  DB 20h                       
  MOV H,L                      
  MOV H,C                      
  MOV M,H                      
  MOV M,E                      
  DB 20h                       
  MOV H,C                      
  DB 20h                       
  MOV L,M                      
  MOV M,L                      
  MOV L,L                      
  MOV H,D                      
  MOV H,L                      
  MOV M,D                      
  INR L                        
  DB 20h                       
  MOV L,C                      
  MOV M,H                      
  DB 20h                       
  MOV H,A                      
  MOV M,D                      
  MOV L,A                      
  MOV M,A                      
  MOV M,E                      
  DB 20h                       
  MOV H,C                      
  DB 20h                       
  MOV L,H                      
  MOV L,C                      
  MOV M,H                      
  MOV M,H                      
  MOV L,H                      
  MOV H,L                      
  DCR C                        
  LDAX B                       
  MOV L,H                      
  MOV L,A                      
  MOV L,M                      
  MOV H,A                      
  MOV H,L                      
  MOV M,D                      
  MVI L, 20h                   
  MOV D,H                      
  MOV L,B                      
  MOV H,L                      
  DB 20h                       
  MOV H,A                      
  MOV L,A                      
  MOV H,C                      
  MOV L,H                      
  DB 20h                       
  MOV L,A                      
  MOV H,M                      
  DB 20h                       
  MOV M,H                      
  MOV L,B                      
  MOV H,L                      
  DB 20h                       
  MOV H,A                      
  MOV H,C                      
  MOV L,L                      
  MOV H,L                      
  DB 20h                       
  MOV L,C                      
  MOV M,E                      
  DB 20h                       
  MOV M,H                      
  MOV L,A                      
  DB 20h                       
  MOV H,M                      
  MOV H,C                      
  MOV M,H                      
  MOV M,H                      
  MOV H,L                      
  MOV L,M                      
  DB 20h                       
  MOV M,H                      
  MOV L,B                      
  MOV H,L                      
  DB 20h                       
  MOV M,A                      
  MOV L,A                      
  MOV M,D                      
  MOV L,L                      
  DCR C                        
  LDAX B                       
  MOV M,L                      
  MOV M,B                      
  DB 20h                       
  MOV H,C                      
  MOV M,E                      
  DB 20h                       
  MOV L,H                      
  MOV L,A                      
  MOV L,M                      
  MOV H,A                      
  DB 20h                       
  MOV H,C                      
  MOV M,E                      
  DB 20h                       
  MOV M,B                      
  MOV L,A                      
  MOV M,E                      
  MOV M,E                      
  MOV L,C                      
  MOV H,D                      
  MOV L,H                      
  MOV H,L                      
  MVI L, 20h                   
  MOV C,B                      
  MOV L,A                      
  MOV M,A                      
  MOV H,L                      
  HLT                          
  MOV H,L                      
  MOV M,D                      
  INR L                        
  DB 20h                       
  MOV L,C                      
  MOV L,M                      
  DB 20h                       
  MOV L,C                      
  MOV M,H                      
  MOV M,E                      
  DB 20h                       
  MOV H,A                      
  MOV M,D                      
  MOV H,L                      
  MOV H,L                      
  MOV H,H                      
  DCR C                        
  LDAX B                       
  MOV L,C                      
  MOV M,H                      
  DB 20h                       
  MOV L,L                      
  MOV M,L                      
  MOV M,E                      
  MOV M,H                      
  MOV L,M                      
  
  MOV M,H                      
  DB 20h                       
  MOV L,M                      
  MOV L,C                      
  MOV H,D                      
  MOV H,D                      
  MOV L,H                      
  MOV H,L                      
  DB 20h                       
  MOV L,A                      
  MOV L,M                      
  DB 20h                       
  MOV L,C                      
  MOV M,H                      
  MOV M,E                      
  MOV H,L                      
  MOV L,H                      
  MOV H,M                      
  DB 20h                       
  MOV L,A                      
  MOV M,D                      
  DB 20h                       
  MOV M,H                      
  MOV H,L                      
  DB 20h                       
  MOV M,B                      
  MOV L,H                      
  MOV H,C                      
  MOV A,C                      
  MOV L,C                      
  MOV L,M                      
  MOV H,A                      
  DB 20h                       
  MOV H,M                      
  MOV L,C                      
  MOV H,L                      
  MOV L,H                      
  MOV H,H                      
  LXI H, 0A0Dh                 
  DCR C                        
  LDAX B                       
  MOV B,A                      
  MOV L,A                      
  MOV L,A                      
  MOV H,H                      
  DB 20h                       
  MOV C,H                      
  MOV M,L                      
  MOV H,E                      
  MOV L,E                      
  LXI H, 2020h                 
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 28h                       
  MOV M,B                      
  MOV M,D                      
  MOV H,L                      
  MOV M,E                      
  MOV M,E                      
  DB 20h                       
  MOV H,C                      
  MOV L,M                      
  MOV A,C                      
  DB 20h                       
  MOV L,E                      
  MOV H,L                      
  MOV A,C                      
  DB 20h                       
  MOV M,H                      
  MOV L,A                      
  DB 20h                       
  MOV H,E                      
  MOV L,A                      
  MOV L,M                      
  MOV M,H                      
  MOV L,C                      
  MOV L,M                      
  MOV M,L                      
  MOV H,L                      
  DAD H                        
  DCR C                        
  LDAX B                       
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
  INR H                        
; --- data: border_data ---
  ; |$$$$$$$$$$$$$$$$|
  ; |$$$$$$$$$$$$$$$$|
  ; |$$$$$$$$$$$$$$$$|
  ; |$$$$$$$$$$$$$$$$|
  ; |$$$$$$$$$$$$$$$$|
  ; |$$$$$$$$$$$$$$$$|
  ; |$$$$$$$$$$...*^.|
  ; |.e..*...&....e..|
  ; | ...............|
  ; |.........*..|...|
  ; |$....$.g}...$..O|
  ; |.$.o...... .$...|
  ; |e.*..|.......k.>|
  ; |....q..2d..0_...|
  ; |....>#.....M....|
  ; |..........G...x.|
  ; |.T.....&.......f|
  ; |....7?z.W{._z.W{|
  ; |._.:....7...?:..|
  ; |.2..:...2.......|
  ; |..........&..2.e|
  ; |..b......^#V....|
  ; |Q..2b.!W.N#F#.2a|
  ; |.{._z.W...:a.<2a|
  ; |....{._z.W:a...2|
  ; |.:b.....:a..02b.|
  ; |..._......x.....|
  ; |y.......0.....'.|
  ; |.d..............|
  ; |..[.....$l&."c..|
  ; |c.....;....,&."c|
  ; |..c.....H....!6.|
  ; |.e........WORM  |
  ; |   V-1.02     (1|
  ; |9.|
  DB 38h                       
  MVI L, 38h                   
  INX SP                       
  DAD H                        
  DCR C                        
  LDAX B                       
  LDAX B                       
  LDAX B                       
  LDAX B                       
  MOV D,H                      
  MOV L,A                      
  DB 20h                       
  MOV H,D                      
  MOV H,L                      
  MOV H,A                      
  MOV L,C                      
  MOV L,M                      
  INR L                        
  DB 20h                       
  MOV M,B                      
  MOV M,D                      
  MOV H,L                      
  MOV M,E                      
  MOV M,E                      
  DB 20h                       
  MOV H,C                      
  MOV L,M                      
  MOV A,C                      
  DB 20h                       
  MOV L,E                      
  MOV H,L                      
  MOV A,C                      
  MVI L, 20h                   
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DB 20h                       
  DCR C                        
  LDAX B                       
  DB 28h                       
  MOV C,C                      
  MOV H,M                      
  DB 20h                       
  MOV A,C                      
  MOV L,A                      
  MOV M,L                      
  DB 20h                       
  MOV M,D                      
  MOV H,L                      
  MOV M,C                      
  MOV M,L                      
  MOV L,C                      
  MOV M,D                      
  MOV H,L                      
  DB 20h                       
  MOV H,M                      
  MOV M,L                      
  MOV M,D                      
  MOV M,H                      
  MOV L,B                      
  MOV H,L                      
  MOV M,D                      
  DB 20h                       
  MOV H,L                      
  MOV A,B                      
  MOV M,B                      
  MOV L,H                      
  MOV H,C                      
  MOV L,M                      
  MOV H,C                      
  MOV M,H                      
  MOV L,C                      
  MOV L,A                      
  MOV L,M                      
  INR L                        
  DB 20h                       
  MOV M,B                      
  MOV M,D                      
  MOV H,L                      
  MOV M,E                      
  MOV M,E                      
  DB 20h                       
  MOV C,B                      
  DAD H                        
  DB 20h                       
  INR H                        
  RLC                          
  DCX D                        
  MOV E,E                      
  STC                          
  MOV L,L                      
  DB 20h                       
  MOV D,H                      
  MOV C,B                      
  MOV B,L                      
  DB 20h                       
  MOV B,A                      
  MOV B,C                      
  MOV C,L                      
  MOV B,L                      
  DB 20h                       
  MOV C,C                      
  MOV D,E                      
  DB 20h                       
  MOV C,A                      
  MOV D,M                      
  MOV B,L                      
  MOV D,D                      
  LXI H, 2021h                 
  DCX D                        
  MOV E,E                      
  DB 30h                       
  MOV L,L                      
  DCR C                        
  LDAX B                       
  RLC                          
  INR H                        
  MOV D,A                      
  MOV L,A                      
  MOV M,D                      
  MOV L,L                      
  DB 20h                       
  MOV M,E                      
  MOV L,C                      
  MOV A,D                      
  MOV H,L                      
  LDA 2420h                    
  LHLD 2A2Ah                   
  DB 20h                       
  MOV B,M                      
  MOV B,L                      
  MOV C,B                      
  MOV C,H                      
  MOV B,L                      
  MOV D,D                      
  DB 20h                       
  LHLD 2A2Ah                   
  INR H                        
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  NOP                          
  MOV D,A                      
  MOV C,A                      
  MOV D,D                      
  MOV C,L                      
  DB 20h                       
  MOV L,C                      
  MOV M,E                      
  DB 20h                       
  MOV H,C                      
  DB 20h                       
  MOV H,A                      
  MOV H,C                      
  MOV L,L                      
  MOV H,L                      
  DB 20h                       
  MOV M,A                      
  MOV L,B                      
  MOV H,L                      
  MOV M,D                      
  MOV H,L                      
  DB 20h                       
  MOV H,C                      
  DB 20h                       
  MOV L,H                      
  MOV H,L                      
  MOV M,H                      
  MOV M,H                      
  MOV H,L                      
  MOV M,D                      
  DB 20h                       
  MOV M,A                      
  MOV L,A                      
  MOV M,D                      
  MOV L,L                      
  DB 20h                       
  MOV L,C                      
  MOV M,E                      
  DB 20h                       
  MOV L,L                      
  MOV L,A                      
  HLT                          
  MOV H,L                      
  MOV H,H                      
  DB 20h                       
  MOV H,C                      
  MOV H,E                      
  MOV M,D                      
  MOV L,A                      
  MOV M,E                      
  MOV M,E                      
  DB 20h                       
  MOV M,H                      
  MOV L,B                      
  MOV H,L                      
  DB 20h                       
  MOV M,B                      
  MOV L,H                      
  MOV H,C                      
  MOV A,C                      
  MOV L,C                      
  MOV L,M                      
  MOV H,A                      
  DB 20h                       
  MOV M,L                      
  MOV M,E                      
  MOV L,C                      
  MOV L,M                      
  MOV H,A                      
  DB 20h                       
  MOV M,H                      

; (truncated - remaining bytes are runtime zero buffer, never in the .COM)
