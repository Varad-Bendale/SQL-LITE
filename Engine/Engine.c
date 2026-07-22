engine{
    tree *find_node(tree * jhad , char *word  , tree *ans , int first ){
        if ( jhad == NULL ){
            return NULL ; 
        }
        else if ( ans != NULL ){
            return ans ; 
        }
        if (strcmp(word , "SELECT") == 0 && first == 1  ){
            if ( strcmp(jhad->comp, word) == 0  ){
                ans  = jhad ; 
                return ans ; 
            }
        }

        int i = 0 ; 
        while (i < jhad->num){
            if (word != "SELECT" && strcmp(jhad->children[i]->comp , "SELECT" ) ==0  ){
                find_node(jhad->children[i] , word  , ans , 1  ) ; 
            }
        }
        return ans ; 
    }


    typedef struct find_the {
        struct tree* groupby;
        struct tree* orderby;
        struct tree* limit;
        struct tree* from;
        struct tree* having;
        struct tree* offset;
        struct tree* select;
        struct tree* where;
        struct tree* unio;
        struct tree* except;
        struct tree* intersect;
        struct tree* distinct;
        struct tree* join;
        struct tree* innerjoin;
        struct tree* leftjoin;
        struct tree* rightjoin;
        struct tree* crossjoin;
        struct tree* fullouterjoin;
        struct tree* case_expre ;
        struct tree* unioall;
        struct tree* exceptall;
        struct tree* intersectall;
    } find_the;



    typedef  find_the find  ; 
    struct tree *node = NULL;

    find* find_func(tree * jhad){
        find*temp ; 
        temp->groupby = find_node(jhad , "GROUP BY" , NULL) ; 
        temp->orderby = find_node(jhad, "ORDER BY", NULL);
        temp->limit = find_node(jhad, "LIMIT", NULL);
        temp->from = find_node(jhad, "FROM", NULL);
        temp->having = find_node(jhad, "HAVING", NULL);
        temp->offset = find_node(jhad, "OFFSET", NULL);
        temp->select = find_node(jhad, "SELECT", NULL);
        temp->where = find_node(jhad, "WHERE", NULL);
        temp->unio = find_node(jhad, "UNION", NULL);
        temp->except = find_node(jhad, "EXCEPT", NULL);
        temp->intersect = find_node(jhad, "INTERSECT", NULL);
        temp->distinct = find_node(jhad, "DISTINCT", NULL);
        temp->join = find_node(jhad, "JOIN", NULL);
        temp->innerjoin = find_node(jhad, "INNER JOIN", NULL);
        temp->leftjoin = find_node(jhad, "LEFT JOIN", NULL);
        temp->rightjoin = find_node(jhad, "RIGHT JOIN", NULL);
        temp->crossjoin = find_node(jhad, "CROSS JOIN", NULL);
        temp->fullouterjoin = find_node(jhad, "FULL OUTER JOIN", NULL);
        temp->case = find_node(jhad, "CASE", NULL);
        temp->unioall = find_node(jhad, "UNION ALL", NULL);
        temp->exceptall = find_node(jhad, "EXCEPT ALL", NULL);
        temp->intersectall = find_node(jhad, "INTERSECT ALL", NULL);
        return temp ; 
    }

    typedef struct compiler{
        type * typ ; 
        int count ; 
        int capacity ; 
        int register_counter ; 
        int cursor_num ; 
        select_info select ; 
    }

    typedef struct plan {
        bool where ; 
        bool orderby ; 
        bool groupby ; 
        bool case ; 
        bool join ; 
        bool from ; 
        bool select ; 
        bool case ; 
        bool having ; 
    }

    typedef struct comp{
        plan pl ; 
        int num_of_stuff ; 
        int current_num ; 
    }

    void emit(compiler * c , int op_code , int p1 , int p2 , int p3 , void * p4  ){
        if (c->count == c->capacity ){
            c->capactiy  = c->capacity * 2 ; 
            c->typ = realloc(c->typ , c->capacity * sizeof(type)) ; 
        }
        c->typ[c->count].operand =  op_code ; 
        c->typ[c->count].p1 = p1 ; 
        c->typ[c->count].p2 = p2 ; 
        c->typ[c->count].p3 = p3 ; 
        c->typ[c->count].p4 = p4 ; 
        c->count++ ; 

    }

    enum column_types{ 
        expression = 1 , 
        column_name , 
        aggregate_func  , 
        normal 
    }

    typedef struct select_select_info {
        column_types col_tp ;
        char *col_name[300] ; 
        int col_counter  ; 
        char * operator ; 
        select_select_info *left ; 
        select_select_info * right ; 
        char * as ; 
        int * num_value ; 
        char * char_value ; 
    }

    typedef struct select_info{
        select_select_info sel ; 
    }

    typedef struct sql_master {
        uint32_t root_page_num ; 

    }

    typedef struct col_det{
        char *name ; 
        int data_type ; 
    }

    typedef struct table  {
        char *name ; 
        int num_of_columns ; 
        col_det col[300] ; 
        int root_page_num ; 
    }

    int col_name_to_int( char * table_name , table * t ){
        for (int i = 0 ; i < t->num_of_columns ; i++ ){
           if ( strcmp(t->col[i].name , table_name ) == 0 ){
              return i ; 
           }
        }
        return -1  ; 
    }

    typedef struct tables_list{
        table * tables[300] ; 
        int num_of_tables ; 
    }

    table * lookup_table( tables_list * tab , char * table_name ){
        for ( int i = 0 ; i < tab->num_of_tables ; i++ ){
           if ( strcmp( tab[i]->name  , table_name  ) == 0 ) { 
                return tab[i] ; 
           }
        }
        return NULL ; 
    }

    void compile_select (compiler c ){
        emit(c , begin_op  , NULL , NULL , NULL , NULL ) ; 
        int cursor = c->cursor_num++ ; 
        emit(open_read_op , cursor , sql_master->page_num ,  NULL , NULL , NULL    ) ; 
        emit(rewind_cursor , cursor , NULL , NULL , NULL , NULL  ) ; 
        int register_num = c->register_counter++ ; 
        for ( int i = 0 ; i < c->select.sel.col_counter ; i++  ){
             emit(column_op ,cursor , col_name_to_int(c->select.sel.col_name[i] , ))
        }
        
        // we leaving at like see the for getting the integer of the column we need the table for the thing so we now only have the column name correctly but which of the table it is start your work from there okay cool 
            

    }
}
