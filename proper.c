typedef struct Tree_def {
    char* comp; 
    struct Tree* left;
    struct Tree* right;
    struct Tree** children;   
    char* as  ; 
    char **direction  ; 
    int child_count;
	int line;                 
    int col;
    int num  ; 
} Tree_def;


struct Tree_def tree  ; 

tree* createNode( char* comp) {
    tree* node = malloc(sizeof(tree));
    if( comp != NULL  ){
    node->value = strdup(comp) ; 
    }
    node->as = NULL ; 
    node->left = NULL;
    node->right = NULL;
    node->children = NULL;
    node->direction = NULL ;  
    node->child_count = 0;
    node->num = 0  ; 
    return node;
}


char *SQL_functions[] = {
  "COUNT", "SUM", "AVG", "MIN", "MAX", "STDDEV", "VARIANCE",
  "UPPER", "LOWER", "LENGTH", "TRIM", "LTRIM", "RTRIM", "SUBSTRING", "REPLACE",
  "CONCAT", "CONCAT_WS", "INSTR", "LEFT", "RIGHT", "LPAD", "RPAD", "REVERSE",
  "REPEAT", "SPACE", "ASCII", "CHAR", "CHARINDEX", "POSITION", "STRCMP",
  "NOW", "CURDATE", "CURTIME", "DATE", "TIME", "YEAR", "MONTH", "DAY",
  "HOUR", "MINUTE", "SECOND", "DATEDIFF", "DATEADD", "DATE_ADD", "DATE_SUB",
  "DATE_FORMAT", "STR_TO_DATE", "TIMESTAMPDIFF", "EXTRACT", "AGE",
  "TO_DATE", "TO_TIMESTAMP",
  "ABS", "CEIL", "FLOOR", "ROUND", "TRUNCATE", "MOD", "POWER", "SQRT",
  "EXP", "LOG", "LOG2", "LOG10", "PI", "RAND", "SIGN", "GREATEST", "LEAST",
  "IF", "IIF", "COALESCE", "NULLIF", "ISNULL", "IFNULL", "NVL",
  "CAST", "CONVERT", "TO_CHAR", "TO_NUMBER",
  "ROW_NUMBER", "RANK", "DENSE_RANK", "NTILE", "LAG", "LEAD",
  "FIRST_VALUE", "LAST_VALUE", "NTH_VALUE", "CUME_DIST", "PERCENT_RANK",
  "JSON_EXTRACT", "JSON_OBJECT", "JSON_ARRAY", "JSON_SET", "JSON_REMOVE",
  "JSON_CONTAINS", "JSON_LENGTH",
  NULL
};


bool if_function( char* word ){
	for ( int i = 0 ; SQL_functions[i] != NULL ; i++  ){
	if (strcmp( word , SQL_functions[i]  ) == 0 ){
		return true ; 
	}  ; 
	}	
	return false ; 
}

Tree_def* make_leaf(char* value , int row , int col ) {
    Tree_def* n = malloc(sizeof(Tree_def));
    n->comp = strdup(value);
    n->as = NULL;
    n->left = NULL  ;  
    n->right = NULL;
    n->children = NULL;
    n->direction = NULL ; 
    n->child_count = 0 ; 
    n->line = row ; 
    n->col = col;
    return n;
}





