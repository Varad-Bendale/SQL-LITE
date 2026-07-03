typedef struct Tree_def {
    char* comp; 
    struct Tree_def** children;   
    char* as  ; 
    char **direction  ; 
    int line;                 
    int col;
    int num  ; 
} Tree_def;

typedef Tree_def tree  ; 

tree* createNode( char* comp) {
    tree* node = malloc(sizeof(tree));
    if (node == NULL) {
        return NULL;   
    }
    if( comp != NULL  ){
        node->comp = strdup(comp) ; 
    }
    else { 
        node->comp = NULL ; 
    }
    node->as = NULL ; 
    node->children = calloc(300, sizeof(tree*));
    
    node->direction = NULL ;  
    node->num = 0  ; 
    node->col = 0 ; 
    node->line = 0 ; 
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
    if (n == NULL) {
        return NULL;   
    }
    if ( value != NULL ){
      n->comp = strdup(value);
    }
    n->as = NULL;
    n->children[300] = NULL;
    n->direction = NULL ; 
    n->line = row ; 
    n->col = col;
    return n;
}








tree *case_expr(char ***buf ,tree*temp , int check ,  int i , int j , int end_row , int end_col ){
    tree * start = temp ; 
    int first = 0 ; 
    tree *prev_where[300] = {0} ; 
    int prev_where_count = 0  ; 

    while ( i <= end_row && j <= end_col ){
        if (  buf[i][j] != NULL &&  (strcmp(buf[i][j] , "WHEN") == 0 ||  strcmp(buf[i][j] , "ELSE") == 0 )){
            temp = start ; 
            if ( first > 0 ){
            temp->num++ ; 
            }
            else { 
                first = 1 ; 
            }
            if ( buf[i][j] != NULL &&  strcmp(buf[i][j] , "WHEN") == 0 ){
                temp->children[temp->num] = createNode("WHEN") ; 
                temp = temp->children[temp->num] ; 
            }
            else{
                temp->children[temp->num] = createNode("ELSE") ; 
                temp = temp->children[temp->num] ; 
            }
            prev_where[prev_where_count++] = temp ; 
        }





        else if ( strcmp(buf[i][j] , "CASE") == 0){
           int cases = 1 ; 
            if (buf[i][j+1] != NULL) {
                j++ ;
            }
            else {
                if (buf[i+1][0] != NULL) {
                    i++ ;
                    j = 0 ;
                }
                else {
                    break ;
                }
            }
            int start_row = i ; 
            int start_col = j   ; 
            while (  i <= end_row && j<= end_col && cases != 0 &&  strcmp(buf[i][j] , "END") != 0  ){
                if ( strcmp(buf[i][j] , "CASE") == 0 ){
                    cases++ ; 
                }
                else if ( cases > 0  && strcmp(buf[i][j] , "END") == 0 ){
                    cases-- ; 
                }
                if (buf[i][j+1] != NULL) {
                    j++ ;
                }
                else {
                    if (buf[i+1][0] != NULL) {
                        i++ ;
                        j = 0 ;
                    }
                    else {
                        break ;
                    }
                }
            }
            temp->children[temp->num++] = case_expr(buf ,temp , check , start_row , start_col , i , j ) ; 
        }


        else { 
            if (buf[i][j] != NULL &&   strcmp(buf[i][j] , "THEN") == 0 ){
                if (  prev_where[prev_where_count -1 ]  == NULL ){
                    check = 1 ; 
                    return NULL ;  
                }
                temp->children[temp->num++] = createNode("THEN") ; 
                temp = temp->children[temp->num - 1 ] ; 
                if (buf[i][j+1] != NULL) {
                    j++ ;
                }
                else {
                    if (buf[i+1][0] != NULL) {
                        i++ ;
                        j = 0 ;
                    }
                    else {
                        break ;
                    }
                    continue ; 
                }

            }

             if ( buf[i][j] != NULL &&  strcmp(buf[i][j] , "(") == 0  ){
                    if ( j+1 <=  end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = 0 ; 
                        int end_row_dec  = 0 ; 
                        int braces = 1 ; 
                        int thing = j+1 ;   ; 
                        for ( int m = i ; m <= end_row ; m++  ){
                            for ( int n = thing; n <= end_col ; n++  ){
                                if ( strcmp(buf[m][n] , "(") == 0  ){
                                    braces++ ; 
                                }
                                else if ( strcmp(buf[m][n] , ")") == 0 ){
                                    braces-- ; 
                                }
                                if ( braces == 0 ){
                                    end_row_dec = m ; 
                                    end_col_dec = n ; 
                                    break ; 
                                }
                            }
                            thing = 0 ; 
                                if ( braces == 0 ){
                                    break ; 
                                }

                        }
                        tree * just_there  =  select_query( i  , j , check ,  end_row_dec ,  end_col_dec  ); 
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
                        temp = temp->children[temp->num- 1 ]  ; 
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                        while ( buf[i][j] != NULL &&  strcmp(buf[i][j] , ")") != 0 ){
                                if ( priority(buf[i][j]) != 0  ){
                                int temp_row = i ; 
                                int temp_col = j ; 
                                while ( buf[i][j] != NULL && strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                    if ( buf[i][j] == NULL ){
                                        if ( i+ 1 <= end_row){
                                        i++ ; 
                                        j = 0 ; 
                                    }
                                    else { 
                                        break ; 
                                    }
                                    }
                                    else {
                                        j++ ;
                                    }
                                }
                                tree *  just_there =  expression(buf , temp , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                if (just_there != NULL ){
                                temp->children[temp->num++ ]  = just_there ; 
                                }
                                }
                                else  {
                                if (if_syntax(buf[i][j]) == false ){
                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                            if ( buf[i][j] == NULL){
                                                if ( buf[i+1][0] != NULL ){
                                                i++ ;
                                                j = 0 ;
                                            } else {
                                                break ;
                                            }
                                        }
                                        else {
                                            j++ ; 
                                        }
                                                continue ;
                                        }
                                        temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                    }
                                    else { 
                                        check = 1 ; 
                                            return NULL ;   
                                    }
                            } 
                        }
                    }
            }




            else {
                if (if_syntax(buf[i][j]) == false ){
                        if ( strcmp(buf[i][j] , ",") == 0 ){
                            if (  buf[i][j] == NULL  ) {
                                if ( buf[i+1][0] != NULL ){
                                i++ ;
                                j = 0 ;
                            } 
                        }
                        else { 
                            j++ ; 
                        }
                                continue ;
                        }
                            if (buf[i][j+1] != NULL && priority(buf[i][j+1]) != 0) {
                            int temp_row = i ; 
                            int temp_col = j ; 
                            while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                if ( buf[i][j] == NULL ){
                                    if ( i+ 1 <= end_row){
                                    i++ ; 
                                    j = 0 ; 
                                }
                                else { 
                                    break ; 
                                }
                                }
                                else {
                                    j++ ;
                                }
                            }
                            tree*  just_there =  expression(buf , temp , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                            if (just_there != NULL ){
                            temp->children[temp->num++ ]  = just_there ; 
                            }
                        }
                        else {
                                temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                        }
                    }
                    else { 
                        check = 1 ; 
                        return NULL ;   
                    }
            }
    }
        if (buf[i][j+1] != NULL) {
            j++ ;
        }
        else {
            if (buf[i+1][0] != NULL) {
                i++ ;
                j = 0 ;
            }
            else {
                break ;
            }
        }

    }
    return start ; 
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
    else if (strcmp("BETWEEN", string) == 0 || strcmp("IN", string) == 0 || strcmp("LIKE", string) == 0 || strcmp("IS", string) == 0 || strcmp("EXISTS", string) == 0 || strcmp("IS NULL", string) == 0 || strcmp("IS NOT NULL", string) == 0 || strcmp("NOT IN", string) == 0 || strcmp("NOT LIKE", string) == 0 || strcmp("NOT BETWEEN", string) == 0){
         return 5;
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






tree* expression(char ***buf , tree * node , int check , int i , int j  , int end_row , int end_col  ){
    if ( check == 1 ){
        return NULL ; 
    }
    char string_temp_buf[600];
    char * operands[300] ; 
    int start_row =  i  ; 
    int start_col = j ; 
    char * operators[300] ; 
    char *string_temp; 
    int operator_top = 0 ; 
    int operand_top = 0 ; 
    tree * prev_tree[300]  ; 
    int prev_tree_top = 0 ; 
    int first = 0 ; 

    while ( buf[i][j] != NULL && strcmp(buf[i][j], ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
        if (priority(buf[i][j]) != 0) {    
            if ( j+1 <= end_col &&  priority(buf[i][j]) != 0  && strcmp(buf[i][j], "IS") == 0 && strcmp(buf[i][j+1], "NULL") == 0   ){
                string_temp = "IS NULL" ; 
                j = j +1 ; 
            }
            else if (j+1 <= end_col &&  priority(buf[i][j]) != 0  && strcmp(buf[i][j], "IS") == 0 && strcmp(buf[i][j+1], "NOT") == 0  && strcmp(buf[i][j+1], "NULL") == 0  ){
                string_temp = "IS NOT NULL" ; 
                j = j+2 ; 
            }
            else if (j+1 <= end_col &&  priority(buf[i][j]) != 0  && strcmp(buf[i][j], "NOT") == 0 && strcmp(buf[i][j+1], "IN") == 0   ){
                string_temp = "NOT IN" ; 
                j = j +1 ; 
            }
            else if ( j+1 <= end_col && priority(buf[i][j]) != 0  && strcmp(buf[i][j], "NOT") == 0 && strcmp(buf[i][j+1], "LIKE") == 0   ){
                string_temp = "NOT LIKE" ; 
                    j = j +1 ; 
            }
            else if (j+1 <= end_col &&  priority(buf[i][j]) != 0  && strcmp(buf[i][j], "NOT") == 0 && strcmp(buf[i][j+1], "BETWEEN") == 0   ){
                string_temp = "NOT BETWEEN" ; 
                j = j +1 ; 
            }
            else if (j + 1 <= end_col ){
                char merged[10] ; 
                strcpy(merged, buf[i][j]);
                strcat(merged, buf[i][j + 1]);
                if ( priority(merged) != 0 ){
                    string_temp = strdup(merged) ; 
                    j += 1  ; 
                }
                else {
                    string_temp = strdup(buf[i][j]);  
                }
            }
            else { 
                   string_temp = strdup(buf[i][j]);
            }

             if  (first == 0 && j == start_col ){
                 if ( i > start_row ){
                        int size = 0  ; 
                        for ( int k = 0 ; buf[i - 1][k] != NULL ; k++ ){
                            size++ ; 
                        }
                        if ( size > 0 ){
                          operands[operand_top++] = buf[i-1][size - 1 ] ; 
                        }
                    }
                        else if ( i == start_row && start_col > 0 ){
                          operands[operand_top++] = buf[i][start_col - 1] ;
                        }
                }
            first = 1 ; 

            if ( operator_top == 0 ){
                operators[operator_top++] = string_temp ;                                            
            }
            else { 
                if  ( priority(string_temp) <= priority(operators[operator_top - 1 ]) ){
                    while ( operator_top > 0 && priority(string_temp) <= priority(operators[operator_top - 1 ]  )){
                        char *oper = operators[operator_top - 1] ; 
                        tree * new  = createNode(oper) ; 
                        operator_top-- ; 
                        int pal = 0 ; 
                        int num_temp = 2  ; 
                        if ( strcmp(oper, "NOT") == 0 ||strcmp(oper, "IS NULL") == 0 || strcmp(oper, "IS NOT NULL") == 0 )  {
                            num_temp = 1 ; 
                        }
                        while ( pal < num_temp  ){
                            operand_top-- ;     
                            fflush(stdout);
                            if ( operands[operand_top] ==  NULL){
                                new->children[num_temp - 1 - pal]  = prev_tree[--prev_tree_top] ; 
                            }
                            else { 
                                new->children[num_temp - 1 - pal] = make_leaf(operands[operand_top] , i  ,  j ) ; 
                            }
                            pal++ ; 
                        }
                        new->num = num_temp;
                        prev_tree[prev_tree_top++] = new;
                        operands[operand_top] = NULL;
                        operand_top++;
                    }
                    operators[operator_top++] = string_temp ; 
                }
                else  {
                    operators[operator_top++] = string_temp ; 
                }
            }
        }
        else { 
                if ( if_function( buf[i][j] ) == true ){
                        int start_row = i ; 
                        int start_col = j ; 
                        int commas = 1 ; 
                        while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( commas == 0 ){
                                    break ; 
                                }
                                if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }
                                if ( buf[i][j] == NULL){
                                    if ( i +1 < end_row){
                                    i++ ; 
                                    j = 0 ; 
                                    }
                                    else { 
                                        break ; 
                                    }
                                }
                                else { 
                                    j++ ; 
                                }
                            }
                            if ( commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                         tree * just_there   ; 
                        if (prev_tree[prev_tree_top - 1 ] == NULL){
                            just_there  =  function( buf , prev_tree[prev_tree_top - 1 ]  ,check ,   start_row ,  start_col , i , j ) ; 
                        }
                        else { 
                          tree * just_there  =  function( buf , prev_tree[prev_tree_top - 1 ]  ,check ,   start_row ,  start_col , i , j ) ; 
                        }
                        if (just_there != NULL  ){
                                prev_tree[prev_tree_top++] = just_there ;
                              operands[operand_top++] = NULL ;
                        } 
                }
                else if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j-1 > 0 && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = 0 ; 
                        int end_row_dec  = 0 ; 
                        int braces = 1 ; 
                        for ( int m = i ; m <= end_row ; m++  ){
                            for ( int n = j+1 ; n <= end_col ; n++  ){
                                if ( strcmp(buf[m][n] , "(") == 0  ){
                                    braces++ ; 
                                }
                                else if ( strcmp(buf[m][n] , ")") == 0 ){
                                    braces-- ; 
                                }
                                if ( braces == 0 ){
                                    end_row_dec = m ; 
                                    end_col_dec = n ; 
                                    break ; 
                                }
                            }
                                if ( braces == 0 ){
                                    break ; 
                                }

                        }
                        tree * just_there  =  select_query( i  , j , check ,  end_row_dec ,  end_col_dec  ); 
                        if (just_there != NULL  ){
                                prev_tree[prev_tree_top++] = just_there ;
                              operands[operand_top++] = NULL ;
                        }
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                        operands[operand_top] = buf[i][j] ; 
                        operand_top++ ; 
                    }
                }
                else {
                    operands[operand_top] = buf[i][j] ; 
                    operand_top++ ; 
                }
        }
            if ( buf[i][j] == NULL){
                if ( i +1 < end_row){
                i++ ; 
                j = 0 ; 
                }
                else { 
                    break ; 
                }
            }
            else { 
                j++ ; 
            }
    }


    while (operator_top > 0) {
        char *oper = operators[operator_top - 1] ; 
        tree * new  = createNode(oper) ; 
        operator_top-- ; 
        int pal = 0 ; 
        int num_temp = 2   ; 
        if ( strcmp(oper, "NOT") == 0 ||strcmp(oper, "IS NULL") == 0 || strcmp(oper, "IS NOT NULL") == 0 )  {
            num_temp = 1 ; 
        }
        while ( pal < num_temp  ){
            operand_top-- ;     
            if ( operands[operand_top] ==  NULL){
                new->children[num_temp - 1 - pal]  = prev_tree[--prev_tree_top] ; 
            }
            else { 
                new->children[num_temp - 1 - pal ] = make_leaf(operands[operand_top] , i  ,  j ) ; 
            }

            pal++ ; 
        }
         new->num = num_temp;
        prev_tree[prev_tree_top++] = new;
        operands[operand_top] = NULL;
        operand_top++;
    }
    tree*exp_tree = prev_tree[prev_tree_top - 1 ] ; 
    if ( j-1 >= start_col ){
        j = j - 1 ;
    }
    return exp_tree ; 
}






