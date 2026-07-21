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


    typedef struct sql_master {
        uint32_t root_page_num ; 

    }

    void compile_select (compiler c ){
        emit(c , begin_op  , NULL , NULL , NULL , NULL ) ; 
        emit(open_read_op , c->cursor_num++ , sql_master->page_num ,  NULL , NULL , NULL    ) ; 
        emit(rewind_cursor , c->cursor_num++  , NULL , NULL , NULL , NULL  ) ; 
        

            

    }
}