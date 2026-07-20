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




    void compile(){

    }
}#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h> 
#include<termios.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/ioctl.h> 
#include<sys/types.h>
#include<time.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdbool.h>
#include <fcntl.h>
#define ctrl(k) ((k) & 0x1f) 
#define version "0.0.1"
#define tab_spaces 8
#define nope -1.0f
#define MAX 1024 
#define quit 1
#define PAGE_SIZE 4096
int highlight = 0 ; 




typedef struct row_input{ 
	int size ; 
	char *data ; 
	char *render  ; 
	int render_size ; 
	bool query ; 
	bool comment ; 
	int comment_close_col ;
	unsigned char *hl  ; 
} row_input ; 

void status_msg_input(const char* msg, ...);
void screen_ready(void);
int  raw_key_press(void);
char *query_data_recovery(void);
 
struct editor_global { 
	int cursor_rows ; 
	int cursor_cols ; 
	int rows  ; 
	int cols ; 
      int row_offset ; 
	int col_offset ; 
	row_input *ri ;
	int row_length ; 
	int changes ; 
	struct termios original  ; 
      int render_cols ; 
	char *filename ; 
	char status_messege[80] ; 
	time_t messege_time ; 
	int comment_start  ; 
	int query_lines ; 
	int *col_max_sizes ; 
} ;

struct proper_data_we_need { 
	char **query  ; 
	char ***data ; 
} ;

struct proper_data_we_need proper_data ; 
struct editor_global  edit ; 

struct dynamic_buffer{
 	char *data ; 
	int size ; 

} ;
char * temp = NULL  ; 

int first = 0 ; 

enum settings_keys {
	Backspace = 127 , 
    Arrow_left = 1000 ,
    Arrow_right ,
    Arrow_up ,
    Arrow_down ,  
    Page_up , 
    Page_down , 
    Home_key , 
    End_key  , 
    delete 
} ;

enum hl{
	hl_normal = 0 ,
	hl_number , 
	hl_search  , 
	hl_comment , 
	hl_syntax
} ; 





#define dynamic_buffer_starter { NULL , 0 } 




char*saving_name(char *name , void (*func)(char *  , int  ) ){
	size_t max  = 128  ; 
		int len = 0 ; 
	char * buf = malloc( max)  ; 

	buf[0] = '\0' ; 
	while(1) {
		status_msg_input(name , buf) ; 
		screen_ready() ; 
		int c = raw_key_press() ; 
		if ( c == delete || c == Backspace || c == ctrl('h')){
			if ( len != 0 ){
				len = len -1 ; 
				buf[len] = '\0' ; 
			}
		}
		else if ( c == '\r' ){
			status_msg_input(" ") ; 
			if ( func != NULL) {
				func(buf , c ) ; 
			}
			return buf ; 
		}
		else if ( c == '\x1b'){
			status_msg_input("The saving is cancel ") ; 
			if ( func != NULL) {
				func(buf , c ) ; 
			}
			free(buf) ; 
			return NULL ; 
		}
		else { 
			if ( !iscntrl(c) && c < 128 ){
				if ( len == max -1 ){ 
					max  = max *2 ; 
					buf  = realloc(buf ,max ) ; 
				}
				buf[len] = c  ; 
				len++ ; 
				buf[len] = '\0' ; 
			}
			if ( func != NULL) {
				func(buf , c ) ; 
			}
		}
	}
}




int render_to_cols(row_input *row  , int pos ){
	int curent_pos =  0 ; 
	for ( int i = 0 ; i < row->size ; i++ ){
		if ( row->data[i] == '\t'){
			curent_pos = curent_pos + (tab_spaces  -1 ) - ( curent_pos % tab_spaces ); 
		}
		else{
			curent_pos++ ; 
		}
		if ( curent_pos > pos ){ 
			return i ; 
		}
	}
	return row->size  ; 
}


void dynamic_buffer_append( struct dynamic_buffer *temp  , const char *s , int len  ){ 
    char *need = realloc(temp->data , temp->size+len) ;
     if (need == NULL) {
         return ;  
     } 
     memcpy( &need[temp->size] , s , len ) ; 
     temp->data = need ; 
     temp->size += len ; 
} 



void finder_word(char *ques ,  int pos  ){
  static int last_match = -1;
  static int  status ; 
  static char *status_line  = NULL ; 
  if ( status_line != NULL ){
	memcpy(edit.ri[status].hl , status_line , edit.ri[status].render_size   ) ; 
	free(status_line) ; 
	status_line = NULL ; 
  } 
  static int direction = 1;
	  if (pos == '\r' || pos == '\x1b') {
   		 last_match = -1 ; 
		 direction = 1 ; 
		 return ; 
 	 }
	else if (pos == Arrow_up || pos == Arrow_left ){
		direction = -1 ; 
	}
	else if (pos == Arrow_down || pos == Arrow_right  ){
		direction = 1 ; 
	}
	if ( last_match == -1 ){
		direction = 1 ; 
	}
	int current  = last_match ; 
	for ( int i =  0 ; i < edit.row_length ; i++ ){
		current  = current + direction  ; 
		if ( current == -1 ){
			current = edit.row_length-1 ; 
		} 
		if ( current  == edit.row_length){
			current = 0 ;
		}
		row_input * row  = &edit.ri[current] ; 
		char *found = strstr(row->render , ques) ; 
		if ( found ){
		last_match = current ; 
		edit.cursor_rows = current ; 
		edit.cursor_cols = render_to_cols( row , found - row->render ) ; 
		status = current ; 
		status_line = malloc(row->render_size ) ; 
		memcpy(status_line , row->hl , row->render_size   ) ; 	
		memset(&row->hl[found - row->render ] , hl_search , strlen(ques)  )  ; 
		if ( edit.cursor_rows < edit.row_offset ){
			edit.row_offset = edit.cursor_rows ;
		}
		if ( edit.cursor_rows  >  edit.row_offset + edit.rows ){
		edit.row_offset = edit.cursor_rows ; 
		} 
		break ; 
		}
}
} 


void finder(){
	int prev_cols = edit.cursor_cols ; 
	int prev_rows  = edit.cursor_rows; 
	int prev_colset  = edit.col_offset; 
	int prev_rowset  = edit.row_offset; 
	char *ques = saving_name("escape = cancel and enter = continue , enter your question %s " , finder_word ) ; 
	if ( ques != NULL ){ 
		free(ques) ; 
	}
	else { 
	edit.cursor_cols =  prev_cols  ; 
	edit.cursor_rows =  prev_rows  ; 
	edit.col_offset =  prev_colset  ; 
	edit.row_offset =  prev_rowset ; 
	}
	

}






void status_msg_input (const char* msg , ...  ){ 
    va_list temp   ; 
	va_start(temp  , msg) ; 
	vsnprintf( edit.status_messege , sizeof(edit.status_messege ) , msg , temp) ; 
	va_end(temp) ; 
    edit.messege_time = time(NULL) ; 
}


char *before_saving(int *buflen){
	int len = 0 ; 
	for ( int i = 0 ; i < edit.row_length ; i++ ){ 
			len = len + edit.ri[i].size ; 
	}
	*buflen = len+edit.row_length ; 
	char *buf  = malloc(len+edit.row_length)  ; 
	char *p = buf ; 
	for ( int i = 0 ; i < edit.row_length  ; i++ ){
		if ( edit.ri[i].query == false){
		memcpy( p , edit.ri[i].data , edit.ri[i].size) ; 
		p = p + edit.ri[i].size ; 
		*p = '\n' ; 
		p++ ; 
		}
	}

   return buf ; 
}

void saving(){
	if (edit.filename == NULL){
		edit.filename = saving_name("Enter file name %s" , NULL) ; 
	}
	if (edit.filename == NULL){
		status_msg_input("Save cancelled.") ;
		return ;
	}
	int len  ; 
	char *buf = before_saving( &len ) ; 
	int token  = open(edit.filename ,   O_RDWR | O_CREAT , 0644) ; 

	if ( token != -1 ) { 
	if ( ftruncate(token , len ) != -1 ) {   
	if ( write( token , buf  , len ) == len ){ 
		status_msg_input("%d copied to the file " , len) ; 
		edit.changes = 0 ; 
	close(token) ; 
	free(buf) ; 
	return  ; 
	} 
	} 
	close(token) ; 

	status_msg_input("Error file could'nt be saved " ) ; 
	free(buf) ; 

} 

void free_dynamic_buffer ( struct dynamic_buffer *temp){
      free(temp->data)  ; 
}

int seperator(int c ){
	return isspace(c) || c == '\0' || strchr(",.()+-/*=~%<>[];&", c) != NULL ; 
}




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

char *C_HL_keywords[] = {
  "int", "char", "short", "long", "float", "double", "void",
  "signed", "unsigned",
  "const", "volatile", "restrict", "_Atomic",
  "auto", "static", "extern", "register",
  "if", "else", "switch", "case", "default",
  "for", "while", "do",
  "break", "continue", "return", "goto",
  "struct", "union", "enum", "typedef",
  "sizeof", "alignof", "alignas",
  "_Bool", "_Complex", "_Imaginary",
  "_Static_assert", "_Noreturn", "_Generic",
  "_Thread_local",
  "inline", "__inline__",
  "__asm__", "asm", "__volatile__",
  "__attribute__", "__typeof__",
  "__restrict__", "__inline",
  "NULL", "true", "false",

  NULL
};

bool if_syntax( char* word ){
	for ( int i = 0 ; SQLITE_HL_keywords[i] != NULL ; i++  ){
	if (strcmp( word , SQLITE_HL_keywords[i]  ) == 0 ){
		return true ; 
	}  ; 
	}	
	return false ; 
}



void color(row_input * row){
	row->hl = realloc(row->hl ,row->render_size ) ; 
	memset(row->hl , hl_normal , row->render_size ) ; 
	int prev_col = -1  ; 
	bool check = true  ; 
	bool comment = false ; 
	int i = 0 ; 
	int k = 0 ; 
	char *buf  = NULL ;
	int col = 0 ;  
	while (i < row->render_size ){
		if(i >= 1 ){ 
			check = seperator(row->render[i-1]) ; 
		}
		else { 
			check = true ; 
		}
		if ( i+1 < row->render_size && row->render[i] == '/' && row->render[i+1] == '/' ) {
			comment = true  ; 
		}
		if (comment) {                    
            row->hl[i] = hl_comment ;
            i++ ;
            continue ;
        }

	

		if ( isdigit(row->render[i] ) && (prev_col == hl_number || check == true ) || (row->render[i] == '.' && prev_col == hl_number )) {
			row->hl[i] = hl_number ; 
			prev_col = hl_number  ;
			check = false ; 
		}
		else { 
		if ( seperator(row->render[i]) ){
			if ( buf != NULL ){ 
				if ( if_syntax( buf )){ 
					int mon = col ; 
					while (mon < i ){
						row->hl[mon] = hl_syntax ; 	
						mon++ ; 	
					}
				}
			free(buf) ; 
			buf = NULL ; 
			}

			k = 0 ; 
			col = i+1   ; 
		}
		else { 
		buf = realloc(buf ,k+2 ) ; 
		buf[k++] = row->render[i] ; 
		buf[k] = '\0' ; 
	
		}
		prev_col = hl_normal  ; 
	}
		i++ ; 
}
	if ( buf != NULL ){
	if ( if_syntax( buf )){ 
		int mon = col ; 
		while (mon < i ){
			row->hl[mon] = hl_syntax ; 	
			mon++ ; 	
		}
	}
	free(buf) ; 
}
}


int decide_color(int hl){
	switch( hl ){ 
		case hl_comment:
			return 31 ; 
	  case hl_number: 
	  	return 32 ; 
		case hl_search :
		  return  34 ; 
	  case hl_normal: 
	  	return 37 ; 
	  case hl_syntax : 
	     return 35 ; 
	}
	return 0 ; 
}



void render_input (row_input *row ) { 
	int tabs  = 0 ; 
	row->render_size  = 0 ;
	for ( int i = 0 ; i < row->size ; i++ ) { 
		if ( row->data[i] == '\t' ) { 
			tabs = tabs + 1 ; 
		} 
	} 
	free ( row->render) ; 
	row->render = malloc( row->size + ( tabs*( tab_spaces -1  )  + 1  ) ) ; 

	int k = 0 ; 
	for ( int i = 0 ; i < row->size ; i++ ) { 
		if ( row->data[i] != '\t') { 
			row->render[k] = row->data[i] ; 
		      k = k + 1 ; 
		} 
		else { 
		   row->render[k] = ' '  ;
			k = k + 1 ;  
			while(k % tab_spaces != 0  )  { 
				row->render[k] = ' '  ; 
		      	k = k + 1 ; 
			} 
	} 
    } 
	  row->render[k] = '\0' ; 
	row->render_size = k ; 
	color(row) ; 
	} 



	       


	void die(const char *s) { 
   write(STDOUT_FILENO , "\x1b[2J" , 4 ) ; 
   write(STDOUT_FILENO , "\x1b[H" , 3 ) ; 
   perror( s ) ; 
   exit(1) ; 
} 
 

 
void append_lines( char *line , int pos  , size_t len) { 
	if ( pos < 0 || pos > edit.row_length){
		return ; 
	}
    edit.ri = realloc( edit.ri , sizeof(row_input)*(edit.row_length+1) )  ;  
	memmove(&edit.ri[pos + 1] , &edit.ri[pos] , sizeof(row_input)*(edit.row_length -pos  )) ; 
    edit.ri[pos].size = len ; 
    edit.ri[pos].data = malloc( len+1 ) ;  
    memcpy(edit.ri[pos].data , line , len) ; 
    edit.ri[pos].data[len] = '\0' ; 
    edit.ri[pos].render = NULL ; 
    edit.ri[pos].render_size = 0 ; 
	edit.ri[pos].hl = NULL ; 
	edit.ri[pos].query = false ; 
    render_input(&edit.ri[pos]) ; 
    edit.row_length++   ; 
	edit.changes++ ; 
}  

void insert_new_lines(){
	bool was_query = edit.ri[edit.cursor_rows].query ;
	if (edit.cursor_cols == 0 ){
		append_lines( "" , edit.cursor_rows  ,  0)  ; 
	}
	else{ 
		row_input *row = &edit.ri[edit.cursor_rows] ; 
		append_lines(&row->data[edit.cursor_cols] , edit.cursor_rows + 1  , row->size - edit.cursor_cols) ; 
		row = &edit.ri[edit.cursor_rows]  ; 
		row->size = edit.cursor_cols ; 
		row->data[row->size] = '\0' ; 
		render_input(row) ; 
	}
   if ( was_query ){            
        edit.query_lines++ ; 
        edit.ri[edit.cursor_rows + 1].query = true ; 
    }
	edit.cursor_rows++ ; 
	edit.cursor_cols = 0 ; 
}




void text_in_input_buffer(char *file){ 
    FILE *fp  = fopen(file , "r") ;
	edit.changes = 0 ; 
    edit.filename = strdup(file) ; 
    if (!fp) {									
      die("fopen") ; 
    }
	edit.row_length = 0;
	append_lines("", 0, 0); 	
    char *line  = NULL ; 
    size_t mem = 0  ; 
    ssize_t len  ; 
    while ( ( len =  getline(&line , &mem , fp  ) )  != -1  ) { 
    while( len > 0 && (  ( line[len-1] == '\n' ) ||  ( line[len-1] == '\r' ) ) )  {
	    len-- ; 	
	} 
    append_lines( line  , edit.row_length , len )  ; 
   } 
   free( line) ; 
   fclose( fp ) ; 
    for (int i = 0; i < edit.row_length; i++) {
        edit.ri[i].query = false;
    }
	edit.ri[0].query = true;
   first = 1 ; 

} 


void insert_char( row_input *line ,  int pos ,  int c ){ 
	if ( pos < 0 || pos > line->size ){ 
		pos  = line->size ; 
	}
	line->data = realloc( line->data , line->size + 2 ) ; 
    memmove( &line->data[pos+ 1 ] , &line->data[pos] ,  line->size - pos + 1 ) ; 
	line->size++ ; 
	line->data[pos] = c ; 
	render_input(line)  ; 
	edit.changes++ ; 
}




void excel_like(){
    char ***temp = proper_data.data ;
	edit.col_max_sizes = NULL ; 
	free(edit.col_max_sizes) ; 

	if ( temp == NULL ){
		return ; 
	}
	int cols = 0 ; 
	if ( temp[0] != NULL ){
	for ( int i = 0 ; temp[0][i] != NULL  && temp[0][i][0] != '\0' ; i++ ){
			cols++ ; 
	}
	}
	edit.col_max_sizes  = malloc(cols) ; 
	int *max_size = calloc(cols , sizeof(int)) ; 
	for ( int i = 0 ; temp[i] != NULL ; i++ ){
		for ( int j = 0 ; j < cols && temp[i][j] ; j++ ){
				if ( strlen(temp[i][j]) > max_size[j] ){
					max_size[j] = strlen(temp[i][j]) ; 
					edit.col_max_sizes[j] = max_size[j] ; 
				} 
		}
	}
	for ( int i = 0 ; temp[i] != NULL ; i++ ){
		int row  = i + edit.row_offset ; 
		if ( row > edit.row_length ){
			break ; 
		}
		int total = 0 ;
		for ( int j = 0 ; j < cols && temp[i][j] != NULL && temp[i][j][0] != '\0' ; j++ ){
			total += max_size[j] + 3 ;
		}
		char *buf = malloc( total + 1 ) ;
		int m = 0 ; 
		for ( int j = 0 ; j < cols && temp[i][j] != NULL && temp[i][j][0] != '\0' ; j++ ){
			memcpy(&buf[m] , temp[i][j] , strlen(temp[i][j]) ) ; 
			m = m + strlen(temp[i][j])  ; 
			int leftout = max_size[j] - strlen(temp[i][j]) + 1 ; 
			memset( &buf[m] , ' ' ,  leftout  ) ; 
			m = m + leftout ; 
			memset( &buf[m] , ',' ,  1  ) ; 
			m = m + 1  ; 
		}
	        buf[m] = '\0' ;	
			row_input * line = &edit.ri[i+1]  ; 
			free(line->data) ; 
			line->data = buf ; 
			line->size = m  ; 
			edit.changes++ ; 
	}
	free(max_size) ; 
	for ( int j = 0 ; j < edit.row_length ; j++ ){
        render_input(&edit.ri[j]) ;
    }

}



void disable_raw_mode(){
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &edit.original) == -1){
  	  die("tcsetattr");
	}
}


