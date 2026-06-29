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
    if ( strcmp("CASE" , string ) == 0 ){
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
                node->left = createNode(buf[i][j]) ; 
                node = node ->left ; 
                prev = 'FROM' ; 
                continue ; 
               }
     
                if ( if_function( buf[i][j] ) == true ){
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
                                            node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                            node = node->left ; 
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
                                        char * operands[300] ; 
                                        char * operators[300] ; 
                                        int g_temp = 0 ; 
                                        char *string_temp; 
                                        tree *exp_tree = node ; 
                                        int operator_top = 0 ; 
                                        int operand_top = 0 ; 
                                        tree * prev_tree = NULL ; 
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


                                        node->left = exp_tree ; 
                                        
                                        if ( j-1 >= col ){
                                            j = j - 1 ;
                                        }


                                    }
                                    else { 
                                        if (if_syntax(buf[i][j]) == false ){
                                                if ( buf[i][j] == ','){
                                                    node->num++ ; 
                                                    continue ; 
                                                }
                                                    operands[operand_top] = buf[i][j] ; 
                                                operand_top++ ; 
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


                        }
                        node->right  = start ; 
                        
                    }


                else {
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
                                node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                node = node->left ; 
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
                        if (if_syntax(buf[i][j]) == false ){
                        if ( buf[i][j] == ','){
                            node->num++ ; 
                            continue ; 
                        }
                        node->children[node->num] = make_leaf(buf[i][j] , i , j ) ; 
                        }
                        else { 
                            status_msg_input("the query is wrong ") ; 
                            check = 1 ; 
                                return NULL  ;   
                            }
                        }

                    }

                }











            else if ( compulsion == 2 ){
                if (  strstr('WHERE' , buf[i][j]) == 0  ) {
                    compulsion++ ; 
                    node->left = createNode(buf[i][j]) ; 
                    node = node->left ; 
                    prev = 'WHERE'  ; 
                    continue ; 
                }

                    if ( if_function( buf[i][j] ) == true ){
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
                                            node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                            node = node->left ; 
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
                                        char * operands[300] ; 
                                        char * operators[300] ; 
                                        int g_temp = 0 ; 
                                        char *string_temp; 
                                        tree *exp_tree = node ; 
                                        int operator_top = 0 ; 
                                        int operand_top = 0 ; 
                                        tree * prev_tree = NULL ; 
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


                                        node->left = exp_tree ; 
                                        
                                        if ( j-1 >= col ){
                                            j = j - 1 ;
                                        }


                                    }
                                    else { 
                                        if (if_syntax(buf[i][j]) == false ){
                                                if ( buf[i][j] == ','){
                                                    node->num++ ; 
                                                    continue ; 
                                                }
                                                    operands[operand_top] = buf[i][j] ; 
                                                operand_top++ ; 
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


                        }
                        node->right  = start ; 
                        
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
                        node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                        node = node->left ; 
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                            status_msg_input("the query is wrong ") ; 
                             check = 1 ; 
                            return NULL  ; 
                        }
                    }







                    else if (  strstr('JOIN' , buf[i][j]) == 0  || 
                            ( j+1 <= end_col && strstr('INNER' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) || 
                            (j+1 <= end_col && strstr('LEFT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr('RIGHT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr('CROSS' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) ||  
                            (j+2 <= end_col && strstr('FULL' , buf[i][j]) == 0 && strstr('OUTER' , buf[i][j+1]) == 0 && strstr('JOIN' , buf[i][j+2]) == 0 )){

            
                            if (strstr('INNER' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                temp->right = createNode( "INNER JOIN") ; 
                                j = j + 1 ; 
                            }
                            else if (strstr('JOIN' , buf[i][j]) == 0 ){
                                temp->right = createNode(buf[i][j]) ; 
                            }
                            else if (strstr('LEFT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                temp->right = createNode( "LEFT JOIN") ; 
                                j = j + 1 ; 
                            }
                            else if (strstr('RIGHT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                temp->right = createNode( "RIGHT JOIN") ; 
                                j = j + 1 ; 
                            }
                            else if (strstr('CROSS' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                    temp->right = createNode( "CROSS JOIN") ; 
                                j = j + 1 ; 
                            }
                            else  if ((strstr('FULL' , buf[i][j]) == 0 && strstr('OUTER' , buf[i][j+1]) == 0 && strstr('JOIN' , buf[i][j+2]) == 0 ) ){
                                        temp->right = createNode( "FULL OUTER JOIN") ; 
                                j = j + 2 ; 
                            }

                            int on = 0 ; 
                            tree* temp = node ; 
                            tree *start = temp ; 
                            while ( temp != NULL ){
                                temp = temp->right ; 
                            }





                            while ( ( !if_syntax(buf[i][j]) || (buf[i][j] == 'ON' ) && on == 0 )  ){


                                if ( buf[i][j] == 'ON'){
                                        if ( temp->comp == 'CROSS MODEL'){
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                                return NULL ; 
                                        }

                                        else if (temp->children == NULL ){
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                            return NULL ; 
                                        }

                                        else{
                                            temp->left = createNode('ON') ; 
                                            temp= temp->left ; 
                                            temp->left = createNode('=') ;                                     
                                            on++ ; 
                                        }
                                }



                                    if ( if_function( buf[i][j] ) == true ){
                                        tree *start = temp ; 
                                        tree *func = temp ; 
                                        while ( func->right != NULL){
                                            func = func->right ; 
                                        }
                                        func->right = createNode(buf[i][j]) ; 
                                        if ( buf[i][j+1] != NULL ){
                                            j++ ; 
                                        }
                                        tree *start_temp = temp ; 
                                        while (temp->)
                                        temp->right = start ; 
                                    }



                                else { 

                                        if ( buf[i][j] == '='){
                                            if ( on == 1 ){
                                                continue ; 
                                            }
                                            else { 
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                        }



                                    else { 
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
                                                node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                                node = node->left ; 
                                                i = end_row_dec ; 
                                                j = end_col_dec ; 
                                            }
                                            else {
                                                    status_msg_input("the query is wrong ") ; 
                                                    check = 1 ; 
                                                    return NULL  ; 
                                                }
                                            }



                                        if (if_syntax(buf[i][j]) == false ){
                                        if ( buf[i][j] == ','){
                                            node->num++ ; 
                                            continue ; 
                                        }
                                        node->children[node->num] = make_leaf(buf[i][j] , i , j )  ; 
                                        }
                                        else { 
                                            status_msg_input("the query is wrong ") ;
                                            check = 1 ;  
                                            return NULL  ;   
                                        }
                                    }


                                }
                            }
                            node->right = start ; 
                            i = i-1 ; 
                        }



                    else { 
                        if (if_syntax(buf[i][j]) == false ){
                            if ( buf[i][j] == ','){
                                node->num++ ; 
                                continue ; 
                            }
                            node->children[node->num] =make_leaf(buf[i][j] , i , j ) ; 
                        }
                        else { 
                            status_msg_input("the query is wrong ") ; 
                            check = 1 ; 
                                return NULL ;   
                        }
                    }

                



                }












    else if ( compulsion == 3 ){

                  if ( if_function( buf[i][j] ) == true ){
                    node->left = function( buf , temp,  i ,  j ) ; 
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
                        node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                        node = node->left ; 
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                            status_msg_input("the query is wrong ") ; 
                             check = 1 ; 
                            return NULL  ; 
                        }
                    }







;;














                else if (buf[i][j] == "GROUP"){
                    if (buf[i][j+1] != NULL ){
                        if (buf[i][j+1] == 'BY' ){
                            node->left = createNode("GROUP BY") ; 
                            node = node->left ; 
                            tree *temp = node ; 
                            tree *start_temp = temp ; 
                            node->num = 0 ; 
                        while ( strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0 &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){

                            if ( if_function( buf[i][j] ) == true ){
                                temp->left = function( buf , temp,  i ,  j ) ; 
                            }

                            if  (strcmp([buf[i][j]  , "HAVING"]) == 0 ){

                                temp->left = createNode("HAVING")  ; 
                                temp = temp->left ; 
                                tree * temp = where() ; 
                            }



                            else { 
                                    if ( buf[i][j] == '(' ){
                                        if ( j-1 > col && strstr("SELECT" , buf[i][j-1]) == 0  ){
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


                                    if (if_syntax(buf[i][j]) == false && if_function(buf[i][j]) == false  ){
                                        if ( buf[i][j] == ','){
                                            temp->num++ ; 
                                            continue ; 
                                        }
                                        temp->children[temp->num] = make_leaf(buf[i][j] , i , j )  ; 
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
                                }
                            if ( buf[i][j] == NULL ){
                                if (i+1 <= end_row){
                                    i = i+ 1 ; 
                                    j = 0  ; 
                                }
                            }
                            else { 
                                j++ ; 
                            }
                            }

                            node->left = start_temp ; 

                        }
                        else { 
                            status_msg_input("the query is wrong ") ; 
                            check = 1 ; 
                            return NULL  ;  
                        }
                    }


                    else { 
                        status_msg_input("the query is wrong ") ; 
                        check = 1 ; 
                        return NULL  ;
                    }

                }











                else if( strcmp("LIMIT") == 0 || strcmp("OFFSET") == 0 ){
                    node->left  = createNode("LIMIT") ; 
                    tree *temp = node ; 
                    while ( buf[i][j] != ';'  && strcmp(buf[i][j], "\0") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0){
                        if ( strcmp("OFFSET") == 0 ){
                            temp->num = temp->num  + 1 ; 
                        }
                        else if ( buf[i][j] == '('){
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
                                node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                node = node->left ; 
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


                    }
                }




















                    else if (  strstr('JOIN' , buf[i][j]) == 0  || 
                            ( j+1 <= end_col && strstr('INNER' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) || 
                            (j+1 <= end_col && strstr('LEFT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr('RIGHT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr('CROSS' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0  ) ||  
                            (j+2 <= end_col && strstr('FULL' , buf[i][j]) == 0 && strstr('OUTER' , buf[i][j+1]) == 0 && strstr('JOIN' , buf[i][j+2]) == 0 )){

            
                            if (strstr('INNER' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                temp->right = createNode( "INNER JOIN") ; 
                                j = j + 1 ; 
                            }
                            else if (strstr('JOIN' , buf[i][j]) == 0 ){
                                temp->right = createNode(buf[i][j]) ; 
                            }
                            else if (strstr('LEFT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                temp->right = createNode( "LEFT JOIN") ; 
                                j = j + 1 ; 
                            }
                            else if (strstr('RIGHT' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                temp->right = createNode( "RIGHT JOIN") ; 
                                j = j + 1 ; 
                            }
                            else if (strstr('CROSS' , buf[i][j]) == 0 && strstr('JOIN' , buf[i][j+1]) == 0 ){
                                    temp->right = createNode( "CROSS JOIN") ; 
                                j = j + 1 ; 
                            }
                            else  if ((strstr('FULL' , buf[i][j]) == 0 && strstr('OUTER' , buf[i][j+1]) == 0 && strstr('JOIN' , buf[i][j+2]) == 0 ) ){
                                        temp->right = createNode( "FULL OUTER JOIN") ; 
                                j = j + 2 ; 
                            }

                            int on = 0 ; 
                            tree* temp = node ; 
                            tree *start = temp ; 
                            while ( temp != NULL ){
                                temp = temp->right ; 
                            }





                            while ( ( !if_syntax(buf[i][j]) || (buf[i][j] == 'ON' ) && on == 0 )  ){


                                if ( buf[i][j] == 'ON'){
                                        if ( temp->comp == 'CROSS MODEL'){
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                                return NULL ; 
                                        }

                                        else if (temp->children == NULL ){
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                            return NULL ; 
                                        }

                                        else{
                                            temp->left = createNode('ON') ; 
                                            temp= temp->left ; 
                                            temp->left = createNode('=') ;                                     
                                            on++ ; 
                                        }
                                }



                                else { 

                                        if ( buf[i][j] == '='){
                                            if ( on == 1 ){
                                                continue ; 
                                            }
                                            else { 
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                        }



                                    else { 
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
                                                node->left = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                                node = node->left ; 
                                                i = end_row_dec ; 
                                                j = end_col_dec ; 
                                            }
                                            else {
                                                    status_msg_input("the query is wrong ") ; 
                                                    check = 1 ; 
                                                    return NULL  ; 
                                                }
                                            }



                                        if (if_syntax(buf[i][j]) == false ){
                                        if ( buf[i][j] == ','){
                                            node->num++ ; 
                                            continue ; 
                                        }
                                        node->children[node->num] =make_leaf(buf[i][j] , i , j )  ; 
                                        }
                                        else { 
                                            status_msg_input("the query is wrong ") ;
                                            check = 1 ;  
                                            return NULL  ;   
                                        }
                                    }


                                }
                            }
                            node->right = start ; 
                            i = i-1 ; 
                        }







;;


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
        
        
        
        }

}
        }
    }














else if (strcmp("ORDER" , buf[i][j]) == 0 ){
    if (buf[i][j+1] != NULL ){
        if (buf[i][j+1] == 'BY' ){
            node->children[node->num] = createNode("ORDER BY") ; 
            node->num++ ; 
            node = node->children[node->num - 1]; 

            tree *temp = node ; 
            tree *start_temp = temp ; 
            node->num = 0 ; 
            while ( strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0  &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){
                    if ( if_function( buf[i][j] ) == true ){
                        temp->left = function( buf , temp,  i ,  j ) ; 
                    }

                    else { 
                        if ( buf[i][j] == '(' ){
                            if ( j-1 > col && strstr("SELECT" , buf[i][j-1]) == 0  ){
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
                                temp->children[temp->num++] = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                temp = temp->children[temp->num - 1]; 
                                i = end_row_dec ; 
                                j = end_col_dec ; 
                            }
                            else {
                                    status_msg_input("the query is wrong ") ; 
                                    check = 1 ; 
                                    return NULL  ; 
                                }
                        }


                        if (if_syntax(buf[i][j]) == false && if_function(buf[i][j]) == false  ){
                            if ( buf[i][j] == ','){
                                temp->direction[temp->num] ="ASC"
                                temp->num++ ; 
                                continue ; 
                            }
                            temp->children[temp->num] = make_leaf(buf[i][j] , i , j )  ; 
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
                                    temp->children[temp->num]  = expression(buf , temp ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                                    
                                }
                                    else  if ( temp->children[temp->num] == NULL ){
                                        if (if_syntax(buf[i][j]) == false ){
                                                if ( buf[i][j] == ','){
                                                    temp->num++ ; 
                                                    continue ; 
                                                }
                                                temp->children[temp->num] = make_leaf( buf[i][j]  , i , j ) ; 
                                                temp->direction[temp->num] = "ASC" ; 
                                                temp->num++ ; 
                                            }
                                            else if (  strcmp(buf[i][j]  , "ASC"  ) == 0 ||  strcmp(buf[i][j]  , "DSC"  ) == 0  ){
                                                char *string_temp[300] ; 
                                                int temp_num = 0 ; 
                                                while ( buf[i][j] != ',' || buf[i][j] != ';'   ){
                                                    if ( buf[i][j] == NULL ){
                                                        if ( i+ 1 <= end_row ){
                                                            i = i+1 ; 
                                                            j = 0 ; 
                                                            continue ; 
                                                        }
                                                    }
                                                    if (  strcmp(buf[i][j]  , "NULLS"  ) == 0 ||  strcmp(buf[i][j]  , "LAST"  ) == 0  ||  strcmp(buf[i][j]  , "FIRST"  ) == 0 ){
                                                    string_temp[temp_num] = buf[i][j] ; 
                                                    temp_num++ ; 
                                                    }
                                                    j++ ; 
                                                }
                                                node->num-- ; 
                                                node->direction[node->num] = string_temp ;     
                                                node->num++ ; 
                                            }
                                            else { 
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                                    return NULL ;   
                                            }
                                    }                     
                            }
                    }




                    

            }
        }

    }
    else {
            status_msg_input("the query is wrong ") ; 
            check = 1 ; 
            return NULL  ;
    }
}




else if ( strcmp("CASE" , buf[i][j]) == 0 ){
    int cases = 0 ; 
    int start_row = i ; 
    int start_col = j ; 
    while ( cases != 0 && buf[i][j] != "END"){
        if ( buf[i][j] == "CASE"){
            cases++ ; 
        }
        else if ( cases > 0  && buf[i][j] == "END"){
            cases-- ; 
        }
        if ( buf[i][j] == NULL){
            if ( i + 1 <=  end_row){
                i = i +1 ; 
                j = 0 ; 
            }
        }
        else { 
            j++ ; 
        }
    }
    node->children[++node->num] = case(buf ,node , start_row , start_col , i , j ) ; 
}




tree *case(char **buf ,tree*node ,  int i , int j , int end_row , int end_col ){
    tree * start = node ; 
    int first = 0 ; 
    while ( buf[i][j] == "END"){
        if ( buf[i][j] == "WHEN" ||  buf[i][j] == "ELSE" ){
            node = start ; 
            if ( first > 0 ){
            node->num++ ; 
            }
            else { 
                first = 1 ; 
            }
            node->chilren[node->num] = createNode("WHEN") ; 
            node = node->chilren[node->num] ; 
        }
        
        else if ( buf[i][j] == "CASE"){
           int cases = 0 ; 
            int start_row = i ; 
            int start_col = j ; 
            while ( cases != 0 && buf[i][j] != "END"){
                if ( buf[i][j] == "CASE"){
                    cases++ ; 
                }
                else if ( cases > 0  && buf[i][j] == "END"){
                    cases-- ; 
                }
                if ( buf[i][j] == NULL){
                    if ( i + 1 <=  end_row){
                        i = i + 1 ; 
                        j = 0 ; 
                    }
                }
                else { 
                    j++ ; 
                }
            }
            node->children[++node->num] = case(buf ,node , start_row , start_col , i , j ) ; 
        }


        else { 
            if ( buf[i][j] == '(' ){
                if ( j-1 > col && strstr("SELECT" , buf[i][j-1]) == 0  ){
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
                    temp->children[temp->num++] = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                    temp = temp->children[temp->num - 1]; 
                    i = end_row_dec ; 
                    j = end_col_dec ; 
                }
                else {
                        status_msg_input("the query is wrong ") ; 
                        check = 1 ; 
                        return NULL  ; 
                    }
            }


            if (if_syntax(buf[i][j]) == false && if_function(buf[i][j]) == false  ){
                if ( buf[i][j] == ','){
                    temp->num++ ; 
                    continue ; 
                }
                temp->children[temp->num] = make_leaf(buf[i][j] , i , j )  ; 
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
                        temp->children[temp->num]  = expression(buf , temp ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                        
                    }
                        else { 
                            status_msg_input("the query is wrong ") ; 
                            check = 1 ; 
                                return NULL ;   
                        }               
                }
        }


    }
    return start ; 
}



















;;