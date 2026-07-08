#include<strings.h>
enum { 
    int_num = 1 , 
    blob_num , 
    string_num , 
    null , 
    integer_op   , 
    begin_op , 
    next_op , 
    print_op , 
    halt  , 
    blob_op , 
    string_op , 
    null_op , 
    real_op ,
     real_num , 
     add_op , 
     subs_op , 
     mul_op , 
     divide_op
}



typedef struct type{
    int operand ; 
    int p1 ; 
    int p2 ; 
    int p3 
    void * p4 ; 
    int p4_type ; 
} ; 


typedef struct reg{
    int type ; 
    int lenght ; 
    union{
        long i ; 
        char *s ; 
        float r ; 
    }val ; 
}


typedef struct byte{
    type prog[300] ; 
    int prog_count ; 
    int ins_count ; 
    reg regis[300] ; 
}


void write(byte *byt , int op , int p1 , int p2 , int p3 , void *p4){
    byt->prog[byt->ins_count].operand = op ; 
    byt->prog[byt->ins_count].p1 = p1 ; 
    byt->prog[byt->ins_count].p2 = p2 ; 
    byt->prog[byt->ins_count].p3 = p3 ; 
    byt->prog[byt->ins_count].p4 = p4 ; 
    byt->ins_count++ ; 
}


void bytcode(byte *byt){
    byt->prog_count = 0;
    while(1){
        type *op = &byt->prog[byt->prog_count];
        switch(op->operand){
            case begin_op:
                break;

            case goto_op:
                byt->pc = op->p2;
                continue;

            case halt:
                return;

            case integer_op:
                byt->regis[op->p2].type = int_num;
                byt->regis[op->p2].val.i = op->p1;
                break;

            case blob_op:
                byt->regis[op->p2].type = blob_num;
                byt->regis[op->p2].val.s = char*(op->p4);
                byt->regis[op->p2].lenght = op->p1;
                break;

            case string_op:
                byt->regis[op->p2].type = string_num;
                byt->regis[op->p2].lenght = op->p1;
                byt->regis[op->p2].val.s = char*(op->p4);
                break;


            case null_op:
                byt->regis[op->p2].type = null;
                break;

            case real_op:
                byt->regis[op->p2].type = real_num;
                byt->regis[op->p2].val.r = op->p1;
                break;

            case copy_op:
                byt->regis[op->p2].type = byt->regis[op->p1].type;
                byt->regis[op->p2].lenght = byt->regis[op->p1].lenght;

                if (byt->regis[op->p2].type == int_num){
                    byt->regis[op->p2].val.i = byt->regis[op->p1].val.i;
                }

                if (byt->regis[op->p2].type == real_op){
                    byt->regis[op->p2].val.r = byt->regis[op->p1].val.r;
                }

                if (byt->regis[op->p2].type == string_num || byt->regis[op->p2].type == blob_num){
                    byt->regis[op->p2].val.s = malloc(byt->regis[op->p2].lenght);
                    memcpy(byt->regis[op->p2].val.s, byt->regis[op->p1].val.s, byt->regis[op->p2].lenght);
                }
                break;

            case move_op:
                if (byt->regis[op->p1].type == string_num || byt->regis[op->p1].type == blob_num){
                    free(byt->regis[op->p1].val.s);
                }

                if (byt->regis[op->p1].type == integer_num || byt->regis[op->p1].type == real_num){
                    break;
                }

                byt->regis[op->p1].type = null;
                byt->regis[op->p2].val.s = byt->regis[op->p1].val.s;
                byt->regis[op->p1].val.s = NULL;
                break;



                
            case add_op:
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == integer_num  ){
                    byt->regis[op->p3].type = integer_num ;
                    byt->regis[op->p3].val.i  = byt->regis[op->p2].val.i + byt->regis[op->p1].val.i  ; 
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == real_num  ){
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p2].val.r + byt->regis[op->p1].val.r  ;   
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = float( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p2].val.r + num ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = float( byt->regis[op->p2].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = num+ byt->regis[op->p1].val.r   ;   
                }

                break ; 


            case subs_op:
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == integer_num  ){
                    byt->regis[op->p3].type = integer_num ; 
                    byt->regis[op->p3].val.i  = byt->regis[op->p1].val.i - byt->regis[op->p2].val.i  ; 
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == real_num  ){
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p1].val.r - byt->regis[op->p2].val.r  ;   
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = float( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = num - byt->regis[op->p2].val.r ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = float( byt->regis[op->p2].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p1].val.r - num ;    
                }

                break ; 



            case mul_op:
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == integer_num  ){
                    byt->regis[op->p3].type = integer_num ;
                    byt->regis[op->p3].val.i  = byt->regis[op->p2].val.i * byt->regis[op->p1].val.i  ; 
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == real_num  ){
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p2].val.r * byt->regis[op->p1].val.r  ;   
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = float( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p2].val.r * num ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = float( byt->regis[op->p2].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = num *  byt->regis[op->p1].val.r   ;   
                }
                break ; 
            

            case divide_op:
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == integer_num  ){
                    byt->regis[op->p3].type = integer_num ; 
                    byt->regis[op->p3].val.i  = byt->regis[op->p1].val.i  / byt->regis[op->p2].val.i  ; 
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == real_num  ){
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p1].val.r  / byt->regis[op->p2].val.r  ;   
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = float( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = num  /  byt->regis[op->p2].val.r ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = float( byt->regis[op->p2].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p1].val.r / num ;    
                }
                break ; 
            




            case gt_op : 
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p3].type == integer_num  ){
                    if (byt->regis[op->p1].val.i < byt->regis[op->p3].val.i ){
                        byt->pc = op->p2;
                    }
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == real_num  ){
                    if (byt->regis[op->p1].val.r < byt->regis[op->p3].val.r ){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = float( byt->regis[op->p1].val.i ) ; 
                    if (num <  byt->regis[op->p3].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = float( byt->regis[op->p3].val.i ) ; 
                    if (num >  byt->regis[op->p1].val.r){
                        byt->pc = op->p2;
                    }
                }
                else if (byt->regis[op->p1].type == string_num && byt->regis[op->p3].type == string_num ){
                    if (strcmp(op->p4 , "BINARY") == 0 ){
                        if (strcmp(byt->regis[op->p1].val.s ,byt->regis[op->p3].val.s ) == 0 ){
                            byt->pc = op->p2;
                        }
                    }
                    else  if (strcmp(op->p4 , "NOCASE") == 0 ){
                        if (strcasecmp(byt->regis[op->p1].val.s ,byt->regis[op->p3].val.s ) == 0 ){
                            byt->pc = op->p2;
                        }
                    }
                    else if (strcmp(op->p4 , "RTRIM") == 0 ){
                        
                    }
                }



        }
    }
}
