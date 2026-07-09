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
     divide_op , 
     eq_op , 
     ne_op , 
     gt_op
     lt_op , 
     le_op , 
     ge_op , 
     cursor_read , 
     cursor_write  , 
     open_write_op , 
     open_read_op
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

typedef struct btree{
    table * Table ; 
    uint32_t start_root_num ; 
    uint32_t page_num ; 
    uint32_t row_num ; 
    bool end ; 
    int mode ; 
}


typedef struct byte{
    type prog[300] ; 
    int prog_count ; 
    int ins_count ; 
    reg regis[300] ; 
    btree btr[300] ; 
    table *db ; 
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
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p2].val.r + num ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p2].val.i ) ; 
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
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = num - byt->regis[op->p2].val.r ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p2].val.i ) ; 
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
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p2].val.r * num ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p2].val.i ) ; 
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
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = num  /  byt->regis[op->p2].val.r ;   
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p2].val.i ) ; 
                    byt->regis[op->p3].type = real_num ; 
                    byt->regis[op->p3].val.r  = byt->regis[op->p1].val.r / num ;    
                }
                break ; 
            




            case eq_op : 
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p3].type == integer_num  ){
                    if (byt->regis[op->p1].val.i == byt->regis[op->p3].val.i ){
                        byt->pc = op->p2;
                    }
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == real_num  ){
                    if (byt->regis[op->p1].val.r == byt->regis[op->p3].val.r ){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    if (num ==  byt->regis[op->p3].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p3].val.i ) ; 
                    if (num ==  byt->regis[op->p1].val.r){
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
                        int num ; 
                        int max_num ; 
                        char * temp ; 
                        if (byt->regis[op->p3].lenght < byt->regis[op->p1].lenght){
                            num = byt->regis[op->p3].lenght  ; 
                            max = byt->regis[op->p1].lenght  ; 
                            temp = ,byt->regis[op->p3].val.s   ; 
                        }
                        else { 
                            num = byt->regis[op->p1].lenght   ; 
                            max = byt->regis[op->p3].lenght  ; 
                            temp = ,byt->regis[op->p1].val.s   ; 
                        }
                        int take = 0 ; 
                        for ( int i = 0 ; i < num ; i++ ){
                            if (byt->regis[op->p1].val.s[i] == byt->regis[op->p3].val.s[i] ){
                                continue ; 
                            }
                            else { 
                                take = 1 ; 
                                break ; 
                            }
                        }
                        if ( take == 1 ){
                            break ; 
                        }
                        else { 
                        if (num < max_num ){
                        for ( int i = num ; i < max_num ; i++ ){
                            if (temp[i] == ' '){
                                continue ; 
                            }
                            else { 
                                take = 1 ; 
                                break ; 
                            }
                        }
                        }
                      }
                        if ( take == 0 ){
                            byt->pc = op->p2;
                        }
                    }
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
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    if (num <  byt->regis[op->p3].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p3].val.i ) ; 
                    if (num <  byt->regis[op->p1].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == string_num && byt->regis[op->p3].type == string_num ){
                    if (strcmp(op->p4 , "BINARY") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i] ; 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)byt->regis[op->p3].val.s[j] ;        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 > num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }                
                    
                    else if (strcmp(op->p4 , "NOCASE") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)to_lowercase(byt->regis[op->p1].val.s[i]); 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)to_lowercase(byt->regis[op->p3].val.s[i]);        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 > num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }

                    else if (strcmp(op->p4 , "RTRIM") == 0){
                        int len_1  = byt->regis[op->p1].lenght -  1   ; 
                        while( len_1 >= 0 && byt->regis[op->p1].val.s[len_1] == ' '){
                            len_1-- ; 
                        }
                        len_1++ ; 

                        int len_2  = byt->regis[op->p3].lenght - 1   ; 
                        while( len_2 >= 0 && byt->regis[op->p3].val.s[len_2] == ' '){
                            len_2-- ; 
                        }
                        len_2++ ; 

                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < len_1 ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i]; 
                                 i++ ; 
                            } 
                            if ( j < len_2  ){
                                num_2 = num_2 + (int)byt->regis[op->p3].val.s[i]; 
                                 j++ ;  
                            }      
                            if ( i >= len_1 &&  j >= len_2  ) {
                                break ; 
                            }
                        }
                        if (num_2 > num_1){
                            byt->pc = op->p2;
                        }
                        break ; 

                    }


                }
                break ; 







            case lt_op : 
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p3].type == integer_num  ){
                    if (byt->regis[op->p1].val.i > byt->regis[op->p3].val.i ){
                        byt->pc = op->p2;
                    }
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == real_num  ){
                    if (byt->regis[op->p1].val.r > byt->regis[op->p3].val.r ){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    if (num >  byt->regis[op->p3].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p3].val.i ) ; 
                    if (num > byt->regis[op->p1].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == string_num && byt->regis[op->p3].type == string_num ){
                    if (strcmp(op->p4 , "BINARY") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i] ; 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)byt->regis[op->p3].val.s[j] ;        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 < num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }                
                    
                    else if (strcmp(op->p4 , "NOCASE") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)to_lowercase(byt->regis[op->p1].val.s[i]); 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)to_lowercase(byt->regis[op->p3].val.s[i]);        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 < num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }

                    else if (strcmp(op->p4 , "RTRIM") == 0){
                        int len_1  = byt->regis[op->p1].lenght -  1   ; 
                        while( len_1 >= 0 && byt->regis[op->p1].val.s[len_1] == ' '){
                            len_1-- ; 
                        }
                        len_1++ ; 

                        int len_2  = byt->regis[op->p3].lenght - 1   ; 
                        while( len_2 >= 0 && byt->regis[op->p3].val.s[len_2] == ' '){
                            len_2-- ; 
                        }
                        len_2++ ; 

                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < len_1 ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i]; 
                                 i++ ; 
                            } 
                            if ( j < len_2  ){
                                num_2 = num_2 + (int)byt->regis[op->p3].val.s[i]; 
                                 j++ ;  
                            }      
                            if ( i >= len_1 &&  j >= len_2  ) {
                                break ; 
                            }
                        }
                        if (num_2  < num_1){
                            byt->pc = op->p2;
                        }
                        break ; 

                    }


                }
                break ; 




            case le_op : 
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p3].type == integer_num  ){
                    if (byt->regis[op->p1].val.i >= byt->regis[op->p3].val.i ){
                        byt->pc = op->p2;
                    }
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == real_num  ){
                    if (byt->regis[op->p1].val.r >= byt->regis[op->p3].val.r ){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    if (num >=  byt->regis[op->p3].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p3].val.i ) ; 
                    if (num >= byt->regis[op->p1].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == string_num && byt->regis[op->p3].type == string_num ){
                    if (strcmp(op->p4 , "BINARY") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i] ; 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)byt->regis[op->p3].val.s[j] ;        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 <= num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }                
                    
                    else if (strcmp(op->p4 , "NOCASE") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)to_lowercase(byt->regis[op->p1].val.s[i]); 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)to_lowercase(byt->regis[op->p3].val.s[i]);        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 <= num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }

                    else if (strcmp(op->p4 , "RTRIM") == 0){
                        int len_1  = byt->regis[op->p1].lenght -  1   ; 
                        while( len_1 >= 0 && byt->regis[op->p1].val.s[len_1] == ' '){
                            len_1-- ; 
                        }
                        len_1++ ; 

                        int len_2  = byt->regis[op->p3].lenght - 1   ; 
                        while( len_2 >= 0 && byt->regis[op->p3].val.s[len_2] == ' '){
                            len_2-- ; 
                        }
                        len_2++ ; 

                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < len_1 ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i]; 
                                 i++ ; 
                            } 
                            if ( j < len_2  ){
                                num_2 = num_2 + (int)byt->regis[op->p3].val.s[i]; 
                                 j++ ;  
                            }      
                            if ( i >= len_1 &&  j >= len_2  ) {
                                break ; 
                            }
                        }
                        if (num_2  <= num_1){
                            byt->pc = op->p2;
                        }
                        break ; 

                    }


                }
                break ; 






            case ge_op : 
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p3].type == integer_num  ){
                    if (byt->regis[op->p1].val.i <= byt->regis[op->p3].val.i ){
                        byt->pc = op->p2;
                    }
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == real_num  ){
                    if (byt->regis[op->p1].val.r <= byt->regis[op->p3].val.r ){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    if (num <= byt->regis[op->p3].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p3].val.i ) ; 
                    if (num <=  byt->regis[op->p1].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == string_num && byt->regis[op->p3].type == string_num ){
                    if (strcmp(op->p4 , "BINARY") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i] ; 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)byt->regis[op->p3].val.s[j] ;        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 >= num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }                
                    
                    else if (strcmp(op->p4 , "NOCASE") == 0 ){
                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < byt->regis[op->p1].lenght ){
                                num_1 = num_1 + (int)to_lowercase(byt->regis[op->p1].val.s[i]); 
                                 i++ ; 
                            } 
                            if ( j < byt->regis[op->p3].lenght  ){
                                 num_2 = num_2 + (int)to_lowercase(byt->regis[op->p3].val.s[i]);        
                                 j++ ;  
                            }      
                            if ( i >= byt->regis[op->p1].lenght &&  j >= byt->regis[op->p3].lenght  ) {
                                break ; 
                            }
                        }
                        if (num_2 >= num_1){
                            byt->pc = op->p2;
                        }
                        break ; 
                    }

                    else if (strcmp(op->p4 , "RTRIM") == 0){
                        int len_1  = byt->regis[op->p1].lenght -  1   ; 
                        while( len_1 >= 0 && byt->regis[op->p1].val.s[len_1] == ' '){
                            len_1-- ; 
                        }
                        len_1++ ; 

                        int len_2  = byt->regis[op->p3].lenght - 1   ; 
                        while( len_2 >= 0 && byt->regis[op->p3].val.s[len_2] == ' '){
                            len_2-- ; 
                        }
                        len_2++ ; 

                        int num_1 = 0 ; 
                        int num_2 = 0 ;
                        int i = 0 ; 
                        int j = 0  ; 
                        while (  num_1 == num_2  ) {
                            if (i < len_1 ){
                                num_1 = num_1 + (int)byt->regis[op->p1].val.s[i]; 
                                 i++ ; 
                            } 
                            if ( j < len_2  ){
                                num_2 = num_2 + (int)byt->regis[op->p3].val.s[i]; 
                                 j++ ;  
                            }      
                            if ( i >= len_1 &&  j >= len_2  ) {
                                break ; 
                            }
                        }
                        if (num_2 >= num_1){
                            byt->pc = op->p2;
                        }
                        break ; 

                    }


                }
                break ; 



            case ne_op : 
                if ( byt->regis[op->p1].type == integer_num && byt->regis[op->p3].type == integer_num  ){
                    if (byt->regis[op->p1].val.i != byt->regis[op->p3].val.i ){
                        byt->pc = op->p2;
                    }
                }
                else if ( byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == real_num  ){
                    if (byt->regis[op->p1].val.r != byt->regis[op->p3].val.r ){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p3].type == real_num && byt->regis[op->p1].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p1].val.i ) ; 
                    if (num !=  byt->regis[op->p3].val.r){
                        byt->pc = op->p2;
                    }
                }

                else if (byt->regis[op->p1].type == real_num && byt->regis[op->p3].type == integer_num   ){
                    float num  = (float)( byt->regis[op->p3].val.i ) ; 
                    if (num !=  byt->regis[op->p1].val.r){
                        byt->pc = op->p2;
                    }
                }
                else if (byt->regis[op->p1].type == string_num && byt->regis[op->p3].type == string_num ){
                    if (strcmp(op->p4 , "BINARY") == 0 ){
                        if (strcmp(byt->regis[op->p1].val.s ,byt->regis[op->p3].val.s ) != 0 ){
                            byt->pc = op->p2;
                        }
                    }
                    else  if (strcmp(op->p4 , "NOCASE") == 0 ){
                        if (strcasecmp(byt->regis[op->p1].val.s ,byt->regis[op->p3].val.s ) != 0 ){
                            byt->pc = op->p2;
                        }
                    }
                    else if (strcmp(op->p4 , "RTRIM") == 0 ){
                        int num ; 
                        int max_num ; 
                        char * temp ; 
                        if (byt->regis[op->p3].lenght < byt->regis[op->p1].lenght){
                            num = byt->regis[op->p3].lenght  ; 
                            max = byt->regis[op->p1].lenght  ; 
                            temp = byt->regis[op->p3].val.s   ; 
                        }
                        else { 
                            num = byt->regis[op->p1].lenght   ; 
                            max = byt->regis[op->p3].lenght  ; 
                            temp = byt->regis[op->p1].val.s   ; 
                        }
                        int take = 0 ; 
                        for ( int i = 0 ; i < num ; i++ ){
                            if (byt->regis[op->p1].val.s[i] != byt->regis[op->p3].val.s[i] ){
                                continue ; 
                            }
                            else { 
                                take = 1 ; 
                                break ; 
                            }
                        }
                        if ( take == 1 ){
                            break ; 
                        }
                        else { 
                            if ( num < max_num ){
                                for ( int i = num ; i < max_num ; i++ ){
                                    if (temp[i] == ' '){
                                        take = 1  ; 
                                    }
                                    else { 
                                        take = 0 ; 
                                        break ; 
                                    }
                                }
                                }
                          }
                        if ( take == 0 ){
                            byt->pc = op->p2;
                        }
                    }
                }
                break ; 

            case open_read_op : 
                byt->btr[op->p1].Table  = lookup_table(db , op->p2) ; 
                byt->btr[op->p1].start_root_num  =  op->p2 ;
                byt->btr[op->p1].page_num  =  op->p2 ;
                byt->btr[op->p1].mode  = cursor_read ; 
                end = false ; 
            
                
            case open_write_op
                byt->btr[op->p1].Table  = lookup_table(db , op->p2) ; 
                byt->btr[op->p1].start_root_num  =  op->p2 ;
                byt->btr[op->p1].page_num  =  op->p2 ;
                byt->btr[op->p1].mode  = cursor_write ; 
                end = false ; 
            
            

            
                



        }
    }
}