tree *function( char ***buf , tree * node ,int check  ,  int i , int j  , int end_row , int end_col ){
        if ( check == 1 ){
            return NULL ; 
        }
         tree* temp = node ; 
        temp->children[temp->num++]  = createNode(buf[i][j]) ; 
        temp = temp->children[temp->num- 1 ] ; 
        tree *start = temp ; 
        int pal = 0 ; 
        while ( pal < 2 ){
        if ( buf[i][j+1] != NULL ){
            j++ ; 
        }
        pal++ ; 
         }


        while ( strcmp(buf[i][j] , ")") != 0 ){
             if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j-1 > 0 && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = 0 ; 
                        int end_row_dec  = 0 ; 
                        int braces = 1 ; 
                        for ( int m = i ; m <= end_row ; m++  ){
                            for ( int n = j+1 ; n <= end_col ; n++  ){
                                if ( strcmp(buf[m][n] , "(") == 0  ){
                                    braces++ ; 
                                }
                                else if ( strcmp(buf[m][n] , ")") == 0 ){
                                    braces-- ; 
                                }
                                if ( braces == 0 ){
                                    end_row_dec = m ; 
                                    end_col_dec = n ; 
                                    break ; 
                                }
                            }
                                if ( braces == 0 ){
                                    break ; 
                                }

                        }
                        tree * just_there  =  select_query( i  , j , check ,  end_row_dec ,  end_col_dec  ); 
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
                        temp = temp->children[temp->num- 1 ]  ; 
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                        while ( strcmp(buf[i][j] , ")") != 0 ){
                                if ( priority(buf[i][j]) != 0  ){
                                int temp_row = i ; 
                                int temp_col = j ; 
                                while ( buf[i][j] != NULL && strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                    if ( buf[i][j] == NULL ){
                                        if ( i+ 1 <= end_row){
                                        i++ ; 
                                        j = 0 ; 
                                    }
                                    else { 
                                        break ; 
                                    }
                                    }
                                    else {
                                        j++ ;
                                    }
                                }
                                tree *  just_there =  expression(buf , temp ,check ,   temp_row ,  temp_col  ,  i ,  j ) ; 
                                if (just_there != NULL ){
                                temp->children[temp->num++ ]  = just_there ; 
                                }
                                }
                                else  {
                                if (if_syntax(buf[i][j]) == false ){
                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                            if ( buf[i][j] == NULL){
                                                if ( buf[i+1][0] != NULL ){
                                                i++ ;
                                                j = 0 ;
                                            } else {
                                                break ;
                                            }
                                        }
                                        else {
                                            j++ ; 
                                        }
                                                continue ;
                                        }
                                        temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                    }
                                    else { 
                                        check = 1 ; 
                                            return NULL ;   
                                    }
                            } 
                        }
                    }
            }

            else { 
                    if ( priority(buf[i][j]) != 0  ){
                        int temp_row = i ; 
                        int temp_col = j ; 
                        while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                            if ( buf[i][j] == NULL ){
                                if ( i+ 1 <= end_row){
                                i++ ; 
                                j = 0 ; 
                            }
                            else { 
                                break ; 
                            }
                            }
                            else {
                                j++ ;
                            }
                        }
                        tree*  just_there =  expression(buf , temp ,check ,   temp_row ,  temp_col  ,  i ,  j ) ; 
                        if (just_there != NULL ){
                        temp->children[temp->num++ ]  = just_there ; 
                        }
                    }         
                    else {
                        if (if_syntax(buf[i][j]) == false ){
                                if ( strcmp(buf[i][j] , ",") == 0 ){
                                    if (  buf[i][j] == NULL  ) {
                                         if ( buf[i+1][0] != NULL ){
                                        i++ ;
                                        j = 0 ;
                                    } 
                                }
                                else { 
                                    j++ ; 
                                }
                                        continue ;
                                }
                                 if (buf[i][j+1] != NULL && priority(buf[i][j+1]) != 0) {
                                    int temp_row = i ; 
                                    int temp_col = j ; 
                                    while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                        if ( buf[i][j] == NULL ){
                                            if ( i+ 1 <= end_row){
                                            i++ ; 
                                            j = 0 ; 
                                        }
                                        else { 
                                            break ; 
                                        }
                                        }
                                        else {
                                            j++ ;
                                        }
                                    }
                                    tree*  just_there =  expression(buf , temp , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                    if (just_there != NULL ){
                                    temp->children[temp->num++ ]  = just_there ; 
                                    }
                                }
                                else {
                                       temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                }
                            }
                            else { 
                                check = 1 ; 
                                return NULL ;   
                            }
                    }                    
            }
            if (buf[i][j+1] != NULL) {
                j++ ;
            }
            else {
                if (buf[i+1][0] != NULL) {
                    i++ ;
                    j = 0 ;
                }
                else {
                    break ;
                }
            }
    }
    return start ; 
}