void rawmode(){
    if (tcgetattr(STDIN_FILENO, &edit.original) == -1){
       die("tcgetattr");
    } 
    struct termios temp = edit.original ; 
    temp.c_iflag &= ~(IXON | ICRNL ) ; 
    temp.c_oflag &= ~(OPOST ) ; 
    temp.c_lflag &= ~(IEXTEN|ECHO|ICANON|ISIG ) ; 
    temp.c_cc[VMIN] = 0 ; 
    temp.c_cc[VTIME] = 1 ; 
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH , &temp) == -1){
       die("tcsetattr");
    } 
    if (atexit(disable_raw_mode) != 0 ){
       die("atexit");
    } 
}

int raw_key_press(){
     int temp ; 
	char c = '\0' ; 

     while((temp = read(STDIN_FILENO, &c, 1)) != 1 )   {
	if (temp == -1 && errno != EAGAIN){
       die("read");
    } 
    }

    first = 1 ; 

     if ( c == '\x1b') { 
		char buf[3] ; 
	   if ( read(STDIN_FILENO , &buf[0] , 1) != 1) { 
		return '\x1b' ; 
	      } 
	   if ( read(STDIN_FILENO , &buf[1] , 1) != 1) { 
		return '\x1b' ; 
	     } 
	   if ( buf[0] == '[' ) { 
	       if ( buf[1] >= '0' && buf[1] <= '9' ) { 
		   if ( read(STDIN_FILENO , &buf[2] , 1) != 1) { 
		      return '\x1b' ; 
	           } 
		   if ( buf[2] == '~') { 
 		      switch( buf[1] ) { 
			case '1' : return Home_key;
           	       case '4' : return End_key;
			case '5' : return Page_up ; 
			case '6' : return Page_down ; 	
			case '7' : return Home_key;
           	       case '8' : return End_key;
			case '3' : return delete  ; 
                   } 
		   } 
                  }
		else { 
 	          switch ( buf[1] ) {
	        	case 'A' : return  Arrow_up ; 
	        	case 'B' : return Arrow_down ; 
		       case 'C' : return  Arrow_right ; 
		       case 'D' : return Arrow_left ; 
			case 'H' : return Home_key;
           	       case 'F' : return End_key;
		    }
		}
	       } 
		if ( buf[0] == 'O') { 
		  switch ( buf[1] ) {
			case 'H' : return Home_key;
           	       case 'F' : return End_key;

                 } 
		}	
	return '\x1b'  ; 
    }


    
    else { 
	return c ; 
    } 
    

}

int position_as_per_cursor( row_input *row ){ 
	int num  = 0 ; 
	 for ( int i = 0 ; i < edit.cursor_cols ; i++ ) { 
		if ( row->data[i] == '\t' ) { 
			num = num + (tab_spaces  -1 ) - ( num % tab_spaces ); 
		} 
		else { 
			num = num + 1 ; 	
		}
	} 
return num ; 
} 



void cursor_change(int c ){ 
	int prev_col ; 
	switch (c)  {
	  case Arrow_up : 
		if( edit.cursor_rows  != 0 ) { 
			prev_col = position_as_per_cursor(&edit.ri[edit.cursor_rows])  ; 
		   edit.cursor_rows -= 1  ; 
			edit.cursor_cols = render_to_cols(&edit.ri[edit.cursor_rows] , prev_col ) ; 
		} 
		   break ; 

	  case Arrow_down : 
		if (edit.cursor_rows < edit.row_length - 1 ) {
				prev_col = position_as_per_cursor(&edit.ri[edit.cursor_rows])  ; 
						  edit.cursor_rows += 1 ; 
				   edit.cursor_cols = render_to_cols(&edit.ri[edit.cursor_rows] , prev_col ) ; 
		} 
		break ; 


	 case Arrow_left : 
		if ( edit.cursor_cols == 0  ) { 
			if ( edit.cursor_rows != 0 ) { 
			    edit.cursor_rows -= 1 ; 
			    edit.cursor_cols = edit.ri[edit.cursor_rows].size  ; 
			 } 
		} 
		else { 
		   edit.cursor_cols -= 1  ;  
		}
		   break ; 


	case Arrow_right : 
	if ( edit.cursor_rows == edit.query_lines -1 && edit.cursor_cols == edit.ri[edit.cursor_rows].size  ){
		break ; 
	}
		if ( edit.cursor_cols < edit.ri[edit.cursor_rows].size ) { 
			edit.cursor_cols += 1 ; 
		} 

		else if ( edit.cursor_rows < edit.row_length  -1 ) { 
		      edit.cursor_rows += 1 ; 
			edit.cursor_cols = 0 ; 
			} 
			break ; 
  }
		
} 


void free_row(row_input *row){
	free(row->render) ; 
	free(row->data) ; 
	free(row->hl) ; 
}



void del_row(int row ){
	if ( row < 0 ||  row >= edit.row_length) {
		return ; 
	}
	free_row(&edit.ri[row]) ; 
	memmove(&edit.ri[row] , &edit.ri[row+1] , sizeof(row_input) * (edit.row_length - row - 1  ) ) ; 
	edit.row_length--;
    edit.changes++;
}

void append_delete_lines(row_input * row  , char *s , size_t len ){
	row->data  = realloc(row->data , len + row->size + 1 ) ; 
	memcpy(&row->data[row->size] , s , len ) ; 
	row->size += len  ; 
	row->data[row->size] = '\0';
	render_input(row);   
	edit.changes++ ; 
}





void del_char( row_input *line  , int pos ){ 
	if ( pos < 0 || pos > line->size ){ 
		return  ; 
	}
    memmove( &line->data[pos ] , &line->data[pos+1 ] ,  line->size - pos  ) ; 
	line->size-- ; 
	render_input(line)  ; 
	edit.changes++ ; 
}



void insert(int c ) {
	if (edit.cursor_rows == edit.row_length ){ 
         append_lines(  "" , edit.row_length , 0 ) ; 
	}
	int pos  = edit.cursor_cols ; 
	insert_char( &edit.ri[edit.cursor_rows] ,   pos ,   c) ; 
	edit.cursor_cols++ ; 
}

void del() {
	if (edit.cursor_rows == edit.row_length ){ 
         append_lines(  "" , edit.row_length , 0 ) ; 
	}
  	if (edit.cursor_cols == 0 && edit.cursor_rows == 0) {
		return;
	} 
	int pos  = edit.cursor_cols ; 
	row_input *row  = &edit.ri[edit.cursor_rows] ; 
	if ( pos > 0 ){ 
	del_char( &edit.ri[edit.cursor_rows] ,   pos-1  ) ; 
	edit.cursor_cols-- ; 
	} 
	else { 
		edit.cursor_cols = edit.ri[edit.cursor_rows - 1 ].size ; 
		append_delete_lines(&edit.ri[edit.cursor_rows - 1 ] ,row->data , row ->size  ) ; 
		del_row(edit.cursor_rows) ; 
		edit.cursor_rows -= 1 ; 
	}
}



int seperator_new(int c ){
	return  c == '\0' || strchr(",()+-/*=~%<>[];", c) != NULL ; 
}

char ***data_tokenizer(){
	char*** data = malloc( (edit.row_length + 1 ) *(sizeof(char**)) ); 
	int data_pointer = 0 ;
	int i = 0 ; 
	while ( edit.ri[i].query == true){
		i++ ; 
	}
	while ( i < edit.row_length ){
		char te[300] ; 
		int j = 0  ; 
		int m = 0 ; 
		char* temp = edit.ri[i].data ; 
		char** strings = malloc((edit.ri[i].size + 2) * sizeof(char*) );
		int len = edit.ri[i].size  ;
		bool exc = false ; 
		for ( int k = 0 ; k < len ; k++ ){
			if ( exc == false && temp[k] == ','){
				te[j] = '\0' ; 
          		  strings[m] = strdup(te) ; 
				  m++ ; 
			 	 j = 0 ; 
			}
			else if (temp[k] == '"' ){
				if ( exc == true ){
					exc = false ; 
				}
				else { 
					exc = true ; 
				}
				continue ; 
			}
			else { 
				if ( j < 299 ){
				te[j] = temp[k] ; 
           		 j++ ; 
				}
			}
		}
		te[j] = '\0' ; 
		while ( j > 0 && isspace((unsigned char)te[j-1]) ){
			j-- ;
			te[j] = '\0' ;
		}
		strings[m] = strdup(te) ; 
		m++ ; 
		strings[m] = NULL ; 
		
		data[data_pointer ] = strings ; 
		data_pointer++ ; 
		i++ ; 

	}
	data[data_pointer] = NULL; 
	return data ; 
}


char** tokenizer(){
	char *buf  = query_data_recovery() ; 
	int j = 0  ; 
	int m = 0 ; 
	int len = strlen(buf) ; 
	char** temp = malloc(300 * sizeof( char* )); 
	char te[300] ; 
	for ( int k = 0 ; k < len  ; k++ ){
	if (isspace(buf[k])  ) {
				te[j] = '\0' ; 
				temp[m] = strdup(te) ; 
				m++ ; 
				j = 0 ;
					continue;  
			}
	if ( seperator_new(buf[k])){
				te[j] = '\0' ; 
				temp[m] = strdup(te) ; 
				m++ ; 
				j = 0 ; 
				char tem[2] = {buf[k] , '\0'} ; 
				temp[m] = strdup(tem)  ; 
				m++ ; 
			}
	else { 
				te[j] = buf[k] ; 
				j++ ; 
			}
		}
	te[j] = '\0' ; 
	temp[m] = strdup(te)  ; 
	m++ ; 
	temp[m] = NULL ; 
	return temp ; 
}



char *query_data_recovery(){
    int i = 0 ;
    int total = 0 ;
    char *buf = NULL ;
    while(i < edit.query_lines){
        buf = realloc(buf , total + edit.ri[i].size + 2) ;
        memcpy(buf + total , edit.ri[i].data , edit.ri[i].size) ;
        total += edit.ri[i].size ;
        buf[total++] = '\n' ;
        i++ ;
    }
    if(buf) buf[total] = '\0' ;
    return buf ;
}





void meta_commnds(char *temp){
	if ( strcmp( ".save"  , temp  ) == 0 ){
		saving() ;
	}
	else if ( strcmp( ".tables"  , temp ) == 0 ){
		highlight = 1 ; 
	}
}



void arrange_data(int row){
    int total = 0 ;
    if ( row > edit.row_length ){
        return ;
    }
    char ***temp = proper_data.data ;
    for ( int j = 0 ; temp[row][j] != NULL && temp[row][j][0] != '\0' ; j++ ){
        total += edit.col_max_sizes[j] + 3 ;
    }
    char *buf = malloc( total + 1 ) ;
    int m = 0 ;
    for ( int j = 0 ; temp[row][j] != NULL && temp[row][j][0] != '\0' ; j++ ){
        memcpy(&buf[m] , temp[row][j] , strlen(temp[row][j]) ) ;
        m = m + strlen(temp[row][j]) ;
        int leftout = edit.col_max_sizes[j] - strlen(temp[row][j]) + 1 ;
        memset( &buf[m] , ' ' , leftout ) ;
        m = m + leftout ;
        memset( &buf[m] , ',' , 1 ) ;
        m = m + 1 ;
    }
    buf[m] = '\0' ;
    row_input * line = &edit.ri[row+1] ;
    free(line->data) ;
    line->data = buf ;
    line->size = m ;
    edit.changes++ ;
    render_input(line) ;  
}










float execute_prog_nums(char *separator , float *number ){
	float st[MAX] ;
	char stack[MAX] ;
	int st_top = -1 ;
	int stack_top = -1 ;
	int num_idx = 0 ;
	int need_num = 1 ;
	int len = strlen(separator) ;

	for ( int i = 0 ; i < len ; i++ ){
		char ch = separator[i] ;
		if ( need_num && ch != '(' ){
			st[++st_top] = number[num_idx++] ;
			need_num = false ;
		}

		if ( ch == '(' ){
			stack[++stack_top] = ch ;
			need_num = true ;
		}

		else if ( ch == ')' ){

			while ( stack_top != -1 && stack[stack_top] != '(' ){
				float b = st[st_top--] ;
				float a = st[st_top--] ;
				char op = stack[stack_top--] ;
				float ans = 0 ;

				switch ( op ){
					case '+' :
						ans = a + b ;
						break ;
					case '-' :
						ans = a - b ;
						break ;
					case '*' :
						ans = a * b ;
						break ;
					case '/' :
						ans = ( b != 0 ) ? a / b : 0 ;
						break ;
					case '%' :
						ans = ( b != 0 ) ? fmod(a , b) : 0 ;
						break ;
					case '^' :
						ans = pow(a , b) ;
						break ;
				}

				st[++st_top] = ans ;
			}

			stack_top-- ;
			need_num = false ;
		}

		else {

			int cur ;

			if ( ch == '*' || ch == '/' || ch == '%' || ch == '^' ){
				cur = 2 ;
			}
			else {
				cur = 1 ;
			}

			while ( stack_top != -1 && stack[stack_top] != '(' ){
				char top = stack[stack_top] ;
				int prev ;
				if ( top == '*' || top == '/' || top == '%' || top == '^' ){
					prev = 2 ;
				}
				else {
					prev = 1 ;
				}

				if ( prev < cur ){
					break ;
				}

				float b = st[st_top--] ;
				float a = st[st_top--] ;
				char op = stack[stack_top--] ;

				float ans = 0 ;

				switch ( op ){
					case '+' :
						ans = a + b ;
						break ;
					case '-' :
						ans = a - b ;
						break ;
					case '*' :
						ans = a * b ;
						break ;
					case '/' :
						ans = ( b != 0 ) ? a / b : 0 ;
						break ;
					case '%' :
						ans = ( b != 0 ) ? fmod(a , b) : 0 ;
						break ;
					case '^' :
						ans = pow(a , b) ;
						break ;
				}

				st[++st_top] = ans ;
			}

			stack[++stack_top] = ch ;
			need_num = true ;
		}
	}

	if ( need_num ){
		st[++st_top] = number[num_idx++] ;
	}

	while ( stack_top != -1 ){

		float b = st[st_top--] ;
		float a = st[st_top--] ;
		char op = stack[stack_top--] ;

		float ans = 0 ;

		switch ( op ){
			case '+' :
				ans = a + b ;
				break ;
			case '-' :
				ans = a - b ;
				break ;
			case '*' :
				ans = a * b ;
				break ;
			case '/' :
				ans = ( b != 0 ) ? a / b : 0 ;
				break ;
			case '%' :
				ans = ( b != 0 ) ? fmod(a , b) : 0 ;
				break ;
			case '^' :
				ans = pow(a , b) ;
				break ;
		}

		st[++st_top] = ans ;
	}

	return st[0] ;
}


char *execute_prog_words(char **data) {
    if (data == NULL) {
        return NULL;
    }

    size_t total = 0;

    for (int i = 0; data[i] != NULL; i++) {
        int len = strlen(data[i]);
        while (len > 0 && data[i][len - 1] == ' ') {
            len--;
        }
        total = total +  len;
    }

    char *result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    for (int i = 0; data[i] != NULL; i++) {
        int len = strlen(data[i]);
        while (len > 0 && data[i][len - 1] == ' '){
           len--;
        }
        memcpy(ptr, data[i], len);
        ptr = ptr +  len;
    }
    *ptr = '\0';

    return result;
}



int seperator_equal(int c ){
	return  c == '\0' || strchr(",()+-/*.~%<>[];", c) != NULL ; 
}




int *coods(char* buf ){
	int i = 0 ; 
		int first_num = 0 ; 
		int second_num = 0 ; 
		while ( buf[i] != '\0' && !isdigit(buf[i])){
			if ( isspace(buf[i]) ){
				i++ ; 
				continue ; 
			}
			else { 
				first_num = first_num *26 + buf[i] - 'A' ; 
			}
			i++ ; 
		}
		while(buf[i] != '\0' && isdigit(buf[i])){
			if ( isspace(buf[i]) ){
				i++ ; 
				continue ; 
			}
			else { 
				second_num = second_num * 10 +  buf[i] - '0' ; 
			}
			i++ ; 
		}
		int *ans = malloc(2 * sizeof(int ));
		if ( second_num == 0 ){           
        ans[0] = -1 ;
        ans[1] = -1 ;
   	    }
		else { 
		ans[0] = second_num - 1 ;
		ans[1] = first_num ;
		}
		return ans;
}





