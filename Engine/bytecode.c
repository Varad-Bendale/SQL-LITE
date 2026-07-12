#include<strings.h>
define PAGE_SIZE 4096
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

typedef struct Pager{
    FILE *file ; 
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

typedef struct path_entry{
    uint32_t page_num     ; 
    uint16_t  cell_index     ; 
}


typedef struct btree{
    table * Table ; 
    uint32_t start_root_num ; 
    uint32_t page_num ; 
    uint32_t row_num ; 
    bool start ; 
    bool end ; 
    int total ; 
    int mode ; 
    int depth ; 
    path_entry stack[300] ; 
}

typedef struct byte{
    type prog[300] ; 
    int prog_count ; 
    int ins_count ; 
    reg regis[300] ; 
    btree btr[300] ; 
    table *db ; 
    Pager *pager ; 
}

typedef struct page_header{
    uint8_t page_type ; 
    uint16_t free_space ; 
    uint16_t num_cells  ; 
}__attribute__((packed)) 




void *pager_get_page(Pager *pager, uint32_t page_num) {
    void *buf = malloc(PAGE_SIZE);
    fseek(pager->file, page_num * PAGE_SIZE, SEEK_SET);
    fread(buf, 1, PAGE_SIZE, pager->file);
    return buf;
}




uint32_t get_child_pointer(Pager * pager ,uint32_t page_num , uint16_t cell_index ){
    uint8_t *raw = pager_get_page(pager , page_num ) ; 
    uint16_t *cell_offset = sizeof(page_header) + ( cell_index * CELL_SIZE ) ; 
    uint32_t *addr  ; 
    memcpy(addr ,raw + cell_offset , sizeof(uint32_t) ) ; 
    return addr ; 
}

void *get_cell(void *node, uint32_t cell_num) {
    char *base = (char*)node;              
    return base + sizeof(page_header) + (cell_num * CELL_SIZE);
}

int data_type(void * addr){

}


int campare(reg target , void * cell_key ){
    int type = data_type(void * cell_key) ; 
   if (reg->type == integer_num){
        if (type == 1 ){
            uint32_t num = *(uint32_t*)cell_key ; 
            if (num >= reg->val.i){
                return 0 ; 
            }
        }
        if (type == 2 ){
            float num = *(float*)cell_key ; 
            int num_temp = int(num) ; 
            if (num_temp >= reg->val.r){
                return 0 ; 
            }
        }
    }
    else if ( reg->type == real_num ){
        if (type == 1 ){
            uint32_t num_temp = *(uint32_t*)cell_key ; 
            float num = (float)num_temp ; 
            if (num >= reg->val.i){
                return 0 ; 
            }
        }
        if (type == 2 ){
            float num = *(float*)cell_key ; 
            if (num >= reg->val.r){
                return 0 ; 
            }
        }
    }
    else { 
        if (type == 3 ){
            
        }
    }
}


int bs( void * node , reg target  ){
    int low = 0 ; 
    int high = node->num_cells - 1 ; 
    int cmp = -1  ;
    bool found = false;  
    while ( low <= high ){
        int mid = ( low + high )/ 2 ; 
        void * cell = get_cell(node , mid ) ; 
        reg cell_key = get_key_from_cell(cell);
        cmp = campare(target , cell_key ) ; 
        if ( cmp == 0  ){
            found = true ; 
            break ; 
        }
        else if (cmp < 0 ){
            high = mid -1 ; 
        }
        else { 
            low = mid + 1 ; 
        }
    }
    if ( found == true ){
        return 1 ; 
    }
    return 0 ; 
    

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
            
            case close_cursor_op : 
                if (byt->btr[op->p1] ==  NULL){
                    free(byt->btr[op->p1]) ; 
                    byt->btr[op->p1] =  NULL
                }
            
            case next_cursor : 
                 path_entry * ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                page_header *hdr = pager_get_page(byt->pager , ptr->page_num ) ; 
                 if (byt->btr[op->p1].end == true ){
                    break ; 
                 }
                if (ptr->cell_index + 1 < hdr->num_cells ){
                    byt->btr[op->p1].row_num++ ; 
                    byt->btr[op->p1].page_num = ptr->page_num ; 
                    ptr->cell_index++ ; 
                    break ; 
                }
                int kept = 0 ; 
                byt->btr[op->p1].depth = byt->btr[op->p1].depth - 1  ; 
                while ( byt->btr[op->p1].depth > 0 ){
                    ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                    hdr = pager_get_page(byt->pager , ptr->cell_index) ; 
                    if (ptr->cell_index + 1 < hdr->num_cells ){
                            ptr->cell_index++ ; 
                            uint32_t children = get_child_pointer(byt->pager , ptr->page_num ,ptr->cell_index ) ; 
                            page_header chdr = (page_header*)pager_get_page(pager,children  ) ; 
                                while ( chdr->page_type != LEAF ){
                                    byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , 0 } ; 
                                    children = get_child_pointer(byt->pager , ptr->page_num  ,0 )  ; 
                                    chdr = (page_header*)pager_get_page(pager,children  ) ; 
                                }
                            byt->btr[op->p1].stack[byt->btr[op->p1].depth++]  = (path_entry){children , 0 } ; 
                            byt->btr[op->p1].page_num = children ; 
                            byt->btr[op->p1].row_num++ ;  
                            kept = 1 ; 
                            break ; 
                    }
                    byt->btr[op->p1].depth-- ; 
                }
                if (kept == 1 ){
                    break ; 
                }
                byt->btr[op->p1].end  = true ; 
                break ; 



            case prev_cursor : 
                 path_entry * ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                page_header *hdr = pager_get_page(byt->pager , ptr->page_num ) ; 
                if (byt->btr[op->p1].start == true ){
                    break ; 
                 }
                if (ptr->cell_index > 0 ){
                    byt->btr[op->p1].row_num-- ; 
                    byt->btr[op->p1].page_num = ptr->page_num ; 
                    ptr->cell_index-- ; 
                    break ; 
                }                  
                int kept = 0 ; 
                byt->btr[op->p1].depth = byt->btr[op->p1].depth - 1  ; 
                while (byt->btr[op->p1].depth  > 0 ){
                    hdr = pager_get_page(byt->pager , byt->btr[op->p1].page_num) ; 
                    ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                    if (ptr->cell_index > 0 ){
                        ptr->cell_index-- ; 
                        uint32_t children = get_child_pointer(byt->pager , ptr->page_num ,ptr->cell_index ) ; 
                        page_header *chdr = (page_header*)pager_get_page(pager,children  ) ; 
                            while ( chdr->page_type != LEAF ){  
                                byt->btr[op->p1].stack[byt->btr[op->p1].depth++]  = (path_entry){children ,chdr->num_cells - 1 } ; 
                                children = get_child_pointer(byt->pager , children  ,chdr->num_cells - 1 )  ; 
                                chdr = (page_header*)pager_get_page(pager,children  ) ; 
                            }
                            byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , chdr->num_cells - 1   } ; 
                            byt->btr[op->p1].page_num = children ; 
                            byt->btr[op->p1].row_num-- ;  
                            kept = 1 ; 
                            break ; 
                    }
                    byt->btr[op->p1].depth-- ; 
                }
                if (kept == 1 ){
                    break ; 
                }
                byt->btr[op->p1].start = true 
                
                break ; 


            case rewind_cursor : 
                byt->btr[op->p1].depth = 0 ; 
                uint32_t children = byt->btr[op->p1].start_root_num   ; 
                page_header *hdr = pager_get_page(byt->pager , children) ; 
                byt->btr[op->p1].stack[byt->btr[op->p1].depth] = (path_entry){children  , 0 } ; 
                while ( hdr->page_type != LEAF ){
                     children = get_child_pointer(byt->pager , children  ,0 )  ; 
                    hdr = (page_header*)pager_get_page(byte->pager,children  ) ; 
                    byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , 0 } ; 
                }
                byt->btr[op->p1].page_num = children ; 
                byt->btr[op->p1].row_num = 0 ; 
                break ; 

            
            case cursor_end : 
                byt->btr[op->p1].depth = 0 ; 
                uint32_t children = byt->btr[op->p1].start_root_num   ; 
                page_header *hdr = pager_get_page(byt->pager , children) ; 
                byt->btr[op->p1].stack[byt->btr[op->p1].depth] = (path_entry){children  , hdr->num_cells-1 } ; 
                while ( hdr->page_type != LEAF ){
                     children = get_child_pointer(byt->pager , children  ,hdr->num_cells-1  )  ; 
                    hdr = (page_header*)pager_get_page(byte->pager,children  ) ; 
                    byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , hdr->num_cells-1  } ; 
                }
                byt->btr[op->p1].page_num = children ; 
                byt->btr[op->p1].row_num = byt->btr[op->p1].total - 1   ; 
                break ; 

            case seek_ge : 
                int size = 0 ; 
                byt->btr[op->p1].depth = 0 ; 
                uint32_t children = byt->btr[op->p1].start_root_num   ; 
                page_header *hdr = pager_get_page(byt->pager , children) ; 
                byt->btr[op->p1].stack[byt->btr[op->p1].depth] = (path_entry){children  , 0 } ; 
                while ( hdr->page_type != LEAF ){
                     children = get_child_pointer(byt->pager , children  ,0 )  ; 
                    hdr = (page_header*)pager_get_page(byte->pager,children  ) ; 
                    size = size + hdr->num_cells ; 
                    byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , 0 } ; 
                }
                int tot = byt->btr[op->p1].total - 1 
                while ( size < tot  ){
                    if(bs(hdr ,byt->regis[op->p3]  ) == 1 ){
                        byt->pc = op->p2;
                        break ; 
                    }
                    int kept = 0 ; 
                    while ( byt->btr[op->p1].depth > 0 ){
                        path_entry * ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                        page_header * hdr = pager_get_page(byt->pager , ptr->cell_index) ; 
                        if (ptr->cell_index + 1 < hdr->num_cells ){
                                ptr->cell_index++ ; 
                                uint32_t children = get_child_pointer(byt->pager , ptr->page_num ,ptr->cell_index ) ; 
                                page_header *chdr = (page_header*)pager_get_page(pager,children  ) ; 
                                    while ( chdr->page_type != LEAF ){
                                        byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , 0 } ; 
                                        children = get_child_pointer(byt->pager , ptr->page_num  ,0 )  ; 
                                        chdr = (page_header*)pager_get_page(pager,children  ) ; 
                                    }
                                byt->btr[op->p1].stack[byt->btr[op->p1].depth++]  = (path_entry){children , 0 } ; 
                                byt->btr[op->p1].page_num = children ; 
                                byt->btr[op->p1].row_num++ ;  
                                kept = 1 ; 
                                size = size + hdr->num_cells ; 
                                break ; 
                        }
                        byt->btr[op->p1].depth-- ; 
                    }
                    if (kept == 0 ){
                        break ; 
                    }
                }
                break ; 
      

                  
                


            case if_op : 
              reg * temp = &byt->regis[op->p1];
              int check = 0 ; 
                if (temp->type == integer_num ){
                    if (temp.val.i != 0 ){
                        check = 1 ; 
                    } 
                }
                else if (temp->type == real_num){
                    if (temp.val.r != 0.0 ){
                        check = 1 ; 
                    } 
                }
                else if(temp->type == string_num) {
                    if (temp->lenght > 0 ){
                        check = 1 ; 
                    }
                }
                if ( check == 1 ){
                    byt->pc = op->p2;
                }
                break ; 


            case if_not_op : 
              reg * temp = &byt->regis[op->p1];
              int check = 0 ; 
                if (temp->type == integer_num ){
                    if (temp.val.i == 0 ){
                        check = 1 ; 
                    } 
                }
                else if (temp->type == real_num){
                    if (temp.val.r == 0.0 ){
                        check = 1 ; 
                    } 
                }
                else if(temp->type == string_num) {
                    if (temp->lenght == 0 ){
                        check = 1 ; 
                    }
                }
                if ( check == 1 ){
                    byt->pc = op->p2;
                }
                break ; 

            



                    }
                }
                
        }




..