tree *comp_1(char*** buf , tree * node  ,  int i , int j , int end_row , int end_col ){

    tree * start = node ; 
    tree * temp  = node ; 
    int check = 0 ; 

    while ( i <= end_row){
       while ( j <= end_col ) {
            if (  strcmp(buf[i][j] ,  "FROM"  ) == 0  ) {
                return start ; 
            }
            else { 
                if ( if_function( buf[i][j] ) == true ){
                    int start_row = i ; 
                    int start_col = j ; 
                    int commas = 1 ; 
                     while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( commas == 0 ){
                                    break ; 
                                }
                                if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }
                                if ( buf[i][j] == NULL){
                                    if ( i +1 < end_row){
                                    i++ ; 
                                    j = 0 ; 
                                    }
                                    else { 
                                        break ; 
                                    }
                                }
                                else { 
                                    j++ ; 
                                }
                            }
                            if ( commas == 0 ){
                                break ; 
                            }
                                if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }
                        }
                temp->children[temp->num++] = function( buf , temp,check ,   i ,  j , end_row , end_col ) ;
            }
                

            else  if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j-1 > 0 && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = 0 ; 
                        int end_row_dec  = 0 ; 
                        int braces = 1 ; 
                        for ( int m = i ; m <= end_row ; m++  ){
                            for ( int n = j+1 ; n <= end_col ; n++  ){
                                if ( strcmp(buf[m][n] , "(") == 0  ){
                                    braces++ ; 
                                }
                                else if ( strcmp(buf[m][n] , ")") == 0 ){
                                    braces-- ; 
                                }
                                if ( braces == 0 ){
                                    end_row_dec = m ; 
                                    end_col_dec = n ; 
                                    break ; 
                                }
                            }
                                if ( braces == 0 ){
                                    break ; 
                                }

                        }
                        tree * just_there  =  select_query( i  , j , check ,  end_row_dec ,  end_col_dec  ); 
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
                        temp = temp->children[temp->num- 1 ]  ; 
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                        while ( strcmp(buf[i][j] , ")") != 0 ){
                                if ( buf[i][j] == NULL){
                                    if ( i +1 < end_row){
                                    i++ ; 
                                    j = 0 ; 
                                    }
                                    else { 
                                        break ; 
                                    }
                                }
                                else { 
                                    j++ ; 
                                }
                               if ( priority(buf[i][j]) != 0 ){
                                int temp_row = i ;
                                int temp_col = j ;
                                int depth = 0 ;

                                while (i <= end_row ){
                                    while (j <= end_col ){
                                    if ( buf[i][j] == NULL ){
                                        if ( i+1 <= end_row ){ 
                                            i++ ;
                                            j = 0 ;
                                             continue ; }
                                        else { 
                                            break ;
                                         }
                                    }

                                    if ( strcmp(buf[i][j], ";") == 0 || strcmp(buf[i][j], "ON") == 0 || strcmp(buf[i][j], "OFFSET") == 0 || strcmp(buf[i][j], "LIMIT") == 0 || strcmp(buf[i][j], "ORDER") == 0 || strcmp(buf[i][j], "HAVING") == 0 || strcmp(buf[i][j], "GROUP") == 0 || strcmp(buf[i][j], "WHERE") == 0 || strcmp(buf[i][j], "FROM") == 0 ){
                                        break ;
                                    }

                                    if ( strcmp(buf[i][j], "(") == 0 ){
                                        depth++ ;
                                    }
                                    else if ( strcmp(buf[i][j], ")") == 0 ){
                                        if ( depth == 0 ){
                                            break ;  
                                        }
                                        depth-- ;
                                    }
                                    if ( buf[i][j] == NULL){
                                        if ( i +1 < end_row){
                                        i++ ; 
                                        j = 0 ; 
                                        }
                                        else { 
                                            break ; 
                                        }
                                    }
                                    else { 
                                        j++ ; 
                                    }   
                                    if ( i > end_row ){
                                        break ;   
                                    }
                                }   
                                }

                                tree * just_there = expression( buf , temp , check , temp_row , temp_col , i , j ) ;
                                if ( just_there != NULL ){
                                    temp->children[temp->num++] = just_there ;
                                }
                            }
                                else  {
                                    if (if_syntax(buf[i][j]) == false ){
                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                            if (  buf[i][j] == NULL  ) {
                                                if ( buf[i+1][0] != NULL ){
                                                i++ ;
                                                j = 0 ;
                                            } 
                                        }
                                        else { 
                                            j++ ; 
                                        }
                                                continue ;
                                        }
                                        else if (buf[i][j+1] != NULL && priority(buf[i][j+1]) != 0) {
                                            int temp_row = i ; 
                                            int temp_col = j ; 
                                            while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                                if ( buf[i][j] == NULL ){
                                                    if ( i+ 1 <= end_row){
                                                    i++ ; 
                                                    j = 0 ; 
                                                }
                                                else { 
                                                    break ; 
                                                }
                                                }
                                                else {
                                                    j++ ;
                                                }
                                            }
                                            tree*  just_there =  expression(buf , temp , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                            if (just_there != NULL ){
                                            temp->children[temp->num++ ]  = just_there ; 
                                            }
                                        }
                                        else {
                                            temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                        }
                                    }
                                    else { 
                                        check = 1 ; 
                                            return NULL ;   
                                    }
                            } 
                        }
                    }
            }




              else { 
                    if ( priority(buf[i][j]) != 0  ){
                        int temp_row = i ; 
                        int temp_col = j ; 
                        while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                            if ( buf[i][j] == NULL ){
                                if ( i+ 1 <= end_row){
                                i++ ; 
                                j = 0 ; 
                            }
                            else { 
                                break ; 
                            }
                            }
                            else {
                                j++ ;
                            }
                        }
                        tree*  just_there =  expression(buf , temp , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                        if (just_there != NULL ){
                        temp->children[temp->num++ ]  = just_there ; 
                        }
                    }         
                    else {
                        if (if_syntax(buf[i][j]) == false ){
                                if ( strcmp(buf[i][j] , ",") == 0 ){
                                    if (  buf[i][j] == NULL  ) {
                                         if ( buf[i+1][0] != NULL ){
                                        i++ ;
                                        j = 0 ;
                                    } 
                                }
                                else { 
                                    j++ ; 
                                }
                                        continue ;
                                }
                                 if (buf[i][j+1] != NULL && priority(buf[i][j+1]) != 0) {
                                    int temp_row = i ; 
                                    int temp_col = j ; 
                                    while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                        if ( buf[i][j] == NULL ){
                                            if ( i+ 1 <= end_row){
                                            i++ ; 
                                            j = 0 ; 
                                        }
                                        else { 
                                            break ; 
                                        }
                                        }
                                        else {
                                            j++ ;
                                        }
                                    }
                                    tree*  just_there =  expression(buf , temp , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                    if (just_there != NULL ){
                                    temp->children[temp->num++ ]  = just_there ; 
                                    }
                                }
                                else {
                                       temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                }
                            }
                            else { 
                                check = 1 ; 
                                return NULL ;   
                            }
                    }                    
            }
        }


             if (buf[i][j+1] != NULL) {
                j++ ;
            }
            else {
                if (buf[i+1][0] != NULL) {
                    i++ ;
                    j = 0 ;
                }
                else {
                    break ;
                }
            }

            }
            break;
    }
    return start  ; 

}