char *commands(char *data){
	if ( strcmp (data ,"SUM" ) == 0  || strcmp (data , "AVG" ) == 0  || strcmp (data , "COUNT" ) == 0 || strcmp (data , "MIN" ) == 0  || strcmp (data , "MAX" ) == 0   ){
		return data ; 
	}
return NULL ; 
}






float data_int(char* data){
	int i = 0 ; 
	float number = 0 ; 

	while(data[i] != '\0' && isdigit(data[i] )){
			number = number*10 + (data[i] - '0') ; 
			i++ ; 
	}

	if ( data[i] == '.'){
		i++ ; 
		float factor = 0.1f;
        while (data[i] != '\0' && isdigit(data[i])) {
            number = number +  (data[i] - '0') * factor;
            factor = factor *  0.1f;
            i++ ;
        }
	}

	if ( data[i] != '\0' ){
		return nope ; 
	}
	return number ; 
}



float execute_commands(char* command , char* first  , char * second  ){
	float ans = 0 ; 
	float temp = 0 ; 
	int *first_index = coods(first) ; 
	int *second_index = coods(second) ; 
	if ( first_index[1] != second_index[1]){
		return nope ;
	}
	if ( strcmp (command , "SUM" ) == 0  ){
	while (first_index[0] <= second_index[0]){
		temp = data_int(proper_data.data[first_index[0]][first_index[1]]) ; 
		if ( temp == nope ){
			return nope   ; 
		}
		ans = ans + temp ; 
		first_index[0]++ ; 
	}
	}
	else if ( strcmp (command , "AVG" ) == 0 ){
	int numbers = 0 ; 
	while (first_index[0] <= second_index[0]){
		temp = data_int(proper_data.data[first_index[0]][first_index[1]]) ; 
		if ( temp == nope ){
			return nope   ; 
		}
		ans = ans + temp ; 
		first_index[0]++ ; 
		numbers++ ; 
	}
	ans = ans / numbers ; 
	}
	else if ( strcmp (command , "MIN" ) == 0  ){
	while (first_index[0] <= second_index[0]){
		temp = data_int(proper_data.data[first_index[0]][first_index[1]]) ; 
		if ( temp == nope ){
			return nope   ; 
		}
		if ( temp < ans ){
			ans = temp ; 
		}
		first_index[0]++ ; 
	}
	}
	else if ( strcmp (command , "MAX" ) == 0 ){
	while (first_index[0] <= second_index[0]){
		temp = data_int(proper_data.data[first_index[0]][first_index[1]]) ; 
		if ( temp == nope ){
			return nope   ; 
		}
		if ( temp > ans ){
			ans = temp ; 
		}
		first_index[0]++ ; 
	}
	}
	else if ( strcmp (command , "COUNT" ) == 0 ){
	while (first_index[0] <= second_index[0]){
		temp = data_int(proper_data.data[first_index[0]][first_index[1]]) ; 
		if ( temp != nope ){
			 ans = ans + 1  ; 
		}
		first_index[0]++ ; 
	}
	}


return ans ; 
}





void assign(char *buf ){ 
	if ( buf == NULL ){
		return  ; 
	}
	int valid = 0 ; 
	int i = 0 ; 

	for (  i = 0 ; buf[i] != NULL ; i++  ){
		if ( isalnum(buf[i]) || seperator(buf[i]) != NULL ){
			valid = 1 ; 
			break ; 
		}
		else { 
			i++ ; 
		}
	}
	if ( valid == 0 ){
		return ; 
	}

		int i = 0 ; 
		int formula = 0 ; 
		char temp[300] ; 
		int m = 0 ; 


		while( seperator(buf[i]) == false ){
			temp[m] = buf[i] ; 
			m++ ; 
			i++ ; 
		}
		temp[m] = '\0' ; 
		int *first = coods(temp) ; 




		while( buf[i] != '\0' && ( isspace(buf[i]) || buf[i] == '=') ){
				if (  buf[i] == '=' ){
					formula++ ; 
				}
				  i++ ; 
		}

		if ( formula > 2 || formula == 0 ){
			status_msg_input("the query is wrong ") ; 
			return ; 
		}


		while ( isspace(buf[i])){
			i++ ; 
		}
		if ( formula == 1 ){
			int n = i ; 
			while( buf[n] != '\0' ){
				n++ ; 
			}
			char *assign  = malloc(n-i+1) ; 
			int quote = 0 ; 
			n = 0 ; 
			while( buf[i] != '\0' ){
				if ( buf[i] == '"'){
					if ( quote == 0 ){
					quote = 1 ; 
					}
					else { 
						quote = 0 ; 
					}
					i++ ; 
					continue ; 
				}
				else if ( isspace(buf[i])){
					if(quote == 1 ){
						assign[n] = buf[i] ; 
						n++ ; 
					}
					i++ ; 
					continue ; 
				}

				else if (seperator_new(buf[i]) && quote == 0  ){
					status_msg_input("the query is wrong ") ; 
					return ; 
				}
				else { 
					assign[n] = buf[i] ; 
					n++ ; 
				}
				
				i++ ; 
			}
			assign[n] = '\0' ; 


				proper_data.data[first[0]][first[1]] = strdup(assign);
			if ( edit.col_max_sizes[first[0]] < n ){
				edit.col_max_sizes[first[0]] = n ; 
				excel_like() ; 
			}
			else { 
				arrange_data(first[1]) ; 
			}
		}


		if ( formula == 2 ){
			int quote = 0 ; 
			int num = 0 ; 
			char **data = malloc(300 *edit.row_length* sizeof(char*)) ; 
			float *integers  = malloc(300 *edit.row_length* sizeof(float)); 
			int pointer = 0 ; 
			int num_pointer = 0 ; 
			int sep = 0  ; 
			char seperators[300] ; 
			int n = 0  ; 
			char size[50];

			while ( buf[i] != '\0'){
				if ( isspace(buf[i])){
					i++ ; 
					continue ; 
				}
				if ( buf[i] == '\''){
					if ( num  == 1 ){
						status_msg_input("the query is wrong ") ; 
						return ; 
					}
					i++ ; 
					int m = i ; 
					while ( buf[m] != '\''  && buf[m] != '\0' ){
						m++ ; 
					}
					char *dat  = malloc(m-i+1 ) ;
					m = 0 ;  
					while ( buf[i] != '\'' && buf[m] != '\0' ){
						dat[m] = buf[i] ; 
						i++ ; 
						m++ ; 
					}
					dat[m] = '\0' ; 
					data[pointer] = dat ; 
					pointer++ ; 
					if (buf[i] == '\''){
					i++ ; 
					}

				}



				else if ( isdigit(buf[i]) ){
					num = 1 ; 
					int m = 0 ; 
					char nume[300] ; 
					if ( quote == 1 ){
						status_msg_input("the query is wrong ") ; 
						return ; 
					}
					while ( !seperator_new(buf[i] )){
						nume[m] = buf[i] ; 
						m++ ; 
						i++ ; 
					}
					nume[m] = '\0' ; 
					float number = data_int(nume) ; 
					if ( number == nope ){
						status_msg_input("the query is wrong ") ; 
						return ; 
					}
					integers[num_pointer] = number ; 
					num_pointer++ ; 
					data[pointer] = strdup(nume) ; 
					pointer++ ; 
				}

				else if ( seperator(buf[i])){
					seperators[sep] = buf[i] ; 
					sep++ ; 
					i++ ; 
				}

				else { 
					char dat[300] ;  
					int m  = 0 ; 
					int *coordinates ; 
					while ( !seperator(buf[i])  ){
						dat[m] = buf[i] ; 
						i++ ;
						m++ ;  
					}
					dat[m] = '\0' ; 

					if ( commands(dat) == NULL ){
						int *coordinates  = coods(dat) ;
						char* grid_data = proper_data.data[coordinates[0]][coordinates[1]] ; 
						int check = data_int(grid_data)  ; 
						if ( check == nope ){
							quote = 1 ; 
							data[pointer] = strdup(grid_data) ; 
							pointer++ ; 
						}
						else { 
							num = 1 ; 
							integers[num_pointer] = number ; 
							num_pointer++ ; 
							data[pointer] = strdup(grid_data) ; 
							pointer++ ; 
						}
						free(coordinates) ; 
					}

					else {
						num = 1 ; 
						if ( quote == 1  ){
							status_msg_input("the query is wrong ") ; 
							return ; 
						}
						char first_index[300] ; 
						int first = 0 ; 
						int first_index = 0 ; 
						int second_index = 0 ; 
						char second_index[300] ; 
						while ( buf[i] != ')' && buf[i] != '\0'){
							if ( isspace(buf[i])){
								i++ ; 
								continue ; 
							}
							else if (buf[i] == '('){
								i++ ; 
								continue ; 
							}
							else if ( buf[i] == ':'){
								i++ ; 
								first = 1 ; 
							}
							else { 
								if ( first == 0 ){
									first_index[first_index] = buf[i] ; 
									first_index++ ; 
								}
								else { 
									second_index[second_index] = buf[i] ; 
									second_index++ ; 
								}
								i++ ; 
							}
						}
						first_index[index] = '\0' ; 
						second_index[index] = '\0' ; 
						if (buf[i] == ')'){
							 i++ ;
						}
						float number = execute_commands(commands(dat) , first_index , second_index ) ; 
						if ( number == nope ){
							status_msg_input("the query is wrong ") ; 
							return ; 
						}
						integers[num_pointer ] = number ; 
						num_pointer++ ; 
						 char number_string[50] ;
						snprintf(number_string, sizeof(number_string), "%.2f", number) ;
						data[pointer] = strdup(number_string) ;
						pointer++ ; 
					}
				}

			}
			seperators[sep] = '\0' ; 


			if ( quote ){
				for ( int l = 0 ;seperators[l] != '\0' ; l++  ){
					if (seperators[l] != '&' && seperators[l] != '(' && seperators[l] != ')' ){
						status_msg_input("the query is wrong ") ; 
						return ; 
					}
				}
				data[pointer] = NULL ; 
				char * ans = execute_prog_words( data ) ; 
				proper_data.data[first[0]][first[1]] = strdup(ans);
				free(ans) ; 
				if ( edit.col_max_sizes[first[0]] < strlen(ans) ){
					edit.col_max_sizes[first[0]] = strlen(ans) ; 
					excel_like() ; 
				}
				else { 
					arrange_data(first[1]) ; 
				}
			}

			else if ( num ){
				integers[num_pointer] = nope ; 
				float as = execute_prog_nums(seperators , integers ) ; 
				sprintf(size, sizeof(size), "%.2f", as);
				proper_data.data[first[0]][first[1]] = strdup(size);
				if ( edit.col_max_sizes[first[0]] < (int)strlen(size) ){
					edit.col_max_sizes[first[0]] = strlen(size) ; 
					excel_like() ; 
				}
				else { 
					arrange_data(first[1]) ; 
				}
			}
    		free(data) ;
  			  free(integers) ;
		}	

	free(first) ;

}
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



bool if_function( char* word ){
	for ( int i = 0 ; SQL_functions[i] != NULL ; i++  ){
	if (strcmp( word , SQL_functions[i]  ) == 0 ){
		return true ; 
	}  ; 
	}	
	return false ; 
}

bool if_sql_syntax( char* word ){
	for ( int i = 0 ; SQLITE_HL_keywords[i] != NULL ; i++  ){
	if (strcmp( word , SQLITE_HL_keywords[i]  ) == 0 ){
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
                        int num_temp = 2  ; 
                        if ( strcmp(oper, "NOT") == 0 ||strcmp(oper, "IS NULL") == 0 || strcmp(oper, "IS NOT NULL") == 0 )  {
                            num_temp = 1 ; 
                        }
                        if ( operand_top < num_temp ){
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
                        int commas = 0 ; 
                        bool present = false ;
                        while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    present = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( present &&  commas == 0 ){
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
                            if ( present &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }

                         tree * just_there;
                        if ( prev_tree_top == 0 || prev_tree[prev_tree_top - 1] == NULL ){
                            tree *func_parent = createNode(NULL);
                            just_there = function( buf , func_parent , check , start_row , start_col , i , j );
                        }
                        else {
                            just_there = function( buf , prev_tree[prev_tree_top - 1] , check , start_row , start_col , i , j );
                        }
                        if (just_there != NULL  ){
                                prev_tree[prev_tree_top++] = just_there ;
                              operands[operand_top++] = NULL ;
                        } 
                }
                else if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j-1 > 0 && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = j+1 ; 
                        int end_row_dec  = i ; 
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
                        tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec , pain  ); 
                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                }
                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                } 
                                just_there->as = strdup(buf[i][j] )  ; 
                            }   
                            else { 
                                check = 1 ; 
                                return NULL ; 
                            }
                        }
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
        int num_temp = 2   ; 
        if ( strcmp(oper, "NOT") == 0 ||strcmp(oper, "IS NULL") == 0 || strcmp(oper, "IS NOT NULL") == 0 )  {
            num_temp = 1 ; 
        }

        if ( operand_top < num_temp ){
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
    tree *exp_tree ; 
    if (prev_tree_top > 0){
        exp_tree = prev_tree[prev_tree_top - 1] ; 
    }
    else {
        exp_tree = NULL ; 
    }
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
                    if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = j+1 ; 
                        int end_row_dec  = i ; 
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
                        tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec  , pain  ); 
                            if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                }
                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                } 
                                just_there->as = strdup(buf[i][j] )  ; 
                            }   
                            else { 
                                check = 1 ; 
                                return NULL ; 
                            }
                        }
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
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
                                            if (j +1 <= end_col){
                                            j++ ; 
                                            }
                                            else {
                                                break ; 
                                            }
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
                                if (buf[i][j+1] != NULL){
                                j++ ; 
                                }
                                else {
                                    break ; 
                                }
                            }
                        }
                        tree*  just_there =  expression(buf , temp ,check ,   temp_row ,  temp_col  ,  i ,  j ) ; 
                        if (just_there != NULL ){
                        temp->children[temp->num++ ]  = just_there ; 
                        }
                        continue ; 
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
                                    continue ;  
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



tree *case_expr(char ***buf , int check ,  int i , int j , int end_row , int end_col ){
    tree*temp = createNode("CASE") ; 
    tree * start = temp ; 
    if (buf[i][j+1] != NULL) {
        j++ ;
    }
    else if (buf[i][j+1] == NULL) {
        if (buf[i+1][0] != NULL) {
            i++ ;
            j = 0 ;
        }
        else {
            break ;
        }
    }

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
            temp->children[temp->num++] = case_expr(buf  , check , start_row , start_col , i , j ) ; 
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
                        int end_col_dec  = j+1 ; 
                        int end_row_dec  = i ; 
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
                        tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec , pain   ); 
                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                }
                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                } 
                                just_there->as = strdup(buf[i][j] )  ; 
                            }   
                            else { 
                                check = 1 ; 
                                return NULL ; 
                            }
                        }
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
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




