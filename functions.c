
tree* expression(char **buf , tree * node , int i , int j  , int end_row , int end_col ){
        char * operands[300] ; 
        int start_row =  i  ; 
        int start_col = j ; 
        char * operators[300] ; 
        int g_temp = 0 ; 
        char *string_temp; 
        tree *exp_tree = node ; 
        int operator_top = 0 ; 
        int operand_top = 0 ; 
        tree * prev_tree = NULL ; 
        int first = 0 ; 
        if ( priority(buf[i][j]) != 0  ){
        while ( buf[i][j] != ';'  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
            if ( priority(buf[i][j]) != 0  ){
                if (j+1 <=end_col &&  priority(buf[i][j+1]) != 0 ){
                    char concat_buf[600] ;       
                    strcpy(concat_buf, buf[i][j]) ;
                    strcat(concat_buf, buf[i][j+1]) ;
                    string_temp = concat_buf ;
                    top++ ;
                }
                else { 
                    string_temp = buf[i][j] ; 
                    top++ ; 
                }
                if  (first == 0 ){
                    if ( j-1 >= start_col  ){
                        operands[operand_top] = buf[i][j-1] ; 
                    }
                    else { 
                        if ( i >= end_row ){
                            int size = 0  ; 
                            for ( int k = 0 ; buf[i][k]!= NULL ; k++ ){
                                size++ ; 
                            }
                        operands[operand_top] = buf[i-1][size] ; 
                        }

                    }
                    operand_top++ ; 
                }
                if ( operator_top == 0 ){
                    operators[operator_top] = string_temp ; 
                }
                else { 
                    if  ( priority(string_temp) <= priority(operators[operator_top] ) ){
                    while ( priority(string_temp) <= priority(operators[operator_top]  )){
                        tree * new  = createNode(string_temp ) ; 
                        operator_top-- ; 
                        int pal = 0 ; 
                        while ( pal < 2 ){
                            if ( strcmp(operands[operand_top] ,  "varad") == 0  ){
                                new->right = prev_tree ; 
                            }
                            else { 
                                new->children[pal] = make_leaf(operands[operand_top] , i  ,  j ) ; 
                            }
                            pal++ ; 
                            operand_top-- ; 
                        }

                        exp_tree->right = new ; 
                        prev_tree = new ; 
                        operand_top++ ; 
                        operands[operand_top] = "varad" ; 
                    }
                    operator_top++ ; 
                    operators[operator_top] = string_temp ; 
                }
                    else  {
                        operator_top++ ; 
                        operators[operator_top] = string_temp ; 
                    }
                }
            }
            else { 
                operands[operand_top] = buf[i][j] ; 
                operand_top++ ; 
            }
            if ( buf[i][j] == NULL){
                if ( i +1 < end_row){
                i++ ; 
                }
                else { 
                    break ; 
                }
            }
            j++ ; 

        }
        while (operator_top > 0) {
            operator_top-- ; 
            char** new = createNode(operators[operator_top]);
            int pal = 0 ; 
                while ( pal < 2 ){
                    if ( strcmp(operands[operand_top] ,  "varad") == 0  ){
                        new->right = prev_tree ; 
                    }
                    else { 
                        new->children[pal] = make_leaf(operands[operand_top] , i  ,  j ) ; 
                    }
                    pal++ ; 
                    operand_top-- ; 
                }
            prev_tree = new ; 
            operand_top++ ; 
            operands[operand_top] = new_node;
        }
        
        if ( j-1 >= col ){
            j = j - 1 ;
        }
        return exp_tree ; 


    }
    return NULL ; 

}







tree *function( char **buf , tree * node , int i , int j ){
                        tree* temp = node ; 
                        tree *start = temp ; 
                        while ( temp->right != NULL){
                            temp = temp->right ; 
                        }
                        temp->right = createNode(buf[i][j]) ; 
                        if ( buf[i][j+1] != NULL ){
                            j++ ; 
                        }



                        while ( buf[i][j] != ')'){
                            if ( buf[i][j] == '(' ){
                                    if ( j-1 > col && strstr('SELECT' , buf[i][j-1]) == 0  ){
                                        int end_col_dec  = 0 ; 
                                        int end_row_dec  = 0 ; 
                                        int braces = 1 ; 
                                        for ( int m = i ; m <= end_row ; m++  ){
                                            for ( int n = j+1 ; n <= end_col ; n++  ){
                                                if ( buf[m][n] =='(' ){
                                                    braces++ ; 
                                                }
                                                else if ( buf[m][n] == ')'){
                                                    braces-- ; 
                                                }
                                                if ( braces == 0 ){
                                                    end_row_dec = m ; 
                                                    end_col_dec = n ; 
                                                    break ; 
                                                }
                                            }
                                        }
                                        temp->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                        temp = temp->left ; 
                                        i = end_row_dec ; 
                                        j = end_col_dec ; 
                                    }
                                    else {
                                        status_msg_input("the query is wrong ") ; 
                                        check = 1 ; 
                                        return NULL  ; 
                                    }
                            }
                        }


                        else { 
                                if ( priority(buf[i][j]) != 0  ){
                                    int temp_row = i ; 
                                    int temp_col = j ; 
                                    while ( buf[i][j] != ';'  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                    if ( buf[i][j] == NULL ){
                                        if ( i+ 1 <= end_row){
                                        i++ ; 
                                        j = 0 ; 
                                    }
                                    else { 
                                        j++ ; 
                                    }
                                    }
                                    }
                                    temp->left  = expression(buf , temp ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                                    
                                }
                                else  if ( temp->left == NULL ){
                                    if (if_syntax(buf[i][j]) == false ){
                                            if ( buf[i][j] == ','){
                                                node->num++ ; 
                                                continue ; 
                                            }
                                            node->children[node->num] = make_leaf( buf[i][j]  , i , j ) ; 
                                            node->num++ ; 
                                        }
                                        else { 
                                            status_msg_input("the query is wrong ") ; 
                                            check = 1 ; 
                                                return NULL ;   
                                        }
                                }                    
                        }
            node->right  = start ; 


}