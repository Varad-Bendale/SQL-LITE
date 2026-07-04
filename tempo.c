#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

char *SQLITE_HL_keywords[] = {
  "CREATE", "TABLE", "VIEW", "INDEX", "TRIGGER", "VIRTUAL", "DROP", "ALTER",
	"ADD", "COLUMN", "RENAME", "ATTACH", "DETACH", "DATABASE",
	"SELECT", "INSERT", "UPDATE", "DELETE", "REPLACE", "INTO", "VALUES", "SET",
	"FROM", "WHERE", "RETURNING", "UPSERT",
	"JOIN", "INNER", "LEFT", "RIGHT", "FULL", "OUTER", "CROSS", "NATURAL", "ON",
	"USING", "GROUP", "BY", "HAVING", "ORDER", "ASC", "DESC", "LIMIT", "OFFSET",
	"UNION", "INTERSECT", "EXCEPT", "ALL", "DISTINCT", "WITH", "RECURSIVE", "AS",
	"WINDOW", "OVER", "PARTITION", "ROWS", "RANGE", "GROUPS", "BETWEEN",
	"UNBOUNDED", "CURRENT", "ROW", "PRECEDING", "FOLLOWING",
	"PRIMARY", "KEY", "FOREIGN", "REFERENCES", "UNIQUE", "NOT", "NULL", "DEFAULT",
	"CHECK", "CONSTRAINT", "WITHOUT", "ROWID", "STRICT", "AUTOINCREMENT",
	"CONFLICT", "ROLLBACK", "ABORT", "FAIL", "IGNORE", "CASCADE", "RESTRICT",
	"NO", "ACTION", "DEFERRABLE", "DEFERRED", "INITIALLY", "IMMEDIATE",
	"BEGIN", "COMMIT", "END", "TRANSACTION", "SAVEPOINT", "RELEASE",
	"EXCLUSIVE", "CONCURRENT",
	"AND", "OR", "IN", "LIKE", "GLOB", "REGEXP", "MATCH", "IS", "ISNULL",
	"NOTNULL", "EXISTS", "CASE", "WHEN", "THEN", "ELSE", "CAST", "COLLATE",
	"RAISE", "INDEXED", "UNINDEXED",
	"PRAGMA", "VACUUM", "ANALYZE", "REINDEX", "EXPLAIN", "QUERY", "PLAN",
	"TEMP", "TEMPORARY", "IF", "EACH", "FOR", "OF", "NEW", "OLD",
	"BEFORE", "AFTER", "INSTEAD" , 
	"TRUE", "FALSE", "CURRENT_TIME", "CURRENT_DATE", "CURRENT_TIMESTAMP",
	"INTEGER", "INT", "REAL", "TEXT", "BLOB", "NUMERIC", "BOOLEAN",
	"DATE", "DATETIME", "FLOAT", "DOUBLE", "CHAR", "VARCHAR", "CLOB", NULL 
};

tree *function( char ***buf , tree * node ,int check  ,  int i , int j  , int end_row , int end_col ) ; 

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

bool if_syntax( char* word ){
	for ( int i = 0 ; SQLITE_HL_keywords[i] != NULL ; i++  ){
	if (strcmp( word , SQLITE_HL_keywords[i]  ) == 0 ){
		return true ; 
	}  ; 
	}	
	return false ; 
}

bool if_function( char* word ){
	for ( int i = 0 ; SQL_functions[i] != NULL ; i++  ){
	if (strcmp( word , SQL_functions[i]  ) == 0 ){
		return true ; 
	}  ; 
	}	
	return false ; 
}

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

Tree_def* make_leaf(char* value , int row , int col ) {
    Tree_def* n = malloc(sizeof(Tree_def));
    if (n == NULL) {
        return NULL;   
    }
    if ( value != NULL ){
        n->comp = strdup(value);
    } else {
        n->comp = NULL;
    }
    n->as = NULL;
    n->children = calloc(300, sizeof(tree*));
    n->direction = NULL;
    n->line = row;
    n->col = col;
    n->num = 0;
    return n;
}

tree*select_query( int i  , int j , int check ,  int end_row_dec ,  int end_col_dec  ){
    tree*node = createNode("select") ; 
    return node ; 
}