tree *comp_2(char** buf , tree * node , int i , int j , int end_row , int end_col , int pain ){

    tree * start = node ; 


    while ( i <= end_row){
       while ( j <= end_col ) {
            if (  strstr('WHERE' , buf[i][j]) == 0  ) {
                return start ; 
            }
            else { 
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
                        nested = temp ; 
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                            while ( buf[i][j] != ')'){
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
                        }
                    }

                    else if (  strstr("JOIN" , buf[i][j]) == 0  || 
                            ( j+1 <= end_col && strstr("INNER" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) || 
                            (j+1 <= end_col && strstr("LEFT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr("RIGHT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr("CROSS" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) ||  
                            (j+2 <= end_col && strstr("FULL" , buf[i][j]) == 0 && strstr("OUTER" , buf[i][j+1]) == 0 && strstr("JOIN" , buf[i][j+2]) == 0 )){

                            int on = 0 ; 
                            tree* temp = node ; 

                            if (strstr("INNER" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] = createNode("INNER JOIN");
                                j = j + 1;
                            }
                            else if (strstr("JOIN" , buf[i][j]) == 0 ){
                                temp->children[temp->num++] = createNode(buf[i][j]);
                            }
                            else if (strstr("LEFT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] =  createNode("LEFT JOIN");
                                j = j + 1;
                            }
                            else if (strstr("RIGHT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] =  createNode("RIGHT JOIN");
                                j = j + 1;
                            }
                            else if (strstr("CROSS" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] =  createNode("CROSS JOIN");
                                j = j + 1;
                            }
                            else if (strstr("FULL" , buf[i][j]) == 0 && strstr("OUTER" , buf[i][j+1]) == 0 && strstr("JOIN" , buf[i][j+2]) == 0 ){
                                temp->children[temp->num++] = createNode("FULL OUTER JOIN");
                                j = j + 2;
                            }

                            temp = temp->children[temp->num - 1 ]   ; 
                            tree *starter = temp ; 





                                while (  strcmp('WHERE' , buf[i][j]) == 0   && strcmp(buf[i][j], "GROUP") != 0 &&  strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0 &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){

                                            if ( if_function( buf[i][j] ) == true ){
                                                temp->children[temp->num++]  = function( buf , temp,  i ,  j ) ; 
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
                                                            temp->children[temp->num++]  = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                                            temp = temp->children[temp->num- 1 ]  ; 
                                                            nested = temp ; 
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
                                                                if ( buf[i][j] == "ON"  && start->comp == "CROSS MODEL" ){
                                                                        status_msg_input("the query is wrong ") ; 
                                                                        check = 1 ; 
                                                                        return NULL ; 
                                                                }
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
                                                                temp->children[temp->num++]   = expression(buf , temp ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                                                                
                                                            }
                                                            else  if ( temp->children[temp->num - 1]  == NULL ){
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
                            if ( j-1 > 0 ){
                                j = j-1 ; 
                            }
                            else {
                                int temp_row ; 
                                int temp_col ; 
                                if ( i- 1 > 0 ){
                                temp_row = i -1 ; 
                                }
                                else {
                                    i = 0 ; 
                                    j = 0 ; 
                                }
                                temp_col = 0 ; 
                                int size = 0 ; 
                                for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; i++ ){
                                }
                                j = temp_col -1 ; 
                                i = temp_row ; 
                            }

                            if ( pain == 0 ){
                                node->children[node->num++] = starter ; 
                            }
                            else { 
                                return starter ; 
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
    }
    return start 

}





tree *comp_3(char** buf , tree * node , int i , int j , int end_row , int end_col , int pain  , int having ){

    tree * start = node ; 


    while ( i <= end_row){
       while ( j <= end_col ) {

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
                            nested = temp ; 
                            i = end_row_dec ; 
                            j = end_col_dec ; 
                        }
                        else {
                             while ( buf[i][j] != ')'){
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
                            }
                    }

                    else if (strcmp("ORDER" , buf[i][j]) == 0 ){
                        if ( having. == 1 ){
                            return start ; 
                        }
                        tree *temp  ; 
                        tree *start_temp ; 
                        if (buf[i][j+1] != NULL ){
                            if (buf[i][j+1] == 'BY' ){
                                j++ ; 
                                node->children[node->num] = createNode("ORDER BY") ; 
                                node->num++ ; 
                                tree *temp = node ; 
                                temp = temp->children[temp->num - 1]; 
                                tree *start_temp = temp ; 
                                temp->num = 0 ; 
                                while ( strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0  &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){
                                        if ( if_function( buf[i][j] ) == true ){
                                            temp->children[temp->num++] = function( buf , temp,  i ,  j ) ; 
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
                                                    temp->children[temp->num++] = select_query( i  , j , check ,  end_row_dec ,  end_col_dec , 0  ) ; 
                                                    temp = temp->children[temp->num - 1]; 
                                                    nested = temp ; 
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
                             if ( j-1 > 0 ){
                                j = j-1 ; 
                            }
                            else {
                                int temp_row ; 
                                int temp_col ; 
                                if ( i- 1 > 0 ){
                                temp_row = i -1 ; 
                                }
                                else {
                                    i = 0 ; 
                                    j = 0 ; 
                                }
                                temp_col = 0 ; 
                                int size = 0 ; 
                                for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; i++ ){
                                }
                                j = temp_col -1 ; 
                                i = temp_row ; 
                            }

                            if ( pain == 0 ){
                                node->children[node->num++] = start_temp ; 
                            }
                            else { 
                                return start_temp ; 
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




                    else if( strcmp("LIMIT") == 0 || strcmp("OFFSET") == 0 ){
                        if ( having == 1 ){
                            return start ; 
                        }
                        node->children[node->num++]  = createNode("LIMIT") ; 
                        tree *temp = node->children[node->num - 1]  ; 
                        tree* start_temp = temp ; 
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
                                    temp->children[node->num++] = select_query( i  , j , check ,  end_row_dec ,  end_col_dec , 0   ) ; 
                                    temp = temp->children[node->num - 1] ; 
                                    nested = temp ; 
                                    i = end_row_dec ; 
                                    j = end_col_dec ; 
                                        }
                                else {
                                    while ( buf[i][j] != ')'){
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
                                        temp->children[node->num++]  = expression(buf , temp ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                                        
                                    }
                                    else  if ( temp->children[temp->num - 1 ] == NULL ){
                                        if (if_syntax(buf[i][j]) == false ){
                                                if ( buf[i][j] == ','){
                                                    temp->num++ ; 
                                                    continue ; 
                                                }
                                                temp->children[temp->num] = make_leaf( buf[i][j]  , i , j ) ; 
                                                temp->num++ ; 
                                            }
                                            else { 
                                                status_msg_input("the query is wrong ") ; 
                                                check = 1 ; 
                                                    return NULL ;   
                                            }
                                    }                    
                                } 


                        }
                                if ( j-1 > 0 ){
                                    j = j-1 ; 
                                }
                                else {
                                    int temp_row ; 
                                    int temp_col ; 
                                    if ( i- 1 > 0 ){
                                    temp_row = i -1 ; 
                                    }
                                    else {
                                        i = 0 ; 
                                        j = 0 ; 
                                    }
                                    temp_col = 0 ; 
                                    int size = 0 ; 
                                    for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; i++ ){
                                    }
                                    j = temp_col -1 ; 
                                    i = temp_row ; 
                                }

                                if ( pain == 0 ){
                                    node->children[node->num++] = start_temp ; 
                                }
                                else { 
                                    return start_temp ; 
                                }
                    }



                    else if (buf[i][j] == "GROUP"){
                        if (buf[i][j+1] != NULL ){
                            if (buf[i][j+1] == 'BY' ){
                                node->children[node->num++] = createNode("GROUP BY") ; 
                                tree *temp =  node->children[node->num - 1 ]  ; 
                                tree *start_temp = temp ; 
                            while ( strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0 &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){

                                if ( if_function( buf[i][j] ) == true ){
                                    temp->children[temp->num++] = function( buf , temp,  i ,  j ) ; 
                                }

                                if  (strcmp([buf[i][j]  , "HAVING"]) == 0 ){
                                    int start_row = i ; 
                                    int start_col = j ; 
                                    while (strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT")!= 0 && strcmp(buf[i][j], "EXCEPT") != 0 && strcmp(buf[i][j], ")") != 0 && strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL ) { 
                                            
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
                                    temp->children[temp->num++] = comp_3( buf ,  temp , start_row, start_col,  i ,  j ,  pain  , 1 ) ; 
                                    continue ; 
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
                                                temp->children[temp->num++] = select_query( i  , j , check ,  end_row_dec ,  end_col_dec  , 0  ) ; 
                                                temp = temp->children[temp->num - 1 ] ; 
                                                nested = temp ; 
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
                                                    temp->children[temp->num++]  = expression(buf , temp ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                                                    
                                                }
                                                else  if ( emp->children[temp->num -1 ]  == NULL ){
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

                                

                                if ( j-1 > 0 ){
                                    j = j-1 ; 
                                }
                                else {
                                    int temp_row ; 
                                    int temp_col ; 
                                    if ( i- 1 > 0 ){
                                    temp_row = i -1 ; 
                                    }
                                    else {
                                        i = 0 ; 
                                        j = 0 ; 
                                    }
                                    temp_col = 0 ; 
                                    int size = 0 ; 
                                    for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; i++ ){
                                    }
                                    j = temp_col -1 ; 
                                    i = temp_row ; 
                                }

                                if ( pain == 0 ){
                                    node->children[node->num++] = start_temp ; 
                                }
                                else { 
                                    return start_temp ; 
                                }

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






                    else if (  strstr("JOIN" , buf[i][j]) == 0  || 
                            ( j+1 <= end_col && strstr("INNER" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) || 
                            (j+1 <= end_col && strstr("LEFT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr("RIGHT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) ||  
                            (j+1 <= end_col && strstr("CROSS" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0  ) ||  
                            (j+2 <= end_col && strstr("FULL" , buf[i][j]) == 0 && strstr("OUTER" , buf[i][j+1]) == 0 && strstr("JOIN" , buf[i][j+2]) == 0 )){

                            int on = 0 ; 
                            tree* temp = node ; 

                            if (strstr("INNER" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] = createNode("INNER JOIN");
                                j = j + 1;
                            }
                            else if (strstr("JOIN" , buf[i][j]) == 0 ){
                                temp->children[temp->num++] = createNode(buf[i][j]);
                            }
                            else if (strstr("LEFT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] =  createNode("LEFT JOIN");
                                j = j + 1;
                            }
                            else if (strstr("RIGHT" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] =  createNode("RIGHT JOIN");
                                j = j + 1;
                            }
                            else if (strstr("CROSS" , buf[i][j]) == 0 && strstr("JOIN" , buf[i][j+1]) == 0 ){
                                temp->children[temp->num++] =  createNode("CROSS JOIN");
                                j = j + 1;
                            }
                            else if (strstr("FULL" , buf[i][j]) == 0 && strstr("OUTER" , buf[i][j+1]) == 0 && strstr("JOIN" , buf[i][j+2]) == 0 ){
                                temp->children[temp->num++] = createNode("FULL OUTER JOIN");
                                j = j + 2;
                            }

                            temp = temp->children[temp->num - 1 ]   ; 
                            tree *starter = temp ; 





                                while (  strcmp('WHERE' , buf[i][j]) == 0   && strcmp(buf[i][j], "GROUP") != 0 &&  strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0 &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){

                                            if ( if_function( buf[i][j] ) == true ){
                                                temp->children[temp->num++]  = function( buf , temp,  i ,  j ) ; 
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
                                                            temp->children[temp->num++]  = select_query( i  , j , check , int end_row_dec , int end_col_dec  ) ; 
                                                            temp = temp->children[temp->num- 1 ]  ; 
                                                            nested = temp ; 
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
                                                                if ( buf[i][j] == "ON"  && start->comp == "CROSS MODEL" ){
                                                                        status_msg_input("the query is wrong ") ; 
                                                                        check = 1 ; 
                                                                        return NULL ; 
                                                                }
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
                                                                temp->children[temp->num++]   = expression(buf , temp ,  i ,  j  ,  temp_row ,  temp_col ) ; 
                                                                
                                                            }
                                                            else  if ( temp->children[temp->num - 1 ]  == NULL ){
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
                            if ( j-1 > 0 ){
                                j = j-1 ; 
                            }
                            else {
                                int temp_row ; 
                                int temp_col ; 
                                if ( i- 1 > 0 ){
                                temp_row = i -1 ; 
                                }
                                else {
                                    i = 0 ; 
                                    j = 0 ; 
                                }
                                temp_col = 0 ; 
                                int size = 0 ; 
                                for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; i++ ){
                                }
                                j = temp_col -1 ; 
                                i = temp_row ; 
                            }

                            if ( pain == 0 ){
                                node->children[node->num++] = starter ; 
                            }
                            else { 
                                return starter ; 
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
    }
    return start  ; 

}








tree* select_query(int row  , int col , int* check  , int end_row , int end_col , int pain   ){
        static int compulsion = 0 ; 
        tree* start_of_tree ; 
        static tree* nested = NULL; 
        char ***buf = proper_data.query ; 
        for ( int i = row ; i <= end_row  ; i++ ){
        for ( int j = col ; j <= end_col   ; j++ ){

            if ( check == 1 ){
                return NULL ; 
            }

            if ( i == row && j == col ){
                if (  strcmp(buf[i][j], "SELECT")==0  ){
                    tree* node =  createNode(buf[0]) ; 
                    start_of_tree = node ; 
                    compulsion++ ;  
                    continue ; 
                }
            }

            else if ( strcmp(buf[i][j], ";")==0 ){
                return NULL   ; 
            }



            else if ( strcmp(buf[i][j], ")")==0  && !if_function(prev)) {
                if (buf[i][j+1] != NULL  ){
                    if ( strcmp(buf[i][j], "AS")==0 && j+1 <= end_col ){
                        if ( buf[i][j+2] == NULL && j+2 <= end_col ){
                            status_msg_input("the query is wrong ") ; 
                            check = 1 ; 
                            return NULL ; 
                        }
                        if ( nested != NULL ){
                        nested->as = strdup(buf[i][j+2] )  ; 
                        }
                    }
                }
                if ( i == end_row && j == end_col ){
                    return start_of_tree ; 
                }
            }


            else if ( strcmp(buf[i][j] , "UNION") == 0 || strcmp(buf[i][j] , "EXCEPT") == 0 || strcmp(buf[i][j] , "INTERSECT") == 0  ){
                pain = 1 ; 
                char *str[300] ; 
                str[0] = buf[i][j] ; 
                if ( buf[i][j] == NULL ){
                    if (i+1 <= end_row){
                        i = i+ 1 ; 
                        j = 0  ; 
                    }
                }
                else { 
                    j++ ; 
                }
                if ( strcmp(buf[i][j]  , "ALL") == 0 ){
                    str[1] = buf[i][j] ; 
                }

                tree* superior = createNode(str) ; 
                superior->children[superior->num] = start_of_tree ; 
                superior->num++ ; 
                start_of_tree = superior ; 
                if ( buf[i][j] == NULL ){
                    if (i+1 <= end_row){
                        i = i+ 1 ; 
                        j = 0  ; 
                    }
                }
                else { 
                    j++ ; 
                }

             start_of_tree->children[start_of_tree->num++] =  select_query( row  ,  col ,  check  ,  end_row ,  end_col ,  pain   ) ; 

            }


            else if (compulsion == 1){
                int start_row = i ; 
                int start_col = j ; 
                while ( strcmp(buf[i][j]  , "FROM ") == 0 ){
                    if ( buf[i][j] == NULL ){
                        if (i+1 <= end_row){s
                            i = i+ 1 ; 
                            j = 0  ; 
                        }
                    }
                    else { 
                        j++ ; 
                    }
                }
                node->children[node->num++] = comp_1(buf , node , start_row , start_col , i , j) ; 
                compulsion++ ; 
                node->children[node->num++]= createNode(buf[i][j]) ; 
                node = node->children[node->num - 1 ] ;  
                continue ; 

            }











            else if (compulsion == 2){
                int start_row = i ; 
                int start_col = j ; 
                while (strcmp(buf[i][j]  , "WHERE ") == 0 || strcmp(buf[i][j]  , "UNION") == 0 || strcmp(buf[i][j]  , "EXCEPT") == 0  || strcmp(buf[i][j]  , "INTERSECT") == 0   ||strcmp(buf[i][j]  , ";") == 0  ){
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
                if (strcmp(buf[i][j]  , "WHERE ") == 0  || strcmp(buf[i][j]  , ";") == 0 ) {
                    if ( j-1 > 0 ){
                        j = j-1 ; 
                    }
                    else {
                        int temp_row  = 0 ; 
                        int temp_col ; 
                        if ( i- 1 > 0 ){
                        temp_row = i -1 ; 
                        }
                        else {
                            i = 0 ; 
                            j = 0 ; 
                        }
                        temp_col = 0 ; 
                        int size = 0 ; 
                        for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; temp_col++ ){
                        }
                        j = temp_col -1 ; 
                        i = temp_row ; 
                    }
                }
                else { 
                    if ( pain == 0 ){
                    node->children[node->num++] = comp_2(buf , node , start_row , start_col , i , j , pain ) ; 
                    compulsion++ ; 
                    node->children[node->num++]= createNode(buf[i][j]) ; 
                    node = node->children[node->num - 1 ] ;  
                    }
                    else { 
                        start_of_tree->children[start_of_tree->num++] = comp_2(buf , node , start_row , start_col , i , j , pain )  ; 
                    }
                }
                continue ; 

            }




            else if (compulsion == 3){
                int start_row = i ; 
                int start_col = j ; 
                while (strcmp(buf[i][j]  , "UNION") == 0 || strcmp(buf[i][j]  , "EXCEPT") == 0  || strcmp(buf[i][j]  , "INTERSECT") == 0   ||strcmp(buf[i][j]  , ";") == 0  ){
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
                if (strcmp(buf[i][j]  , ";") == 0 ) {
                    if ( j-1 > 0 ){
                        j = j-1 ; 
                    }
                    else {
                        int temp_row = 0  ; 
                        int temp_col ; 
                        if ( i- 1 > 0 ){
                        temp_row = i -1 ; 
                        }
                        else {
                            i = 0 ; 
                            j = 0 ; 
                        }
                        temp_col = 0 ; 
                        int size = 0 ; 
                        for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; temp_col++ ){
                        }
                        j = temp_col -1 ; 
                        i = temp_row ; 
                    }
                }
                else { 
                    if ( pain == 0 ){
                    node->children[node->num++] = comp_3(buf , node , start_row , start_col , i , j , pain  , 0 ) ; 
                    compulsion++ ; 
                    node->children[node->num++]= createNode(buf[i][j]) ; 
                    node = node->children[node->num - 1 ] ;  
                    }
                    else { 
                        start_of_tree->children[start_of_tree->num++] =  comp_3(buf , node , start_row , start_col , i , j , pain  , 0 ) ; 
                    }
                }
                continue ; 

            }


        }
    }
    return start_of_tree ; 

}























































































tree *comp_1(char*** buf , tree * node  int i , int j , int end_row , int end_col ){

    tree * start = node ; 
    tree * temp ; 
    int check = 0 ; 

    while ( i <= end_row){
       while ( j <= end_col ) {
            if (  strcmp(buf[i][j] ,  "FROM"  ) == 0  ) {
                return start ; 
            }
            else { 
            if ( if_function( buf[i][j] ) == true ){
                temp->children[temp->num++] = function( buf , temp,check ,   i ,  j , end_row , end_col ) ; 
            }

            else  if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j-1 > 0 && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = 0 ; 
                        int end_row_dec  = 0 ; 
                        int braces = 1 ; 
                        for ( int m = i ; m <= end_row ; m++  ){
                            for ( int n = j+1 ; n <= end_col ; n++  ){
                                if ( strcmp(buf[m][n] , "(") == 0  ){
                                    braces++ ; 
                                }
                                else if ( strcmp(buf[m][n] , ")") == 0 ){
                                    braces-- ; 
                                }
                                if ( braces == 0 ){
                                    end_row_dec = m ; 
                                    end_col_dec = n ; 
                                    break ; 
                                }
                            }
                                if ( braces == 0 ){
                                    break ; 
                                }

                        }
                        tree * just_there  =  select_query( i  , j , check ,  end_row_dec ,  end_col_dec  ); 
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
                        nested  = temp ; 
                        temp = temp->children[temp->num- 1 ]  ; 
                        i = end_row_dec ; 
                        j = end_col_dec ; 
                    }
                    else {
                        while ( strcmp(buf[i][j] , ")") != 0 ){
                                if ( priority(buf[i][j]) != 0  ){
                                int temp_row = i ; 
                                int temp_col = j ; 
                                while ( buf[i][j] != NULL && strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                    if ( buf[i][j] == NULL ){
                                        if ( i+ 1 <= end_row){
                                        i++ ; 
                                        j = 0 ; 
                                    }
                                    else { 
                                        break ; 
                                    }
                                    }
                                    else {
                                        j++ ;
                                    }
                                }
                                tree *  just_there =  expression(buf , temp ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                if (just_there != NULL ){
                                temp->children[temp->num++ ]  = just_there ; 
                                }
                                }
                                else  {
                                if (if_syntax(buf[i][j]) == false ){
                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                            if ( buf[i][j] == NULL){
                                                if ( buf[i+1][0] != NULL ){
                                                i++ ;
                                                j = 0 ;
                                            } else {
                                                break ;
                                            }
                                        }
                                        else {
                                            j++ ; 
                                        }
                                                continue ;
                                        }
                                        temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                    }
                                    else { 
                                        check = 1 ; 
                                            return NULL ;   
                                    }
                            } 
                        }
                    }
            }




              else { 
                    if ( priority(buf[i][j]) != 0  ){
                        int temp_row = i ; 
                        int temp_col = j ; 
                        while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                            if ( buf[i][j] == NULL ){
                                if ( i+ 1 <= end_row){
                                i++ ; 
                                j = 0 ; 
                            }
                            else { 
                                break ; 
                            }
                            }
                            else {
                                j++ ;
                            }
                        }
                        tree*  just_there =  expression(buf , temp ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                        if (just_there != NULL ){
                        temp->children[temp->num++ ]  = just_there ; 
                        }
                    }         
                    else {
                        if (if_syntax(buf[i][j]) == false ){
                                if ( strcmp(buf[i][j] , ",") == 0 ){
                                    if (  buf[i][j] == NULL  ) {
                                         if ( buf[i+1][0] != NULL ){
                                        i++ ;
                                        j = 0 ;
                                    } 
                                }
                                else { 
                                    j++ ; 
                                }
                                        continue ;
                                }
                                 if (buf[i][j+1] != NULL && priority(buf[i][j+1]) != 0) {
                                    int temp_row = i ; 
                                    int temp_col = j ; 
                                    while (buf[i][j] != NULL &&  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
                                        if ( buf[i][j] == NULL ){
                                            if ( i+ 1 <= end_row){
                                            i++ ; 
                                            j = 0 ; 
                                        }
                                        else { 
                                            break ; 
                                        }
                                        }
                                        else {
                                            j++ ;
                                        }
                                    }
                                    tree*  just_there =  expression(buf , temp ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                    if (just_there != NULL ){
                                    temp->children[temp->num++ ]  = just_there ; 
                                    }
                                }
                                else {
                                       temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                }
                            }
                            else { 
                                check = 1 ; 
                                return NULL ;   
                            }
                    }                    
            }
        }


             if (buf[i][j+1] != NULL) {
                j++ ;
            }
            else {
                if (buf[i+1][0] != NULL) {
                    i++ ;
                    j = 0 ;
                }
                else {
                    break ;
                }
            }

            }
    }
    return start 

}









