int priority(char *string){
    if ( strcmp("CASE" , string ) == 0 ||  strcmp("ON" , string ) == 0   ){
        return 1 ; 
    }
    else if (strcmp("OR" , string ) == 0  ){
        return 2 ; 
    }
    else if (strcmp("AND" , string ) == 0  ){
        return 3 ; 
    }
    else if (strcmp("NOT" , string ) == 0  ){
        return 4 ; 
    }
    else if ( strcmp("BETWEEN" , string ) == 0  || strcmp("IN" , string ) == 0  || strcmp("LIKE" , string ) == 0  || strcmp("IS NULL" , string ) == 0  ||strcmp("EXISTS" , string ) == 0 ){
        return 5 ; 
    }

    else if (  strcmp("=" , string ) == 0  || strcmp("!=" , string ) == 0  || strcmp("<>" , string ) == 0  || strcmp(">" , string ) == 0  || strcmp("<" , string ) == 0  || strcmp(">=" , string ) == 0  || strcmp("<=" , string ) == 0  ){
        return 6 ; 
    }
    else if (strcmp("||" , string ) == 0   ){
        return 7 ; 
    }
    else if ( strcmp("+" , string ) == 0   || strcmp("-" , string ) == 0  ){
        return 8 ; 
    }
    else if (strcmp("*" , string ) == 0   || strcmp("/" , string ) == 0  || strcmp("%" , string ) == 0   ) {
        return 9 ; 
    }
    return 0  ; 
}







tree* expression(char **buf , tree * node , int i , int j  , int end_row , int end_col   , int pain ){
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
         start->right  = start ; 
    }
    return start ; 
}





tree *comp_1(char** buf , tree * node , int i , int j , int end_row , int end_col ){
    tree * start = node ; 
    if ( if_function( buf[i][j] ) == true ){
        node->children[node->num++] = function( buf , temp,  i ,  j ) ; 
    }

    else if ( buf[i][j] == '(' ){
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
                    node->children[node->num++] = select_query( i  , j , check ,  end_row_dec ,  end_col_dec  , 0  ) ; 
                    node = node->children[node->num -1 ] ; 
                    i = end_row_dec ; 
                    j = end_col_dec ; 
                }
                else {
                        status_msg_input("the query is wrong ") ; 
                            check = 1 ; 
                        return NULL  ; 
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
                        node->children[node->num++ ]  = expression(buf , node ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                    }
                    else  {
                        if (if_syntax(buf[i][j]) == false ){
                                if ( buf[i][j] == ','){
                                    node->num++ ; 
                                    continue ; 
                                }
                                node->children[node->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                            }
                            else { 
                                status_msg_input("the query is wrong ") ; 
                                check = 1 ; 
                                    return NULL ;   
                            }
                    }                    
            } 
    return start 

}









tree* select_query(int row  , int col , int check  , int end_row , int end_col  ){
        int compulsary = 3 ;  
        int compulsion = 0 ; 
        char * prev[300] ; 
        tree* start_of_tree ; 
        tree* nested ; 
        char **buf = proper_data.query ; 
        if ( check == 1 ){
            return NULL ; 
        }
        for ( int i = row ; i <= end_row  ; i++ ){
        for ( int j = col ; j <= end_col   ; j++ ){

            if ( i == row && j == col ){
              tree* node =  createNode(buf[0]) ; 
              start_of_tree = node ; 
              prev = buf[0] ;
              compulsion++ ;  
              prev = 'SELECT' ; 
              continue ; 
            }

            else if ( buf[i][j] == ';'){
                if ( compulsion < compulsary){
                        status_msg_input("the query is wrong ") ; 
                        check = 1 ; 
                        return NULL  ;   
                }
                return node   ; 
            }

            else if ( buf[i][j] == ')' && !if_function(prev)) {
                if (buf[i][j+1] != NULL  ){
                    if ( buf[i][j+1] == 'AS' && j+1 <= end_col ){
                        if ( buf[i][j+2] == NULL && j+2 <= end_col ){
                            status_msg_input("the query is wrong ") ; 
                            return NULL ; 
                        }
                        if ( nested != NULL ){
                        nested->as = buf[i][j+2] ; 
                        }
                    }
                }
                if ( i == end_row && j == end_col ){
                    return start_of_tree ; 
                }
            }




            else if (compulsion == 1){
                    if (  strstr('FROM' , buf[i][j]) == 0  ) {
                        compulsion++ ; 
                        node->children[node->num++]= createNode(buf[i][j]) ; 
                        node = node->children[node->num- 1 ] ;  
                        continue ; 
                    }
                    else {
                        node->children[node->num++] = comp_1(buf , node , i , j , end_row , end_col) ; 
                    }

            }














;;;