tree* expression(char ***buf , tree * node , int check , int i , int j  , int end_row , int end_col  ){
    fprintf(stderr, "[expr] ENTER i=%d j=%d end_row=%d end_col=%d tok=%s\n",
            i, j, end_row, end_col, buf[i][j] ? buf[i][j] : "NULL"); fflush(stderr);
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
        fprintf(stderr, "[expr] LOOP i=%d j=%d tok=%s operand_top=%d operator_top=%d prev_tree_top=%d\n",
                i, j, buf[i][j] ? buf[i][j] : "NULL", operand_top, operator_top, prev_tree_top); fflush(stderr);

        if (priority(buf[i][j]) != 0) {    
            fprintf(stderr, "[expr] priority token '%s'\n", buf[i][j]); fflush(stderr);
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
                        int num_temp = 2  ; 
                        if ( strcmp(oper, "NOT") == 0 ||strcmp(oper, "IS NULL") == 0 || strcmp(oper, "IS NOT NULL") == 0 )  {
                            num_temp = 1 ; 
                        }
                        if ( operand_top < num_temp ){
                            fprintf(stderr, "[expr] UNDERFLOW GUARD(inline): oper='%s' needs %d, have %d -> skip\n",
                                    oper, num_temp, operand_top); fflush(stderr);
                            operator_top-- ;
                            continue ;
                        }
                        tree * new  = createNode(oper) ; 
                        operator_top-- ; 
                        int pal = 0 ; 
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
                        fprintf(stderr, "[expr] if_function TRUE for '%s' at i=%d j=%d\n", buf[i][j], i, j); fflush(stderr);
                        int start_row = i ; 
                        int start_col = j ; 
                        int commas = 0 ; 
                        bool paren_opened = false ;
                        while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    paren_opened = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( paren_opened &&  commas == 0 ){
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
                            if ( paren_opened &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                        fprintf(stderr, "[expr] if_function paren-scan done: i=%d j=%d commas=%d prev_tree_top=%d\n",
                                i, j, commas, prev_tree_top); fflush(stderr);

                         tree * just_there;
                        if ( prev_tree_top == 0 || prev_tree[prev_tree_top - 1] == NULL ){
                            fprintf(stderr, "[expr] no existing subtree, creating throwaway parent\n"); fflush(stderr);
                            tree *func_parent = createNode(NULL);
                            just_there = function( buf , func_parent , check , start_row , start_col , i , j );
                        }
                        else {
                            fprintf(stderr, "[expr] attaching function to prev_tree top\n"); fflush(stderr);
                            just_there = function( buf , prev_tree[prev_tree_top - 1] , check , start_row , start_col , i , j );
                        }
                        fprintf(stderr, "[expr] function() returned %p\n", (void*)just_there); fflush(stderr);
                        if (just_there != NULL  ){
                                prev_tree[prev_tree_top++] = just_there ;
                              operands[operand_top++] = NULL ;
                        } 
                }
                else if ( strcmp(buf[i][j] , "(") == 0  ){
                    fprintf(stderr, "[expr] '(' branch i=%d j=%d\n", i, j); fflush(stderr);
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
                    fprintf(stderr, "[expr] plain operand '%s'\n", buf[i][j]); fflush(stderr);
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

    fprintf(stderr, "[expr] MAIN LOOP DONE, entering drain, operator_top=%d operand_top=%d prev_tree_top=%d\n",
            operator_top, operand_top, prev_tree_top); fflush(stderr);

    while (operator_top > 0) {
        char *oper = operators[operator_top - 1] ; 
        int num_temp = 2   ; 
        if ( strcmp(oper, "NOT") == 0 ||strcmp(oper, "IS NULL") == 0 || strcmp(oper, "IS NOT NULL") == 0 )  {
            num_temp = 1 ; 
        }

        if ( operand_top < num_temp ){
            fprintf(stderr, "[expr] UNDERFLOW GUARD(drain): oper='%s' needs %d, have %d -> skip\n",
                    oper, num_temp, operand_top); fflush(stderr);
            operator_top-- ;
            continue ;
        }

        tree * new  = createNode(oper) ; 
        operator_top-- ; 
        int pal = 0 ; 
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

    fprintf(stderr, "[expr] DRAIN DONE, prev_tree_top=%d, returning\n", prev_tree_top); fflush(stderr);

    tree*exp_tree = (prev_tree_top > 0) ? prev_tree[prev_tree_top - 1] : NULL ; 
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
                        continue ;   /* <-- FIX: i,j already sits on ")" (or another terminator);
                                             don't fall through to the blind j++ below, or we
                                             skip past the closing paren and the outer while
                                             loop misreads the next token (e.g. WHERE) as if
                                             it were still inside the function's argument list. */
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
                                    continue ;   /* <-- FIX: same reason as above */
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


tree *comp_2(char*** buf , tree * node  ,  int i , int j , int end_row , int end_col ){
    fprintf(stderr, "[comp2] ENTER i=%d j=%d end_row=%d end_col=%d\n", i, j, end_row, end_col); fflush(stderr);
    int start_row = i ; 
    int start_col = j ; 
    tree * start = node ; 
    tree * temp  = node ; 
    int check = 0 ; 
    int pain  = 0  ;
    while ( i <= end_row){
       fprintf(stderr, "[comp2] OUTER-LOOP i=%d end_row=%d\n", i, end_row); fflush(stderr);
       while ( j <= end_col ) {
            fprintf(stderr, "[comp2] INNER-LOOP i=%d j=%d end_col=%d tok=%s\n",
                    i, j, end_col, buf[i][j] ? buf[i][j] : "NULL"); fflush(stderr);

            if (  strcmp(buf[i][j] ,  "WHERE"  ) == 0  ) {
                fprintf(stderr, "[comp2] WHERE hit -> returning start\n"); fflush(stderr);
                return start ; 
            }

            else if (  strcmp(buf[i][j], "JOIN") == 0  || 
                    ( j+1 <= end_col && strcmp(buf[i][j], "INNER") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) || 
                    (j+1 <= end_col && strcmp(buf[i][j], "LEFT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                    (j+1 <= end_col && strcmp(buf[i][j], "RIGHT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                    (j+1 <= end_col && strcmp(buf[i][j], "CROSS") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                    (j+2 <= end_col && strcmp(buf[i][j], "FULL") == 0 && strcmp(buf[i][j+1], "OUTER") == 0 && strcmp(buf[i][j+2], "JOIN") == 0 )){

                fprintf(stderr, "[comp2] JOIN branch entered i=%d j=%d\n", i, j); fflush(stderr);
                int on = 0 ; 
                tree* starter  ; 

                if (strcmp(buf[i][j], "INNER") == 0 && strcmp(buf[i][j+1], "JOIN") == 0 ){
                    starter = createNode("INNER JOIN");
                    j = j + 2;
                }
                else if (strcmp(buf[i][j], "JOIN") == 0 ){
                    starter = createNode(buf[i][j]);
                    j++ ; 
                }
                else if (strcmp(buf[i][j], "LEFT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0 ){
                    starter = createNode("LEFT JOIN");
                    j = j + 2;
                }
                else if (strcmp(buf[i][j], "RIGHT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0 ){
                    starter =  createNode("RIGHT JOIN");
                    j = j + 2;
                }
                else if (strcmp(buf[i][j], "CROSS") == 0 && strcmp(buf[i][j+1], "JOIN") == 0 ){
                    starter =  createNode("CROSS JOIN");
                    j = j + 2;
                }
                else if (strcmp(buf[i][j], "FULL") == 0 && strcmp(buf[i][j+1], "OUTER") == 0 && strcmp(buf[i][j+2], "JOIN") == 0 ){
                   starter = createNode("FULL OUTER JOIN");
                    j = j + 3;
                }
                else {
                    check = 1 ; 
                    fprintf(stderr, "[comp2] JOIN: no match, check=1, returning NULL\n"); fflush(stderr);
                    return NULL  ; 
                }

                fprintf(stderr, "[comp2] JOIN type resolved: %s, new j=%d\n", starter->comp, j); fflush(stderr);
                tree *temp_word = starter ; 

                while ( strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && strcmp(buf[i][j] , "WHERE") != 0   && strcmp(buf[i][j], "GROUP") != 0 &&  strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0 &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0  && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){
                        fprintf(stderr, "[comp2] JOIN-INNER-LOOP i=%d j=%d tok=%s\n",
                                i, j, buf[i][j] ? buf[i][j] : "NULL"); fflush(stderr);

                        if ( if_function( buf[i][j] ) == true ){
                            fprintf(stderr, "[comp2] JOIN: if_function true for '%s'\n", buf[i][j]); fflush(stderr);
                            int start_row = i ; 
                            int start_col = j ; 
                            int commas = 0 ; 
                            bool paren_opened = false ; 
                              while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    paren_opened = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if (paren_opened && commas == 0 ){
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
                            if ( paren_opened &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                        fprintf(stderr, "[comp2] JOIN: calling function() start=(%d,%d) end=(%d,%d)\n",
                                start_row, start_col, i, j); fflush(stderr);
                        temp_word->children[temp_word->num++] = function( buf , temp_word,check ,   start_row ,  start_col , i , j ) ;
                        fprintf(stderr, "[comp2] JOIN: function() returned\n"); fflush(stderr);
                    }
                        

                    else  if ( strcmp(buf[i][j] , "(") == 0  ){
                            fprintf(stderr, "[comp2] JOIN: '(' encountered i=%d j=%d\n", i, j); fflush(stderr);
                            if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                                fprintf(stderr, "[comp2] JOIN: subquery detected\n"); fflush(stderr);
                                int end_col_dec  = 0 ; 
                                int end_row_dec  = 0 ; 
                                int braces = 1 ; 
                                int m = i ; 
                                int n = j+1 ; 
                                while (m<= end_row){
                                    while (n <= end_col){
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
                                        if ( buf[m][n] == NULL){
                                            if ( m +1 < end_row){
                                            m++ ; 
                                            n = 0 ; 
                                            }
                                            else { 
                                                break ; 
                                            }
                                        }
                                        else { 
                                            n++ ; 
                                        }
                                    }
                                        if ( braces == 0 ){
                                            break ; 
                                        }

                                }
                                tree * just_there  =  select_query( i  , j , check ,  end_row_dec ,  end_col_dec  ); 
                                if (just_there != NULL  ){
                                    temp_word->children[temp_word->num++]  = just_there ; 
                                }
                                temp_word = temp_word->children[temp_word->num- 1 ]  ; 
                                i = end_row_dec ; 
                                j = end_col_dec ; 
                            }
                            else {
                                while ( strcmp(buf[i][j] , ")") != 0 ){
                                        fprintf(stderr, "[comp2] JOIN-PAREN-LOOP i=%d j=%d tok=%s\n",
                                                i, j, buf[i][j] ? buf[i][j] : "NULL"); fflush(stderr);
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
                                            if (buf[i][j+1] != NULL ){
                                                j++ ; 
                                            }   
                                             else {
                                                    break ;
                                                }
                                        }
                                        if (buf[i][j] != NULL && strcmp(buf[i][j] , "ON") == 0   ){
                                        if (strcmp(starter->comp, "CROSS MODEL") == 0) {
                                                check = 1;
                                                fprintf(stderr, "[comp2] CROSS MODEL check trip, returning NULL\n"); fflush(stderr);
                                                return NULL;
                                            }
                                            j++;
                                            continue;
                                    }
                                    if ( priority(buf[i][j]) != 0 ){
                                        fprintf(stderr, "[comp2] JOIN-PAREN: priority token '%s', calling expression()\n", buf[i][j]); fflush(stderr);
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

                                        tree * just_there = expression( buf , temp_word , check , temp_row , temp_col , i , j ) ;
                                        fprintf(stderr, "[comp2] JOIN-PAREN: expression() returned %p\n", (void*)just_there); fflush(stderr);
                                        if ( just_there != NULL ){
                                            temp_word->children[temp_word->num++] = just_there ;
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
                                                    tree*  just_there =  expression(buf , temp_word , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                                    if (just_there != NULL ){
                                                    temp_word->children[temp_word->num++ ]  = just_there ; 
                                                    }
                                                }
                                                else {
                                                    fprintf(stderr, "[comp2] JOIN-PAREN: make_leaf('%s')\n", buf[i][j]); fflush(stderr);
                                                    temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                                }
                                            }
                                            else { 
                                                check = 1 ; 
                                                fprintf(stderr, "[comp2] JOIN-PAREN: if_syntax true on '%s', returning NULL\n", buf[i][j]); fflush(stderr);
                                                    return NULL ;   
                                            }
                                    } 
                                }
                            }
                    }




                    else { 
                            if (buf[i][j] != NULL && strcmp(buf[i][j] , "ON") == 0   ){
                                 if (strcmp(starter->comp, "CROSS MODEL") == 0) {
                                        check = 1;
                                        fprintf(stderr, "[comp2] CROSS MODEL(2) trip, returning NULL\n"); fflush(stderr);
                                        return NULL;
                                    }
                                    j++;
                                    continue;
                            }
                             if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                                    temp->children[temp->num++] = make_leaf("*", i, j) ;
                                }
                            if ( priority(buf[i][j]) != 0  ){
                                fprintf(stderr, "[comp2] JOIN-ELSE: priority token '%s', calling expression()\n", buf[i][j]); fflush(stderr);
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
                                tree*  just_there =  expression(buf , temp_word , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                fprintf(stderr, "[comp2] JOIN-ELSE: expression() returned %p\n", (void*)just_there); fflush(stderr);
                                if (just_there != NULL ){
                                temp_word->children[temp_word->num++ ]  = just_there ; 
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
                                            while ( strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
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
                                            tree*  just_there =  expression(buf , temp_word , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
                                            if (just_there != NULL ){
                                            temp_word->children[temp_word->num++ ]  = just_there ; 
                                            }
                                        }
                                        else {
                                            fprintf(stderr, "[comp2] JOIN-ELSE: make_leaf('%s')\n", buf[i][j]); fflush(stderr);
                                            temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                        }
                                    }
                                    else { 
                                        check = 1 ; 
                                        fprintf(stderr, "[comp2] JOIN-ELSE: if_syntax true on '%s', returning NULL\n", buf[i][j]); fflush(stderr);
                                        return NULL ;   
                                    }
                            }                    
                    }


                    fprintf(stderr, "[comp2] JOIN-INNER: about to advance, i=%d j=%d bufNext=%s\n",
                            i, j, buf[i][j+1] ? buf[i][j+1] : "NULL"); fflush(stderr);
                    if (buf[i][j+1] != NULL) {
                        j++ ;
                    }
                    else {
                        if (buf[i+1][0] != NULL) {
                            i++ ;
                            j = 0 ;
                        }
                        else {
                            fprintf(stderr, "[comp2] JOIN-INNER: no more rows, breaking\n"); fflush(stderr);
                            break ;
                        }
                    }

                }

                fprintf(stderr, "[comp2] JOIN-INNER-LOOP exited, i=%d j=%d\n", i, j); fflush(stderr);

                if ( j-1 > 0 ){
                    j = j-1 ; 
                }
                else {
                    int temp_row ; 
                    int temp_col ; 
                    if ( i- 1 > start_row ){
                        temp_row = i -1 ; 
                        temp_col = start_col ; 
                        for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; temp_col++ ){
                        }
                        j = temp_col -1 ; 
                        i = temp_row ; 
                    }
                  
          
                      else {
                        i = start_row ; 
                        j = start_col ; 
                    }
                }

                fprintf(stderr, "[comp2] JOIN: post-adjust i=%d j=%d pain=%d\n", i, j, pain); fflush(stderr);

                if ( pain == 0 ){
                    temp->children[temp->num++] = starter ; 
                }
                else { 
                    fprintf(stderr, "[comp2] JOIN: pain!=0, returning starter\n"); fflush(stderr);
                    return starter ; 
                }

                }



            else { 
                fprintf(stderr, "[comp2] OTHER-branch i=%d j=%d tok=%s\n",
                        i, j, buf[i][j] ? buf[i][j] : "NULL"); fflush(stderr);

                if ( if_function( buf[i][j] ) == true ){
                    fprintf(stderr, "[comp2] OTHER: if_function true for '%s'\n", buf[i][j]); fflush(stderr);
                    int start_row = i ; 
                    int start_col = j ; 
                    int commas = 0 ; 
                    bool paren_opened = false ; 
                          while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    paren_opened = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( paren_opened && commas == 0 ){
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
                            if ( paren_opened &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                fprintf(stderr, "[comp2] OTHER: calling function() at i=%d j=%d end_row=%d end_col=%d\n",
                        i, j, end_row, end_col); fflush(stderr);
                temp->children[temp->num++] = function( buf , temp,check ,   i ,  j , end_row , end_col ) ;
                fprintf(stderr, "[comp2] OTHER: function() returned\n"); fflush(stderr);
            }
                

            else  if ( strcmp(buf[i][j] , "(") == 0  ){
                    fprintf(stderr, "[comp2] OTHER: '(' encountered i=%d j=%d\n", i, j); fflush(stderr);
                    if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        fprintf(stderr, "[comp2] OTHER: subquery detected\n"); fflush(stderr);
                        int end_col_dec  = 0 ; 
                        int end_row_dec  = 0 ; 
                        int braces = 1 ; 
                        int m = i ; 
                        int n = j+1 ; 
                        while (m<= end_row){
                            while (n <= end_col){
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
                                if ( buf[m][n] == NULL){
                                    if ( m +1 < end_row){
                                    m++ ; 
                                    n = 0 ; 
                                    }
                                    else { 
                                        break ; 
                                    }
                                }
                                else { 
                                    n++ ; 
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
                                fprintf(stderr, "[comp2] OTHER-PAREN-LOOP i=%d j=%d tok=%s\n",
                                        i, j, buf[i][j] ? buf[i][j] : "NULL"); fflush(stderr);
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
                                    if (buf[i][j+1] != NULL ){
                                        j++ ; 
                                    }   
                                        else {
                                            break ;
                                        }
                                }
                               if ( priority(buf[i][j]) != 0 ){
                                fprintf(stderr, "[comp2] OTHER-PAREN: priority token '%s', calling expression()\n", buf[i][j]); fflush(stderr);
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
                                fprintf(stderr, "[comp2] OTHER-PAREN: expression() returned %p\n", (void*)just_there); fflush(stderr);
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
                                            fprintf(stderr, "[comp2] OTHER-PAREN: make_leaf('%s')\n", buf[i][j]); fflush(stderr);
                                            temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                        }
                                    }
                                    else { 
                                        check = 1 ; 
                                        fprintf(stderr, "[comp2] OTHER-PAREN: if_syntax true on '%s', returning NULL\n", buf[i][j]); fflush(stderr);
                                            return NULL ;   
                                    }
                            } 
                        }
                    }
            }




              else { 
                 if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                        temp->children[temp->num++] = make_leaf("*", i, j) ;
                    }
                    else if ( priority(buf[i][j]) != 0  ){
                        fprintf(stderr, "[comp2] OTHER-ELSE: priority token '%s', calling expression()\n", buf[i][j]); fflush(stderr);
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
                        fprintf(stderr, "[comp2] OTHER-ELSE: expression() returned %p\n", (void*)just_there); fflush(stderr);
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
                                       fprintf(stderr, "[comp2] OTHER-ELSE: make_leaf('%s')\n", buf[i][j]); fflush(stderr);
                                       temp->children[temp->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                }
                            }
                            else { 
                                check = 1 ; 
                                fprintf(stderr, "[comp2] OTHER-ELSE: if_syntax true on '%s', returning NULL\n", buf[i][j]); fflush(stderr);
                                return NULL ;   
                            }
                    }                    
            }
        }


             fprintf(stderr, "[comp2] end-of-inner about to advance i=%d j=%d\n", i, j); fflush(stderr);
             if (buf[i][j+1] != NULL) {
                j++ ;
            }
            else {
                if (buf[i+1][0] != NULL) {
                    i++ ;
                    j = 0 ;
                }
                else {
                    fprintf(stderr, "[comp2] end-of-inner: no more tokens, breaking outer\n"); fflush(stderr);
                    break ;
                }
            }

            }
            break;
    }
    fprintf(stderr, "[comp2] RETURN start=%p comp=%s\n", (void*)start, start->comp ? start->comp : "NULL"); fflush(stderr);
    return start  ; 

}
void printTree(Tree_def* root, int depth) {
    if (root == NULL) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf(" %s \n", root->comp ? root->comp : "NULL" );

    if (root->children != NULL) {
        for (int i = 0; i < root->num; i++) {
            printTree(root->children[i], depth + 1);
        }
    }

}

int main() {
    char *tokens[14] = { "*" , "FROM" , "users" , "JOIN" , "students" , "*" , "AVG" , "(" , "a" , "+" , "b" , ")" , "WHERE" , NULL};
    char **rows[1] = { tokens };
    char ***buf = rows;

    tree *root = createNode("SELECT");
    // start comp_2 at "users" (index 2), i.e. right after FROM
    tree *result = comp_2(buf, root, 0, 2, 0, 14);

    printf("\n=== TREE ===\n");
    printTree(result, 0);
    return 0;
}