tree *comp_1(char*** buf , tree * node  ,  int i , int j , int end_row , int end_col ){
    int start_row = i ; 
    int start_col = j ; 
    tree * start = node ; 
    tree * temp  = node ; 
    int check = 0 ; 
    int pain  = 0  ;
    while ( i <= end_row){
       while ( j <= end_col ) {

            if (  strcmp(buf[i][j] ,  "FROM"  ) == 0  ) {
                return start ; 
            }
           else { 

                if ( if_function( buf[i][j] ) == true ){
                    int start_row = i ; 
                    int start_col = j ; 
                    int commas = 0 ; 
                    bool present = false ; 
                          while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    present = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( present && commas == 0 ){
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
                            if ( present &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                temp->children[temp->num++] = function( buf , temp,check ,   i ,  j , end_row , end_col ) ;
            }
                

            else  if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = j+1 ; 
                        int end_row_dec  = i ; 
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
                        tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec  , pain ); 
                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                }
                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                } 
                                just_there->as = strdup(buf[i][j] )  ; 
                            }   
                            else { 
                                check = 1 ; 
                                return NULL ; 
                            }
                        }
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
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
                                    if (buf[i][j+1] != NULL ){
                                        j++ ; 
                                    }   
                                        else {
                                            break ;
                                        }
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
                 if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                        temp->children[temp->num++] = make_leaf("*", i, j) ;
                    }
                    else if ( priority(buf[i][j]) != 0  ){
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




tree *comp_2(char*** buf , tree * node  ,  int i , int j , int end_row , int end_col ){
    int start_row = i ; 
    int start_col = j ; 
    tree * start = node ; 
    tree * temp  = node ; 
    int check = 0 ; 
    int pain  = 0  ;
    while ( i <= end_row){
       while ( j <= end_col ) {

            if (  strcmp(buf[i][j] ,  "WHERE"  ) == 0  ) {
                return start ; 
            }

            else if (  strcmp(buf[i][j], "JOIN") == 0  || 
                    ( j+1 <= end_col && strcmp(buf[i][j], "INNER") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) || 
                    (j+1 <= end_col && strcmp(buf[i][j], "LEFT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                    (j+1 <= end_col && strcmp(buf[i][j], "RIGHT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                    (j+1 <= end_col && strcmp(buf[i][j], "CROSS") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                    (j+2 <= end_col && strcmp(buf[i][j], "FULL") == 0 && strcmp(buf[i][j+1], "OUTER") == 0 && strcmp(buf[i][j+2], "JOIN") == 0 )){

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
                    return NULL  ; 
                }

                tree *temp_word = starter ; 

                while ( strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && strcmp(buf[i][j] , "WHERE") != 0   && strcmp(buf[i][j], "GROUP") != 0 &&  strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0 &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0  && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){

                        if ( if_function( buf[i][j] ) == true ){
                            int start_row = i ; 
                            int start_col = j ; 
                            int commas = 0 ; 
                            bool present = false ; 
                              while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    present = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if (present && commas == 0 ){
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
                            if ( present &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                        temp_word->children[temp_word->num++] = function( buf , temp_word,check ,   start_row ,  start_col , i , j ) ;
                    }
                        

                    else  if ( strcmp(buf[i][j] , "(") == 0  ){
                            if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                                int end_col_dec  = j+1 ; 
                                int end_row_dec  = i ; 
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
                                tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec , pain   ); 
                                    if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                            if (buf[i][j+1] != NULL) {
                                                j++ ;
                                            }
                                            else if (buf[i][j+1] == NULL) {
                                                if (buf[i+1][0] != NULL) {
                                                    i++ ;
                                                    j = 0 ;
                                                }
                                                else {
                                                    break ;
                                                }
                                            }
                                        if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                            if (buf[i][j+1] != NULL) {
                                                j++ ;
                                            }
                                            else if (buf[i][j+1] == NULL) {
                                                if (buf[i+1][0] != NULL) {
                                                    i++ ;
                                                    j = 0 ;
                                                }
                                                else {
                                                    break ;
                                                }
                                            } 
                                            just_there->as = strdup(buf[i][j] )  ; 
                                        }   
                                        else { 
                                            check = 1 ; 
                                            return NULL ; 
                                        }
                                    }
                                if (just_there != NULL  ){
                                    temp_word->children[temp_word->num++]  = just_there ; 
                                }
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
                                                return NULL;
                                            }
                                            j++;
                                            continue;
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

                                        tree * just_there = expression( buf , temp_word , check , temp_row , temp_col , i , j ) ;
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
                                                    temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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
                            if (buf[i][j] != NULL && strcmp(buf[i][j] , "ON") == 0   ){
                                 if (strcmp(starter->comp, "CROSS MODEL") == 0) {
                                        check = 1;
                                        return NULL;
                                    }
                                    j++;
                                    continue;
                            }
                             if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                                    temp->children[temp->num++] = make_leaf("*", i, j) ;
                                }
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
                                tree*  just_there =  expression(buf , temp_word , check ,  temp_row ,  temp_col  ,  i ,  j ) ; 
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
                                            temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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


                if ( pain == 0 ){
                    temp->children[temp->num++] = starter ; 
                }
                else { 
                    return starter ; 
                }

                }



            else { 

                if ( if_function( buf[i][j] ) == true ){
                    int start_row = i ; 
                    int start_col = j ; 
                    int commas = 0 ; 
                    bool present = false ; 
                          while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    present = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( present && commas == 0 ){
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
                            if ( present &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                temp->children[temp->num++] = function( buf , temp,check ,   i ,  j , end_row , end_col ) ;
            }
                

            else  if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
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
                        tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec  , pain  ); 
                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                }
                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                if (buf[i][j+1] != NULL) {
                                    j++ ;
                                }
                                else if (buf[i][j+1] == NULL) {
                                    if (buf[i+1][0] != NULL) {
                                        i++ ;
                                        j = 0 ;
                                    }
                                    else {
                                        break ;
                                    }
                                } 
                                just_there->as = strdup(buf[i][j] )  ; 
                            }   
                            else { 
                                check = 1 ; 
                                return NULL ; 
                            }
                        }
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
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
                                    if (buf[i][j+1] != NULL ){
                                        j++ ; 
                                    }   
                                        else {
                                            break ;
                                        }
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
                 if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                        temp->children[temp->num++] = make_leaf("*", i, j) ;
                    }
                    else if ( priority(buf[i][j]) != 0  ){
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





tree *comp_3(char*** buf , tree * node  ,  int i , int j , int end_row , int end_col  , int pain  , int having ){
    int start_row = i ; 
    int start_col = j ; 
    tree * start = node ; 
    tree * temp  = node ; 
    int check = 0 ; 
    while ( i <= end_row){
       while ( j <= end_col ) {



                if (  strcmp(buf[i][j], "JOIN") == 0  || 
                            ( j+1 <= end_col && strcmp(buf[i][j], "INNER") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) || 
                            (j+1 <= end_col && strcmp(buf[i][j], "LEFT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                            (j+1 <= end_col && strcmp(buf[i][j], "RIGHT") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                            (j+1 <= end_col && strcmp(buf[i][j], "CROSS") == 0 && strcmp(buf[i][j+1], "JOIN") == 0  ) ||  
                            (j+2 <= end_col && strcmp(buf[i][j], "FULL") == 0 && strcmp(buf[i][j+1], "OUTER") == 0 && strcmp(buf[i][j+2], "JOIN") == 0 )){

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
                            return NULL  ; 
                        }

                        tree *temp_word = starter ; 

                        while ( strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && strcmp(buf[i][j] , "WHERE") != 0   && strcmp(buf[i][j], "GROUP") != 0 &&  strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0 &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0  && strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 && buf[i][j] != NULL){

                                if ( if_function( buf[i][j] ) == true ){
                                    int start_row = i ; 
                                    int start_col = j ; 
                                    int commas = 0 ; 
                                    bool present = false ; 
                                    while (i<=end_row){
                                    while (j <= end_col){
                                        if ( strcmp(buf[i][j] , "(") == 0  ){
                                            commas++ ;
                                            present = true ; 
                                        }
                                        else if ( strcmp(buf[i][j] , ")") == 0 ){
                                            commas-- ; 
                                        }
                                        if (present && commas == 0 ){
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
                                    if ( present &&  commas == 0 ){
                                        break ; 
                                    }                               
                                    if ( i >= end_row && j > end_col ){ 
                                            break ; 
                                        }


                                }
                                temp_word->children[temp_word->num++] = function( buf , temp_word,check ,   start_row ,  start_col , i , j ) ;
                            }
                                

                            else  if ( strcmp(buf[i][j] , "(") == 0  ){
                                    if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                                        int end_col_dec  = j+1 ; 
                                        int end_row_dec  = i ; 
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
                                        if ( braces != 0 ){
                                            check = 1 ; 
                                            return NULL  ; 
                                        }
                                        tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec , pain  ); 
                                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                }
                                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                } 
                                                just_there->as = strdup(buf[i][j] )  ; 
                                            }   
                                            else { 
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                        }
                                        if (just_there != NULL  ){
                                            temp_word->children[temp_word->num++]  = just_there ; 
                                        }
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
                                                        return NULL;
                                                    }
                                                    j++;
                                                    continue;
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

                                                tree * just_there = expression( buf , temp_word , check , temp_row , temp_col , i , j ) ;
                                                if ( just_there != NULL ){
                                                    temp_word->children[temp_word->num++] = just_there ;
                                                }
                                            }
                                                else  {
                                                    if (if_syntax(buf[i][j]) == false ){
                                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                                            if (  buf[i][j+1] == NULL  ) {
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
                                                            temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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
                                    if (buf[i][j] != NULL && strcmp(buf[i][j] , "ON") == 0   ){
                                        if (strcmp(starter->comp, "CROSS MODEL") == 0) {
                                                check = 1;
                                                return NULL;
                                            }
                                            j++;
                                            continue;
                                    }
                                    if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                                            temp->children[temp->num++] = make_leaf("*", i, j) ;
                                        }
                                else  if ( priority(buf[i][j]) != 0  ){
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
                                        if (if_syntax(buf[i][j]) == false ){
                                                if ( strcmp(buf[i][j] , ",") == 0 ){
                                                    if (  buf[i][j+1] == NULL  ) {
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
                                                    temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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


                        if ( j-1 >= 0 ){
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
                                if (temp_col > 0 ){
                                    j = temp_col -1 ; 
                                }
                                else { 
                                    j = 0 ; 
                                }
                                i = temp_row ; 
                            }
                            

                                else {
                                i = start_row ; 
                                j = start_col ; 
                            }
                        }


                        if ( pain == 0 ){
                            temp->children[temp->num++] = starter ; 
                        }
                        else { 
                            return starter ; 
                        }

                }


                else if (strcmp( buf[i][j] , "ORDER") == 0 ){
                            if (buf[i][j+1] != NULL ){
                                if (strcmp( buf[i][j+1] , "BY") == 0 ){
                                    j++ ; 
                                    tree * temp_word = createNode("ORDER BY") ; 
                                    tree *starter = temp_word ; 



                                    while ( strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 &&  strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0  &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 ){
                                            if ( if_function( buf[i][j] ) == true ){
                                                int start_row = i ; 
                                                int start_col = j ; 
                                                int commas = 0 ; 
                                                bool present = false ; 
                                                while (i<=end_row){
                                                while (j <= end_col){
                                                    if ( strcmp(buf[i][j] , "(") == 0  ){
                                                        commas++ ;
                                                        present = true ; 
                                                    }
                                                    else if ( strcmp(buf[i][j] , ")") == 0 ){
                                                        commas-- ; 
                                                    }
                                                    if (present && commas == 0 ){
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
                                                if ( present &&  commas == 0 ){
                                                    break ; 
                                                }                               
                                                if ( i >= end_row && j > end_col ){ 
                                                        break ; 
                                                    }


                                            }
                                            temp_word->children[temp_word->num++] = function( buf , temp_word,check ,   start_row ,  start_col , i , j ) ;
                                        }


                                else  if ( strcmp(buf[i][j] , "(") == 0  ){
                                        if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                                            int end_col_dec  = j+1 ; 
                                            int end_row_dec  = i ; 
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
                                            if (braces != 0 ){
                                                check = 1 ; 
                                                return NULL 
                                            }
                                            tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec  , pain  ); 
                                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                }
                                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                } 
                                                just_there->as = strdup(buf[i][j] )  ; 
                                            }   
                                            else { 
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                        }                                            
                                            if (just_there != NULL  ){
                                                temp_word->children[temp_word->num++]  = just_there ; 
                                            }
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
                                                            return NULL;
                                                        }
                                                        j++;
                                                        continue;
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

                                                    tree * just_there = expression( buf , temp_word , check , temp_row , temp_col , i , j ) ;
                                                    if ( just_there != NULL ){
                                                        temp_word->children[temp_word->num++] = just_there ;
                                                    }
                                                }
                                                    else  {
                                                        if (if_syntax(buf[i][j]) == false ){
                                                            if ( strcmp(buf[i][j] , ",") == 0 ){
                                                                if (  buf[i][j+1] == NULL  ) {
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
                                                                temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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
                                                if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                                                    temp_word->children[temp_word->num++] = make_leaf("*", i, j) ;
                                                }
                                            else if ( priority(buf[i][j]) != 0  ){
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
                                                if (if_syntax(buf[i][j]) == false ){
                                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                                            if (  buf[i][j+1] == NULL  ) {
                                                                if ( buf[i+1][0] != NULL ){
                                                                i++ ;
                                                                j = 0 ;
                                                            } 
                                                        }
                                                        else { 
                                                            j++ ; 
                                                        }
                                                            temp_word->direction[temp_word->num - 1 ] = "ASC" ; 
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
                                                            temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
                                                        }
                                                    }
                                                    else if ( strcmp(buf[i][j]  , "ASC"  ) == 0 ||  strcmp(buf[i][j]  , "DSC"  ) == 0 || strcmp(buf[i][j]  , "NULLS"  ) == 0   ){
                                                            int dir = 0 ; 
                                                            int first = 0 ; 
                                                            tree * cat  ; 
                                                            tree * startcat ; 
                                                            while (  strcmp(buf[i][j] , ",") != 0 &&  strcmp(buf[i][j] , ";") != 0   ){
                                                                if (dir == 0 ) {
                                                                if (strcmp(buf[i][j]  , "NULLS"  ) == 0 || strcmp(buf[i][j]  , "ASC"  ) == 0  ){
                                                                    temp_word->direction[temp_word->num -1 ] = "ASC" ; 
                                                                }
                                                                else if ( strcmp(buf[i][j]  , "DSC"  ) == 0 ){
                                                                    temp_word->direction[temp_word->num - 1 ] = "DSC" ; 
                                                                }
                                                                dir = 1 ; 
                                                                }
                                                                if (  strcmp(buf[i][j]  , "NULLS"  ) == 0 ||  strcmp(buf[i][j]  , "LAST"  ) == 0  ||  strcmp(buf[i][j]  , "FIRST"  ) == 0 ){
                                                                    if ( first == 0 ){
                                                                        cat = createNode(buf[i][j] ); 
                                                                        startcat = cat ; 
                                                                        first = 1 ; 
                                                                    }
                                                                    else {
                                                                        cat->children[cat->num++ ]  = createNode(buf[i][j] ); 
                                                                        cat = cat->children[cat->num - 1 ] ;  
                                                                    }
                                                                }
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
                                                            if (startcat != NULL ){
                                                                temp_word->children[temp_word->num++ ] = startcat ; 
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


                                if ( j-1 >= 0 ){
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
                                        if (temp_col > 0 ){
                                            j = temp_col -1 ; 
                                        }
                                        else { 
                                            j = 0 ; 
                                        }
                                        i = temp_row ; 
                                    }
                                    

                                        else {
                                        i = start_row ; 
                                        j = start_col ; 
                                    }
                                }

                                if ( pain == 0 ){
                                    temp->children[temp->num++] = starter ; 
                                }
                                else { 
                                    return starter ; 
                                }

                                }
                                }
                        else {
                        check = 1 ; 
                        return NULL  ; 
                        }
                }

            
                else if ( strcmp(buf[i][j] , "CASE" ) == 0 ){
                    int cases = 1 ; 
                    int start_row = i ; 
                    int start_col = j ; 
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

                    while ( i <= end_row ){
                        while ( j <= end_col){
                        if (strcmp(buf[i][j] , "CASE" ) == 0){
                            cases++ ; 
                        }
                        else if (  strcmp(buf[i][j] , "END" ) == 0  ){
                            if ( cases > 0 ){
                                    cases-- ; 
                                    if ( cases == 0 ){
                                    break ; 
                                    }
                            }
                            else { 
                                break ; 
                            }
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
                    if (cases == 0 ){
                        break ; 
                    }
                    }
                    temp->children[temp->num++] = case_expr(buf  ,check , start_row , start_col , i , j ) ; 
                }


            
 
                else if (strcmp( buf[i][j] , "GROUP") == 0 ){
                            if (buf[i][j+1] != NULL ){
                                if (strcmp( buf[i][j+1] , "BY") == 0 ){
                                    j++ ; 
                                    tree * temp_word = createNode("GROUP BY") ; 
                                    tree *starter = temp_word ; 


                                    while ( strcmp(buf[i][j], ")") != 0 &&  strcmp(buf[i][j], ";") != 0 &&  strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "FETCH") != 0  &&  strcmp(buf[i][j], "LIMIT") != 0 &&strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT") != 0 && strcmp(buf[i][j], "EXCEPT") != 0 ){
                                            if ( if_function( buf[i][j] ) == true ){
                                                int start_row = i ; 
                                                int start_col = j ; 
                                                int commas = 0 ; 
                                                bool present = false ; 
                                                while (i<=end_row){
                                                while (j <= end_col){
                                                    if ( strcmp(buf[i][j] , "(") == 0  ){
                                                        commas++ ;
                                                        present = true ; 
                                                    }
                                                    else if ( strcmp(buf[i][j] , ")") == 0 ){
                                                        commas-- ; 
                                                    }
                                                    if (present && commas == 0 ){
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
                                                if ( present &&  commas == 0 ){
                                                    break ; 
                                                }                               
                                                if ( i >= end_row && j > end_col ){ 
                                                        break ; 
                                                    }


                                            }
                                            temp_word->children[temp_word->num++] = function( buf , temp_word,check ,   start_row ,  start_col , i , j ) ;
                                        }


                                else if  (strcmp(buf[i][j]  , "HAVING") == 0 ){
                                    int temp_start_row = i ; 
                                    int temp_start_col = j ; 
                                    while ( strcmp(buf[i][j], ")") != 0 && strcmp(buf[i][j], ";") != 0  && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "UNION") != 0 && strcmp(buf[i][j], "INTERSECT")!= 0 && strcmp(buf[i][j], "EXCEPT") != 0 ) { 
                                            
                                            if ( buf[i][j] == NULL ){
                                                if (i+1 <= end_row){
                                                    i = i+ 1 ; 
                                                    j = 0  ; 
                                                }
                                                else {
                                                    break ; 
                                                }
                                            }
                                            else { 
                                                j++ ; 
                                            }
                                    }
                                    tree * cat = createNode("HAVING") ; 
                                    tree * just_there  =   comp_3( buf ,  cat , temp_start_row, temp_start_col,  i ,  j ,  pain  , 1 ) ;
                                    if (just_there != NULL  ){
                                        temp_word->children[temp_word->num++]  = just_there ; 
                                    }
                                    continue ; 
                                }


                                else  if ( strcmp(buf[i][j] , "(") == 0  ){
                                        if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                                            int end_col_dec  = j+1  ; 
                                            int end_row_dec  = i ; 
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
                                            if ( braces != 0 ){
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                            tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec  , pain  ); 
                                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                }
                                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                } 
                                                just_there->as = strdup(buf[i][j] )  ; 
                                            }   
                                            else { 
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                        }                                            
                                            if (just_there != NULL  ){
                                                temp_word->children[temp_word->num++]  = just_there ; 
                                            }
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
                                                        if (buf[i][j+1] != NULL ){
                                                            j++ ; 
                                                        }   
                                                        else {
                                                                break ;
                                                            }
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

                                                    tree * just_there = expression( buf , temp_word , check , temp_row , temp_col , i , j ) ;
                                                    if ( just_there != NULL ){
                                                        temp_word->children[temp_word->num++] = just_there ;
                                                    }
                                                }
                                                    else  {
                                                        if (if_syntax(buf[i][j]) == false ){
                                                            if ( strcmp(buf[i][j] , ",") == 0 ){
                                                                if (  buf[i][j+1] == NULL  ) {
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
                                                                while (  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
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
                                                                temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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
                                                if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                                                    temp_word->children[temp_word->num++] = make_leaf("*", i, j) ;
                                                }
                                            else if ( priority(buf[i][j]) != 0  ){
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
                                                if (if_syntax(buf[i][j]) == false ){
                                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                                            if (  buf[i][j+1] == NULL  ) {
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
                                                            temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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


                                if ( j-1 >= 0 ){
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
                                        if (temp_col > 0 ){
                                            j = temp_col -1 ; 
                                        }
                                        else { 
                                            j = 0 ; 
                                        }
                                        i = temp_row ; 
                                    }
                                    

                                        else {
                                        i = start_row ; 
                                        j = start_col ; 
                                    }
                                }

                                if ( pain == 0 ){
                                    temp->children[temp->num++] = starter ; 
                                }
                                else { 
                                    return starter ; 
                                }

                                }
                                        else {
                                        check = 1 ; 
                                        return NULL  ; 
                                        }
                                }
                        else {
                        check = 1 ; 
                        return NULL  ; 
                        }
                }


      


                    else if( strcmp(buf[i][j] , "LIMIT") == 0 || strcmp(buf[i][j] ,"OFFSET") == 0 ){
                                tree * temp_word ; 
                                if (strcmp(buf[i][j] ,"LIMIT") == 0 ){
                                     temp_word = createNode("LIMIT") ; 
                                }
                                else if (strcmp(buf[i][j] ,"OFFSET") == 0) {
                                    temp_word = createNode("OFFSET") ; 
                                }
                                tree *starter = temp_word ; 
                                j++ ; 

                        while ( strcmp(buf[i][j], ";") != 0  && strcmp(buf[i][j], ")") != 0 ){

                            if ( strcmp(buf[i][j] , "OFFSET") == 0 ){
                                if (strcmp(starter->comp , "LIMIT") == 0 ){
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
                                continue ; 
                                }
                                else {
                                    return NULL ; 
                                }
                            }

                            else if ( strcmp(buf[i][j], "(") == 0 ){

                                        if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                                            int end_col_dec  = j+1  ; 
                                            int end_row_dec  = i ; 
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
                                            if ( braces != 0 ){
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                            tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec  , pain  ); 
                                        if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                }
                                            if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                                if (buf[i][j+1] != NULL) {
                                                    j++ ;
                                                }
                                                else if (buf[i][j+1] == NULL) {
                                                    if (buf[i+1][0] != NULL) {
                                                        i++ ;
                                                        j = 0 ;
                                                    }
                                                    else {
                                                        break ;
                                                    }
                                                } 
                                                just_there->as = strdup(buf[i][j] )  ; 
                                            }   
                                            else { 
                                                check = 1 ; 
                                                return NULL ; 
                                            }
                                        }                                            
                                            if (just_there != NULL  ){
                                                temp_word->children[temp_word->num++]  = just_there ; 
                                            }
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
                                                        if (buf[i][j+1] != NULL ){
                                                            j++ ; 
                                                        }   
                                                        else {
                                                                break ;
                                                            }
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

                                                    tree * just_there = expression( buf , temp_word , check , temp_row , temp_col , i , j ) ;
                                                    if ( just_there != NULL ){
                                                        temp_word->children[temp_word->num++] = just_there ;
                                                    }
                                                }
                                                    else  {
                                                        if (if_syntax(buf[i][j]) == false ){
                                                            if ( strcmp(buf[i][j] , ",") == 0 ){
                                                                if (  buf[i][j+1] == NULL  ) {
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
                                                                while (  strcmp(buf[i][j] , ";") != 0  && strcmp(buf[i][j], "ON") != 0 && strcmp(buf[i][j], "OFFSET") != 0 && strcmp(buf[i][j], "LIMIT") != 0 && strcmp(buf[i][j], "ORDER") != 0 && strcmp(buf[i][j], "HAVING") != 0 && strcmp(buf[i][j], "GROUP") != 0&& strcmp(buf[i][j], "WHERE") != 0 && strcmp(buf[i][j], "FROM") != 0 && strcmp(buf[i][j], ")") != 0 ){
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
                                                                temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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
                                                if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                                                    temp_word->children[temp_word->num++] = make_leaf("*", i, j) ;
                                                }
                                            else if ( priority(buf[i][j]) != 0  ){
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
                                                if (if_syntax(buf[i][j]) == false ){
                                                        if ( strcmp(buf[i][j] , ",") == 0 ){
                                                            if (  buf[i][j+1] == NULL  ) {
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
                                                            temp_word->children[temp_word->num++] = make_leaf( buf[i][j]  , i , j ) ; 
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


                        if ( j-1 >= 0 ){
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
                                if (temp_col > 0 ){
                                      j = temp_col -1 ; 
                                }
                                else { 
                                    j = 0 ; 
                                }
                                i = temp_row ; 
                            }
                            

                                else {
                                i = start_row ; 
                                j = start_col ; 
                            }
                        }

                        if ( pain == 0 ){
                            temp->children[temp->num++] = starter ; 
                        }
                        else { 
                            return starter ; 
                        }

                        }





      



            else { 

                if ( if_function( buf[i][j] ) == true ){
                    int start_row = i ; 
                    int start_col = j ; 
                    int commas = 0 ; 
                    bool present = false ; 
                          while (i<=end_row){
                            while (j <= end_col){
                                if ( strcmp(buf[i][j] , "(") == 0  ){
                                    commas++ ;
                                    present = true ; 
                                }
                                else if ( strcmp(buf[i][j] , ")") == 0 ){
                                    commas-- ; 
                                }
                                if ( present && commas == 0 ){
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
                            if ( present &&  commas == 0 ){
                                break ; 
                            }                               
                             if ( i >= end_row && j > end_col ){ 
                                    break ; 
                                }


                        }
                temp->children[temp->num++] = function( buf , temp,check ,   i ,  j , end_row , end_col ) ;
            }
                

            else  if ( strcmp(buf[i][j] , "(") == 0  ){
                    if ( j+1 <= end_col && strcmp(buf[i][j+1] , "SELECT" ) == 0  ){
                        int end_col_dec  = j+1 ; 
                        int end_row_dec  = i ; 
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
                        tree * just_there  =  select_query( i  , j+1 , check ,  end_row_dec ,  end_col_dec , pain   ); 
                            if ( (j+1 <= end_col && strcmp(buf[i][j+1] , "AS") == 0 ) || (i+1 <= end_row && strcmp(buf[i+1][0] , "AS") == 0   )){
                                    if (buf[i][j+1] != NULL) {
                                        j++ ;
                                    }
                                    else if (buf[i][j+1] == NULL) {
                                        if (buf[i+1][0] != NULL) {
                                            i++ ;
                                            j = 0 ;
                                        }
                                        else {
                                            break ;
                                        }
                                    }
                                if ( ( just_there != NULL && j+1 <= end_col && if_sql_syntax(buf[i][j+1]) == false   ) || (just_there != NULL && i+1 <= end_col && if_sql_syntax(buf[i+1][0]) == false   )){
                                    if (buf[i][j+1] != NULL) {
                                        j++ ;
                                    }
                                    else if (buf[i][j+1] == NULL) {
                                        if (buf[i+1][0] != NULL) {
                                            i++ ;
                                            j = 0 ;
                                        }
                                        else {
                                            break ;
                                        }
                                    } 
                                    just_there->as = strdup(buf[i][j] )  ; 
                                }   
                                else { 
                                    check = 1 ; 
                                    return NULL ; 
                                }
                            }
                        if (just_there != NULL  ){
                              temp->children[temp->num++]  = just_there ; 
                        }
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
                                    if (buf[i][j+1] != NULL ){
                                        j++ ; 
                                    }   
                                        else {
                                            break ;
                                        }
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
                                            if (  buf[i][j+1] == NULL  ) {
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
                 if ( strcmp(buf[i][j], "*") == 0 && (j == 0 || strcmp(buf[i][j-1], "SELECT") == 0 || strcmp(buf[i][j-1], ",") == 0) ){
                        temp->children[temp->num++] = make_leaf("*", i, j) ;
                    }
                    else if ( priority(buf[i][j]) != 0  ){
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
                                    if (  buf[i][j+1] == NULL  ) {
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
 
 






tree * select_query( int row , int col , int check , int end_row , int end_col , int pain){
         int compulsion = 0 ; 
        tree* start_of_tree = NULL  ; 
        char ***buf = proper_data.query ; 
        int i = row ; 
        int j = col ; 
        if ( check == 1 ){
            return NULL ; 
        }
        tree * node = NULL ; 
        while ( i <= end_row){
            while ( j<= end_col ){
                if ( check == 1 ){
                    return NULL ; 
                }
                if ( i == row && j == col ){
                    if (  strcmp(buf[i][j], "SELECT")==0  ){
                        node =  createNode("SELECT") ; 
                        start_of_tree = node ; 
                        compulsion++ ; 
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
                        continue ; 
                    }
                }

                else if ( strcmp(buf[i][j], ";")==0 ){
                    return start_of_tree   ; 
                }

                else if (compulsion == 1){
                    int start_row = i ; 
                    int start_col = j ; 
                    while ( strcmp(buf[i][j]  , "FROM ") != 0 ){
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
                    node->children[node->num++] = comp_1(buf , node , start_row , start_col , i , j) ; 
                    compulsion++ ; 
                    if (strcmp(buf[i][j]  , "FROM ") == 0 ){
                        node->children[node->num++]= createNode("FROM") ; 
                        node = node->children[node->num - 1 ] ;  
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
                    continue ; 

                }

            else if ( strcmp(buf[i][j] , "UNION") == 0 || strcmp(buf[i][j] , "EXCEPT") == 0 || strcmp(buf[i][j] , "INTERSECT") == 0  ){
                pain = 1 ; 
                tree* superior ; 
                if ( (j+1 <= end_col && strcmp(buf[i][j+1]  , "ALL") == 0  ) || (i+1 <= end_row && strcmp(buf[i+1][0]  , "ALL") == 0 )){
                    if (strcmp(buf[i][j] , "UNION") == 0 ){
                        superior = createNode("UNION ALL") ;      
                    }
                    else if (strcmp(buf[i][j] , "EXCEPT") == 0 ){
                        superior = createNode("EXCEPT ALL") ;      
                    }
                    else if (strcmp(buf[i][j] , "INTERSECT") == 0 ){
                        superior = createNode("INTERSECT ALL") ;      
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
                else { 
                    if (strcmp(buf[i][j] , "UNION") == 0 ){
                        superior = createNode("UNION ") ;      
                    }
                    else  if (strcmp(buf[i][j] , "EXCEPT") == 0 ){
                        superior = createNode("EXCEPT ") ;      
                    }
                    else if (strcmp(buf[i][j] , "INTERSECT") == 0 ){
                        superior = createNode("INTERSECT ") ;      
                    }
                }
                if ( buf[i][j] == NULL ){
                    if (i+1 <= end_row){
                        i = i+ 1 ; 
                        j = 0  ; 
                    }
                }
                else if (buf[i][j] != NULL   ) { 
                    j++ ; 
                }
                superior->children[superior->num++] = start_of_tree ; 
                start_of_tree = superior ; 

             start_of_tree->children[start_of_tree->num++] =  select_query( i  ,  j ,  check  ,  end_row ,  end_col ,  pain   ) ; 
                return start_of_tree ; 
            }


            else if (compulsion == 2){
                int start_row = i ; 
                int start_col = j ; 
                while (strcmp(buf[i][j]  , "WHERE ") != 0 && strcmp(buf[i][j]  , "UNION") != 0 && strcmp(buf[i][j]  , "EXCEPT") != 0  && strcmp(buf[i][j]  , "INTERSECT") != 0   &&strcmp(buf[i][j]  , ";") != 0  ){
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
                if ( pain == 0 ){
                    node->children[node->num++] = comp_2(buf , node , start_row , start_col , i , j , pain ) ; 
                    compulsion++ ; 
                    if (strcmp(buf[i][j]  , "WHERE ") == 0 ){
                        node->children[node->num++]= createNode("WHERE") ; 
                        node = node->children[node->num - 1 ] ;  
                    }
                    }
                else if ( pain == 1 ) { 
                        start_of_tree->children[start_of_tree->num++] = comp_2(buf , node , start_row , start_col , i , j , pain )  ; 
                }

                if (strcmp(buf[i][j]  , ";") == 0 ) {
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
                        for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; temp_col++ ){
                        }
                        j = temp_col -1 ; 
                        i = temp_row ; 
                    }
                }
                else {
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
                continue ; 

            }



            else if (compulsion == 3){
                int start_row = i ; 
                int start_col = j ; 
                while (strcmp(buf[i][j]  , ";") != 0  && strcmp(buf[i][j]  , "UNION") != 0 && strcmp(buf[i][j]  , "EXCEPT") != 0  && strcmp(buf[i][j]  , "INTERSECT") != 0    ){
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

                if ( pain == 0 ){
                    node->children[node->num++] = comp_3(buf , node , start_row , start_col , i , j , pain  , 0 ) ; 
                    compulsion++ ; 
                }
                else { 
                    start_of_tree->children[start_of_tree->num++] =  comp_3(buf , node , start_row , start_col , i , j , pain  , 0 ) ; 
                }

                if (strcmp(buf[i][j]  , ";") == 0 ) {
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
                        for ( temp_col= 0 ; buf[temp_row][temp_col] != NULL ; temp_col++ ){
                        }
                        j = temp_col -1 ; 
                        i = temp_row ; 
                    }
                }
                else {
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
                continue ; 

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
}

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




    void compile(){

    }
}

bytecode { 
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
        end_num , 
        cursor_read , 
        boolean_op , 
        cursor_write  , 
        open_write_op , 
        open_read_op
    }

    typedef enum collation { 
        BINARY = 1 ,
        NOCASE,
        RTRIM 
    } ;

    typedef enum direction { 
        ASC = 1 ,
        DESC 
    } ;

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
        int data_type ; 
        bool end ; 
        int total ; 
        int mode ; 
        int depth ; 
        path_entry stack[300] ; 
        bool null ; 
    }

    typedef struct aggregate{
        reg min ; 
        reg max ; 
        double total ; 
        int type ; 
        char *concat_string ; 
        int * string_len ; 
        bool have_value ; 
        int count ; 
    }

    typedef struct sort_arr{
        unsigned char * key ; 
        int key_type ; 
        unsigned char * array ; 
        int len ;  
    }

    typedef struct Key_info{
        int feild ; 
        collation * coll  ; 
        direction * dir  ; 
    }

    typedef struct sorter{
        int row_count ; 
        sort_arr * array ; 
        int capacity ;
        int keycols;  
        int cursor ; 
        int  cols_to_look ;  
        Key_info * keyinfo ; 
    }


    int count = 0 ; 
    sorter[op->p1]->array[count].key = get_data_sort( sorter[op->p1]->array[count] , sorter[op->p1].cols_to_look  ) ; 



    unsigned char * make_record_data(byte * byt , int start , int end ){
        unsigned char *ans[300] ; 
        int pos = 0 ; 
        reg temp = byt->regis[start] ; 
        for ( int i = start ; i <= end ; i++ ){
            temp = byt->regis[i] ; 
            memcpy( ans + pos  , temp->type  , 1   ) ; 
            pos = pos + 1 ; 
            if (temp->type == integer_num ){
                memcpy(ans + pos , temp->val.i , sizeof(int)) ; 
                pos  = pos + sizeof(int) ; 
            }
            else if (temp->type == real_num ){
                memcpy(ans + pos , temp->val.i , sizeof(float)) ; 
                pos  = pos + sizeof(float) ; 
            }
            else if (temp->type == string_num || temp->type == blob_num  ){
                memcpy( ans + pos , temp->lenght , sizeof(int)) ; 
                pos = pos + sizeof(int) ; 
                memcpy(ans + pos , temp->val.s , temp->lenght ) ; 
                pos = pos + temp->lenght  ; 
            }
        }
        return ans ; 
    }





    unsigned char * get_data_sort(sort_arr thing , int key , int * lenght , int * type ){
        thing->array + key + 1  ; 
        int pos = 0 ; 
        unsigned char * temp = thing[pos] ; 
        for ( int i =  0 ; i < key ; i++ ){
            temp = thing[pos] ; 
            pos = pos + 1 ; 
            if (temp == integer_num){
                pos = pos + sizeof(long) ; 
            }
            else if (temp == real_num){
                pos = pos + sizeof(float ) ;   
            }
            else if (temp == string_num ){
                uint32_t size ; 
                memcpy(&size , thing + pos , sizeof(uint32_t)) ; 
                pos = pos + sizeof(uint32_t) ; 
                pos = pos + size ; 
            }
        }
        temp = thing[pos] ; 
        int len ; 
        pos = pos + 1 ; 
        if (temp == integer_num){
            len =  sizeof(long) ; 
            type = integer_num ; 
        }
        else if (temp == real_num){
            len =  sizeof(float ) ; 
            type =  real_num ; 
        }
        else if (temp == string_num ){
            uint32_t size ; 
            memcpy(&size , thing + pos , sizeof(uint32_t)) ; 
            len =  sizeof(uint32_t) ; 
            len = len + size ; 
            type = string_num ; 
        }

        unsigned char * ans = malloc(len ) ; 
        memcpy(ans , thing + pos   , len ) ; 
        *lenght = len ; 
        return ans  ; 
    }

    typedef struct byte{
        type prog[300] ; 
        int prog_count ; 
        int ins_count ; 
        reg regis[300] ; 
        int reg_start ; 
        int reg_end ; 
        int reg_mode ; 
        aggregate agg[300] ; 
        btree btr[300] ; 
        table *db ; 
        Pager *pager ; 
        sorter * sort ; 
    }

    typedef struct page_header{
        uint8_t page_type ; 
        uint16_t free_space ; 
        uint16_t num_cells  ; 
    }__attribute__((packed)) 


    int compare_sort(const void * a, const void * b , void * sorter_e  ){
        sorter sort = (sorter *)sorter_e ; 
        sort_arr * first = (sort_arr * )a ; 
        first->key = get_data_sort(first , sort->cols_to_look ,first->len , first->key_type  ) ;  
        sort_arr * second = (sort_arr * )b ; 
        second->key = get_data_sort(second , sort->cols_to_look ,second->len , second->key_type  ) ;  
        int result = 0 ; 
        if ( first->key_type == integer_num && second->key_type == integer_num  ){
            long first_num ;
            memcpy(&first_num, first->key, sizeof(long));
            long second_num  ;
            memcpy(&second_num, second->key, sizeof(long));
            if (first_num < second_num){
                if (sort->keyinfo.dir == DESC  ){
                    result =  1 ; 
                }
                else { 
                    result = -1 ; 
                }
            }
            else if (first_num > second_num){
                if (sort->keyinfo.dir == DESC  ){
                    result =  -1 ; 
                }
                else { 
                    result = 1 ; 
                }
            }
            else {
                result =  0 ; 
            }
        }
        else if ( ( first->key_type == real_num && second->key_type == real_num )  ){
            float first_num ;
            memcpy(&first_num, first->key, sizeof(float));
            float second_num  ;
            memcpy(&second_num, second->key, sizeof(float));
            if (first_num < second_num){
                if (sort->keyinfo.dir == DESC  ){
                    result =  1 ; 
                }
                else { 
                    result =  -1 ; 
                }
            }
            else if (first_num > second_num){
                if (sort->keyinfo.dir == DESC  ){
                    result =  -1 ; 
                }
                else { 
                result =  1 ; 
                }
            }
            else {
                result =  0 ; 
            }
        }

        else if ( ( first->key_type == real_num && second->key_type == integer_num ) || ( first->key_type == integer_num && second->key_type == real_num )    ){
            float first_num;
            if (first->key_type == real_num) {
                memcpy(&first_num, first->key, sizeof(float));
            } 
            else if (first->key_type == integer_num) {
                long tmp;
                memcpy(&tmp, first->key, sizeof(long));
                first_num = (float)tmp;
            }

            float second_num;
            if (second->key_type == real_num) {
                memcpy(&second_num, second->key, sizeof(float));
            } 
            else if (second->key_type == integer_num) {
                long tmp;
                memcpy(&tmp, second->key, sizeof(long));
                second_num = (float)tmp;
            }
            if (first_num < second_num){
                if (sort->keyinfo.dir == DESC  ){
                    result =  1 ; 
                }
                else { 
                    result = -1 ; 
                }
            }
            else if (first_num > second_num){
                if (sort->keyinfo.dir == DESC  ){
                    result =  -1 ; 
                }
                else {
                    result = 1 ; 
                }
            }
            else {
                result =  0 ; 
            }
        }



        
        else if (first->key_type  == string_num && second->key_type == string_num ){
            if (sort->keyinfo.coll == BINARY  ){
                int num_1 = 0 ; 
                int num_2 = 0 ;
                int i = 0 ; 
                int j = 0  ; 
                while (  num_1 == num_2  ) {
                    if (i < first->len ){
                        num_1 = num_1 + (int)first->key[i] ; 
                        i++ ; 
                    } 
                    if ( j < second->len  ){
                        num_2 = num_2 + (int)second->key[j] ;        
                        j++ ;  
                    }      
                    if ( i >= first->len &&  j >= second->len   ) {
                        break ; 
                    }
                }
                if (num_2 > num_1){
                    if (sort->keyinfo.dir == DESC  ){
                        result =  1 ; 
                    }
                    else {
                        result = -1 ; 
                    }
                }
                else if (num_2 < num_1){
                    if (sort->keyinfo.dir == DESC  ){
                        result =  -1 ; 
                    }
                    else { 
                        result = 1 ; 
                    }
                }
                else {
                    result =  0 ; 
                }
            }    

            else if (sort->keyinfo.coll == NOCASE  ){
                int num_1 = 0 ; 
                int num_2 = 0 ;
                int i = 0 ; 
                int j = 0  ; 
                while (  num_1 == num_2  ) {
                    if (i < first->len ){
                        num_1 = num_1 + (int)to_lowercase(first->key[i]) ; 
                        i++ ; 
                    } 
                    if ( j < second->len  ){
                        num_2 = num_2 + (int)to_lowercase(second->key[j] )  ;        
                        j++ ;  
                    }      
                    if ( i >= first->len &&  j >= second->len   ) {
                        break ; 
                    }
                }
                if (num_2 > num_1){
                    if (sort->keyinfo.dir == DESC  ){
                        result =  1 ; 
                    }
                    else { 
                        result = -1 ; 
                    }
                }
                else if (num_2 < num_1){
                    if (sort->keyinfo.dir == DESC  ){
                        result =  -1 ; 
                    }
                    else { 
                        result = 1 ; 
                    }
                }
                else {
                    result =  0 ; 
                }
            }   

            else if (sort->keyinfo.coll == RTRIM  ){
                int num_1 = 0 ; 
                int num_2 = 0 ;
                int i = 0 ; 
                int j = 0  ; 
                int len_1  = first->len -  1   ; 
                while( len_1 >= 0 && first->key[len_1] == ' '){
                    len_1-- ; 
                }
                len_1++ ; 

                int len_2  = second->len - 1   ; 
                while( len_2 >= 0 && second->key[len_2] == ' '){
                    len_2-- ; 
                }
                len_2++ ; 

                while (  num_1 == num_2  ) {
                    if (i <len_1 ){
                        num_1 = num_1 + (int)first->key[i]; 
                        i++ ; 
                    } 
                    if ( j < len_2 ){
                        num_2 = num_2 + (int)second->key[j]  ;        
                        j++ ;  
                    }      
                    if ( i >= len_1 &&  j >= len_2   ) {
                        break ; 
                    }
                }
                if (num_2 > num_1){
                    if (sort->keyinfo.dir == DESC  ){
                        result =  1 ; 
                    }
                    else { 
                        result = -1 ; 
                    }
                }
                else if (num_2 < num_1){
                    if (sort->keyinfo.dir == DESC  ){
                        result =  -1 ; 
                    }
                    else { 
                        result = 1 ; 
                    }
                }
                else {
                    result =  0 ; 
                }
            }   

        }
        free(first->key) ; 
        free(second->key) ; 
        return result ; 
    }


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

    int campare_ge(reg target , void * cell_key , int  data_type ){
      if (target->type == integer_num){
            if (data_type == 1 ){
                uint32_t num = *(uint32_t*)cell_key ; 
                if (num >= target->val.i){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else if (data_type == 2 ){
                float num = *(float*)cell_key ; 
                int num_temp = int(num) ; 
                if (num_temp >= target->val.i){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else {
                return -1 ; 
            }
        }
        else if ( target->type == real_num ){
            if (data_type == 1 ){
                uint32_t num_temp = *(uint32_t*)cell_key ; 
                float num = (float)num_temp ; 
                if (num >= target->val.r){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            if (data_type == 2 ){
                float num = *(float*)cell_key ; 
                if (num >= target->val.r){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else { 
                return -1 ; 
            }
        }
        else { 
            if (data_type == 3 ){
                char *str_temp = (char *)cell_key; 
                int len = strlen(str_temp) ; 
                    if (strlen(target->val.s) >= (size_t)len ? strncmp(target->val.s, str_temp, len) >= 0 : strncmp(target->val.s, str_temp, strlen(target->val.s)) > 0){
                        return 0 ; 
                    }
                    else { 
                        return -1 
                    } 
            }
            else { 
                return -1 ; 
            }
        }
    }

    int campare_gt(reg target , void * cell_key , int  data_type ){
     if (target->type == integer_num){
            if (data_type == 1 ){
                uint32_t num = *(uint32_t*)cell_key ; 
                if (num > target->val.i){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else if (data_type == 2 ){
                float num = *(float*)cell_key ; 
                int num_temp = int(num) ; 
                if (num_temp > target->val.i){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else {
                return -1 ; 
            }
        }
        else if ( target->type == real_num ){
            if (data_type == 1 ){
                uint32_t num_temp = *(uint32_t*)cell_key ; 
                float num = (float)num_temp ; 
                if (num > target->val.r){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            if (data_type == 2 ){
                float num = *(float*)cell_key ; 
                if (num > target->val.r){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else { 
                return -1 ; 
            }
        }
        else { 
            if (data_type == 3 ){
                char *str_temp = (char *)cell_key; 
                int len = strlen(str_temp) ; 
                    if (strlen(target->val.s) > (size_t)len ? strncmp(target->val.s, str_temp, len) >= 0 : strncmp(target->val.s, str_temp, strlen(target->val.s)) > 0){
                        return 0 ; 
                    }
                    else { 
                        return -1 
                    } 
            }
            else { 
                return -1 ; 
            }
        }
    }

    int campare_lt(reg target , void * cell_key , int  data_type ){
     if (target->type == integer_num){
            if (data_type == 1 ){
                uint32_t num = *(uint32_t*)cell_key ; 
                if (num < target->val.i){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else if (data_type == 2 ){
                float num = *(float*)cell_key ; 
                int num_temp = int(num) ; 
                if (num_temp < target->val.i){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else {
                return -1 ; 
            }
        }
        else if ( target->type == real_num ){
            if (data_type == 1 ){
                uint32_t num_temp = *(uint32_t*)cell_key ; 
                float num = (float)num_temp ; 
                if (num < target->val.r){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            if (data_type == 2 ){
                float num = *(float*)cell_key ; 
                if (num < target->val.r){
                    return 0 ; 
                }
                else {
                    return -1 ; 
                }
            }
            else { 
                return -1 ; 
            }
        }
        else { 
            if (data_type == 3 ){
                char *str_temp = (char *)cell_key; 
                int len = strlen(str_temp) ; 
                    if (strlen(target->val.s) < (size_t)len ? strncmp(target->val.s, str_temp, len) >= 0 : strncmp(target->val.s, str_temp, strlen(target->val.s)) > 0){
                        return 0 ; 
                    }
                    else { 
                        return -1 
                    } 
            }
            else { 
                return -1 ; 
            }
        }
    }

    int campare_le(reg target , void * cell_key , int  data_type ){
        if (target->type == integer_num){
                if (data_type == 1 ){
                    uint32_t num = *(uint32_t*)cell_key ; 
                    if (num <= target->val.i){
                        return 0 ; 
                    }
                    else {
                        return -1 ; 
                    }
                }
                else if (data_type == 2 ){
                    float num = *(float*)cell_key ; 
                    int num_temp = int(num) ; 
                    if (num_temp <= target->val.i){
                        return 0 ; 
                    }
                    else {
                        return -1 ; 
                    }
                }
                else {
                    return -1 ; 
                }
            }
            else if ( target->type == real_num ){
                if (data_type == 1 ){
                    uint32_t num_temp = *(uint32_t*)cell_key ; 
                    float num = (float)num_temp ; 
                    if (num <= target->val.r){
                        return 0 ; 
                    }
                    else {
                        return -1 ; 
                    }
                }
                if (data_type == 2 ){
                    float num = *(float*)cell_key ; 
                    if (num <= target->val.r){
                        return 0 ; 
                    }
                    else {
                        return -1 ; 
                    }
                }
                else { 
                    return -1 ; 
                }
            }
            else { 
                if (data_type == 3 ){
                    char *str_temp = (char *)cell_key; 
                    int len = strlen(str_temp) ; 
                        if (strlen(target->val.s) <= (size_t)len ? strncmp(target->val.s, str_temp, len) >= 0 : strncmp(target->val.s, str_temp, strlen(target->val.s)) > 0){
                            return 0 ; 
                        }
                        else { 
                            return -1 
                        } 
                }
                else { 
                    return -1 ; 
                }
            }
    }

    int bs( void * node , reg target  , int data_type  , int *index  , int (*function_name)(reg, void*, int)){
        int low = 0 ; 
        int high = node->num_cells - 1 ; 
        int cmp = -1  ;
        bool found = false;  
        while ( low <= high ){
            int mid = ( low + high )/ 2 ; 
            void * cell = get_cell(node , mid ) ; 
            reg cell_key = get_key_from_cell(cell);
            cmp = function_name(target , cell_key  , data_type  ) ; 
            if (cmp == 0 ){
                found = true ; 
                if (index != NULL){
                    *index = mid ; 
                }
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

    void agg_operation( aggregate *ans  , reg *num ,  char *  operation ){
        if (strcmp(operation , "SUM") == 0 ){
            if (num->type == integer_num ) {
            ans->total =  ans->total + num->val.i ; 
            ans->type = integer_num ; 
            }
            else if (num->type == real_num  ){
            ans->total =  ans->total + num->val.r ;         
            ans->type = real_num ;
            }
            else {
                return  ; 
            }
        }
        else if (strcmp(operation , "AVG") == 0){
            if (num->type == integer_num ) {
            ans->total =  ans->total + num->val.i ; 
            ans->type = integer_num ; 
            }
            else if (num->type == real_num  ){
            ans->total =  ans->total + num->val.r ;    
            ans->type = real_num  ; 
            } 
            else {
                return  ; 
            }
            ans->count = ans->count + 1 ; 
        }
        else if (strcmp(operation , "COUNT") == 0 ){
            ans->count = ans->count + 1 ; 
        }
        else if (strcmp(operation , "MIN") == 0  ){
        if (ans->have_value == false ){
                if (num->type == integer_num){
                    ans->min.val.i = num->val.i ; 
                    ans->have_value = true ; 
                    ans->type = integer_num ; 
                }
                else if (num->type == real_num){
                    ans->min.val.r = num->val.r ; 
                    ans->have_value = true ; 
                    ans->type = real_num ; 
                }
                else {
                    return  ; 
                }
        } 
        else {
                if (num->type == integer_num){
                    ans->type = integer_num ; 
                    if (num->val.i < ans->min.val.i ){
                        ans->min.val.i = num->val.i ; 
                    }
                }
                else if (num->type == real_num){
                    ans->type = real_num ; 
                    if (num->val.r < ans->min.val.r ){
                        ans->min.val.r = num->val.r ; 
                    }
                }
                else {
                    return  ; 
                }
        }
        }

        else if (strcmp(operation , "MAX") == 0  ){
        if (ans->have_value == false ){
                if (num->type == integer_num){
                    ans->max.val.i = num->val.i ; 
                    ans->have_value = true ; 
                    ans->type = integer_num ; 
                }
                else if (num->type == real_num){
                    ans->max.val.r = num->val.r ; 
                    ans->have_value = true ; 
                    ans->type = real_num ; 
                }
                else {
                    return  ; 
                }
        } 
        else {
                if (num->type == integer_num){
                    ans->type = integer_num ; 
                    if (num->val.i > ans->max.val.i ){
                        ans->max.val.i = num->val.i ; 
                    }
                }
                else if (num->type == real_num){
                    ans->type = real_num ; 
                    if (num->val.r > ans->max.val.r ){
                        ans->max.val.r = num->val.r ; 
                    }
                }
                else {
                    return  ; 
                }
        }
        }

        else if (strcmp(operation , "GROUP_CONCAT") == 0 ){
            if (num->type  != string_num ){
                return  ; 
            }
            ans->type = string_num ; 
            if ( ans->concat_string == NULL ){
                ans->concat_string = malloc(num->lenght) ; 
                ans->string_len = num->lenght ; 
                memcpy(&ans->concat_string  ,num->val.s  , num->lenght  ) ; 
            }
            else  {
                ans->concat_string = realloc(ans->concat_string  , ans->string_len + num->lenght ) ; 
                strcat(ans->concat_string , num->val.s ) ; 
            }

        }
        return ; 
    }

    void agg_final(aggregate *ans  , reg *num ,  char *  operation ){
            if (strcmp(operation , "SUM") == 0 ){
                if (ans->type == integer_num ) {
                    num->type = integer_num ; 
                    num->val.i = ans->total ; 
                }
                else if (ans->type == real_num  ){
                    num->type = real_num ; 
                    num->val.r = ans->total ;  
                }
                }

            else if (strcmp(operation , "AVG") == 0 ){
                num->type = real_num ; 
                num->val.r = ans->total/ans->count ; 
            }
            
            else if (strcmp(operation , "COUNT") == 0 ){
                num->val.i = ans->count ; 
            }
            else if (strcmp(operation , "MIN") == 0 ){
                if (ans->min.type == integer_num){
                    num->val.i = ans->min.val.i ; 
                }
                else if (ans->min.type == real_num){
                    num->val.r = ans->min.val.r ; 
                }
            }
            else if (strcmp(operation , "MAX") == 0 ){
                if (ans->max.type == integer_num){
                    num->val.i = ans->max.val.i ; 
                }
                else if (ans->max.type == real_num){
                    num->val.r = ans->max.val.r ; 
                }
            }
            else if (strcmp(operation , "GROUP_CONCAT") == 0 ){
                num->lenght = ans->string_len ; 
                num->val.s = ans->concat_string  ;    
            }
            return ; 
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
                
                    
                case open_write_op : 
                    byt->btr[op->p1].Table  = lookup_table(db , op->p2) ; 
                    byt->btr[op->p1].start_root_num  =  op->p2 ;
                    byt->btr[op->p1].page_num  =  op->p2 ;
                    byt->btr[op->p1].mode  = cursor_write ; 
                    end = false ; 
                    break ; 
                
                case close_cursor_op : 
                    if (byt->btr[op->p1] ==  NULL){
                        free(byt->btr[op->p1]) ; 
                        byt->btr[op->p1] =  NULL
                    }
                    break ; 
                
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
                        int id = hdr->num_cells ; 
                        for ( int i = 0 ; i < hdr->num_cells ; i++  ){
                            void *cell = get_cell(hdr, i);
                            reg cell_key = get_key_from_cell(cell);
                            if (campare(byt->regis[op->p3], cell_key, cur->data_type) == 0) {
                                id = i;
                                break;
                            }
                        }
                        children = get_child_pointer(byt->pager , children  ,id )  ; 
                        hdr = (page_header*)pager_get_page(byte->pager,children  ) ; 
                        size = size + hdr->num_cells ; 
                        byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , id } ; 
                    }

                    int tot = byt->btr[op->p1].total - 1  ; 
                    int ans_id = -1 ; 
                    int found = 0 ; 
                    while ( size < tot  ){
                        if(bs(hdr ,byt->regis[op->p3]  , byt->btr[op->p1].data_type ,&ans_id ,  campare_ge ) == 1 ){
                            byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , ans_id } ; 
                            byt->btr[op->p1].page_num = children ; 
                            byt->btr[op->p1].row_num = ans_id ; 
                            found = 1 ; 
                            break ; 
                        }

                        int kept = 0 ; 
                        while ( byt->btr[op->p1].depth > 0 ){
                            path_entry * ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                            page_header * hdr = pager_get_page(byt->pager , ptr->page_num) ; 
                            if (ptr->cell_index + 1 < hdr->num_cells ){
                                    ptr->cell_index++ ; 
                                    children = get_child_pointer(byt->pager , ptr->page_num ,ptr->cell_index ) ; 
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
                                    size = size + chdr->num_cells ; 
                                    hdr = chdr ; 
                                    break ; 
                            }
                            byt->btr[op->p1].depth-- ; 
                        }
                        if (kept == 0 ){
                            byt->pc = op->p2;
                            break ; 
                        }
                    }

                    if (!found && size >= tot) {
                        byt->pc = op->p2;
                    }

                    break;
            


                case seek_le : 
                    int size = 0 ; 
                    byt->btr[op->p1].depth = 0 ; 
                    uint32_t children = byt->btr[op->p1].start_root_num   ; 
                    page_header *hdr = pager_get_page(byt->pager , children) ; 
                    byt->btr[op->p1].stack[byt->btr[op->p1].depth] = (path_entry){children  , 0 } ; 
                    while ( hdr->page_type != LEAF ){
                        int id = hdr->num_cells ; 
                        for ( int i = 0 ; i < hdr->num_cells ; i++  ){
                            void *cell = get_cell(hdr, i);
                            reg cell_key = get_key_from_cell(cell);
                            if (campare(byt->regis[op->p3], cell_key, cur->data_type) == 0) {
                                id = i;
                                break;
                            }
                        }
                        children = get_child_pointer(byt->pager , children  ,id )  ; 
                        hdr = (page_header*)pager_get_page(byte->pager,children  ) ; 
                        size = size + hdr->num_cells ; 
                        byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , id } ; 
                    }

                    int tot = byt->btr[op->p1].total - 1  ; 
                    int ans_id = -1 ; 
                    int found = 0 ; 
                    while ( size < tot  ){
                        if(bs(hdr ,byt->regis[op->p3]  , byt->btr[op->p1].data_type ,&ans_id ,  campare_le   ) == 1 ){
                            byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , ans_id } ; 
                            byt->btr[op->p1].page_num = children ; 
                            byt->btr[op->p1].row_num = ans_id ; 
                            found = 1 ; 
                            break ; 
                        }

                        int kept = 0 ; 
                        while ( byt->btr[op->p1].depth > 0 ){
                            path_entry * ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                            page_header * hdr = pager_get_page(byt->pager , ptr->page_num) ; 
                            if (ptr->cell_index + 1 < hdr->num_cells ){
                                    ptr->cell_index++ ; 
                                    children = get_child_pointer(byt->pager , ptr->page_num ,ptr->cell_index ) ; 
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
                                    size = size + chdr->num_cells ; 
                                    hdr = chdr ; 
                                    break ; 
                            }
                            byt->btr[op->p1].depth-- ; 
                        }
                        if (kept == 0 ){
                            byt->pc = op->p2;
                            break ; 
                        }
                    }

                    if (!found && size >= tot) {
                        byt->pc = op->p2;
                    }

                    break;
            
    
                case seek_lt : 
                    int size = 0 ; 
                    byt->btr[op->p1].depth = 0 ; 
                    uint32_t children = byt->btr[op->p1].start_root_num   ; 
                    page_header *hdr = pager_get_page(byt->pager , children) ; 
                    byt->btr[op->p1].stack[byt->btr[op->p1].depth] = (path_entry){children  , 0 } ; 
                    while ( hdr->page_type != LEAF ){
                        int id = hdr->num_cells ; 
                        for ( int i = 0 ; i < hdr->num_cells ; i++  ){
                            void *cell = get_cell(hdr, i);
                            reg cell_key = get_key_from_cell(cell);
                            if (campare(byt->regis[op->p3], cell_key, cur->data_type) == 0) {
                                id = i;
                                break;
                            }
                        }
                        children = get_child_pointer(byt->pager , children  ,id )  ; 
                        hdr = (page_header*)pager_get_page(byte->pager,children  ) ; 
                        size = size + hdr->num_cells ; 
                        byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , id } ; 
                    }

                    int tot = byt->btr[op->p1].total - 1  ; 
                    int ans_id = -1 ; 
                    int found = 0 ; 
                    while ( size < tot  ){
                        if(bs(hdr ,byt->regis[op->p3]  , byt->btr[op->p1].data_type ,&ans_id ,  campare_lt   ) == 1 ){
                            byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , ans_id } ; 
                            byt->btr[op->p1].page_num = children ; 
                            byt->btr[op->p1].row_num = ans_id ; 
                            found = 1 ; 
                            break ; 
                        }

                        int kept = 0 ; 
                        while ( byt->btr[op->p1].depth > 0 ){
                            path_entry * ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                            page_header * hdr = pager_get_page(byt->pager , ptr->page_num) ; 
                            if (ptr->cell_index + 1 < hdr->num_cells ){
                                    ptr->cell_index++ ; 
                                    children = get_child_pointer(byt->pager , ptr->page_num ,ptr->cell_index ) ; 
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
                                    size = size + chdr->num_cells ; 
                                    hdr = chdr ; 
                                    break ; 
                            }
                            byt->btr[op->p1].depth-- ; 
                        }
                        if (kept == 0 ){
                            byt->pc = op->p2;
                            break ; 
                        }
                    }

                    if (!found && size >= tot) {
                        byt->pc = op->p2;
                    }

                    break;
            

                case seek_gt : 
                    int size = 0 ; 
                    byt->btr[op->p1].depth = 0 ; 
                    uint32_t children = byt->btr[op->p1].start_root_num   ; 
                    page_header *hdr = pager_get_page(byt->pager , children) ; 
                    byt->btr[op->p1].stack[byt->btr[op->p1].depth] = (path_entry){children  , 0 } ; 
                    while ( hdr->page_type != LEAF ){
                        int id = hdr->num_cells ; 
                        for ( int i = 0 ; i < hdr->num_cells ; i++  ){
                            void *cell = get_cell(hdr, i);
                            reg cell_key = get_key_from_cell(cell);
                            if (campare(byt->regis[op->p3], cell_key, cur->data_type) == 0) {
                                id = i;
                                break;
                            }
                        }
                        children = get_child_pointer(byt->pager , children  ,id )  ; 
                        hdr = (page_header*)pager_get_page(byte->pager,children  ) ; 
                        size = size + hdr->num_cells ; 
                        byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , id } ; 
                    }

                    int tot = byt->btr[op->p1].total - 1  ; 
                    int ans_id = -1 ; 
                    int found = 0 ; 
                    while ( size < tot  ){
                        if(bs(hdr ,byt->regis[op->p3]  , byt->btr[op->p1].data_type ,&ans_id ,  campare_gt   ) == 1 ){
                            byt->btr[op->p1].stack[byt->btr[op->p1].depth++] = (path_entry){children , ans_id } ; 
                            byt->btr[op->p1].page_num = children ; 
                            byt->btr[op->p1].row_num = ans_id ; 
                            found = 1 ; 
                            break ; 
                        }

                        int kept = 0 ; 
                        while ( byt->btr[op->p1].depth > 0 ){
                            path_entry * ptr = &byt->btr[op->p1].stack[byt->btr[op->p1].depth - 1 ] ; 
                            page_header * hdr = pager_get_page(byt->pager , ptr->page_num) ; 
                            if (ptr->cell_index + 1 < hdr->num_cells ){
                                    ptr->cell_index++ ; 
                                    children = get_child_pointer(byt->pager , ptr->page_num ,ptr->cell_index ) ; 
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
                                    size = size + chdr->num_cells ; 
                                    hdr = chdr ; 
                                    break ; 
                            }
                            byt->btr[op->p1].depth-- ; 
                        }
                        if (kept == 0 ){
                            byt->pc = op->p2;
                            break ; 
                        }
                    }

                    if (!found && size >= tot) {
                        byt->pc = op->p2;
                    }

                    break;

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

                case is_null : 
                    if (byt->regis[op->p1].type == null_op ){
                        byt->pc = op->p2;
                    }
                    break ; 

                case is_not_null : 
                    if (byt->regis[op->p1].type != null_op ){
                        byt->pc = op->p2;
                    }
                    break ; 

                case and_op : 
                    if (byt->regis[op->p1].type != string_op && byt->regis[op->p2].type != string_op  ){
                        byt->regis[op->p3].type = integer_num ; 
                        if (byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == integer_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.i  && byt->regis[op->p2].val.i  ; 
                        }
                        else if (byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == real_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.r && byt->regis[op->p2].val.r ; 
                        }
                        else if (byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == real_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.i  && byt->regis[op->p2].val.r ; 
                        }
                        else if (byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == integer_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.r  && byt->regis[op->p2].val.i  ; 
                        }
                    }
                    break ; 
                
                case or_op : 
                    if (byt->regis[op->p1].type != string_op && byt->regis[op->p2].type != string_op  ){
                        byt->regis[op->p3].type = integer_num ; 
                        if (byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == integer_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.i  || byt->regis[op->p2].val.i  ; 
                        }
                        else if (byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == real_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.r || byt->regis[op->p2].val.r ; 
                        }
                        else if (byt->regis[op->p1].type == integer_num && byt->regis[op->p2].type == real_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.i  || byt->regis[op->p2].val.r ; 
                        }
                        else if (byt->regis[op->p1].type == real_num && byt->regis[op->p2].type == integer_num   ){
                            byt->regis[op->p3].val.i =  byt->regis[op->p1].val.r  ||  byt->regis[op->p2].val.i  ; 
                        }
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

                case aggregate_init : 
                    byt->agg[op->p1].total = 0 ; 
                    byt->agg[op->p1].have_value = false ; 
                    byt->agg[op->p1].count = 0 ; 
                    byt->agg[op->p1].concat_string = NULL ; 
                    break  ; 

                case aggregate_reset:
                    if (byt->agg[op->p1].concat_string != NULL) {
                        free(byt->agg[op->p1].concat_string);
                    }
                    byt->agg[op->p1].total = 0;
                    byt->agg[op->p1].have_value = false;
                    byt->agg[op->p1].count = 0;
                    byt->agg[op->p1].concat_string = NULL;
                    break;

                    
                case aggregate_step : 
                    char *  operation = *(char*)op->p4 ; 
                    agg_operation(byt->agg[op->p1] , byt->regis[op->p2] , operation )  ; 
                    break ; 
                
                case aggregate_final : 
                    char * operation = *(char*)op->p4  ; 
                    agg_final(byt->agg[op->p1] , byt->regis[op->p3] , operation) ; 
                    break ; 

                case sorter_open : 
                    byt->sort[op->p1].array = NULL ; 
                    byt->sort[op->p1].row_count = 0 ; 
                    byt->sort[op->p1].capacity = 0 ; 
                    byt->sort[op->p1].cols_to_look = op->p2  ; 
                    byt->sort[op->p1].keycols = op->p4  ; 
                    byt->sort[op->p1].cursor = 0 ;  
                    
                case sorter_insert : 
                    if (byt->sort[op->p1].row_count == byt->sort[op->p1].capacity) {
                            if (byt->sort[op->p1].capacity == 0 ){
                                byt->sort[op->p1].capacity  = 4  ; 
                            }
                            else if (byt->sort[op->p1].capacity > 0 ){
                                byt->sort[op->p1].capacity  = byt->sort[op->p1].capacity*2   ; 
                            }
                            byt->sort[op->p1].capacity = byt->sort[op->p1].capacity == 0 ? 4 : byt->sort[op->p1].capacity * 2;  
                            sort_arr **tmp = realloc( byt->sort[op->p1].array, byt->sort[op->p1].capacity * sizeof(*byt->sort[op->p1].array)   );
                            if (tmp == NULL) { 
                                break; 
                            }
                            byt->sort[op->p1].array = tmp;
                        }
                        byt->sort[op->p1].array[byt->sort[op->p1].row_count++ ] = byt->regis[op->p2] ; 
                        break ; 
                    


                    
                case sortersort : 
                    byt->sort[op->p1] ; 
                    qsort_r(byt->sort[op->p1].array  ,byt->sort[op->p1].keycols , sizeof(sort_arr) , campare_sort  , byt->sort[op->p1] ) ; 
                    break ; 


                case sorter_next : 
                    if (byt->sort[op->p1].cursor < byt->sort[op->p1].row_count ){
                        byt->sort[op->p1].cursor++ ; 
                        byt->pc = op->p2; 
                    }
                    break ; 

                
                case sorter_data : 
                    sort_arr *temp =  byt->sort[op->p1].array ; 
                    byt->regis[op->p2].lenght = temp->len[ byt->sort[op->p1].cursor]  ; 
                    byt->regis[op->p2].type =  blob_op ; 
                    byt->regis[op->p2].val.s = temp->array[ byt->sort[op->p1].cursor]  ; 
                    break ; 




                case sorter_campare : 
                    sort_arr *temp =  byt->sort[op->p1].array ; 
                    if ( temp->key_type[byt->sort[op->p1].cursor] == integer_num && byt->regis[op->p3].type == integer_num  ){
                        int comp ; 
                        memcpy(&comp, temp->key[byt->sort[op->p1].cursor] , sizeof(int));
                        int comp = (int)temp->key[byt->sort[op->p1].cursor]  ; 
                        if (comp == byt->regis[op->p3].val.i ){
                            byt->pc = op->p2;
                        }
                    }
                    else if ( temp->key_type[byt->sort[op->p1].cursor]  == real_num && byt->regis[op->p3].type == real_num  ){
                        float comp  ;
                        memcpy(&comp, temp->key[byt->sort[op->p1].cursor], sizeof(float));
                        if (comp == byt->regis[op->p3].val.r ){
                            byt->pc = op->p2;
                        }
                    }

                    else if (byt->regis[op->p3].type == real_num && temp->key_type[byt->sort[op->p1].cursor]  == integer_num   ){
                        float comp  ;
                        memcpy(&comp, temp->key[byt->sort[op->p1].cursor], sizeof(float));
                        if (comp == byt->regis[op->p3].val.r ){
                            byt->pc = op->p2;
                        }
                    }

                    else if (temp->key_type[byt->sort[op->p1].cursor]  == real_num && byt->regis[op->p3].type == integer_num   ){
                        float comp  ;
                        memcpy(&comp, temp->key[byt->sort[op->p1].cursor], sizeof(float));
                        float num  = (float)( byt->regis[op->p3].val.i ) ; 
                        if (comp == byt->regis[op->p3].val.r ){
                            byt->pc = op->p2;
                        }
                    }
                    else if (temp->key_type[byt->sort[op->p1].cursor] == string_num && byt->regis[op->p3].type == string_num ){
                        if (strcmp(temp->key[byt->sort[op->p1].cursor] ,byt->regis[op->p3].val.s ) == 0 ){
                            byt->pc = op->p2;
                        }
                    }
                    break ; 


                case column_op : 
                    if (byt->btr[op->p1].null == true ){
                        break ; 
                    }
                    void * temp = pager_get_page( byt->pager , byt->btr[op->p1].stack[depth].page_num  ) ; 
                    void * cell = get_cell(temp , byt->btr[op->p1].stack[depth].cell_num  ) ; 
                    reg tempo = get_key_from_cell(cell) ; 
                    int pos = 0 ;
                    unsigned char thing = tempo->val.s ; 
                    unsigned char temp = thing[pos] ;  
                    int key = op->p2 ; 
                    reg * ans = byt->regis[op->p3] ; 
                    for ( int i =  0 ; i < key ; i++ ){
                        temp = thing[pos] ; 
                        pos = pos + 1;  
                        if (temp == integer_num){
                            pos = pos + sizeof(long) ; 
                        }
                        else if (temp == real_num){
                            pos = pos + sizeof(float ) ;   
                        }
                        else if (temp == string_num ){
                            uint32_t size ; 
                            memcpy(&size , thing + pos , sizeof(uint32_t)) ; 
                            pos = pos + sizeof(uint32_t) ; 
                            pos = pos + size ; 
                        }
                    }

                    int len = 0  ; 
                    pos = pos + 1 ; 
                    if (temp == integer_num){
                        len =  sizeof(long) ; 
                        ans->type = integer_num ; 
                    }
                    else if (temp == real_num){
                        len =  sizeof(float ) ; 
                        ans->type =  real_num ; 
                    }
                    else if (temp == string_num ){
                        uint32_t size ; 
                        memcpy(&size , thing + pos , sizeof(uint32_t)) ; 
                        len =  sizeof(uint32_t) ; 
                        len = len + size ; 
                        ans->type = string_num ; 
                    }

                    unsigned char * valli = malloc(len ) ; 
                    memcpy(valli , thing + pos   , len ) ; 
                    if (ans->type == integer_num ){
                        ans->val.i = (int)valli ;  
                    }
                    else if (ans->type == real_num ){
                        ans->val.r = (float)valli ;     
                    }
                    else {
                        ans->val.s = valli ; 
                        ans->lenght = len ; 
                    }
                    byt->btr[op->p1].null == false ; 
                    break ; 
                    
                    
                case make_record : 
                   byt->reg[op->p3].type = string_num ; 
                   byt->reg[op->p3].val.s = make_record_data(byt , op->p1 , op->p1 + op->p2 ) ; 
                   byt->reg[op->p3].lenght = strlen(byt->reg[op->p3].val.s) ; 
                   break ; 
                
                case result_row : 
                    byt->reg_start = op->p1 ; 
                    byt->reg_end = byt->reg_start  + op->p2 ; 
                    byt->reg_mode = end_num ; 
              
                case limit_op : 
                    if (byt->reg[op->p1].val.i > 0 ){
                        byt->reg[op->p1].val.i-- ; 
                        if (byt->reg[op->p1].val.i == 0  ){
                            byt->pc = op->p2;
                            continue ; 
                        }
                    } break ; 

                case null_join_op : 
                    byt->btr[op->p1].null = true ; 
                    break ; 
           
                }
            }
            
    }




    int like_campare(reg *a , reg *b ){
        int ans = 0 ; 
        if (a->type == string_num && b->type == string_num ){
            int first = 0 ; 
            int second = 0 ; 
            while ( first < a->len && second < b->len ){
                if (strcmp(a->val.s[first] , b->val.s[second] ) == 0 ){
                    first++ ; 
                    second++ ; 
                }
                else if (strcmp(a->val.s[first] , '%' ) == 0 ){
                    
                }
                else if ( strcmp(a->val.s[first] , "_" ) == 0 ){
                    int first_temp = first ;  
                }
            }
        }
    }





}

void process_query(){
	for ( int i = 0 ; i < edit.query_lines ; i++ ){
		char *data = edit.ri[i].data ; 
		if ( data == NULL){
			continue ; 
		}
			int valid = 0 ; 
			int i = 0 ; 

			for (  i = 0 ; data[i] != NULL ; i++  ){
				if ( (isalnum(data[i]) || seperator(data[i]) != NULL) && data[i] !='\0'   ){
					valid = 1 ; 
					break ; 
				}
				else { 
					i++ ; 
				}
			}
			if ( valid == 0 ){
				continue ; 
			}

		if ( data[0] == '.'){
			meta_commnds(line) ;
		}
		int spread_sheet = 0 ; 
		for ( int i = 1 ; line[i] != '\0' ; i++ ){
			if ( isdigit(line[i]) == 0 && isalpha(line[i-1])  ){
				spread_sheet = 1 ; 
			}
		}
		if ( spread_sheet == 1 ){
            assign(line) ; 
		}
		else { 
			sql_queries() ; 
		}
	}
}





void process_raw_key_press(){
    static int  quit_times = quit ; 
	int word  = raw_key_press() ; 
	switch (word) {
		case '\r' : 
		insert_new_lines() ; 	
		break ; 
		case ctrl('f') : 
			finder() ; 
			break ; 
	  case ctrl('q') : 
	    if ( edit.changes > 0 && quit_times > 0  ){
			status_msg_input("The file is changed and not saved press %d times for still quitting without saving " , quit_times ) ; 
			quit_times-- ; 
			return  ; 
		}
 		write(STDOUT_FILENO , "\x1b[2J" , 4 ) ; 
	       write(STDOUT_FILENO , "\x1b[H" , 3 ) ; 
	       exit(0)  ; 
              break ; 
		case ctrl('e'): 
		if ( edit.ri[edit.cursor_rows].query == true ){
			for ( int i = edit.cursor_rows + 1 ; i < edit.row_length ; i++ ){
				edit.ri[i].query = false ; 
			}
			edit.query_lines = edit.cursor_rows + 1 ; 
			 edit.cursor_rows = edit.cursor_rows + 1  ;
			 edit.cursor_cols = 0 ; 
			status_msg_input("The query is under execution") ; 
			 if (proper_data.query != NULL) {
				free(proper_data.query);   
				proper_data.query = NULL;
			}
			if (proper_data.data != NULL) {
				free(proper_data.data);     
				proper_data.data = NULL;
			}
			proper_data.query = tokenizer() ; 	
			proper_data.data = data_tokenizer() ; 
			process_query() ; 
		}
		else { 
			edit.cursor_rows = 0 ; 
		}
			break ; 
	  case ctrl('w'): 
		saving() ; 
		break ; 
	  case Page_up : 
	  case Page_down :
             if ( word == Page_up ) { 
			if ( edit.row_offset - edit.rows > 0 ) { 
				edit.cursor_rows = edit.row_offset - edit.rows  ; 
			   } 
			else { 
				edit.cursor_rows = 0 ; 
			}
		   } 
		  if (word == Page_down ) { 
			if ( edit.row_offset + edit.rows < edit.row_length ){ 
				edit.cursor_rows = edit.row_offset + edit.rows ; 
		   } 
			else { 
			   edit.cursor_rows = edit.row_length - edit.rows ; 
		 } 
	    	} 
		 
 		int times  = edit.rows ; 


		while(times > 0 ) { 
		  if ( word == Page_up) { 
			cursor_change(Arrow_up) ; 
			times-- ; 
		}
		else if ( word == Page_down) { 
			cursor_change(Arrow_down) ; 
			times-- ; 
		}
	}
	break ; 



	  case End_key : 
		if ( edit.cursor_rows < edit.row_offset + edit.rows ) { 
			edit.cursor_cols = edit.ri[edit.cursor_rows].size ; 
		  } 
			break ; 

	  case Home_key : 
		edit.cursor_cols = 0  ; 
		break ; 

      case Backspace:
      case ctrl('h'):
      case delete:
	      if (word == delete){
			 cursor_change(Arrow_right) ; 
		  }
		  del() ; 
        break;

	  case Arrow_up : 
	  case Arrow_down : 
	  case Arrow_left : 
	  case Arrow_right : 
		 cursor_change(word) ; 
		break ; 
	  case ctrl('l'):
      case '\x1b':
         break;
	  default:
         insert(word);
         break;
	}
	quit_times = quit ;  

} 







void scroll_offset(){
	edit.render_cols = 0 ; 
            
	if ( edit.cursor_rows < edit.rows + edit.row_offset && edit.cursor_rows < edit.row_length ) { 
      edit.render_cols = position_as_per_cursor( &edit.ri[edit.cursor_rows] )  ; 
	} 
		
     if ( edit.cursor_rows <  edit.row_offset) { 
            edit.row_offset  = edit.cursor_rows ; 
      }
      if ( edit.cursor_rows >= edit.row_offset + edit.rows ) { 
		edit.row_offset = edit.cursor_rows - edit.rows + 1 ; 
       } 
      if ( edit.render_cols < edit.col_offset) { 
		edit.col_offset = edit.render_cols ; 
	} 
	if ( edit.render_cols >= edit.cols + edit.col_offset ) { 
		edit.col_offset = edit.render_cols - edit.cols + 1  ; 
	} 
} 



void status_msg(struct dynamic_buffer *temp ) { 
	dynamic_buffer_append(temp, "\x1b[7m" , 4) ; 
	int msglen = 0 ;
	msglen = strlen(edit.status_messege) ; 
	if ( msglen > edit.cols){
		msglen = edit.cols ; 
	}
	int k = 0 ; 
	if (msglen > 0 &&  time(NULL) - edit.messege_time  < 5 ){ 
		dynamic_buffer_append(temp, edit.status_messege , msglen) ; 
		k = 1 ; 
	} 
	int tes = 0  ; 
	if ( k == 1 ) tes = msglen ; 
	for (int i = tes ; i < edit.cols ; i++ ){ 
		dynamic_buffer_append(temp, " " , 1) ; 
	}
	dynamic_buffer_append(temp, "\x1b[m" , 3) ; 
}



void status_line(struct dynamic_buffer *temp ) { 
	dynamic_buffer_append(temp, "\x1b[7m" , 4) ; 
	int len = 0 ; 
	 char file[80] ; 
	char position[80] ; 
	int pos_len = 0 ; 
	len = snprintf( file , sizeof(file)  , "%s - %d - %d - %s " , edit.filename ? edit.filename: "no name" , edit.cursor_rows , edit.cursor_cols  , edit.changes ? "org" : "modified")  ; 
	pos_len = snprintf( position , sizeof(position) , "%d-%d" , edit.cursor_rows + 1  , edit.row_length ) ; 
      if(len > edit.cols) { 
		len = edit.cols ; 	
	} 
	if ( len <= edit.cols ) { 
	dynamic_buffer_append(temp, file , len) ; 
	} 
	int space  = edit.cols - pos_len  - len  ; 
	if ( space < 0 ){ 
		space = 0 ; 
	}
	for (int i = 0 ; i < space  ; i++) { 	
			dynamic_buffer_append(temp ," "  ,  1 ) ; 
		}  
	dynamic_buffer_append(temp, position , pos_len) ; 

	

	dynamic_buffer_append(temp, "\x1b[m" , 3) ; 		

} 






void txt_print(struct dynamic_buffer *temp  ){ 
	char welcome[100] ; 
      for(int i = 0 ; i < edit.rows ; i++){
		 int correct_row = i + edit.row_offset ; 
        if ( correct_row >= edit.row_length) {
		if ( first == 0 ) { 
		if ( i == edit.rows / 2 ) {
            int  welcome_len = snprintf(welcome , sizeof(welcome) , "PALX excel %s", version ) ; 
		if (welcome_len > edit.cols){
			welcome_len = edit.cols ; 
		}
		int extra =  (edit.cols - welcome_len ) /2 ; 
		if (extra) { 
			 dynamic_buffer_append(temp, "~" , 1) ; 
			extra-- ; 
		} 
		while(extra > 0 ) { 
		   dynamic_buffer_append(temp, " " , 1 ) ; 
		   extra-- ; 
		} 
		dynamic_buffer_append(temp, welcome  , welcome_len ) ; 
		}
          else { 
		    dynamic_buffer_append(temp, "~" , 1) ; 
		} 
		}
		else {  
              dynamic_buffer_append(temp, "~" , 1) ; 
			} 
		} 
	else { 
		int temp_len = edit.ri[correct_row].render_size - edit.col_offset ; 
		if (temp_len < 0) { 
			temp_len = 0 ; 
		} 
		if (temp_len > edit.cols) { 
			temp_len = edit.cols ; 
		} 
		if ( edit.ri[correct_row].query == true ){
			dynamic_buffer_append(temp, "\x1b[7m" , 4) ;  
		}
		if ( temp_len > 0 && edit.ri[correct_row].render != NULL && edit.ri[correct_row].hl != NULL ){
			char *row = &edit.ri[correct_row].render[edit.col_offset] ; 
			unsigned char *hl = &edit.ri[correct_row].hl[edit.col_offset]  ; 
				if ( highlight == 1 && correct_row == edit.query_lines ){
			dynamic_buffer_append(temp, "\x1b[7;96m" , 7) ;  
			dynamic_buffer_append(temp, row , temp_len) ; 
		}
		else { 
			int prev_color = -1 ; 
			for ( int j = 0 ; j < temp_len ; j++ ){ 
			if (hl[j] == hl_normal) {
			if ( prev_color != -1 ){ 
				dynamic_buffer_append(temp, "\x1b[39m" , 5) ; 
				prev_color = -1 ; 
			} 
				dynamic_buffer_append(temp, &row[j] , 1) ; 
			}
			else { 
			int col = decide_color(hl[j]) ; 
			if ( prev_color != col ){
				char buf[100] ;  
				int len = snprintf(buf , sizeof(buf) , "\x1b[%dm" , col) ; 
				dynamic_buffer_append(temp, buf , len) ; 
				prev_color = col ; 
			}
				dynamic_buffer_append(temp, &row[j] , 1) ;					
			}				
			
		}
	} 
		}
		dynamic_buffer_append(temp, "\x1b[m" , 3) ;
	}
	dynamic_buffer_append(temp, "\x1b[K" , 3) ; 
	dynamic_buffer_append(temp, "\r\n", 2) ;
	}
}



void screen_ready(){
        scroll_offset() ; 
        struct  dynamic_buffer temp = dynamic_buffer_starter ; 
	dynamic_buffer_append(&temp, "\x1b[?25l" , 6 ) ; 
	dynamic_buffer_append(&temp, "\x1b[H" , 3) ; 
	txt_print( &temp ) ; 
	status_line(&temp) ; 
	status_msg(&temp) ; 
        char buf[32] ; 
	snprintf(buf , sizeof(buf) , "\x1b[%d;%dH" , (edit.cursor_rows - edit.row_offset )+ 1  ,(edit.render_cols - edit.col_offset )+ 1  ) ; 
       	dynamic_buffer_append(&temp, buf , strlen(buf) ) ; 
	dynamic_buffer_append(&temp, "\x1b[?25h" , 6 ) ; 
        write(STDOUT_FILENO , temp.data , temp.size)  ; 
	free_dynamic_buffer(&temp) ; 
} 


int cursor_position(int *rows, int *cols) {
     char  temp[32];
     unsigned int i  =   0;
     if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4){
        return -1;
     } 

     while (i < sizeof(temp) - 1) {
         if (read(STDIN_FILENO, &temp[i], 1) != 1) break;
   	 if (temp[i] == 'R') break;
   	 i++;
     }

     temp[i] = '\0';
     if (temp[0] != '\x1b' || temp[1] != '[' ) {
        return -1 ; 
      } 
     if(sscanf(&temp[2]  , "%d;%d" , rows , cols ) !=2 ) {
          return -1 ; 
      } 
     return 0;                         
}
	

int get_window_size(int *rows , int *columns){ 
	struct winsize ws ; 
	if(ioctl(STDOUT_FILENO , TIOCGWINSZ , & ws ) == -1 || ws.ws_col  == 0  || ws.ws_row == 0 ) {
		if (write(STDOUT_FILENO , "\x1b[999C\x1b[999B" , 12) != 12){ 
			return -1 ; 
		} 
   		return  cursor_position (rows , columns ) ; 

	}
	else { 
		*columns = ws.ws_col ; 
		*rows = ws.ws_row ; 
       	return 0 ; 
	}
	
} 

void starter(){
      edit.cursor_rows = 0 ; 
      edit.cursor_cols = 0 ;
	edit.row_length = 0 ; 
    edit.ri = calloc(1, sizeof(row_input)) ;  
      edit.row_offset = 0 ; 
	  edit.changes = 0  ; 
	  edit.comment_start = -1 ; 
	edit.col_offset = 0 ; 
	edit.query_lines = 0 ; 
	proper_data.data = NULL ; 
	proper_data.query = NULL ; 

      if(get_window_size(&edit.rows , &edit.cols) == -1 ) { 
		die("get_window_size") ; 
	} 
	edit.status_messege[0] = '\0' ; 
	edit.messege_time = 0 ; 
	edit.rows  = edit.rows - 2  ; 
	edit.ri[0].query = true ; 
    edit.query_lines = 1 ;
	edit.filename = NULL ; 
	    edit.row_length = 1 ; 
}


int main(int argc , char *argv[] ){
    rawmode() ; 
    starter() ;
    if (argc >= 2 ){ 
	 text_in_input_buffer(argv[1]) ; 
	 	proper_data.data = data_tokenizer() ; 
	excel_like() ; 
	} 
	status_msg_input( "ctrl + w for saving the file | ctrl + q for quitting | ctrl + f for finding words ") ; 
    while(1) {
     screen_ready() ; 
    process_raw_key_press() ; 
    }
    return 0 ; 
} 

