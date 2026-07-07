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

void ast_work(tree * start){
    find* help = find_func( start) ; 
    if ((node = help->intersectall) || (node = help->exceptall) || (node = help->unioall) || (node = help->except) || (node = help->intersect) || (node = help->unio)){    
        superop(node) ; 
    }

   else  if ((node = help->from) ){    
        comp_from(node) ; 
    }

    else if ((node = help->where)){
        comp_where(node) ; 
    }
    else if ((node = help->groupby)){
        comp_group_by(node) ; 
    }
    else if ((node = help->distinct)){
        comp_distinct(node) ; 
    }
    else if ((node = help->orderby)){
        comp_order_by(node) ; 
    }
    else if ((node = help->limit) || (node = help->offset)  ){
        comp_limit(node) ; 
    }


}